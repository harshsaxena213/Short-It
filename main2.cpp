#include <crow.h>
#include <sqlite3.h>
#include "include/api_verify.h"
#include "include/short.h"
#include "include/full.h"
#include "include/admin_api_verify.h"
#include "include/admin_api_add.h"
#include "include/admin_remove_key.h"

int main()
{
    crow::SimpleApp app;
    CROW_ROUTE(app, "/")([]()
                         {
        auto load=crow::mustache::load("index.html");
        return load.render(); });
    app.port(8082).multithreaded().run();
}