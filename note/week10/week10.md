# 📖第十周筆記

## race condition

[race.c](https://github.com/nohano1l/sp109b/blob/main/note/week10/race.c)

* race.c的組合語言
![](https://nohano1l.github.io/sp109b/note/week10/picture/2.png)

[norace.c](https://github.com/nohano1l/sp109b/blob/main/note/week10/norace.c)

[deadlock.c](https://github.com/nohano1l/sp109b/blob/main/note/week10/deadlock.c)

![](https://nohano1l.github.io/sp109b/note/week10/picture/1.jpg)

* Run
![](https://nohano1l.github.io/sp109b/note/week10/picture/1.png)

## MMU記憶體管理單元

### 重定位暫存器
![](https://nohano1l.github.io/sp109b/note/week10/picture/4.png)

### 基底-界線暫存器
![](https://nohano1l.github.io/sp109b/note/week10/picture/2.jpg)

以圖為例,最多存取到4029。

### 分段機制
![](https://nohano1l.github.io/sp109b/note/week10/picture/3.jpg)

可以分為程式段(不能被寫入)、資料段(僅限自己可以寫入)、堆疊段(可存取長大)...

### 分頁機制

![](https://nohano1l.github.io/sp109b/note/week10/picture/5.png)

## X86架構的通用暫存器（GPR）

![](https://nohano1l.github.io/sp109b/note/week10/picture/3.png)

```
1.累加器暫存器（AX）。用在算術運算。
2.基址暫存器（BX）。作為一個指向資料的指標（在分段模式下，位於段暫存器DS）。
3.計數器暫存器（CX）。用於移位/迴圈指令和迴圈。
4.資料暫存器（DX）。用在算術運算和I/O操作。
5.堆疊指標暫存器（SP）。用於指向堆疊的頂部。
6.棧基址指標暫存器（BP）。用於指向堆疊的底部。
7.源變址暫存器（SI）。在流操作中用作源的一個指標。
8.目標索引暫存器（DI）。用作在流操作中指向目標的指標。
```