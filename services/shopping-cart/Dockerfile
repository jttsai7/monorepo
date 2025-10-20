# --- 階段一: 建置 ---
FROM alpine:latest AS builder
RUN apk add --no-cache build-base
WORKDIR /app
COPY services/httplib.h .
COPY services/shopping-cart/main.cpp main.cpp

# 編譯 shopping_cart_service 執行檔
RUN g++ -std=c++17 -o shopping_cart_service main.cpp -I. -lpthread -static

# --- 階段二: 運行 ---
FROM alpine:latest
WORKDIR /app
COPY --from=builder /app/shopping_cart_service .
RUN chmod +x /app/shopping_cart_service
CMD ["/app/shopping_cart_service"]
