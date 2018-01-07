  #include "metadatamanager.h"

#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "../include/tableMetadataInfo.h"
#include <unistd.h>
using namespace std;
using namespace libconfig;

MetadataManager* MetadataManager::pmtr = NULL;
MetadataManager::MetadataManager()
{
   
    initialize_from_config_file(METADATA_CONFIG_FILE);//initialize the MetadataManager

    initialize_database();//initialize DDB segment
    load_tablemetadata_fromcfg();
    cout<<"MetadataManager() is starting"<<endl;

}


MetadataManager::~MetadataManager()
{

}

void MetadataManager::read_config_file( const string& filename)
{
    if(-1 == access(filename.c_str(),F_OK))//whether the metadata.cfg exist
    {
        ofstream of;
        of.open(filename.c_str());
        of.close();
        cout<<"file not exist create it"<<endl;
    }
    //try-catch block from libconfig manual
    // Read the file. If there is an error, report it and exit.
    try
    {
      cfg.readFile(filename.c_str());
    }
    catch(const FileIOException &fioex)
    {
      std::cerr << "I/O error while reading file." << std::endl;
      //return(EXIT_FAILURE);
    }
    catch(const ParseException &pex)
    {
      std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                << " - " << pex.getError() << std::endl;
      //return(EXIT_FAILURE);
    }


}

void MetadataManager::initialize_from_config_file(const string &str)
{
    read_config_file(str);//open and read metadata.cfg

    try
    {
        Setting &root = cfg.getRoot();

        if(! root.exists(CONFIG_NAME_VERSION))
          {
            root.add(CONFIG_NAME_VERSION, Setting::TypeString);
            this->version = "";
            cout<<"initialize_from_config_file no version\n";
          }
        else
        {
            string version = cfg.lookup(CONFIG_NAME_VERSION);
            cout << "version: " << version << endl;
            this->version = version;//get version info
        }


    }
    catch(const SettingNotFoundException &nfex)
    {
      cerr << "No 'version' setting in configuration file." << endl;
    }


    try
    {
      string database_path = cfg.lookup("db1.database_path");

      this->database_path = database_path;//get database path info
      cout << "database_path: " << this->database_path << endl;
    }
    catch(const SettingNotFoundException &nfex)
    {
      cerr << "No 'database_path' setting in configuration file." << endl;
    }


    try
    {
      string database_name = cfg.lookup("db1.database");

      this->database_name = database_name;//get database name info
      cout << "database_name: " << this->database_name << endl;
    }
    catch(const SettingNotFoundException &nfex)
    {
      cerr << "No 'database_name' setting in configuration file." << endl;
    }
}

//not to use anymore
void MetadataManager::initialize_tablemetadata()
{


      try
        {
        cfg.setOptions(Config::OptionFsync
                       | Config::OptionSemicolonSeparators
                       | Config::OptionColonAssignmentForGroups
                       | Config::OptionOpenBraceOnSeparateLine);
        Setting &root = cfg.getRoot();

                if(! root.exists(CONFIG_NAME_DATABASE))
                {
                  root.add(CONFIG_NAME_DATABASE, Setting::TypeGroup);
                  cout<<"initialize_tablemetadata no database"<<endl;
                }
          }

        catch(const SettingNotFoundException &nfex)
        {
          //Ignore.
          cout<<"initialize_tablemetadata() error"<<endl;
        }



}


