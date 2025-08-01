#include <crow.h>
#include <sqlite3.h>


struct Data{
    std::string passed_key;
    bool found=false;

};

static int callback(void* data, int argc, char** argv, char** azColName){
    auto* cb_data=static_cast<Data*>(data);
    for (int i = 0; i < argc; i++) {
        std::string key=argv[i];
        if(key == cb_data->passed_key){
            cb_data->found=true;
            return 1;
        }
    }
    return 0;
    
}
    

bool api_verify(std::string passed_key){
    sqlite3* db;
    int exit=sqlite3_open("db.sqlite",&db);
    if(exit!=SQLITE_OK){
        std::cout<<"Error While Opening The DataBase!";
    }
    std::string query="SELECT api_key FROM api_keys ;";

    Data cb_data;
    cb_data.passed_key=passed_key;

    exit=sqlite3_exec(db,query.c_str(),callback,&cb_data,nullptr);

    if(exit!=SQLITE_OK){
        std::cout<<"Error WHile Runnig Query!";
    }

    sqlite3_close(db);
    return cb_data.found;
}

