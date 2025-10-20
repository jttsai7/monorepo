# 這個 Dockerfile 的結構與 user-management 的完全相同，只是編譯的目標不同
# --- 階段一: 建置 ---
FROM alpine:latest AS builder
RUN apk add --no-cache build-base
WORKDIR /app
COPY services/httplib.h .
COPY services/product-catalog/main.cpp main.cpp

# 編譯 product_service 執行檔
RUN g++ -std=c++17 -o product_service main.cpp -I. -lpthread -static

# --- 階段二: 運行 ---
FROM alpine:latest
WORKDIR /app
COPY --from=builder /app/product_service .
RUN chmod +x /app/product_service
CMD ["/app/product_service"]
