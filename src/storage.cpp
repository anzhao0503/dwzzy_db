/*
 * storage.cpp
 *
 *  Created on: Oct 15, 2017
 *      Author: wcw
 */
#include "../include/storage.h"

BufferTableItem::BufferTableItem(int index):   index(index), virtual_addr(-1), in_buffer(false), is_written(false), U(false), M(false) {}
BufferTableItem::BufferTableItem(): index(-1), virtual_addr(-1), in_buffer(false), is_written(false), U(false), M(false) {}

BlockTableItem::BlockTableItem(int index):   index(index), virtual_addr(-1), in_buffer(false), is_written(false), U(false), M(false) {}
BlockTableItem::BlockTableItem(): index(-1), virtual_addr(-1), in_buffer(false), is_written(false), U(false), M(false) {}

StorageManagement::StorageManagement() {
	this->last_used = 0;
	this->last_used_block = 0;
	this->InitBufferTable();
	this->InitBlockTable();
	this->segment_table = SegmentTable();
	this->fd = (int*)malloc(sizeof(int)*MAX_TABLE_NUM);
}

StorageManagement::~StorageManagement() {
	this->FlushBuffer();
	for (int i = 0; i < (sizeof(this->fd) / sizeof(this->fd[0])); i++) {
		close(this->fd[i]);
	}
	//cout<<"end "<<endl;
}
/*
 * initial storage, pass file_path
 */
int StorageManagement::InitStorage(vector<char*> path){

	for (int i = 0; i < path.size(); i++) {
		if((access(path[i], 0))!=0) {
			this->fd[i] = open(path[i],O_CREAT|O_EXCL|O_RDWR,0777);
		}
		else {
			this->fd[i] = open(path[i],O_APPEND|O_RDWR,0777);
		}
		if (this->fd[i]!=-1) {
			//cout<<"Disk space initializing is done"<<endl;
			this->segment_table.Add_Seg();
		} else {
			cout<<"Opening file meets error"<<endl;
			return -1;
		}
	}
	return -1;
}

void StorageManagement::InitBufferTable() {
	for (int i = 0; i < BUFFER_SIZE; i ++) {
		this->buffer_table[i] = BufferTableItem(i);
	}
}

void StorageManagement::InitBlockTable() {
	for (int i = 0; i < N_BLOCK; i ++) {
		this->block_table[i] = BlockTableItem(i);
	}
}

int StorageManagement::HitBuffer(ADDR virtual_addr) {
	int index= -1;
	int i = 0;
	while (i < BUFFER_SIZE && buffer_table[i].in_buffer == true) {
		if (buffer_table[i].virtual_addr == virtual_addr) {
			return i;
		}
		i++;
	}
	return index;
}

int StorageManagement::HitBlock(ADDR virtual_addr) {
	int index= -1;
	int i = 0;
	while (i < N_BLOCK && block_table[i].in_buffer == true) {
		if (block_table[i].virtual_addr == virtual_addr) {
			return i;
		}
		i++;
	}
	return index;
}

/*
 * Replacement Algorithm: Not Recently Used(NRU or Advanced Clock)
 */
BufferTableItem* StorageManagement::NRU(BufferTableItem* buffer_table) {
	/*
	 * if there is free space ,return the free space address
	 */
	for (int i = 0; i < BUFFER_SIZE; i ++) {
		if (buffer_table[i].in_buffer == false) {
			this->last_used = i;
			//cout<<i<<endl;
			return &buffer_table[i];
		}
	}
	int i = this->last_used + 1;
	while (true) {
		int num = 0;
		int index = i % BUFFER_SIZE;
		// Round 1
		while (num < BUFFER_SIZE+1) {
			if (buffer_table[index].M == false && buffer_table[index].U == false) {
				// Neither be used nor be modified
				this->last_used = index;
				return &buffer_table[index];
			}
			i++;
			num++;
			index = i % BUFFER_SIZE;
		}
		num = 0;
		// Round 2
		while (num < BUFFER_SIZE+1) {
			if ( buffer_table[index].U == false && buffer_table[index].M == true) {
				// be modified but not be used
				if (buffer_table[index].is_written == true) {
					// write blocks swaped out to disk

					this->WritePage(buffer_table[index].virtual_addr, buffer[index].frame_content, PAGE_SIZE);
					//cout<<"swap out index "<<index<<endl;
					//cout<<"swap out virtual addr "<<buffer_table[index].virtual_addr<<endl;
					//cout<<"buffer write back: "<<buffer[index].frame_content<<endl;
				}
				buffer_table[index].in_buffer = false;
				this->last_used = index;
				return &buffer_table[index];
			}
			buffer_table[index].U = false;
			i++;
			num++;
			index = i % BUFFER_SIZE;
		}
		// Repeat Round 1, if necessary, repeat Round 2
	}
}

