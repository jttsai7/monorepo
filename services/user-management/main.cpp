#include "../httplib.h"
#include <iostream>
#include <map>
#include <string>
#include <mutex>

std::map<std::string, std::string> users;
std::mutex users_mutex;

int main() {
    httplib::Server svr;
    svr.Post("/register", [](const httplib::Request& req, httplib::Response& res) {
        std::string username = req.get_param_value("username");
        std::string password = req.get_param_value("password");
        if (username.empty() || password.empty()) {
            res.status = 400;
            res.set_content("Username or password missing.", "text/plain");
            return;
        }
        {
            std::lock_guard<std::mutex> guard(users_mutex);
            users[username] = password;
        }
        res.set_content("User registered successfully.", "text/plain");
    });
    svr.Get("/validate", [](const httplib::Request& req, httplib::Response& res) {
        std::string username = req.get_param_value("username");
        bool user_exists = false;
        {
            std::lock_guard<std::mutex> guard(users_mutex);
            user_exists = users.count(username);
        }
        if (user_exists) {
            res.set_content("true", "text/plain");
        } else {
            res.set_content("false", "text/plain");
        }
    });
    std::cout << "User Management Service listening on port 8081" << std::endl;
    svr.listen("0.0.0.0", 8081);
    return 0;
}
