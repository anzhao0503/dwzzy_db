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

#define BUFFER_SIZE		1024 * 256 // page num in buffer(1GB buffer)
//#define BUFFER_SIZE		1024 * 256 // page num in buffer(1GB buffer)
#define PAGE_SIZE		4096 // 512 * 8
#define MAX_SEG_SIZE	256 * 1024 * 4
#define N_BLOCK 32 // number of blocks
#define BLOCK_SIZE 1024 * 256 / 32 // page num per block
/*
 * address space 8M
 * per tuple 512B
 * MAX_TUPLE_SIZE 512 Bytes
 * seg_id | page_id | offset
 * store 4GB data
 */
#define MAX_TUPLE_SIZE 512
#define SEG_BIT 30
#define PAGE_BIT 22
#define OFFSET_BIT 12
#define MAX_FRAME_COUNT 1048576 //2^20
#define OFFSET_MASK 0XFFF
#define PAGE_MASK	0X3FFFFF
#define	SEG_MASK	0X3FFFFFFF
#define TUPLE_MASK  0XFF

#define MAX_TABLE_NUM 30

# define ADDR unsigned long long

class Frame {
public:
	/*
	 * relate to offset in file
	 */
	ADDR frame_id;
	bool is_modified;
	bool is_used;
	unsigned int ntuples;
	unsigned int free_tuples=0xFF;//bit map 8 tuples, 0 unused, 1used
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
		this->free_tuples = 0xFF;
	}
	Frame() {
		this->is_modified=true;
		this->is_used=true;
		this->frame_id = 0;
		this->ntuples = 0;
		this->free_tuples = 0xFF;
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
	int FlushFrame(const void* buf, int fd);
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
	ADDR count;
	/*
	 * assign a free frame, add it to frame_table
	 * return a free frame_id
	 */
	ADDR AllocFrame();
	vector<ADDR> AllocFrames(unsigned int nframes);

	void CountInc(){
		this->count++;
	}
	FrameTable(ADDR seg_id){
//			this->frame_table = new vector<Frame*>;
//			this->free_frame_list  = new vector<ADDR*>;
			this->count = seg_id << PAGE_BIT;
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
	Page(){
		this->page_id = 0;
		this->ntuples = 0;
		this->start_addr = 0;
		this->is_modified = true;
		this->is_used = true;
		this->content=(char*)calloc(sizeof(char)*PAGE_SIZE, sizeof(char));
		this->free_tuples = 0xFF;
	}
	Page(ADDR page_id, bool is_modified,bool is_used){
		this->page_id = page_id;
		this->start_addr = 0;
		this->is_modified = is_modified;
		this->is_used = is_used;
		this->ntuples = 0;
		this->content=(char*)calloc(sizeof(char)*PAGE_SIZE, sizeof(char));
		this->free_tuples = 0xFF;
	}
	// free_tuples 0 for valid 1 for invalid
	int SetTuple(int n); // set tuple 0 to 1
	int FreeTuple(int n); // set tuple 1 to 0
	int TestTuple(int n); // return 0 for valid 1 for invalid

	void ResetPage();
	~Page(){
		free(this->content);
		cout<<"Page free"<<endl;
	}
private:
	unsigned int free_tuples = 0xFF;//bit map 8 tuples in 1 page
};

/*
 * record virtual base address
 */
class AddressSpace{
private:
	ADDR current_seg;
	ADDR current_addr;
public:
	bool IsValid(int length) {
		if ((current_addr + length) >> (PAGE_BIT + OFFSET_BIT) != current_seg) {
			return false;
		}
		return true;
	}
	AddressSpace(ADDR seg_id){
		this->current_addr = seg_id << (PAGE_BIT + OFFSET_BIT);
		this->current_seg = seg_id;
	}
	ADDR GetCurrentAddr(){
		return this->current_addr;
	}
	ADDR GetCurrentSeg(){
		return this->current_seg;
	}
	void ADDRInc(){
		if (IsValid(1))
			this->current_addr++;
	}
	void ADDRIncrease(int length) {
		if (IsValid(length))
			this->current_addr += length;
	}
	void SetBaseAddr(ADDR current_addr){
		this->current_addr = current_addr;
	}
};

class Segment {
public:
	ADDR seg_id;
	ADDR start; //start from which frame id
	ADDR start_addr;
	map<ADDR,ADDR> addr_map; //<page_id,frame_id>
	vector<Page*> page_table;
	unsigned int count;
	stack<ADDR> free_pages;
	FrameTable* frame_table;
	AddressSpace* addr_space;

	Segment(){
		this->frame_table = new FrameTable(0);
		this->seg_id = 0;
		this->start = 0;
		this->count = 0;
		this->start_addr = 0;
		this->addr_space = new AddressSpace(0);
	}
	Segment(ADDR seg_id) {
		this->frame_table = new FrameTable(seg_id);
		this->seg_id = seg_id;
		this->start = seg_id << PAGE_BIT;
		this->start_addr = seg_id << (PAGE_BIT+OFFSET_BIT);
		this->count = 0;
		this->addr_space = new AddressSpace(seg_id);
	}
//	Segment(ADDR seg_id, ADDR start, unsigned int count){
//		this->count = count;
//		this->seg_id = seg_id;
//		this->start = start;
//	}
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
 * organize segments array;
 */
class SegmentTable {
public:
	vector<Segment*> seg_table;
	unsigned int size;
	SegmentTable(){
		this->size = 0;
//		this->seg_table = new vector<Segment*>();
	}
	/*
	 * add one seg
	 */
	void Add_Seg() {
		Segment* seg = new Segment(this->size);
		this->seg_table.push_back(seg);
		this->size++;
	}
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

class BlockTableItem {
public:
	int index; //index in block table
	ADDR virtual_addr;
	bool in_buffer;
	// whether need to write back to disk when swaped out
	bool is_written;
	// flags used in NRU
	bool U;
	bool M;
	BlockTableItem();
	BlockTableItem(int index);
};

class StorageManagement {
private:
	/*
	 * buffer management
	 */
	int last_used; //last page's position of pointer in NRU
	int last_used_block; // last block's position of pointer in NRU
	void InitBufferTable();
	void InitBlockTable();
	int HitBuffer(ADDR virtual_addr);
	int HitBlock(ADDR virtual_addr);
	BufferTableItem* NRU(BufferTableItem* buffer_table);
	BlockTableItem* NRU(BlockTableItem* block_table, BufferTableItem* buffer_table);

	/*
	 * address management
	 */


	/*
	 * parse address
	 */

	ADDR GetSegId(ADDR virtual_addr);
	int GetBlockId(ADDR virtual_addr);
	ADDR GetBlockOffset(ADDR virtual_addr);
	/*
	 * Given address, load & write page
	 */
	unsigned char* LoadPage(ADDR virtual_addr, int length);
	int WritePage(ADDR virtual_addr,const void *buf, unsigned int length);

	int WriteBlock(ADDR virtual_addr, void *buf, unsigned int length);
public:
	int* fd; //for file operations
	BufferTableItem  buffer_table[BUFFER_SIZE];
	BlockTableItem block_table[N_BLOCK];
	Frame buffer[BUFFER_SIZE];
	SegmentTable segment_table; //user define the number of segs, 1 seg by default
	ADDR GetPageId(ADDR virtual_addr);
	ADDR GetOffset(ADDR virtual_addr);
	StorageManagement();
	~StorageManagement();

	char* ReadFile(ADDR addr);
	int InitStorage(vector<char*> path); //flag=0:create new file else:do not need create
	int ReadBuffer(ADDR virtual_addr, void *buf, unsigned int length);
	int ReadBlock(ADDR virtual_addr, char** buf, unsigned int length);
	int WriteBuffer(ADDR virtual_addr, void *buf, unsigned int length);
	int Write(int tb_id, void *buf, unsigned int length);
	void FlushBuffer();
	void FlushBlock();
};
