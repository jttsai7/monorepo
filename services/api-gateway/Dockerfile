# --- 階段一: 建置 ---
FROM alpine:latest AS builder
RUN apk add --no-cache build-base
WORKDIR /build

COPY services/httplib.h ./services/
COPY services/api-gateway/main.cpp ./services/api-gateway/

# 關鍵: 進入 api-gateway 原始碼所在的目錄
WORKDIR /build/services/api-gateway

# 編譯 api_gateway_service，輸出到 /app
RUN mkdir -p /app && g++ -std=c++17 -o /app/api_gateway_service main.cpp -I../ -lpthread -static

# --- 階段二: 運行 ---
FROM alpine:latest
WORKDIR /app
COPY --from=builder /app/api_gateway_service .
RUN chmod +x /app/api_gateway_service
CMD ["/app/api_gateway_service"]