void MetadataManager::set_tablemetadata(TableMedata &Tbm)
{



    string str = Tbm.table_name;
    tableMetadataInfo.set_table_metadata(Tbm);

    add_tablename_intolist(str);

    Setting& root = cfg.getRoot();
    Setting& ddb_cfg = root[CONFIG_NAME_DATABASE];
    if(ddb_cfg.exists(str.c_str()))
        ddb_cfg.remove(str.c_str());

    ddb_cfg.add(str.c_str(),Setting::TypeGroup);
    Setting& tb_cfg = ddb_cfg[str.c_str()];

    //int pos = tableMetadataInfo.get_tablemetadata_pos_bystr(str);
    //TableMedata tmp =tableMetadataInfo.get_tablemetadata_bypos(pos);
    TableMedata tmp =tableMetadataInfo.get_tablemetadata_bystr(str);
     tb_cfg.add(CONFIG_NAME_TALBE_ATTR_NUM,Setting::TypeInt) = tmp.table_attr_num;

    for(int i = 0; i<tmp.table_attr_num; i++)
    {
        tb_cfg.add(CONFIG_NAME_TABLE_ATTR_SLICE+to_string(i), Setting::TypeGroup);
        Setting& attr_cfg = tb_cfg[CONFIG_NAME_TABLE_ATTR_SLICE+to_string(i)];

        attr_cfg.add(CONFIG_NAME_TABLE_ATTR_NAME, Setting::TypeString) = tmp.Attr[i].attr_name;
        attr_cfg.add(CONFIG_NAME_TABLE_ATTR_DATATYPE,Setting::Setting::TypeInt) \
                = (int)tmp.Attr[i].attr_datatype;
        attr_cfg.add(CONFIG_NAME_TABLE_ATTR_LENGTH,Setting::TypeInt) = tmp.Attr[i].attr_length;
        attr_cfg.add(CONFIG_NAME_TABLE_ATTR_RULESTYPE,Setting::TypeInt) = (int)tmp.Attr[i].attr_rulestype;


    }

    write_to_config_file(METADATA_CONFIG_FILE);

}
void MetadataManager::delete_tablemetadata(string str)
{
    tableMetadataInfo.delete_tablemetadata_inmap(str);

    delete_tablename_formlist(str);

    Setting& root = cfg.getRoot();
    Setting& ddb_cfg = root[CONFIG_NAME_DATABASE];
    if(ddb_cfg.exists(str.c_str()))
    {
        ddb_cfg.remove(str.c_str());
        cout<<"delete_tablemetadata: "<<str<<endl;
        write_to_config_file(METADATA_CONFIG_FILE);
        return;
    }
    cout<<"delete_tablemetadata: "<<str<<" table not exist, no need to delete!"<<endl;
}

int MetadataManager:: GetTableId(string table_name){
    Setting& root = cfg.getRoot();
    Setting& db_cfg = root[CONFIG_NAME_DATABASE];
    Setting& tb_namelist = db_cfg[CONFIG_NAME_TABLE_LIST];
    int len = tb_namelist.getLength();
    for(int i = 0; i<len; i++){
      string tmp_name = tb_namelist[i];
      if(table_name == tmp_name){
        return i;
      }
    }
    cout<<"No Such Table In MetadataManager. Cannot Return TableId Correctly."<<endl;
    return -1;

}
std::string MetadataManager::GetTableName(int table_id){
      Setting& root = cfg.getRoot();
      Setting& db_cfg = root[CONFIG_NAME_DATABASE];
      Setting& tb_namelist = db_cfg[CONFIG_NAME_TABLE_LIST];
      int len = tb_namelist.getLength();
      if(table_id > (len-1)){
        cout<<"No Such Table In MetadataManager. Cannot Return TableName Correctly."<<endl;
        return "";
      }
      return tb_namelist[table_id];
}
void MetadataManager::add_tablename_intolist(string str)
{


    Setting& root = cfg.getRoot();
    Setting& db_cfg = root[CONFIG_NAME_DATABASE];
    Setting& tb_namelist = db_cfg[CONFIG_NAME_TABLE_LIST];
    bool b = true;
    int len = tb_namelist.getLength();
    for(int i=0;i<len;i++)
    {
        string s = tb_namelist[i];
        if(str == s) b = false;
    }

    if(b)
    {

        tb_namelist.add(Setting::TypeString) = str;
        write_to_config_file(METADATA_CONFIG_FILE);
    }

}
void MetadataManager::delete_tablename_formlist(string str)
{

    Setting& root = cfg.getRoot();
    Setting& db_cfg = root[CONFIG_NAME_DATABASE];
    Setting& tbname_list = db_cfg[CONFIG_NAME_TABLE_LIST];

    bool b = false;
    int len = tbname_list.getLength();
    int pos;
    for(int i=0;i<len;i++)
    {
        string s = tbname_list[i];
        if(str == s)
        {
            b = true;
            pos = i;
            break;
        }
    }

    if(b)
    {

        tbname_list.remove((unsigned)pos);
        write_to_config_file(METADATA_CONFIG_FILE);
    }

}

