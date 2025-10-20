# --- 階段一: 建置 ---
FROM alpine:latest AS builder
RUN apk add --no-cache build-base
WORKDIR /app
COPY services/httplib.h .
COPY services/api-gateway/main.cpp main.cpp

# 編譯 api_gateway_service 執行檔
RUN g++ -std=c++17 -o api_gateway_service main.cpp -I. -lpthread -static

# --- 階段二: 運行 ---
FROM alpine:latest
WORKDIR /app
COPY --from=builder /app/api_gateway_service .
RUN chmod +x /app/api_gateway_service
CMD ["/app/api_gateway_service"]
