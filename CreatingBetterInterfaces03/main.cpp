#include <iostream>
#include <span>
#include <thread>
#include <string_view>
//#include <boost/asio/io_context.hpp>
#include "logger.h"

using namespace helpers;

int main(int argc, char *argv[]) {
    auto run_server = false;
    auto log = logger::get_logger();
    if (argc > 1) {
        for (std::string_view arg : std::span{&argv[1], static_cast<int>(argc - 1)}) {
            if (arg == "-server") {
                run_server = true;
            }
            if (arg == "-debug") {
                log.set_level(log_level::debug);
            }
        }
    }
    log.write(log_level::debug, "Starting up");
    constexpr short port = 1234;
//    try {
//        boost::asio::io_context io_context;
//        auto work = boost::asio::make_work_guard(io_context);
//        std::thread thread{[&io_context]() { io_context.run(); }};
//
//        helpers::scope_guard guard{[&thread, &io_context]() {
//            io_context.stop();
//            if (thread.joinable()) {
//                thread.join();
//            }
//        }};
//
//        if (run_server) {
//            write_log(log, log_level, "Listening on port", port);
//            daytime::server server{io_context, port};
//            thread.join();
//        } else {
//            daytime::client client {io_context, "local_host", port};
//            auto time = client.query_daytime();
//            std::cout << "Current time from daytime server: " << time << std::endl;
//        }
//    } catch (Exception e) {
//
//    }
    return 0;
}
