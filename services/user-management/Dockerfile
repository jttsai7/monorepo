# --- 階段一: 建置 ---
# 使用輕量的 Alpine Linux 作為基礎映像檔，並命名此階段為 'builder'
FROM alpine:latest AS builder

# 安裝 C++ 編譯工具鏈 (g++, make 等)
# --no-cache 選項可以確保不安裝快取，讓映像檔更小
RUN apk add --no-cache build-base

# 設定容器內的工作目錄
WORKDIR /app

# 將必要的原始碼複製到容器中
# 修正: 來源路徑改為相對於 context (monorepo) 的完整路徑
COPY services/httplib.h .
COPY services/user-management/main.cpp main.cpp

# 編譯 user_service 執行檔
# -o 指定輸出檔名
# -I. 告訴編譯器在目前目錄尋找標頭檔 (httplib.h)
# -lpthread 連結 POSIX 線程函式庫
# -static 進行靜態連結，產生無依賴的執行檔
RUN g++ -std=c++17 -o user_service main.cpp -I. -lpthread -static

# --- 階段二: 運行 ---
# 再次使用一個全新的、乾淨的 Alpine 作為最終的運行環境
FROM alpine:latest

# 設定工作目錄
WORKDIR /app

# 使用 --from=builder 從第一階段複製編譯好的執行檔
# 這是多階段建置的核心，只保留必要的產物
COPY --from=builder /app/user_service .

# 賦予執行檔執行的權限
RUN chmod +x /app/user_service

# 設定容器啟動時的預設指令
CMD ["/app/user_service"]