BlockTableItem* StorageManagement::NRU(BlockTableItem* block_table, BufferTableItem* buffer_table) {
	/*
	 * if there is free space ,return the free space address
	 */

	for (int i = 0; i < N_BLOCK; i ++) {
		if (block_table[i].in_buffer == false) {
			this->last_used_block = i;
			this->last_used = i * N_BLOCK;
			//cout<<i<<endl;
			return &block_table[i];
		}
	}
	int i = this->last_used_block + 1;

	while (true) {
		int num = 0;
		int index = i % N_BLOCK;
		// Round 1
		while (num < N_BLOCK+1) {
			if (block_table[index].M == false && block_table[index].U == false) {
				// Neither be used nor be modified
				this->last_used_block = index;
				this->last_used = index * BLOCK_SIZE;
				return &block_table[index];
			}
			i++;
			num++;
			index = i % N_BLOCK;
		}
		num = 0;
		// Round 2
		while (num < N_BLOCK+1) {
			if ( block_table[index].U == false && block_table[index].M == true) {
				// be modified but not be used
				if (block_table[index].is_written == true) {
					// write blocks swaped out to disk
					for (int j = 0; j < BLOCK_SIZE; j++) {
//						cout << index*BLOCK_SIZE+j << " " << buffer_table[index*BLOCK_SIZE+j].virtual_addr << " " << buffer[index*BLOCK_SIZE+j].frame_content << endl;
						this->WritePage(buffer_table[index*BLOCK_SIZE+j].virtual_addr, buffer[index*BLOCK_SIZE+j].frame_content, PAGE_SIZE);
						buffer_table[index*BLOCK_SIZE+j].in_buffer = false;
					}
//					cout<<"swap out index "<<index<<endl;
					//cout<<"swap out virtual addr "<<buffer_table[index].virtual_addr<<endl;
					//cout<<"buffer write back: "<<buffer[index].frame_content<<endl;
				}
				block_table[index].in_buffer = false;
				this->last_used_block = index;
				this->last_used = index * BLOCK_SIZE;
				return &block_table[index];
			}
			block_table[index].U = false;
			for (int j = 0; j < BLOCK_SIZE; j++) {
				buffer_table[index*BLOCK_SIZE+j].U = false;
			}
			i++;
			num++;
			index = i % N_BLOCK;
		}
		// Repeat Round 1, if necessary, repeat Round 2
	}
}

/*
 * read frame contents from buffer
 */
int StorageManagement::ReadBuffer(ADDR virtual_addr, void *buf, unsigned int length) {
	int index = this->HitBuffer(virtual_addr);
	BufferTableItem* item = NULL;
	if (index < 0) {
		/*
		 * if the address not exists in the buffer, change the BufferTable of the item to swap out
		 */
		item = this->NRU(this->buffer_table);
		unsigned int swap_index = item->index;
		/*
		 * swap in the page. update the buffer and change the BufferTable item
		 * load page using virtual address
		 */
		unsigned char* ret = this->LoadPage(virtual_addr, length);
		if (ret == NULL) {
			cout << "Content does not exist in file" << endl;
			return 0;
		}
		item->virtual_addr = virtual_addr;
		item->in_buffer = true;
		item->U = true;
		item->M = true;
		buffer[swap_index].frame_content = ret;
		return this->ReadBuffer(virtual_addr, buf, length);
	}
	else {
		//hit
		memcpy(buf, buffer[index].frame_content, length);
		this->buffer_table[index].U = true;
		return length;
	}
}