void MetadataManager::load_tablemetadata_fromcfg()
{
    Setting& root = cfg.getRoot();
    Setting& db_cfg = root[CONFIG_NAME_DATABASE];
    Setting& tb_namelist = db_cfg[CONFIG_NAME_TABLE_LIST];
    int len = tb_namelist.getLength();
    if(len == 0) return;//len==0 means no table in GDD

    for(int i=0;i<len;i++)
    {
        TableMedata tmp;
        string tbname = tb_namelist[i];
        Setting& table_cfg = db_cfg[tbname];
        int attr_num;
        table_cfg.lookupValue(CONFIG_NAME_TALBE_ATTR_NUM,attr_num);

        tmp.table_name = tbname;
        tmp.table_attr_num = attr_num;

           for(int j=0;j<attr_num;j++)
           {
               Setting& attr_cfg = table_cfg[CONFIG_NAME_TABLE_ATTR_SLICE+to_string(j)];

               attr_cfg.lookupValue(CONFIG_NAME_TABLE_ATTR_NAME, tmp.Attr[j].attr_name);
               attr_cfg.lookupValue(CONFIG_NAME_TABLE_ATTR_DATATYPE,tmp.Attr[j].attr_datatype);
               attr_cfg.lookupValue(CONFIG_NAME_TABLE_ATTR_LENGTH,tmp.Attr[j].attr_length);
               attr_cfg.lookupValue(CONFIG_NAME_TABLE_ATTR_RULESTYPE,tmp.Attr[j].attr_rulestype);
            }

           tableMetadataInfo.set_table_metadata(tmp);
    }




}

void MetadataManager::setMetadataVer(string str)
{


    cfg.setOptions(Config::OptionFsync
                   | Config::OptionSemicolonSeparators
                   | Config::OptionColonAssignmentForGroups
                   | Config::OptionOpenBraceOnSeparateLine);

    Setting &root = cfg.getRoot();

    if(! root.exists(CONFIG_NAME_VERSION))
    {
      root.add(CONFIG_NAME_VERSION, Setting::TypeString);
      cout<<"setMetadataVer no version\n";
    }

    Setting &version = root[CONFIG_NAME_VERSION];
    version = str;



    // Write out the updated configuration.
    try
    {
      cfg.writeFile(METADATA_CONFIG_FILE);
      cerr << "Updated configuration successfully written to: " << METADATA_CONFIG_FILE
           << endl;

    }
    catch(const FileIOException &fioex)
    {
      cerr << "I/O error while writing file: " << METADATA_CONFIG_FILE << endl;
    }
    string s = cfg.lookup(CONFIG_NAME_VERSION);
    cout << "the update version is: " << s << endl;
    this->version = s;
}

MetadataManager *MetadataManager::getInstance()
{
    if(pmtr == NULL )
        pmtr = new MetadataManager();

    return pmtr;
}

void MetadataManager::initialize_database()
{
    cfg.setOptions(Config::OptionFsync
                   | Config::OptionSemicolonSeparators
                   | Config::OptionColonAssignmentForGroups
                   | Config::OptionOpenBraceOnSeparateLine);

    Setting &root = cfg.getRoot();
    if(! root.exists(CONFIG_NAME_DATABASE))
    {
      root.add(CONFIG_NAME_DATABASE, Setting::TypeGroup);
      Setting& db_cfg = root[CONFIG_NAME_DATABASE];

      db_cfg.add(CONFIG_NAME_TABLE_LIST, Setting::TypeArray);

      write_to_config_file(METADATA_CONFIG_FILE);
      cout<<"initialize_database:"<<CONFIG_NAME_DATABASE<<endl;
    }


    cout << "initialize_siteinfo is ok! "  << endl;


}

void MetadataManager::write_to_config_file(std::string filename)
{
    try
    {
      cfg.writeFile(filename.c_str());
      cerr << "Updated configuration successfully written to: " << filename
           << endl;

    }
    catch(const FileIOException &fioex)
    {
      cerr << "I/O error while writing file: " << filename << endl;
    }
    cout<<"write_to_config file:"<<filename;

}
