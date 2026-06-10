FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y socat && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

# 预编译二进制 + 本地调试用假 flag
COPY assembly_csharp ./
COPY flag.txt ./

RUN chmod +x assembly_csharp && \
    chmod 444 flag.txt

EXPOSE 9001

CMD ["socat", "TCP-LISTEN:9001,reuseaddr,fork", "EXEC:./assembly_csharp,stderr"]