int StorageManagement::ReadBlock(ADDR virtual_addr, char* buf[], unsigned int length) {
//	cout << virtual_addr << endl;
	int block_id = this->GetBlockId(virtual_addr);
	virtual_addr = block_id * PAGE_SIZE * BLOCK_SIZE;

	int index = this->HitBlock(virtual_addr);
	BlockTableItem* item = NULL;
	if (index < 0) {
		/*
		 * if the address not exists in the buffer, change the BufferTable of the item to swap out
		 */
		item = this->NRU(this->block_table, this->buffer_table);
		unsigned int swap_index = item->index;

		/*
		 * swap in the page. update the buffer and change the BufferTable item
		 * load page using virtual address
		 */
		for (int i = 0; i < BLOCK_SIZE; i++) {
			ADDR page_addr = virtual_addr + i * PAGE_SIZE;
			unsigned char* ret = this->LoadPage(page_addr, PAGE_SIZE);
			// if (ret == NULL) {
			// 	cout << "Content does not exist in file" << endl;
			// 	return 0;
			// }
			buffer[swap_index*BLOCK_SIZE+i].frame_content = ret;
			buffer_table[swap_index*BLOCK_SIZE+i].virtual_addr = page_addr;
			buffer_table[swap_index*BLOCK_SIZE+i].in_buffer = true;
			buffer_table[swap_index*BLOCK_SIZE+i].U = true;
			buffer_table[swap_index*BLOCK_SIZE+i].M = true;
		}
		item->virtual_addr = virtual_addr;
		item->in_buffer = true;
		item->U = true;
		item->M = true;
		return this->ReadBlock(virtual_addr, buf, length);
	}
	else {
		//hit
		for (int i = 0; i < BLOCK_SIZE; i++) {
			if ((char*)buffer[index*BLOCK_SIZE+i].frame_content == NULL){

			}
			else {
				memcpy(buf[i], (char*)buffer[index*BLOCK_SIZE+i].frame_content, PAGE_SIZE);
			}
			this->buffer_table[index*BLOCK_SIZE+i].U = true;
		}
		this->block_table[index].U = true;
		return length;
	}
}

/*
 * write frame to buffer and change the BufferTable
 */
int StorageManagement::WriteBlock(ADDR virtual_addr, void *buf, unsigned int length) {

	int block_id = this->GetBlockId(virtual_addr);

	ADDR block_addr = block_id * BLOCK_SIZE * PAGE_SIZE;

	int index = this->HitBlock(block_addr);

	if (index < 0) {
		block_id = block_id % N_BLOCK;
	} else {
		block_id = index;
	}
	BlockTableItem* item = NULL;
	int buffer_id = block_id * BLOCK_SIZE + (virtual_addr - block_addr) / PAGE_SIZE;

	if (index < 0) {
		/*
		 * if the address not exists in the buffer, change the BufferTable of the item to swap out
		 */
		item = this->NRU(this->block_table, this->buffer_table);
		item->virtual_addr = block_addr;
		item->in_buffer = true;
		buffer_id = item->index * BLOCK_SIZE + (virtual_addr - block_addr) / PAGE_SIZE;
		buffer_table[buffer_id].virtual_addr = virtual_addr;

		return this->WriteBuffer(virtual_addr, buf, length);
	}
	else {
		/*
		 * if the address exists in the buffer, change the buffer with new frame content
		 */
//		cout << block_id << " " << buffer_id << " " << virtual_addr << endl;
		memcpy(buffer[buffer_id].frame_content, buf, length);
		/*
		 * change items in BufferTable
		*/
		this->buffer_table[buffer_id].is_written = true;
		this->buffer_table[buffer_id].in_buffer = true;
		this->buffer_table[buffer_id].U = true;
		this->buffer_table[buffer_id].M = true;
		this->buffer_table[buffer_id].virtual_addr = virtual_addr;


		this->block_table[block_id].is_written = true;
		this->block_table[block_id].in_buffer = true;
		this->block_table[block_id].U = true;
		this->block_table[block_id].M = true;
		return length;
	}
}

