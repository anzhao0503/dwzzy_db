/*
 * storage.h
 *
 *  Created on: Oct 15, 2017
 *      Author: wcw
 */

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <stack>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <map>
#include <vector>

using namespace std;


#define BUFFER_SIZE		1024 * 256 // 1GB buffer (4KB per page)
#define PAGE_SIZE		4096 //512 * 8
#define MAX_SEG_SIZE	256 * 1024 * 4
/*
 * address space 8M
 * per tuple 512B
 * MAX_TUPLE_SIZE 512 Bytes
 * seg_id | page_id | offset
 * store 4GB data
 */
#define MAX_TUPLE_SIZE 512
#define SEG_BIT 4
#define PAGE_BIT 16
#define OFFSET_BIT 12
#define MAX_FRAME_COUNT 1048576 //2^20
#define OFFSET_MASK 0XFFF
#define PAGE_MASK	0XFFFF
#define	SEG_MASK	0XF
#define TUPLE_MASK  0XFF

# define ADDR unsigned long

class Frame {
public:
	/*
	 * relate to offset in file
	 */
	ADDR frame_id;
	bool is_modified;
	bool is_used;
	unsigned int ntuples;
	unsigned int free_tuples;//bit map 8 tuples, 0 unused, 1used
	/*
	 * when load or write page, store content.
	 */
	unsigned char*  frame_content;

	Frame(ADDR id, bool is_modified, bool is_used)
	{
		this->is_modified = is_modified;
		this->frame_id = id;
		this->is_used = is_used;
		this->ntuples = 0;
		this->frame_content = (unsigned char*)calloc(sizeof(unsigned char)*PAGE_SIZE, sizeof(unsigned char));
		this->free_tuples = 0;
	}
	Frame() {
		this->is_modified=true;
		this->is_used=true;
		this->frame_id = 0;
		this->ntuples = 0;
		this->free_tuples = 0;
		this->frame_content = (unsigned char*)calloc(sizeof(unsigned char)*PAGE_SIZE, sizeof(unsigned char));
	}
	/*
	 * get one frame with content,
	 * a.k.a. read from file fd according to frame_id
	 */
	void* GetFrameContent(int fd);
	/*
	 * flush PAGE_SIZE to file fd
	 */
	int FlushFrame(const void* buf,int fd);
	/*
	* set used tuple
	* 0<n<8
	*/
	int SetTuple(int n);
	int FreeTuple(int n);
	int TestTuple(int n);
	void ResetFrame();
};

class FrameTable{
public:
	vector<Frame*> frame_table;
	stack<ADDR> free_frame_list;
	/*
	 * count frames
	 */
	unsigned int count;
	/*
	 * assign a free frame, add it to frame_table
	 * return a free frame_id
	 */
	ADDR AllocFrame();
	vector<ADDR> AllocFrames(unsigned int nframes);

	void CountInc(){
		this->count++;
	}
	FrameTable(){
//			this->frame_table = new vector<Frame*>;
//			this->free_frame_list  = new vector<ADDR*>;
			this->count = 0;
		}
	void CollectFreeSpace();
	ADDR GetFromFreeSpace();
};

class Page {
public:
	ADDR page_id;
	bool is_modified;
	bool is_used;
	unsigned int ntuples;
	char *content;
	ADDR start_addr;
	unsigned int free_tuples;//bit map 8 tuples in 1 page
	Page(){
		this->page_id = 0;
		this->free_tuples = 0;
		this->ntuples = 0;
		this->start_addr = 0;
		this->is_modified = true;
		this->is_used = true;
		this->content=(char*)calloc(sizeof(char)*PAGE_SIZE, sizeof(char));
	}
	Page(ADDR page_id, bool is_modified,bool is_used){
		this->page_id = page_id;
		this->start_addr = 0;
		this->is_modified = is_modified;
		this->is_used = is_used;
		this->free_tuples = 0;
		this->ntuples = 0;
		this->content=(char*)calloc(sizeof(char)*PAGE_SIZE, sizeof(char));
	}
	int SetTuple(int n);
	int FreeTuple(int n);
	int TestTuple(int n);
	void ResetPage();
	~Page(){
		free(this->content);
		cout<<"Page free"<<endl;
	}
};

