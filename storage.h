#include<iostream>
#include<cstring>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include<stack>

using namespace std;

#define BUFFER_SIZE 16
#define PAGE_SIZE 1024*4
#define SEG_SIZE 1024*1024*8
#define SEG_BIT 10
#define PAGE_BIT 8

# define ADDR unsigned long

class Frame {
public:
	unsigned int frame_id;
	bool is_valid;
	unsigned char  frame_content[PAGE_SIZE];

	Frame();
};
class Page {
public:
	unsigned int page_id;
	Frame frame;

	Page();
};

class Segment {
public:
	unsigned int seg_id;
	Page* page_table;
	stack<unsigned int> free_pages;

	Segment();
	int SetFreePage(unsigned int page_id);
	unsigned int GetFreePage();
};

class SegmentTable {
public:
	Segment* segment_table;
};

class BufferTableItem {
public:
	int index; //在Buffer_table中的index
	ADDR page_entry;
	bool in_buffer;
	// 换出时是否需要写回硬盘
	bool is_written;
	// NRU标志位
	bool U;
	bool M;
	BufferTableItem();
	BufferTableItem(int index);
};

class StorageManagement {
private:
	int last_used; //置换策略中上一次访问的位置

	void InitBufferTable();
	int HitBuffer(ADDR page_entry);
	BufferTableItem* NRU(BufferTableItem* buffer_table);

	unsigned int GetAddress(ADDR page_entry);
	unsigned int GetPageId(ADDR page_entry);
	unsigned int GetSegId(ADDR page_entry);
	unsigned int GetOffset(ADDR page_entry);

	int LoadPage(ADDR page_entry, void *buf, unsigned int length);
	int WriteFile(ADDR page_entry, const void *buf, unsigned int length);
public:
	BufferTableItem  buffer_table[BUFFER_SIZE];
	Frame buffer[BUFFER_SIZE];

	StorageManagement();
	~StorageManagement();

	int ReadBuffer(ADDR page_entry, void *buf, unsigned int length);
	int WriteBuffer(ADDR page_entry, const void *buf, unsigned int length);
	void FlushBuffer();
};
