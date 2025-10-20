# monorepo/services/product-catalog/BUILD

# 匯入 C++ 規則
package(default_visibility = ["//visibility:public"])

# 定義一個 C++ 執行檔
cc_binary(
    name = "api_gateway_service",
    srcs = ["main.cpp"],
    deps = ["//services:httplib"],
)