int StorageManagement::WriteBuffer(ADDR virtual_addr, void *buf, unsigned int length) {
	int index = this->HitBuffer(virtual_addr);
//	cout << virtual_addr << endl;
	BufferTableItem* item = NULL;
	if (index < 0) {
		/*
		 * if the address not exists in the buffer, change the BufferTable of the item to swap out
		 */
		item = this->NRU(this->buffer_table);
		item->virtual_addr = virtual_addr;
		item->in_buffer = true;
		return this->WriteBuffer(virtual_addr, buf, length);
	}
	else {
		/*
		 * if the address exists in the buffer, change the buffer with new frame content
		 */
		memcpy(buffer[index].frame_content, buf, length);
		/*
		 * change items in BufferTable
		 */
		this->buffer_table[index].is_written = true;
		this->buffer_table[index].in_buffer = true;
		this->buffer_table[index].U = true;
		this->buffer_table[index].M = true;
		return length;
	}
}
/*
 * write *buf to buffer
 */
int StorageManagement::Write(int tb_id, void *buf, unsigned int length){
	/*
	 * Allocate pages;
	 */
	ADDR seg_id = tb_id;
	Segment* seg = this->segment_table.seg_table[seg_id];
	ADDR current_addr = seg->addr_space->GetCurrentAddr();
	int npages = length/PAGE_SIZE;
	ADDR tmp_new_page_id;
	if (npages == 0) {
		if (this->GetOffset(seg->addr_space->GetCurrentAddr()) == 0) {
			tmp_new_page_id = seg->AllocPage();
			seg->page_table[tmp_new_page_id]->start_addr = seg->addr_space->GetCurrentAddr();
			seg->page_table[tmp_new_page_id]->is_used = true;
			memcpy(seg->page_table[tmp_new_page_id]->content, buf, length);
			seg->page_table[tmp_new_page_id]->is_used = true;
		}
		else {
			memcpy(seg->page_table[this->GetPageId(current_addr)]->content+this->GetOffset(seg->addr_space->GetCurrentAddr()), buf, length);
			seg->page_table[this->GetPageId(current_addr)]->is_used = true;
		}
		this->WriteBuffer(seg->page_table[this->GetPageId(current_addr)]->start_addr, seg->page_table[this->GetPageId(current_addr)]->content, PAGE_SIZE);
//		cout << seg->page_table[this->GetPageId(current_addr)]->content+this->GetOffset(seg->addr_space->GetCurrentAddr()) << endl;
		seg->addr_space->ADDRIncrease(length);
//		cout << "write page " << current_addr << " " << (char*)seg->page_table[this->GetPageId(current_addr)]->content << endl;
		return 1;
	}
	for(int i = 0; i < npages; i++){
		if (this->GetOffset(seg->addr_space->GetCurrentAddr()) == 0) {
			tmp_new_page_id = seg->AllocPage();
			seg->page_table[tmp_new_page_id]->start_addr = seg->addr_space->GetCurrentAddr();
			memcpy(seg->page_table[tmp_new_page_id]->content, buf+i*PAGE_SIZE, length);
			seg->page_table[tmp_new_page_id]->is_used = true;
		}
		else {
			memcpy(seg->page_table[this->GetPageId(current_addr)]->content+this->GetOffset(seg->addr_space->GetCurrentAddr()), buf+i*PAGE_SIZE, length);
			seg->page_table[this->GetPageId(current_addr)]->is_used = true;
		}

		this->WriteBuffer(seg->page_table[this->GetPageId(current_addr)]->start_addr, seg->page_table[this->GetPageId(current_addr)]->content, PAGE_SIZE);
		seg->addr_space->ADDRIncrease(length);
//		cout << current_addr << " " << (char*)buf << endl;
	}

	return 1;
}
/*
 * flush all frames int buffer to disk
 */

