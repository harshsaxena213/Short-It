#include <sqlite3.h>
#include <crow.h>
#include <string>
#include <random>
#include <iostream>

std::string shorten(const std::string& full_url) {
    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::srand(static_cast<unsigned int>(std::time(nullptr))); 
    int id = std::rand() % 100 + 1;
    

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

   
    std::string shortened_url;
    for (size_t i = 0; i < 15; ++i) {
        shortened_url += characters[distribution(generator)];
    }

    sqlite3* db;
    int exit = sqlite3_open("db.sqlite", &db);
    if (exit != SQLITE_OK) {
        CROW_LOG_INFO << "Error While Opening The DataBase " << sqlite3_errmsg(db);
    }

    
    const char* query = "INSERT INTO url (id, original_url, shortened_url) VALUES (?, ?, ?);";
    sqlite3_stmt* final_query = nullptr;
    exit = sqlite3_prepare_v2(db, query, -1, &final_query, nullptr);
    if (exit != SQLITE_OK) {
        CROW_LOG_INFO << "Failed To Preapaer: " << sqlite3_errmsg(db);

    }

    
    sqlite3_bind_int(final_query, 1, id);
    sqlite3_bind_text(final_query, 2, full_url.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(final_query, 3, shortened_url.c_str(), -1, SQLITE_TRANSIENT);

    
    exit = sqlite3_step(final_query);
    if (exit != SQLITE_DONE) {
        CROW_LOG_INFO << "Failed to execute statement: " << sqlite3_errmsg(db);
        sqlite3_finalize(final_query);
        sqlite3_close(db);
        return "";
    }

    
    sqlite3_finalize(final_query);
    sqlite3_close(db);

    return shortened_url;
}

