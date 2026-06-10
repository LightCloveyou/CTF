如果选手运行题目程序遇到

```bash
./pwn: /lib/x86_64-linux-gnu/libstdc++.so.6: version `GLIBCXX_3.4.32' not found (required by ./pwn)
./pwn: /lib/x86_64-linux-gnu/libstdc++.so.6: version `GLIBCXX_3.4.29' not found (required by ./pwn)
./pwn: /lib/x86_64-linux-gnu/libc.so.6: version `GLIBC_2.38' not found (required by ./pwn)
./pwn: /lib/x86_64-linux-gnu/libc.so.6: version `GLIBC_2.34' not found (required by ./pwn)
```

等版本相关问题

请执行

```bash
patchelf --set-interpreter ./ld-linux-x86-64.so.2 ./pwn
patchelf --replace-needed libc.so.6 ./libc.so.6 ./pwn
patchelf --replace-needed libstdc++.so.6 ./libstdc++.so.6 ./pwn
```

另外，`cpp-lib` 文件夹中的库文件是题目程序的其他运行依赖库
一般而言这些库本地都已经默认带有，选手如果无法运行题目程序，则考虑使用该文件夹中的库，仿照上面命令来继续patch题目程序。
如果能够本地运行调试题目程序则可以忽略`cpp-lib` 文件夹