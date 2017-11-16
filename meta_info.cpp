/*
 * meta_info.cpp
 *
 *  Created on: Nov 15, 2017
 *      Author: anzhao
 */
# include "meta_info.h"

MetaInfo::MetaInfo() {
	db_meta = new DBMeta();
}

MetaInfo::~MetaInfo() {
	delete db_meta;
}
