#include <crow.h>
#include <sqlite3.h>
#include "include/api_verify.h"
#include "include/short.h"
#include "include/full.h"

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


int main(){
    crow::App<api_key> app;

    crow::Blueprint bp("api");
    bp.CROW_MIDDLEWARES(app,api_key);

    CROW_BP_ROUTE(bp,"/")([](){
        return "Your Api Key Is Valid !";
    });

    CROW_BP_ROUTE(bp,"/short/<string>")([](std::string url){
        std::string shorted_url=shorten(url);
        std::string final_string = std::string("Your New Url") + "<-->" + shorted_url;
        return final_string;
    });

    CROW_BP_ROUTE(bp,"/full/<string>")([](std::string short_url){
        std::string original_url=full_url(short_url);
        return original_url;
    });

    CROW_ROUTE(app,"/")([](){
        return "Public Route Of Short-It Please Refer To Docs For Usage Understanding!!";
    });
    app.register_blueprint(bp);

    app.port(8080).multithreaded().run();
}   