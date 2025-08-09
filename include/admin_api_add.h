#include <crow.h>
#include <sqlite3.h>
#include <iostream>
#include <string>
#include <random>


std::string get_current_time() {
    time_t t = std::time(nullptr);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
    return std::string(buf);
}

std::string add_key(std::string username,std::string email_id,std::string description,int id){
    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string created_at = get_current_time();
    CROW_LOG_INFO<<created_at<<"This Is Current Time";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    sqlite3* db;
    int exit=sqlite3_open("db.sqlite",&db);
    if(exit!=SQLITE_OK){
        CROW_LOG_INFO<<"Erro While Opening The Database";
    
    }
       
    std::string api_key;
    for (size_t i = 0; i < 15; ++i) {
        api_key += characters[distribution(generator)];
    }
    int no_of_time = 0;

    CROW_LOG_INFO<<"--------------------------";

    CROW_LOG_INFO<<username;
    CROW_LOG_INFO<<api_key;
    CROW_LOG_INFO<<email_id;
    CROW_LOG_INFO<<no_of_time;
    CROW_LOG_INFO<<description;
    CROW_LOG_INFO<<created_at;
    CROW_LOG_INFO<<"--------------------------";

    const char* query="INSERT INTO admin_api_key (api_key, username, email, no_of_time, description, created_at) VALUES (?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* final_statement=nullptr;
    exit=sqlite3_prepare_v2(db,query,-1,&final_statement,nullptr);
    if(exit!=SQLITE_OK){
        CROW_LOG_INFO<<"Erro While Preparing The Database"<<sqlite3_errmsg(db);
    }
    



    sqlite3_bind_text(final_statement, 1, api_key.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(final_statement, 2, username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(final_statement, 3, email_id.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(final_statement,  4, no_of_time);
    sqlite3_bind_text(final_statement, 5, description.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(final_statement, 6, created_at.c_str(), -1, SQLITE_TRANSIENT);

    exit=sqlite3_step(final_statement);
    if(exit!=SQLITE_OK){
        CROW_LOG_INFO<<"Erro While Executing The Statemetn";
    
    }


    return api_key;
}

