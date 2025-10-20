# monorepo/services/user-management/BUILD

# 匯入 C++ 規則
package(default_visibility = ["//visibility:public"])

# 定義一個 C++ 執行檔
cc_binary(
    name = "user_service",
    srcs = ["main.cpp"],
    # 宣告此執行檔依賴於我們在上一層定義的 httplib 函式庫
    deps = ["//services:httplib"],
)
