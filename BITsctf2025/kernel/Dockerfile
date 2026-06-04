FROM ubuntu:24.04 AS app

RUN apt-get update && apt-get install -yq --no-install-recommends \
  qemu-system-x86 socat \
  && rm -rf /var/lib/apt/lists/*

COPY run.sh /
COPY rootfs.qcow2 bzImage flag /

RUN chmod +x /run.sh

EXPOSE 10001
CMD ["socat", "tcp-listen:10001,fork", "exec:/run.sh,reuseaddr"]
