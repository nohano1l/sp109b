# 📖第十六周筆記

## multiroom

multithread/ 的執行，跟 poll/ 和 epoll/ 差不多

![](https://nohano1l.github.io/sp109b/note/week16/picture/0.png)

![](https://nohano1l.github.io/sp109b/note/week16/picture/1.png)

![](https://nohano1l.github.io/sp109b/note/week16/picture/2.png)

![](https://nohano1l.github.io/sp109b/note/week16/picture/3.png)

[client.c](https://github.com/nohano1l/sp109b/blob/main/note/week16/client.c)

### multithread

[server.c](https://github.com/nohano1l/sp109b/blob/main/note/week16/server1.c)

### poll

[server.c](https://github.com/nohano1l/sp109b/blob/main/note/week16/server2.c)

### epoll

[server.c](https://github.com/nohano1l/sp109b/blob/main/note/week16/server3.c)

### 差別
```
//能支撐的客戶端及效能 epoll > poll > mutithread
mutithread 每多一個客戶要多一個thread
poll 整個server只用一個thread(主程式+一個thread),事件要一個一個測
epoll 整個server只用一個thread(主程式+一個thread),只要測有事件發生的串流,而不需要全測
```