// requires libboost1.74-dev on top of the standard CPSC 120A packages
// Compile with:
// clang++ -Wall -pedantic -std=c++17 main.cc
// Once you run the program, use your web brower to view the page.
// ex: http://127.0.0.1:80808/
// or to find your ip address, use the command:
// ip address

#include <chrono>
#include <ctime>

#include "crow_all.h"

int main(int argc, char const *argv[]) {
  crow::SimpleApp app;

  CROW_ROUTE(app, "/")
  ([]() {
    return "<!DOCTYPE html><html><body><h1>Hello World!</h1></body></html>";
  });

  CROW_ROUTE(app, "/time")
  ([]() {
    std::chrono::system_clock::time_point now =
        std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);
    // tm utc_tm = *gmtime(&tt);
    tm local_tm = *localtime(&tt);

    auto page = crow::mustache::load("time.html");

    crow::mustache::context ctx({{"year", local_tm.tm_year + 1900},
                                 {"month", local_tm.tm_mon + 1},
                                 {"day", local_tm.tm_mday},
                                 {"hour", local_tm.tm_hour},
                                 {"min", local_tm.tm_min},
                                 {"sec", local_tm.tm_sec}});
    return page.render(ctx);
  });

  CROW_ROUTE(app, "/<string>")
  ([](std::string name) {
    auto page = crow::mustache::load("hello.html");
    crow::mustache::context ctx({{"person", name}});
    return page.render(ctx);
  });

  app.port(18080).multithreaded().run();

  return 0;
}