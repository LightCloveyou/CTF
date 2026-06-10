#!/bin/sh
# Add your startup script
# Get the user
user=$(ls /home)

# Check the environment variables for the flag and assign to INSERT_FLAG
if [ "$ICQ_FLAG" ]; then
    INSERT_FLAG="$ICQ_FLAG"
    unset ICQ_FLAG
else
    INSERT_FLAG="flag{TDjHchkxCaXUd16LaJR9hd6Nu49CLRdLGF85m2NfHWkF5}"
fi

# 将FLAG写入文件 请根据需要修改
echo $INSERT_FLAG | tee /flag
unset INSERT_FLAG
# 赋予程序运行权限
chmod 755 /home/ctf/*
cd /home/ctf

./main
