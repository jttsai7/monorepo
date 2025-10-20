# monorepo/services/product-catalog/BUILD

# 匯入 C++ 規則
package(default_visibility = ["//visibility:public"])

# 定義一個 C++ 執行檔
cc_binary(
    name = "product_service",
    srcs = ["main.cpp"],
    # 宣告此執行檔也依賴於 httplib
    deps = ["//services:httplib"],
)
