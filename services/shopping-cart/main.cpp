#include "../httplib.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstdlib> // For std::getenv

// Helper to get service configuration from environment variables
std::string get_env(const std::string& name, const std::string& defaultValue) {
    const char* value = std::getenv(name.c_str());
    return value ? value : defaultValue;
}

std::map<std::string, std::vector<int>> carts;

int main() {
    // 從環境變數讀取依賴服務的位址，若沒有則使用本地預設值
    std::string user_service_host = get_env("USER_SERVICE_HOST", "localhost");
    int user_service_port = std::stoi(get_env("USER_SERVICE_PORT", "8081"));
    std::string product_service_host = get_env("PRODUCT_SERVICE_HOST", "localhost");
    int product_service_port = std::stoi(get_env("PRODUCT_SERVICE_PORT", "8082"));

    httplib::Server svr;
    svr.Post("/cart/add", [&](const httplib::Request& req, httplib::Response& res) {
        std::string username = req.get_param_value("username");
        int product_id = std::stoi(req.get_param_value("product_id"));

        httplib::Client user_client(user_service_host, user_service_port);
        auto user_res = user_client.Get(("/validate?username=" + username).c_str());
        if (!user_res || user_res->body != "true") {
            res.status = 401;
            res.set_content("User not validated.", "text/plain");
            return;
        }

        httplib::Client product_client(product_service_host, product_service_port);
        auto product_res = product_client.Get(("/product/" + std::to_string(product_id)).c_str());
        if (!product_res || product_res->status != 200) {
            res.status = 404;
            res.set_content("Product not found.", "text/plain");
            return;
        }

        carts[username].push_back(product_id);
        res.set_content("Item added to cart for user " + username, "text/plain");
    });
    std::cout << "Shopping Cart Service listening on port 8083" << std::endl;
    svr.listen("0.0.0.0", 8083);
    return 0;
}