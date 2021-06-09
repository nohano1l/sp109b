# 📖第十五周筆記

## chat

![](https://nohano1l.github.io/sp109b/note/week15/picture/1.png)

* fifo/chat.c 的執行,跟 mmap/ 和 msg/ 執行差不多

![](https://nohano1l.github.io/sp109b/note/week15/picture/2.png)

![](https://nohano1l.github.io/sp109b/note/week15/picture/3.png)

### fifo(具名管道)
[chat.c](https://github.com/nohano1l/sp109b/blob/main/note/week15/chat1.c)

### mmap(記憶體映射)
[chat.c](https://github.com/nohano1l/sp109b/blob/main/note/week15/chat2.c)

### msg(訊息佇列)
[chat.c](https://github.com/nohano1l/sp109b/blob/main/note/week15/chat3.c)

### udp 和 tcp 的執行與差別

兩個執行差不多

```
$ ./chat
I am server...
receive: <connect request> from client addr 127.0.0.1
receive: hi
hello
```

```
$ ./chat 127.0.0.1
I am client...
hi
receive: hello
```

![](https://nohano1l.github.io/sp109b/note/week15/picture/4.png)

### udp（用戶資料包協定）
[chat.c](https://github.com/nohano1l/sp109b/blob/main/note/week15/chat4.c)

### tcp（通訊控制協定）
[chat.c](https://github.com/nohano1l/sp109b/blob/main/note/week15/chat5.c)