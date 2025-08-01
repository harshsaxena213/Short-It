#include <sqlite3.h>
#include <crow.h>
#include <string>
#include <random>
#include <iostream>


std::string full_url(std::string short_url){
    std::string original_url = "";
    sqlite3 *db;
    int exit=sqlite3_open("db.sqlite",&db);
    if(exit!=SQLITE_OK){
        CROW_LOG_INFO<<"Error While Opening The DataBase";
    }
    const char* query="SELECT * FROM url WHERE shortened_url=?;";
    sqlite3_stmt* final_statement=nullptr;
    exit=sqlite3_prepare_v2(db,query,-1,&final_statement,nullptr);
    if(exit!=SQLITE_OK){
        CROW_LOG_INFO<<"Error While Prasing The SQL!";
    }

    exit=sqlite3_bind_text(final_statement,1,short_url.c_str(),-1,SQLITE_TRANSIENT);
    if(exit!=SQLITE_OK){
        CROW_LOG_INFO<<"Error While Binding The Query!"; 
    }
    exit=sqlite3_step(final_statement);
    if(exit==SQLITE_ROW){
        const unsigned char* text=sqlite3_column_text(final_statement,1);
        if(text){
            original_url=reinterpret_cast<const char*>(text);
        }
        else if(exit==SQLITE_DONE){
            CROW_LOG_INFO<<"No Url To Short";
        }
        else{
            CROW_LOG_INFO<<"Error While Executing Statement";
        }
    }

    sqlite3_finalize(final_statement);
    sqlite3_close(db);
    return original_url;

}

