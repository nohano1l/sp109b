# 📖第三周筆記

## fopen用法

```
int readText(char *fileName, char *text, int size) {
  FILE *file = fopen(fileName, "r");  //讀檔
  int len = fread(text, 1, size, file);
  text[len] = '\0';
  fclose(file);
  return len;
}
```
* 參數
```
"r":讀-打開文件進行輸入操作。該文件必須存在。

"w":寫-創建一個空文件用於輸出操作。如果已經存在同名文件，則其內容將被丟棄，並且該文件將被視為新的空文件。

"a":加附-打開文件以在文件末尾輸出。輸出操作始終將數據寫入文件的末尾，然後對其進行擴展。重新定位操作（fseek，fsetpos，rewind）將被忽略。如果文件不存在，則創建該文件。

"r+":讀/更新-打開文件進行更新（用於輸入和輸出）。該文件必須存在。

"w+":寫/更新-創建一個空文件並打開以進行更新（用於輸入和輸出）。如果已經存在同名文件，則將其內容丟棄，並將該文件視為新的空文件。

"a+":加附/更新-打開文件進行更新（用於輸入和輸出），所有輸出操作均在文件末尾寫入數據。重新定位操作（fseek，fsetpos，rewind）會影響下一個輸入操作，但是輸出操作會將位置移回文件末尾。如果文件不存在，則創建該文件。
```

## c語言指標

### pointer1.c

```
# include <stdio.h>

int main(){
    char x='a';
    char *p=&x;
    *p='b';
    printf("*p=%c x=%c\n",*p,x);
}
```
* result
```
cxz1d@MSI MINGW64 ~/OneDrive/桌面/nohano1l/sp/_c (master)
$ ./pointer1
*p=b x=b
```

![](https://nohano1l.github.io/sp109b/note/week3/picture/未命名.png)

### pointer1bug.c(野指標)
```
# include <stdio.h>

int main(){
    char x='a';
    char *p;  // =&x;
    *p='b';
    printf("*p=%c x=%c\n",*p,x);
}
```

因為p指標沒有值，所以他會亂指，導致發生錯誤。

* result
```
cxz1d@MSI MINGW64 ~/OneDrive/桌面/nohano1l/sp/_c (master)
$ ./pointer1bug
Segmentation fault  //分段錯誤
```

## 💻程式碼的輸出及理解

### [lexer.c](https://nohano1l.github.io/sp109b/note/week3/02-lexer/lexer.c)

* p++ 指的是指標++,*p是指p的內容

![](https://nohano1l.github.io/sp109b/note/week3/picture/1.png)

* sum.c
```
#include "sum.h"

int main() {
  int t = sum(10);
  printf("sum(10)=%d\n", t);
}
```

* result(./lexer 'sum.c')
```
cxz1d@MSI MINGW64 ~/OneDrive/桌面/nohano1l/sp/03-compiler/02-lexer (master)
$ ./lexer 'sum.c'
#include "sum.h"

int main() {
  int t = sum(10);
  printf("sum(10)=%d\n", t);
}
token=#      
token=include
token="sum.h"
token=int    
token=main
token=(
token=)
token={
token=int
token=t
token==
token=sum
token=(
token=10
token=)
token=;
token=printf
token=(
token="sum(10)=%d\n"
token=,
token=t
token=)
token=;
token=}
0:#
1:include
2:"sum.h"
3:int
4:main
5:(
6:)
7:{
8:int
9:t
10:=
11:sum
12:(
13:10
14:)
15:;
16:printf
17:(
18:"sum(10)=%d\n"
19:,
20:t
21:)
22:;
23:}
```

### compiler

* make(gcc -std=c99 -O0 lexer.c compiler.c main.c -o compiler)
```
CC := gcc
CFLAGS = -std=c99 -O0
TARGET = compiler

all: $(TARGET)

$(TARGET): lexer.c compiler.c main.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o *.exe $(TARGET)
```

* main.c
```
#include "compiler.h"

int readText(char *fileName, char *text, int size) {
  FILE *file = fopen(fileName, "r");
  int len = fread(text, 1, size, file);
  text[len] = '\0';
  fclose(file);
  return len;
}

void dump(char *strTable[], int top) {
  printf("========== dump ==============\n");
  for (int i=0; i<top; i++) {
    printf("%d:%s\n", i, strTable[i]);
  }
}

int main(int argc, char * argv[]) {
  readText(argv[1], code, TMAX);
  puts(code);
  lex(code);
  dump(tokens, tokenTop);
  parse(); //compiler
  return 0;
}
```
* [compiler.c](https://nohano1l.github.io/sp109b/note/week3/03a-compiler/compiler.c)

* while.c
```
i = 1;
while (i<10) i = i + 1;
```

* result(./compiler 'test/while.c')
由於是在03-compiler開啟終端，while.c在test檔案中,執行要寫'test/while.c'
```
cxz1d@MSI MINGW64 ~/OneDrive/桌面/nohano1l/sp/03-compiler/03-compiler (master)
$ ./compiler 'test/while.c'
i = 1;
while (i<10) i = i + 1;

========== lex ==============
token=i
token==
token=1
token=;
token=while
token=(
token=i
token=<
token=10
token=)
token=i
token==
token=i
token=+
token=1
token=;
========== dump ==============
0:i
1:=
2:1
3:;
4:while
5:(
6:i
7:<
8:10
9:)
10:i
11:=
12:i
13:+
14:1
15:;
============ parse =============
t0 = 1
i = t0
(L0)
t1 = i
t2 = 10
t3 = t1 < t2
if not T3 goto L1
t4 = i
t5 = 1
t6 = t4 + t5
i = t6
goto L0
(L1)
```