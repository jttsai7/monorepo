# --- 階段一: 建置 ---
FROM alpine:latest AS builder
RUN apk add --no-cache build-base
WORKDIR /build

COPY services/httplib.h ./services/
COPY services/product-catalog/main.cpp ./services/product-catalog/

# 關鍵: 進入 product-catalog 原始碼所在的目錄
WORKDIR /build/services/product-catalog

# 編譯 product_service，輸出到 /app
RUN mkdir -p /app && g++ -std=c++17 -o /app/product_service main.cpp -I../ -lpthread -static

# --- 階段二: 運行 ---
FROM alpine:latest
WORKDIR /app
COPY --from=builder /app/product_service .
RUN chmod +x /app/product_service
CMD ["/app/product_service"]
