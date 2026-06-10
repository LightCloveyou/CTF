FROM i386/debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive

# 只装运行必需组件
RUN apt update && apt install -y \
    socat \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /pwn

COPY src/pwn .
COPY src/libc.so.6 .
COPY src/ld-linux.so.2 .

RUN chmod +x pwn ld-linux.so.2

# 监听端口
EXPOSE 9999

# socat 起远程服务，用你给的 ld + libc
CMD ["socat", \
     "TCP-LISTEN:9999,reuseaddr,fork", \
     "EXEC:./ld-linux.so.2 --library-path . ./pwn,stderr"]
