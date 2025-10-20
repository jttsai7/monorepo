# --- 階段一: 建置 ---
FROM alpine:latest AS builder
RUN apk add --no-cache build-base
WORKDIR /build

COPY services/httplib.h ./services/
COPY services/shopping-cart/main.cpp ./services/shopping-cart/

# 關鍵: 進入 shopping-cart 原始碼所在的目錄
WORKDIR /build/services/shopping-cart

# 編譯 shopping_cart_service，輸出到 /app
RUN mkdir -p /app && g++ -std=c++17 -o /app/shopping_cart_service main.cpp -I../ -lpthread -static

# --- 階段二: 運行 ---
FROM alpine:latest
WORKDIR /app
COPY --from=builder /app/shopping_cart_service .
RUN chmod +x /app/shopping_cart_service
CMD ["/app/shopping_cart_service"]
