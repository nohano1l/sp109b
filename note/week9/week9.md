# 📖第九周筆記

## 程式的位置

[vmem.c](https://github.com/nohano1l/sp109b/blob/main/note/week9/vmem.c)

![](https://nohano1l.github.io/sp109b/note/week9/picture/1.png)
![](https://nohano1l.github.io/sp109b/note/week9/picture/2.png)

```
text:這個區段通常位於 heap 或 stack 之後，避免因 heap 或 stack 溢位而覆寫 CPU 指令。

data:儲存的是一些已經初始化的靜態變數。變數又可分為唯讀區域（read-only area）以及可讀寫區域（read-write area），可讀寫區域用於存放一般變數，其資料會隨著程式的執行而改變，而唯讀區域則是存放固定的常數。

bss:儲存尚未被初始化的靜態變數，而這些變數在程式執行之前會被系統初始化為 0 或是 null。

stack:一般的狀況會從高記憶體位址往低記憶體位址成長，儲存函數的區域變數，以及各種函數呼叫時需要儲存的資訊，每次函式呼叫會儲存該次呼叫的所有變數與狀態，不會互相干擾。

heap:儲存動態配置的變數，例如 C 語言的 malloc 以及 C++ 的 new 所建立的變數都是儲存於此。

system:儲存一些命令列參數與環境變數，這部分會跟系統有關。
```

## Process行程

![](https://nohano1l.github.io/sp109b/note/week9/picture/1.jpg)

[mem.c](https://github.com/nohano1l/sp109b/blob/main/note/week9/mem.c)

```
ps      //列出目前的行程
ps -A   //列出目前全部的行程
```

![](https://nohano1l.github.io/sp109b/note/week9/picture/2.jpg)
![](https://nohano1l.github.io/sp109b/note/week9/picture/3.jpg)