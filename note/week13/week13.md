# 📖第十三周筆記

## 第十二周的疑問補充

![](https://nohano1l.github.io/sp109b/note/week13/picture/1.png)

[io1.c](https://github.com/nohano1l/sp109b/blob/main/note/week13/io1.c)

* 為什麼a=3,b=4?
```
(預設)  //0、1、2已經被分配
0:標準輸入
1:標準輸出
2:標準錯誤
```

[fecho1.c](https://github.com/nohano1l/sp109b/blob/main/note/week13/fecho1.c)

* 為什麼a=0,b=1?
```
因為0、1被關掉，所以a=0、b=1
```

[fecho2.c](https://github.com/nohano1l/sp109b/blob/main/note/week13/fecho2.c)

## 分別印出stdout跟stderr

[stderr1.c](https://github.com/nohano1l/sp109b/blob/main/note/week13/stderr1.c)

```
$ gcc stderr1.c -o stderr1
$ ./stderr1
Some message!
Warning: xxx
Error: yyy
$ ./stderr1 2>error.txt   //把stderr存在error.txt
Some message!
$ ./stderr1 1>output.txt  //把stdout存在output.txt
Warning: xxx
Error: yyy
$ ./stderr1 1>output.txt 2>error.txt
```

## blocking & nonblocking

[nonblocking2.c](https://github.com/nohano1l/sp109b/blob/main/note/week13/nonblocking2.c)

```
$ gcc blocking1.c -o blocking1
$ ./blocking1
abc
buf is abc

test
123
buf is 123

test
^C

$ gcc nonblocking1.c -o nonblocking1
$ ./nonblocking1
read /dev/tty: Resource temporarily unavailable
no input,buf is null
read /dev/tty: Resource temporarily unavailable
no input,buf is null
adsjkf;lasf
ret = 12, buf is adsjkf;lasf

read /dev/tty: Resource temporarily unavailable
no input,buf is null
adfkread /dev/tty: Resource temporarily unavailable
no input,buf is null
a;
adlsfkret = 7, buf is adfka;

read /dev/tty: Resource temporarily unavailable
no input,buf is null
^C

$ gcc nonblocking2.c -o nonblocking2
$ ./nonblocking2
read /dev/tty: Resource temporarily unavailable
no input,buf is null

aldjf
ret = 6, buf is aldjf

```

## Time

[time.c](https://github.com/nohano1l/sp109b/blob/main/note/week13/time.c)

[server1.c](https://github.com/nohano1l/sp109b/blob/main/note/week13/server1.c)

```
$ ./server&
[1] 20830
$ ./client
Wed May 19 15:04:47 2021
$ ./client
Wed May 19 15:04:49 2021
$ ./client
Wed May 19 15:04:50 2021
```

## telnet1

```
$ make
gcc -Wall -std=gnu99 server.c ../net.c -o server
gcc -Wall -std=gnu99 client.c ../net.c -o client
$ ./server&
[1] 24441
$ ./client
connect to server 127.0.0.1 success!
127.0.0.1 $ ls
cmd=ls
client
client.c
Makefile
README.md
server
server.c

127.0.0.1 $ exit
```