void StorageManagement::FlushBuffer() {
	for (int i = 0; i < BUFFER_SIZE; i++) {
		if (this->buffer_table[i].is_written == true) {
//			for (int j = strlen((char*)buffer[i].frame_content); j < PAGE_SIZE; j++)
//				buffer[i].frame_content[j] = '*';
//			buffer[i].frame_content[PAGE_SIZE] = '\0';
			this->WritePage(buffer_table[i].virtual_addr, buffer[i].frame_content, PAGE_SIZE);
			this->block_table[i / BLOCK_SIZE] = BlockTableItem(i / BLOCK_SIZE);
			this->buffer_table[i] = BufferTableItem(i);
		}
	}
}


void StorageManagement::FlushBlock() {
	for (int i = 0; i < N_BLOCK; i++) {
		if (this->block_table[i].is_written == true) {
//			for (int j = strlen((char*)buffer[i].frame_content); j < PAGE_SIZE; j++)
//				buffer[i].frame_content[j] = '*';
//			buffer[i].frame_content[PAGE_SIZE] = '\0';

			for (int j = 0; j < BLOCK_SIZE; j++) {
//				cout << buffer[i*BLOCK_SIZE+j].frame_content << endl;
				this->WritePage(buffer_table[i*BLOCK_SIZE+j].virtual_addr, buffer[i*BLOCK_SIZE+j].frame_content, PAGE_SIZE);
				this->block_table[i] = BlockTableItem(i);
				this->buffer_table[i*BLOCK_SIZE+j] = BufferTableItem(i*BLOCK_SIZE+j);
			}

		}
	}
}

/*
 * seg-page related functions
 */
ADDR StorageManagement::GetSegId(ADDR virtual_addr){
	ADDR seg_id;
	seg_id = (virtual_addr >> (PAGE_BIT + OFFSET_BIT)) & SEG_MASK;
	return seg_id;
}
ADDR StorageManagement::GetPageId(ADDR virtual_addr){
	ADDR page_id;
	page_id = (virtual_addr >> OFFSET_BIT) & PAGE_MASK;
	return page_id;
}
ADDR StorageManagement::GetOffset(ADDR virtual_addr){
	ADDR offset;
	offset = virtual_addr & OFFSET_MASK;
	return offset;
}
int StorageManagement::GetBlockId(ADDR virtual_addr) {
	ADDR block_id;
	block_id = virtual_addr / (BLOCK_SIZE * PAGE_SIZE);
	return block_id;
}
ADDR StorageManagement::GetBlockOffset(ADDR virtual_addr) {
	ADDR offset;
	offset = virtual_addr % (BLOCK_SIZE * PAGE_SIZE);
	return offset;
}

/*
 * Given fd and frame.id, read frame content from file
 * to be continued:
 * 	See if it's possible to pass a *buff instead of writing into frame_content
 */
void* Frame::GetFrameContent(int fd){
	off_t offset = this->frame_id * PAGE_SIZE;
	if (this->is_modified == false){
//		printf("ERROR: Invalid Frame! %u\n ",this->frame_id);
		return NULL;
	}
	if(lseek(fd,offset,SEEK_SET) != -1){
		read(fd,this->frame_content,PAGE_SIZE);
		return this->frame_content;
	}
	return NULL; //lseek failed.
}

/*
* Nth tuple is used;
*/
int Frame::SetTuple(int n){
	unsigned int tmp = this->free_tuples;
	if((n<0)||(n>=8)){
		cout<<"invalid tuple number!";
		return -1;
	}
	this->free_tuples = tmp | (1<<(n & TUPLE_MASK));
	return 0;
}
int Frame::FreeTuple(int n){
	unsigned int tmp = this->free_tuples;
	if((n<0)||(n>=8)){
		cout<<"invalid tuple number!";
		return -1;
	}
	this->free_tuples = tmp & (~(1<<(n & TUPLE_MASK)));
	return 0;
}
/*
 * test if n tuple is used
 * 1 : used
 * 0 : unused
 */
