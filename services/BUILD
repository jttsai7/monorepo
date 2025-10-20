# monorepo/services/BUILD

# 定義一個 C++ 函式庫叫做 "httplib"
cc_library(
    name = "httplib",
    hdrs = ["httplib.h"],
    # 讓 services/ 目錄下的所有子套件 (例如 user-management) 都能看見並使用它
    visibility = ["//services:__subpackages__"],
)