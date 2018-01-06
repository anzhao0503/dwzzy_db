#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <libconfig.h++>
#include <string>

#define MAX_ATTRIBUTION_NUM 100 // max numbers of attributin in a table
#define MAX_TABLE_NUM 100 //max numbers of table in a database

#define CONFIG_NAME_DATABASE "DDB"
#define BASE_DATABASE_PATH "./database/" //database path
#define METADATA_CONFIG_FILE "data.cfg" //config file name


#define CONFIG_NAME_VERSION "version"

#define CONFIG_NAME_TABLE_LIST "table_name_list"
#define CONFIG_NAME_TALBE_ATTR_NUM "attr_num"
#define CONFIG_NAME_TABLE_ATTR_NAME "attr_name"
#define CONFIG_NAME_TABLE_ATTR_DATATYPE "attr_datatype"
#define CONFIG_NAME_TABLE_ATTR_LENGTH "attr_length"
#define CONFIG_NAME_TABLE_ATTR_RULESTYPE "attr_rulestype"
#define CONFIG_NAME_TABLE_ATTR_SLICE "ATTR"

typedef enum _RulesType
{
    PRIMARY_KEY = 0,
    NOT_NULL,
    FOREIGN_KEY,
    RULES_NULL

}RulesType;
#endif // GLOBAL_H