int Frame::TestTuple(int n){
	unsigned int tmp = this->free_tuples;
	return (tmp | (1<<(n & TUPLE_MASK)));
}

int Page::SetTuple(int n){
	unsigned int tmp = this->free_tuples;
	if((n<0)||(n>=8)){
		cout<<"invalid tuple number!";
		return -1;
	}
	this->free_tuples = tmp | (1<<(n & TUPLE_MASK));
	return 0;
}
int Page::FreeTuple(int n){
	unsigned int tmp = this->free_tuples;
	if((n<0)||(n>=8)){
		cout<<"invalid tuple number!";
		return -1;
	}
	this->free_tuples = tmp & (~(1<<(n & TUPLE_MASK)));
	return 0;
}
int Page::TestTuple(int n){
	unsigned int tmp = this->free_tuples;
	cout << "free_tuples " << this->free_tuples << "addr " << &this->free_tuples<< endl;
	return (tmp >> n) & 1;
//	return (tmp & (1<<(n & TUPLE_MASK)) >>(n & TUPLE_MASK));
}

ADDR FrameTable::AllocFrame(){
	unsigned int count = this->count;
	if(count < MAX_FRAME_COUNT){
		Frame* new_frame = new Frame(count,true,true);
		frame_table.insert((vector<Frame*>::iterator)frame_table.begin()+count, new_frame);
		this->CountInc();
		return new_frame->frame_id;
	}
	else{
		ADDR frame_id = this->GetFromFreeSpace();
		return frame_id;
	}
}
vector<ADDR> FrameTable::AllocFrames(unsigned int nframes){
	unsigned int i = 0;
	vector<ADDR> addr;
	for(i = 0;i<nframes;i++){
		addr.push_back(this->AllocFrame());
	}
	return addr;
}
/*
 * Free Space Management
 */
void FrameTable::CollectFreeSpace(){
	for(vector<Frame*>::const_iterator iter = this->frame_table.begin(); iter != this->frame_table.end();iter++){
		if(!(*iter)->is_used){
			ADDR tmp = (*iter)->frame_id;
			this->free_frame_list.push(tmp);
		}
	}
}
void Frame::ResetFrame(){
	this->free_tuples = 0;
	this->is_modified = false;
	this->is_used = false;
	this->ntuples = 0;
}
ADDR FrameTable::GetFromFreeSpace(){
	if(this->free_frame_list.size()==0){
		cout << "There is no space left.";
		return -1;
	}
	ADDR free_frame_id = this->free_frame_list.top();
	this->free_frame_list.pop();
	this->frame_table[free_frame_id]->ResetFrame();
	return free_frame_id;
}

/*
 * Free Page Management
 */
void Segment::CollectFreePage(){
	for(vector<Page*>::const_iterator iter = this->page_table.begin();iter!=this->page_table.end();iter++){
		if(!(*iter)->is_used){
			ADDR tmp = (*iter)->page_id;
			this->free_pages.push(tmp);
		}
	}
}
ADDR Segment::GetFreePage(){
	if(this->free_pages.size()==0){
		cout << "EROR: Invalid Page Address.";
		return -1;
	}
	ADDR new_page_id  = this->free_pages.top();
	this->free_pages.pop();
	this->page_table[new_page_id]->ResetPage();
	return new_page_id;
}
void Page::ResetPage(){
	this->is_modified = false;
	this->is_used = false;
	this->ntuples = 0;
	this->free_tuples=0;
}
/*
 * write frame content into file related offset
 * not write into frame.content
 */
int Frame::FlushFrame(const void *buf, int fd){
	off_t offset = (this->frame_id & PAGE_MASK) * PAGE_SIZE;
	if(lseek(fd,offset,SEEK_SET) != -1){
		// write(fd,buf,PAGE_SIZE);
		return 0;
	}
	return -1;
}

