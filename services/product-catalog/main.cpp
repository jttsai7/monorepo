#include "../httplib.h"
#include <iostream>
#include <map>
#include <string>

std::map<int, std::string> products;
void init_products() {
    products[101] = "{\"id\": 101, \"name\": \"Laptop\", \"price\": 1200.00}";
    products[102] = "{\"id\": 102, \"name\": \"Keyboard\", \"price\": 75.00}";
}
int main() {
    httplib::Server svr;
    init_products();
    svr.Get("/product/:id", [](const httplib::Request& req, httplib::Response& res) {
        int product_id = std::stoi(req.path_params.at("id"));
        if (products.count(product_id)) {
            res.set_content(products[product_id], "application/json");
        } else {
            res.status = 404;
            res.set_content("Product not found.", "text/plain");
        }
    });
    std::cout << "Product Catalog Service listening on port 8082" << std::endl;
    svr.listen("0.0.0.0", 8082);
    return 0;
}
