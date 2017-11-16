#include "table.h"

Table::Table(char* name, int db_id, int index, ADDR seg_id, ADDR start_addr, bool exist, AttrType *types, int *attr_length, int attribute_num) {
	this->db_id = db_id;
	this->start_addr = start_addr;
	this->index = index;
	if (!exist) {
		// not in the disk
		TableMeta new_table_meta = new TableMeta();
		memcpy(new_table_meta.table_name, name, MAX_TABLE_NAME_LENGTH);
		new_table_meta.db_id = db_id;
		new_table_meta.start_addr = start_addr;
		new_table_meta.attribute_num = attribute_num;
		int off = 0;
		for (int i = 0; i < attribute_num; i++) {
			AttributeMeta new_attr_meta = new AttributeMeta();
			new_attr_meta.attribute_index = i;
			new_attr_meta.attribute_type = types[i];
			new_attr_meta.attribute_length = attr_length[i];
			new_attr_meta.attribute_offset = off;
			off += attr_length[i];
			new_table_meta.attr_meta.push_back(new_attr_meta);
		}
		this->table_meta = new_table_meta;
		if (meta_info.db_meta.size() <= db_id) {
			// database not exists
			DBMeta new_db_meta = new DBMeta();
			new_db_meta.seg_id = seg_id;
			new_db_meta.table_num = 1;
			new_db_meta.table_meta.push_back(new_table_meta);
			meta_info.db_meta.insert((vector<DBMeta>::iterator)meta_info.db_meta.begin()+db_id, new_db_meta);
			meta_info.db_meta[db_id].table_num = 1;
		} else {
			meta_info.db_meta[db_id].table_meta.insert((vector<TableMeta>::iterator)meta_info.db_meta[db_id].table_meta.begin()+index, new_table_meta);
			meta_info.db_meta[db_id].table_num++;
		}
	}
	else {
		this->table_meta = meta_info.db_meta[db_id].table_meta[index];
	}
}
