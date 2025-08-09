#include <crow.h>
#include <sqlite3.h>
#include "include/api_verify.h"
#include "include/short.h"
#include "include/full.h"
#include "include/admin_api_verify.h"
#include "include/admin_api_add.h"
#include "include/admin_remove_key.h"


struct api_key:crow::ILocalMiddleware{
    struct context {};
    
    void before_handle(crow::request& req,crow::response& res,context& ctx){
        std::string passed_key=req.get_header_value("user-api-key");
        bool check=api_verify(passed_key);
        CROW_LOG_INFO<<passed_key;
        if(!check){
            res.code=401;
            res.set_header("WWW-Authenticate","API key required");
            res.body="Invalid Api Key";
            res.end();    
        }
    }

    void after_handle(crow::request& req,crow::response& res,context& ctx){}
};

struct api_key_admin:crow::ILocalMiddleware{
    struct context {};
    
    void before_handle(crow::request& req,crow::response& res,context& ctx){
        std::string passed_key=req.get_header_value("admin-api-key");
        CROW_LOG_INFO<<"You Passed Key Is :-->"<<passed_key;
        bool check=admin_api_verify(passed_key);
        if(!check){
            res.code=401;
            res.set_header("WWW-Authenticate","API key required");
            res.body="Invalid Api Key";
            res.end();    
        }
    }

    void after_handle(crow::request& req,crow::response& res,context& ctx){}
};


int main(){
    crow::App<api_key,api_key_admin> app;

    crow::Blueprint bp("api");
    bp.CROW_MIDDLEWARES(app,api_key);

    crow::Blueprint bp_admin("admin");
    bp_admin.CROW_MIDDLEWARES(app,api_key_admin);

    CROW_BP_ROUTE(bp,"/")([](){
        return "Your Api Key Is Valid !";
    });

    CROW_BP_ROUTE(bp,"/short/<string>")([](crow::response& res,std::string url){
        std::string shorted_url=shorten(url);
        std::string final_string = std::string("http://localhost:8080/api/full/") + shorted_url;
        crow::json::wvalue jsonobj;
        jsonobj["Url"]=final_string;
        res.code=200;
        res.write(jsonobj.dump());
        res.end();

    });

    CROW_BP_ROUTE(bp,"/full/<string>")([](crow::response& res,std::string short_url){
        std::string original_url=full_url(short_url);
        crow::json::wvalue jsonobj;
        jsonobj["Url"]=original_url;
        res.code=200;

        res.write(jsonobj.dump());
        res.end();
   
    });

    CROW_BP_ROUTE(bp_admin,"/")([](){
        return "Verified";
    });

    CROW_BP_ROUTE(bp_admin,"/add_api_key/<string>/<string>/<string>/<string>")([](crow::request& req,crow::response& res,std::string username,std::string email_id,std::string description,std::string id){
        CROW_LOG_INFO<<"PAssed";

        CROW_LOG_INFO<<username,email_id,description,id;
        int id_int = std::stoi(id);
        CROW_LOG_INFO<<id<<"Converted";
        std::string api_key_of_user=add_key(username,email_id,description,id_int);
        res.code=200;
        res.write(api_key_of_user);
        res.end();
    });

        CROW_BP_ROUTE(bp_admin,"/remove_api_key/<string>/<string>")([](crow::request& req,crow::response& res,std::string api_key,std::string username){
        bool isDeleted=remove_key(username,api_key);
        if(isDeleted==true){
            res.code=200;
            res.write("Deleted");
            res.end();
        }
        else{
        res.code=200;
        res.write("Wrong Username Or API Key Please Check Again");
        res.end();
        }

    });

    CROW_ROUTE(app,"/")([](){
        return "To Short URL /api/short And To Get Full /api/full";
    });

    app.register_blueprint(bp);
    app.register_blueprint(bp_admin);
    app.port(8081).multithreaded().run();
}   