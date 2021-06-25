# 📖第十四週筆記

## 管線

是一系列將標準輸入輸出連結起來的行程，其中每一個行程的輸出被直接作為下一個行程的輸入。 每一個連結都由匿名管道(pipe)實現。管道中的組成元素也被稱作過濾程式。

![](https://nohano1l.github.io/sp109b/note/week14/picture/1.png)

[popen1.c](https://github.com/nohano1l/sp109b/blob/main/note/week14/popen1.c)

[popen2.c](https://github.com/nohano1l/sp109b/blob/main/note/week14/popen2.c)

[upper.c](https://github.com/nohano1l/sp109b/blob/main/note/week14/upper.c)

## fifo(具名管道)

可以通過呼叫mkfifo或od(8進位)來構建，當被呼叫時表現為輸入或輸出的檔案。這樣可以允許建立多個管道，並且將其同標準錯誤重新導向或tee結合起來使用更為有效。 

* install screen

```
sudo apt-get install screen
```

* 指令

```
screen : 執行他
exit : 離開
ctrl + a + c : 新增視窗
ctrl + a + n : 變換視窗
```

![](https://nohano1l.github.io/sp109b/note/week14/picture/2.png)

* fifo1先寫再讀,fifo2先讀再寫,如果沒按照順序執行會錯誤

## 參考資料
[管道](https://zh.wikipedia.org/wiki/%E7%AE%A1%E9%81%93_(Unix))