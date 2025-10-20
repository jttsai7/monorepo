# --- 階段一: 建置 ---
# 使用 Alpine 作為輕量級建置環境
FROM alpine:latest AS builder
# 安裝 C++ 編譯工具
RUN apk add --no-cache build-base

# 使用 /build 作為臨時建置工作區
WORKDIR /build

# 複製 httplib.h 到 /build/services/httplib.h
# (源路徑相對於 build context 'monorepo')
COPY services/httplib.h ./services/
# 複製 main.cpp 到 /build/services/user-management/main.cpp
COPY services/user-management/main.cpp ./services/user-management/

# 關鍵: 進入 user-management 原始碼所在的目錄
WORKDIR /build/services/user-management

# 執行編譯
# 'main.cpp' -> 在當前目錄 (/build/services/user-management) 找到
# '-I../' -> 告訴 g++ 去上一層目錄 (/build/services) 尋找 include (httplib.h)
# '-o /app/user_service' -> 將輸出的執行檔放到 /app 目錄下 (先建立 /app)
RUN mkdir -p /app && g++ -std=c++17 -o /app/user_service main.cpp -I../ -lpthread -static

# --- 階段二: 運行 ---
# 使用乾淨的 Alpine 作為運行環境
FROM alpine:latest
# 設定運行時的工作目錄
WORKDIR /app
# 從 builder 階段的 /app 目錄複製最終編譯好的執行檔
COPY --from=builder /app/user_service .
# 賦予執行權限
RUN chmod +x /app/user_service
# 設定預設啟動指令
CMD ["/app/user_service"]
