#include "../httplib.h"
#include <iostream>
#include <cstdlib> // For std::getenv

std::string get_env(const std::string& name, const std::string& defaultValue) {
    const char* value = std::getenv(name.c_str());
    return value ? value : defaultValue;
}

int main() {
    // 依賴服務的位址
    std::string user_service_host = get_env("USER_SERVICE_HOST", "localhost");
    int user_service_port = std::stoi(get_env("USER_SERVICE_PORT", "8081"));
    std::string product_service_host = get_env("PRODUCT_SERVICE_HOST", "localhost");
    int product_service_port = std::stoi(get_env("PRODUCT_SERVICE_PORT", "8082"));
    std::string cart_service_host = get_env("CART_SERVICE_HOST", "localhost");
    int cart_service_port = std::stoi(get_env("CART_SERVICE_PORT", "8083"));

    httplib::Server svr;

    svr.Post("/register", [&](const httplib::Request& req, httplib::Response& res) {
        httplib::Client client(user_service_host, user_service_port);
        if (auto fwd_res = client.Post(req.path, req.body, req.get_header_value("Content-Type"))) {
            res.set_content(fwd_res->body, fwd_res->get_header_value("Content-Type"));
            res.status = fwd_res->status;
        } else {
            res.status = 503;
            res.set_content("User Management service is unavailable.", "text/plain");
        }
    });

    svr.Get("/product/:id", [&](const httplib::Request& req, httplib::Response& res) {
        httplib::Client client(product_service_host, product_service_port);
        if (auto fwd_res = client.Get(req.path)) {
            res.set_content(fwd_res->body, fwd_res->get_header_value("Content-Type"));
            res.status = fwd_res->status;
        } else {
            res.status = 503;
            res.set_content("Product Catalog service is unavailable.", "text/plain");
        }
    });
    
    svr.Post("/cart/add", [&](const httplib::Request& req, httplib::Response& res) {
        httplib::Client client(cart_service_host, cart_service_port);
        if (auto fwd_res = client.Post(req.path, req.body, req.get_header_value("Content-Type"))) {
            res.set_content(fwd_res->body, fwd_res->get_header_value("Content-Type"));
            res.status = fwd_res->status;
        } else {
            res.status = 503;
            res.set_content("Shopping Cart service is unavailable.", "text/plain");
        }
    });

    std::cout << "API Gateway listening on port 8080" << std::endl;
    svr.listen("0.0.0.0", 8080);
    return 0;
}