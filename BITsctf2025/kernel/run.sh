#!/bin/sh
qemu-system-x86_64 \
  -cpu kvm64 \
  -m 64M \
  -smp cores=2,threads=1 \
  -append "root=/dev/sda rw console=ttyS0 oops=panic panic=1 nokaslr" \
  -monitor /dev/null \
  -kernel ./bzImage \
  -hda ./rootfs.qcow2 \
  -hdb ./flag \
  -nographic \
  -no-reboot \
  -s
