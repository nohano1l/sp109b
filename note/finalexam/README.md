# 💻C4 編譯器

## 授權聲明
* 本專案中的程式採用[GPL](https://github.com/nohano1l/sp109b/blob/main/note/finalexam/LICENCE)、[MIT 授權](https://zh.wikipedia.org/wiki/MIT%E8%A8%B1%E5%8F%AF%E8%AD%89)
* 文章和圖片部分衍生自維基百科，採用 [CC:BY-SA](https://zh.wikipedia.org/zh-hant/Wikipedia%3ACC_BY-SA_3.0%E5%8D%8F%E8%AE%AE%E6%96%87%E6%9C%AC) 授權
* 資料夾內所有程式碼皆來自[程式人媒體授權聲明](https://programmermedia.org/root/%E7%A8%8B%E5%BC%8F%E4%BA%BA%E5%AA%92%E9%AB%94/%E6%8E%88%E6%AC%8A.md)

## c4的基本介紹
[C4](https://github.com/rswier/c4) 是由 [Robert Swierczek](https://github.com/rswier/) 寫的一個小型 C 語言編譯器，全部 500 多行的原始碼都在 c4.c 裡 。

C4 編譯完成後，會產生一種《堆疊機機器碼》放在記憶體內，然後 虛擬機 會立刻執行該機器碼。

## [我的程式碼](https://github.com/nohano1l/sp109b/blob/main/note/finalexam/c4.c)

我使用的程式碼是陳忠誠老師gitlab上的[c4.c](https://gitlab.com/ccc109/sp/-/blob/master/C1-c4/c4.c)加以理解，並添加一些註釋。

## c4的特色

c4的原始碼全部只有 500 多行，卻是個自舉編譯器(Self-Host Compiler)

## gcc編譯

* 不加-m32就會默認用-m64，那樣編譯出來的C4執行會出問題

```
$ gcc -m32 c4.c -o c4  //-m32參數表示要產生的目的碼是32位元
```

## [c4虛擬機](https://github.com/nohano1l/sp109b/blob/main/note/finalexam/c4虛擬機.md)

## [c4的語法](https://github.com/nohano1l/sp109b/blob/main/note/finalexam/c4語法.md)

## 執行與問題解釋

![](https://nohano1l.github.io/sp109b/note/finalexam/picture/1.png)

### 加入-s參數可以印出組合語言(堆疊機)

建議先看我上面c4虛擬機的指令碼，了解各個指令碼的意思會比較好理解

![](https://nohano1l.github.io/sp109b/note/finalexam/picture/3.png)

![](https://nohano1l.github.io/sp109b/note/finalexam/picture/4.png)

* 執行$ ./c4 -s test/sum.c的部分結果

![](https://nohano1l.github.io/sp109b/note/finalexam/picture/5.png)

### 什麼是自舉編譯器(Self-Host Compiler)?

* 簡單來說就是可以編譯自己的編譯器，達到《自我編譯》的功能

![](https://nohano1l.github.io/sp109b/note/finalexam/picture/2.png)

### 為什麼token類別的enum要從128開始?
```
// tokens and classes (operators last and in precedence order) (按優先權順序排列)
enum { // token : 0-127 直接用該字母表達， 128 以後用代號。
  Num = 128, Fun, Sys, Glo, Loc, Id,
  Char, Else, Enum, If, Int, Return, Sizeof, While,
  Assign, Cond, Lor, Lan, Or, Xor, And, Eq, Ne, Lt, Gt, Le, Ge, Shl, Shr, Add, Sub, Mul, Div, Mod, Inc, Dec, Brak
};
```
* 主要是因為 [ASCII Code](https://zh.wikipedia.org/wiki/ASCII) 定義的範圍是 0~127 共 128 字元，所以我們自訂的 token number 必須從 128 開始編號。其實從0到127，加上這Num（128）到Brak（164）的範圍都可以表示token類別，只是ASCII的部分默認映射到對於的字符上而已。

### 是如何進行運算式的?

* 在expr()函數內，採用“遞歸下降”方式（recursive-descent），在表達式部分採用遞歸下降與“運算符優先級”方式（operator precedence）混合的做法。

* 對單目運算符、函數調用、單個變量名等的部分可以說是用了遞歸下降方式
* 對雙目運算符採用了運算符優先級方式

### 為什麼c4會略過標頭檔，還要寫標頭檔?

建議先看我上面c4語法及程式碼

*　因為gcc編譯要認函式庫才能編譯

## 參考資料
[有哪些關於c4 - C in four function 編譯器的文章？](https://www.zhihu.com/question/28249756)

[C中四函數(c4)編譯器](https://hackmd.io/@srhuang/Bkk2eY5ES)

[陳忠誠老師gitlab上的sp/C1-c4](https://gitlab.com/ccc109/sp/-/tree/master/C1-c4)

[陳忠誠老師社團直播 系統程式 第五週 Part 1 -- 虛擬機＋連結器+multipass](https://www.facebook.com/ccckmit/videos/10158852743611893)