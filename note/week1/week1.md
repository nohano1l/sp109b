## 第一周筆記
### 我遇到的問題
#### 壹. 呼叫不出gcc
* 下載CodeBlocks
* 從電腦工具列搜尋"編輯系統環境變數",並點擊
* 系統內容 -> 進階 -> 環境變數 -> 系統變數
* 點擊變數"Path",按編輯,瀏覽,點選CodeBlocks檔案夾內的MinGW\bin ,更改環境變數
#### 貳. 執行hello.c中文變亂碼
* 在vscode的設定搜尋files.encoding,更改為UTF-8
#### 參. gcc指令代表什麼意思?
![指令意思](https://nohano1l.github.io/sp109b/note/week1/picture/指令mean.png)
#### 肆. makefile指令的意思
![指令意思](https://nohano1l.github.io/sp109b/note/week1/picture/makefile.png)
#### 伍. make clean 沒clean掉
* 由於"rm"這個指令只能在bash終端機執行,所以要更改終端機的種類!(很重要)
#### Makefile 特殊符號
```
$@ : 該規則的目標文件 (Target file)
$* : 代表 targets 所指定的檔案，但不包含副檔名
$< : 依賴文件列表中的第一個依賴文件 (Dependencies file)
$^ : 依賴文件列表中的所有依賴文件
$? : 依賴文件列表中新於目標文件的文件列表

?= 語法 : 若變數未定義，則替它指定新的值。
:= 語法 : make 會將整個 Makefile 展開後，再決定變數的值。
```