/*
 * add a page in a given seg
 * return page_id
 */
ADDR Segment::AllocPage(){
	/*
	 * insert a new page into page_table
	 */
	Page* new_page = new Page(this->count,true,true);
	this->page_table.insert((vector<Page*>::iterator)page_table.begin()+this->count, new_page);
	this->CountInc();
	return new_page->page_id;
}
vector<ADDR> Segment::AllocPages(unsigned int npages){
	vector<ADDR> addr;
	for(unsigned int i = 0; i < npages; i++){
		addr.push_back(this->AllocPage());
	}
	return addr;
}
/*
 * given virtual_addr, load page content into buf
 * first, parse it into seg_id,page_id
 * get seg start_id and addr_map in segment table.
 * find frame_id in addr_map.
 */
unsigned char* StorageManagement::LoadPage(ADDR virtual_addr, int length){
	unsigned char* buf = (unsigned char*)calloc(sizeof(unsigned char)*length, sizeof(unsigned char));

	ADDR seg_id = this->GetSegId(virtual_addr);
	Segment* seg = this->segment_table.seg_table[seg_id];
//	ADDR start_id = this->segment_table.seg_table[seg_id]->start;
	map<ADDR,ADDR> addr_map = this->segment_table.seg_table[seg_id]->addr_map;
	map<ADDR, ADDR>::iterator it = addr_map.begin();
//	cout << "map" << endl;
//	for(; it != addr_map.end(); ++it)
//		cout << it->first << endl;
	ADDR page_id = this->GetPageId(virtual_addr);
	/*
	 * look up map to get frame_id
	 */
	map<ADDR,ADDR>::iterator iter;
	iter = addr_map.find(page_id);
	if(iter != addr_map.end())
	{
		Frame* frame = seg->frame_table->frame_table[iter->second];

		if((unsigned char*)frame->GetFrameContent(this->fd[seg_id]) != NULL){
			memcpy(buf, frame->GetFrameContent(this->fd[seg_id]), PAGE_SIZE);
			return buf;
		}
		else {
//			memcpy(buf, "***", BLOCK_SIZE*PAGE_SIZE);
//			return buf;
			return NULL;
		}

	}
//	printf("ERROR:cannot find page %u in map!",page_id);
	return NULL;
}


/*
 * Basically, the virtual_addr is assigned by Class AddressSpace,
 *
 * write *buf to file, size of buf no more than one page
 */
int StorageManagement::WritePage(ADDR virtual_addr,const void *buf, unsigned int length){
	if(length > PAGE_SIZE){
		printf("ERROR: Write more than one page!");
		return -1;
	}
	ADDR seg_id = this->GetSegId(virtual_addr);
	Segment* seg = this->segment_table.seg_table[seg_id];
//	ADDR start_id = this->segment_table.seg_table[seg_id]->start;
	map<ADDR,ADDR> addr_map = this->segment_table.seg_table[seg_id]->addr_map;
	ADDR page_id = this->GetPageId(virtual_addr);
//	cout << "page: " << page_id << endl;
	map<ADDR,ADDR>::iterator iter;
	iter = addr_map.find(page_id);
	/*
	 *the address already have been mapped,
	 *which means the page has contents
	 *invalid old page, and assign new pages
	 */
	if(iter != addr_map.end()){
		Frame* frame = seg->frame_table->frame_table[iter->second];
		frame->is_modified = false;
		Page* page = this->segment_table.seg_table[seg_id]->page_table[page_id];
		page->is_modified = false;
	}
	/*
	 * allocate new page
	 */
	ADDR new_page = this->GetPageId(virtual_addr);
	ADDR new_frame = seg->frame_table->AllocFrame();
	this->segment_table.seg_table[seg_id]->addr_map.insert(map<ADDR,ADDR>::value_type (new_page,new_frame));
	int ret = seg->frame_table->frame_table[new_frame]->FlushFrame(buf, this->fd[seg_id]);
	return ret;
}




