#ifndef METADATAMANAGER_H
#define METADATAMANAGER_H

#include "../include/global.h"
#include "../include/tableMetadataInfo.h"


#include <libconfig.h++>


class MetadataManager
{
public:

    void read_config_file(const std::string &filename);
    void initialize_from_config_file(const std::string& str);
    void write_to_config_file(std::string filename);//write the new data into meatadata.cfg

    void initialize_tablemetadata();
    void initialize_database();


    void add_tablename_intolist(std::string str);
    void delete_tablename_formlist(std::string str);
    void load_tablemetadata_fromcfg();


    void set_tablemetadata(TableMedata &Tbm);
    TableMedata get_tablemetadata(std::string str){return tableMetadataInfo.get_tablemetadata_bystr(str);}
    void delete_tablemetadata(std::string str);

    void setMetadataVer(std::string str);//set the version of DDB
    std::string get_metadata_version(){return version;}//get the version info
    //Interface for ohter user///////////////////////////////////////////////////////

    static MetadataManager* getInstance();
private:
    MetadataManager();
   ~MetadataManager();
    MetadataManager(const MetadataManager&);
    MetadataManager& operator=(const MetadataManager&);
    static MetadataManager* pmtr;

    class GarbageCollection //use for garbage collection, embedded class
    {
    public:
        ~GarbageCollection()
        {
            if(MetadataManager::getInstance())
                delete MetadataManager::pmtr;
        }
    };
    static GarbageCollection GC;

  
    TableMetadataInfo tableMetadataInfo;
  
    //database info
    std::string database_name;
    std::string version;
    std::string database_path;

    libconfig::Config cfg;


};

#endif // METADATAMANAGER_H
