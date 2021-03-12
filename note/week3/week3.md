# 第三周筆記

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

## 程式碼的輸出及理解

### lexer.c

```
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TMAX 10000000
#define SMAX 100000

enum { Id, Int, Keyword, Literal, Char }; //列舉

char *typeName[5] = {"Id", "Int", "Keyword", "Literal", "Char"};

char code[TMAX];
char strTable[TMAX], *strTableEnd=strTable;
char *tokens[TMAX]; //字元指標
int tokenTop=0;
int types[TMAX];

#define isDigit(ch) ((ch) >= '0' && (ch) <='9')

#define isAlpha(ch) (((ch) >= 'a' && (ch) <='z') || ((ch) >= 'A' && (ch) <= 'Z'))

int readText(char *fileName, char *text, int size) {
  FILE *file = fopen(fileName, "r");  //讀檔
  int len = fread(text, 1, size, file);
  text[len] = '\0';
  fclose(file);
  return len;
}

/* strTable =
#\0include\0"sum.h"\0int\0main\0.....
*/
char *next(char *p) {
  while (isspace(*p)) p++;//略空白

  char *start = p; //         include "sum.h"
                   //         ^      ^
                   //  start= p      p
  int type;
  if (*p == '\0') return NULL;
  if (*p == '"') { //取"sum.h"
    p++;
    while (*p != '"') p++;   //p的內容不等於'"',p++表示p的指標++(如果是32位元(Bits)p=p+4;)
    p++;
    type = Literal;
  } else if (*p >='0' && *p <='9') { // 數字
    while (*p >='0' && *p <='9') p++;
    type = Int;
  } else if (isAlpha(*p) || *p == '_') { // 變數名稱或關鍵字
    while (isAlpha(*p) || isDigit(*p) || *p == '_') p++;
    type = Id;
  } else { // 單一字元
    p++;
    type = Char;
  }
  int len = p-start;
  char *token = strTableEnd;
  strncpy(strTableEnd, start, len);  //複製len
  strTableEnd[len] = '\0';  //補0
  strTableEnd += (len+1);
  types[tokenTop] = type;
  tokens[tokenTop++] = token;
  printf("token=%s\n", token);
  return p;
}

void lex(char *code) {
  char *p = code;
  while (1) {
    p = next(p);
    if (p == NULL) break;
  }
}

void dump(char *strTable[], int top) {
  for (int i=0; i<top; i++) {
    printf("%d:%s\n", i, strTable[i]);
  }
}

int main(int argc, char * argv[]) {
  readText(argv[1], code, sizeof(code)-1);
  puts(code);
  lex(code);
  dump(tokens, tokenTop);
}
```

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
* compiler.c
```
#include <assert.h>
#include "compiler.h"

int E();
void STMT();
void IF();
void BLOCK();

int tempIdx = 0, labelIdx = 0;

#define nextTemp() (tempIdx++)
#define nextLabel() (labelIdx++)
#define emit printf

int isNext(char *set) {
  char eset[SMAX], etoken[SMAX];
  sprintf(eset, " %s ", set);
  sprintf(etoken, " %s ", tokens[tokenIdx]);
  return (tokenIdx < tokenTop && strstr(eset, etoken) != NULL);
}

int isEnd() {
  return tokenIdx >= tokenTop;
}

char *next() {
  // printf("token[%d]=%s\n", tokenIdx, tokens[tokenIdx]);
  return tokens[tokenIdx++];
}

char *skip(char *set) {
  if (isNext(set)) {
    return next();
  } else {
    printf("skip(%s) got %s fail!\n", set, next());
    assert(0);
  }
}

// F = (E) | Number | Id
int F() {
  int f;
  if (isNext("(")) { // '(' E ')'
    next(); // (
    f = E();
    next(); // )
  } else { // Number | Id
    f = nextTemp();
    char *item = next();
    emit("t%d = %s\n", f, item);
  }
  return f;
}

// E = F (op E)*
int E() {
  int i1 = F();
  while (isNext("+ - * / & | ! < > =")) {
    char *op = next();
    int i2 = E();
    int i = nextTemp();
    emit("t%d = t%d %s t%d\n", i, i1, op, i2);
    i1 = i;
  }
  return i1;
}

// ASSIGN = id '=' E;
void ASSIGN() {
  char *id = next();
  skip("=");
  int e = E();
  skip(";");
  emit("%s = t%d\n", id, e);
}

// WHILE = while (E) STMT
void WHILE() {
  int whileBegin = nextLabel();
  int whileEnd = nextLabel();
  emit("(L%d)\n", whileBegin);
  skip("while");
  skip("(");
  int e = E();
  emit("if not T%d goto L%d\n", e, whileEnd);
  skip(")");
  STMT();
  emit("goto L%d\n", whileBegin);
  emit("(L%d)\n", whileEnd);
}

// STMT = WHILE | BLOCK | ASSIGN
void STMT() {
  if (isNext("while"))
    return WHILE();
  // else if (isNext("if"))
  //   IF();
  else if (isNext("{"))
    BLOCK();
  else
    ASSIGN();
}

// STMTS = STMT*
void STMTS() {
  while (!isEnd() && !isNext("}")) {
    STMT();
  }
}

// BLOCK = { STMTS }
void BLOCK() {
  skip("{");
  STMTS();
  skip("}");
}

// PROG = STMTS
void PROG() {
  STMTS();
}

void parse() {
  printf("============ parse =============\n");
  tokenIdx = 0;
  PROG();  //整程式
}
```

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