class Segment {
public:
	ADDR seg_id;
	ADDR start; //start from which frame id
	map<ADDR,ADDR> addr_map; //<page_id,frame_id>
	vector<Page*> page_table;
	unsigned int count;
	stack<ADDR> free_pages;

	Segment(){
		this->seg_id = 0;
		this->start = 0;
		this->count = 0;
	}
	Segment(ADDR seg_id, ADDR start, unsigned int count){
		this->count = count;
		this->seg_id = seg_id;
		this->start = start;
	}
	/*
	 * assign caller a new free page;
	 * call AllocFrame() to get a free frame_id;
	 * insert map<page_id, frame_id>;
	 * return page_id;
	 */
	ADDR AllocPage();
	vector<ADDR> AllocPages(unsigned int npages);
	void CountInc(){
		this->count++;
	}

	void CollectFreePage();
	ADDR GetFreePage();
};

/*
 * record virtual base address
 */
class AddressSpace{
private:
	ADDR current_seg;
	ADDR current_addr;
public:
	AddressSpace(ADDR current_addr){
		this->current_addr = current_addr;
		this->current_seg = current_addr >> 28;
	}
	ADDR GetCurrentAddr(){
		return this->current_addr;
	}
	ADDR GetCurrentSeg(){
		this->current_seg = this->current_addr >> 28;
		return this->current_seg;
	}
	void ADDRInc(){
		this->current_addr++;
	}
	void ADDRIncrease(int length) {
		this->current_addr += length;
	}
	void SetBaseAddr(ADDR current_addr){
		this->current_addr = current_addr;
	}
};
/*
 * organize segments array;
 */
class SegmentTable {
public:
	vector<Segment*> seg_table;
	unsigned int size;
	SegmentTable(){
		this->size = 1;
		Segment* seg = new Segment();
		this->seg_table.push_back(seg);
	}
	SegmentTable(unsigned int size, vector<Segment*> seg_table)
	{
		this->size = size;
		this->seg_table = seg_table;
	}
	/*
	 * add one seg
	 */
	int Add_Seg(Segment seg);
	/*
	 * delete seg
	 */
};

class BufferTableItem {
public:
	int index; //index in buffer table
	ADDR virtual_addr;
	bool in_buffer;
	// whether need to write back to disk when swaped out
	bool is_written;
	// flags used in NRU
	bool U;
	bool M;
	BufferTableItem();
	BufferTableItem(int index);
};

class StorageManagement {
private:
	/*
	 * buffer management
	 */
	int last_used; //last position of pointer in NRU
	void InitBufferTable();
	int HitBuffer(ADDR virtual_addr);
	BufferTableItem* NRU(BufferTableItem* buffer_table);

	/*
	 * address management
	 */
	SegmentTable segment_table; //user define the number of segs, 1 seg by default
	FrameTable frame_table;
	AddressSpace addr_space = AddressSpace(0);

	/*
	 * parse address
	 */

	ADDR GetSegId(ADDR virtual_addr);
	ADDR GetOffset(ADDR virtual_addr);
	/*
	 * Given address, load & write page
	 */
	unsigned char* LoadPage(ADDR virtual_addr, int length);
	int WritePage(ADDR virtual_addr,const void *buf, unsigned int length);

	int WriteBuffer(ADDR virtual_addr, void *buf, unsigned int length);
public:
	int fd; //for file operations
	BufferTableItem  buffer_table[BUFFER_SIZE];
	Frame buffer[BUFFER_SIZE];
	ADDR GetPageId(ADDR virtual_addr);

	StorageManagement();
	~StorageManagement();

	char* ReadFile(ADDR addr);
	void WriteFile(char *buf,unsigned int length, int count);
	int InitStorage(char *path); //flag=0:create new file else:do not need create
	int ReadBuffer(ADDR virtual_addr, void *buf, unsigned int length);
	int Write(void *buf, unsigned int length);
	void FlushBuffer();
};
