#!/bin/sh

echo $GZCTF_FLAG >/flag

cd /home/ctf/src || exit 1 && ./pwn
