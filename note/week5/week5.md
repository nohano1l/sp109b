# 第五周筆記

## 虛擬機和模擬器的區別?

```
虛擬機:有模擬整套CPU的指令集
模擬器:模擬電腦外部的行為
```

## 堆疊機的執行

![](https://nohano1l.github.io/sp109b/note/week5/picture/1.png)

## Download

* make
```
sudo apt install make
```
* java

```
sudo apt install default-jre
sudo apt install default-jdk
```

* 把HelloWorld.java編譯成class檔並執行

![](https://nohano1l.github.io/sp109b/note/week5/picture/2.png)

## 上次compiler for功能的改良

修改i++執行的順序,參考上課時老師的範例，使用暫存的方式，再離開迴圈的時候執行

```
// #define emit printf
int isTempIr = 0;
char tempIr[100000], *tempIrp = tempIr;
#define emit(...) ({ \
  if (isTempIr){ \                         //暫存
    sprintf(tempIrp, __VA_ARGS__); \
    tempIrp += strlen(tempIrp);\
  }\
  else { \
    printf(__VA_ARGS__);\
  }\
})

// for(ASSIGN E; F) STMT
void FOR() {
  int forBegin = nextLabel();
  int forEnd = nextLabel();
  skip("for");
  skip("(");
  ASSIGN();
  emit("(L%d)\n", forBegin);
  int e = E();
  emit("if not t%d goto L%d\n", e, forEnd);
  skip(";");
  isTempIr = 1;
  F();
  isTempIr = 0;
  char e3str[1000];
  strcpy(e3str, tempIr);  //複製tempIr到e3str
  skip(")");
  STMT();
  emit("%s\n",e3str);
  emit("goto L%d\n", forBegin);
  emit("(L%d)\n", forEnd);
}
```
* Run
```
cxz1d@MSI MINGW64 ~/OneDrive/桌面/nohano1l/sp109b/note/week4/03b-compiler2 (main)
$ ./compiler 'test/for.c'
for(i=0;i<=3;i++){
    a=a+1;        
}
`
`
`
============ parse =============
t0 = 0
i = t0
(L0)
t1 = i
t2 = 3
t3 = t1 <= t2
if not t3 goto L1
t5 = a
t6 = 1
t7 = t5 + t6
a = t7
i = i + 1

goto L0
(L1)
```

## C4 編譯器

[C4](https://github.com/rswier/c4) 是由 [Robert Swierczek](https://github.com/rswier/) 寫的一個小型 C 語言編譯器，全部 500 多行的原始碼都在 c4.c 裡 。

C4 編譯完成後，會產生一種《堆疊機機器碼》放在記憶體內，然後 虛擬機 會立刻執行該機器碼。

以下是 C4 編譯器的用法，C4 可以進行《自我編譯》:

```
./c4 test/hello.c
./c4 c4.c test/hello.c  //用c4執行c4.c(編譯器的code),還是編譯器再執行test/hello.c
./c4 c4.c c4.c test/hello.c
```