# 📖第二周筆記
## Compiler 6 steps

![](https://nohano1l.github.io/sp109b/note/week2/picture/未命名.png)

## Grammar
### EBNF

```
E=T ([+-] T)*    *：可以重複多次
T=F ([*/] F)?    ?：可以出現0到多次
F=[0-9] | (E)    |：或(or)
```

![](./img/expBnfTree.png)

## 💻程式碼的理解與執行
### genExp.c

* 程式碼
```
#include "rlib.h"/*標頭檔*/

void E();
void T();
void F();

// === EBNF Grammar =====
// E=T ([+-] T)*
// T=F ([*/] F)?
// F=[0-9] | (E)

int main(int argc, char * argv[]) {
	E();
	int i;
	for (i=0; i<10; i++) /*輸出10行*/{
		E();
		printf("\n");
	}
}

void E() {
    T();
	while (randInt(10) < 3) /*有10/3的機會產生+或-*/{
       printf("%c", randChar("+-"));
	   T();
	}
}

void T() {
    F();
	if (randInt(10) < 7) {
		printf("%c", randChar("*/"));
		F();
	}
}

void F() {
    if (randInt(10) < 8) {
		printf("%c", randChar("0123456789"));
	} else {
		printf("(");
		E();
		printf(")");
	}
}
```

* 產生genExp.exe
```
gcc genExp.c rlib.c -o genExp  //把genExp.c和rlib.c做連結
```

* result
```
cxz1d@MSI MINGW64 ~/OneDrive/桌面/nohano1l/sp/03-compiler/00-gen (master)
$ ./genExp
7*(8+5/1)-1*2-8/1(7)/2
4/8
2
(1)/2
0*(5/0)-((4*6)*9)/((9/9)*6)
5*9
7*1
7*2+4*1
7
5
```

### genEnglish.c

* 程式碼
```
#include "rlib.h"

// === EBNF Grammar =====
// S = NP VP
// NP = DET N
// VP = V NP
// N = dog | cat
// V = chase | eat
// DET = a | the

char* n[] = {"dog", "cat"};
char* v[] = {"chase", "eat"};
char* det[] = {"a", "the"};

void N() {
  printf("%s", randSelect(n, 2));
}

void V() {
  printf("%s", randSelect(v, 2));
}

void DET() {
  printf("%s", randSelect(det, 2));
}

void NP() {
  DET();
  printf(" ");
  N();
}

void VP() {
  V();
  printf(" ");
  NP();
}

void S() {
  NP();
  printf(" ");
  VP();
  printf("\n");
}

int main() {
  timeSeed();  //隨機
  S();
}
```

![](https://nohano1l.github.io/sp109b/note/week2/picture/1.png)

* result
```
cxz1d@MSI MINGW64 ~/OneDrive/桌面/nohano1l/sp/03-compiler/00-gen (master)
$ ./genEnglish
the cat chase the cat

cxz1d@MSI MINGW64 ~/OneDrive/桌面/nohano1l/sp/03-compiler/00-gen (master)
$ ./genEnglish
a cat eat the dog
```

### exp0.c

* 程式碼
```
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

int tokenIdx = 0;
char *tokens;

int E();
int F();

/*除錯*/
void error(char *msg) {
  printf("%s", msg);/*堆疊情況*/
  assert(0); /*中止程式*/
}

// 取得目前字元
char ch() {
  char c = tokens[tokenIdx];
  return c;
}

// 取得目前字元，同時進到下一格
char next() {
  char c = ch();
  tokenIdx++;
  return c;
}

// ex: isNext("+-") 用來判斷下一個字元是不是 + 或 -
int isNext(char *set) {
  char c = ch();
  return (c!='\0' && strchr(set, c)!=NULL);
}

// 產生下一個臨時變數的代號， ex: 3 代表 t3。
int nextTemp() {
  static int tempIdx = 0;
  return tempIdx++;
}

// F =  Number | '(' E ')'
int F() {
  int f;
  char c = ch();
  if (isdigit(c)) /*整數*/{
    next(); // skip c
    f = nextTemp();
    printf("t%d=%c\n", f, c);
  } else if (c=='(') { // '(' E ')'
    next();
    f = E();
    assert(ch()==')');
    next();
  } else {
    error("F = (E) | Number fail!");/*除錯*/
  }
  return f; 
}

// E = F ([+-] F)* 
int E() {
  int i1 = F();/*臨時變數*/
  while (isNext("+-")) {
    char op=next();
    int i2 = F();
    int i = nextTemp();
    printf("t%d=t%d%ct%d\n", i, i1, op, i2);
    i1 = i;
  }
  return i1;
}

void parse(char *str) {
  tokens = str;
  E();
}

int main(int argc, char * argv[]) /*argc參數個數argv參數*/{
  printf("argv[0]=%s argv[1]=%s\n", argv[0], argv[1]);
  printf("=== EBNF Grammar =====\n");
  printf("E=F ([+-] F)*\n");
  printf("F=Number | '(' E ')'\n");
  printf("==== parse:%s ========\n", argv[1]);
  parse(argv[1]);
}
```

* result
```
cxz1d@MSI MINGW64 ~/OneDrive/桌面/nohano1l/sp/03-compiler/01-exp0 (master)
$ ./exp0 '3+(5-4)'
argv[0]=C:\Users\cxz1d\OneDrive\桌面\nohano1l\sp\03-compiler\01-exp0\exp0.exe argv[1]=3+(5-4)
=== EBNF Grammar =====
E=F ([+-] F)*
F=Number | '(' E ')'
==== parse:3+(5-4) ========
t0=3
t1=5
t2=4
t3=t1-t2
t4=t0+t3

//除錯
cxz1d@MSI MINGW64 ~/OneDrive/桌面/nohano1l/sp/03-compiler/01-exp0 (master)
$ ./exp0
argv[0]=C:\Users\cxz1d\OneDrive\桌面\nohano1l\sp\03-compiler\01-exp0\exp0.exe argv[1]=(null)
=== EBNF Grammar =====
E=F ([+-] F)*
F=Number | '(' E ')'
==== parse:(null) ========
Segmentation fault

cxz1d@MSI MINGW64 ~/OneDrive/桌面/nohano1l/sp/03-compiler/01-exp0 (master)
$ ./exp0 'x'
argv[0]=C:\Users\cxz1d\OneDrive\桌面\nohano1l\sp\03-compiler\01-exp0\exp0.exe argv[1]=x
=== EBNF Grammar =====
E=F ([+-] F)*
F=Number | '(' E ')'
==== parse:x ========
F = (E) | Number fail!Assertion failed: 0, file exp0.c, line 14
```
### exp0hack

* 程式碼
```
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

int tokenIdx = 0;
char *tokens;

int E();
int F();

void error(char *msg) {
  printf("%s", msg);
  assert(0);
}

char ch() {
  char c = tokens[tokenIdx];
  return c;
}

char next() {
  char c = ch();
  tokenIdx++;
  return c;
}

int isNext(char *set) {
  char c = ch();
  return (c!='\0' && strchr(set, c)!=NULL);
}

int nextTemp() {
  static int tempIdx = 0;
  return tempIdx++;
}

// ex : t1=3
void genOp1(int i, char c) {
  printf("# t%d=%c\n", i, c);
  // t1=3 轉成 @3; D=A; @t1; M=D
  printf("@%c\n", c);
  printf("D=A\n");
  printf("@t%d\n", i);
  printf("M=D\n");
}

// ex : t2 = t0+t1
void genOp2(int i, int i1, char op, int i2) {
  printf("# t%d=t%d%ct%d\n", i, i1, op, i2);
  // t0=t1+t2 轉成 @t1; D=M; @t2; D=D+M; @t0; M=D;
  printf("@t%d\n", i1);
  printf("D=M\n");
  printf("@t%d\n", i2);
  printf("D=D%cM\n", op);
  printf("@t%d\n", i);
  printf("M=D\n");
}

// F =  Number | '(' E ')'
int F() {
  int f;
  char c = ch();
  if (isdigit(c)) {
    next(); // skip c
    f = nextTemp();
    genOp1(f, c);
  } else if (c=='(') { // '(' E ')'
    next();
    f = E();
    assert(ch()==')');
    next();
  } else {
    error("F = (E) | Number fail!");
  }
  return f; 
}

// E = F ([+-] F)*
int E() {
  int i1 = F();
  while (isNext("+-")) {
    char op=next();
    int i2 = F();
    int i = nextTemp();
    genOp2(i, i1, op, i2);
    i1 = i;
  }
  return i1;
}

void parse(char *str) {
  tokens = str;
  E();
}

int main(int argc, char * argv[]) {
  printf("=== EBNF Grammar =====\n");
  printf("E=F ([+-] F)*\n");
  printf("F=Number | '(' E ')'\n");
  printf("==== parse:%s ========\n", argv[1]);
  parse(argv[1]);
}
```

* result
```
cxz1d@MSI MINGW64 ~/OneDrive/桌面/nohano1l/sp/03-compiler/01-exp0 (master)
$ ./exp0hack '3+5-4'
=== EBNF Grammar =====
E=F ([+-] F)*
F=Number | '(' E ')'
==== parse:3+5-4 ========
# t0=3
@3
D=A
@t0
M=D
# t1=5
@5
D=A
@t1
M=D
# t2=t0+t1
@t0
D=M
@t1
D=D+M
@t2
M=D
# t3=4
@4
D=A
@t3
M=D
# t4=t2-t3
@t2
D=M
@t3
D=D-M
@t4
M=D
```

### exp0var.c

* 程式碼
```
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

int tokenIdx = 0;
char *tokens;

int E();
int F();

void error(char *msg) {
  printf("%s", msg);
  assert(0);
}

char ch() {
  char c = tokens[tokenIdx];
  return c;
}

char next() {
  char c = ch();
  tokenIdx++;
  return c;
}

int isNext(char *set) {
  char c = ch();
  return (c!='\0' && strchr(set, c)!=NULL);
}

int nextTemp() {
  static int tempIdx = 0;
  return tempIdx++;
}

void genOp1(int i, char c) {
  printf("# t%d=%c\n", i, c);
  // t1=3 轉成 @3; D=A; @t1; M=D
  // t1=x 轉成 @x; D=M; @t1; M=D
  printf("@%c\n", c);
  char AM = (isdigit(c)) ? 'A':'M';
  printf("D=%c\n", AM);
  printf("@t%d\n", i);
  printf("M=D\n");
}

void genOp2(int i, int i1, char op, int i2) {
  printf("# t%d=t%d%ct%d\n", i, i1, op, i2);
  // t0=t1+t2 轉成 @t1; D=M; @t2; D=D+M; @t0; M=D;
  printf("@t%d\n", i1);
  printf("D=M\n");
  printf("@t%d\n", i2);
  printf("D=D%cM\n", op);
  printf("@t%d\n", i);
  printf("M=D\n");
}

// F =  Number | '(' E ')'
int F() {
  int f;
  char c = ch();
  if (isdigit(c) || (c>='a'&&c<='z')) {
    next(); // skip c
    f = nextTemp();
    genOp1(f, c);
  } else if (c=='(') { // '(' E ')'
    next();
    f = E();
    assert(ch()==')');
    next();
  } else {
    error("F = (E) | Number fail!");
  }
  return f; 
}

// E = F ([+-] F)*
int E() {
  int i1 = F();
  while (isNext("+-")) {
    char op=next();
    int i2 = F();
    int i = nextTemp();
    genOp2(i, i1, op, i2);
    i1 = i;
  }
  return i1;
}

void parse(char *str) {
  tokens = str;
  E();
}

int main(int argc, char * argv[]) {
  printf("=== EBNF Grammar =====\n");
  printf("E=F ([+-] F)*\n");
  printf("F=Number | '(' E ')'\n");
  printf("==== parse:%s ========\n", argv[1]);
  parse(argv[1]);
}
```

* result
```
cxz1d@MSI MINGW64 ~/OneDrive/桌面/nohano1l/sp/03-compiler/01-exp0 (master)
$ ./exp0var 'x+5-y'
=== EBNF Grammar =====
E=F ([+-] F)*
F=Number | '(' E ')'
==== parse:x+5-y ========
# t0=x
@x
D=M
@t0
M=D
# t1=5
@5
D=A
@t1
M=D
# t2=t0+t1
@t0
D=M
@t1
D=D+M
@t2
M=D
# t3=y
@y
D=M
@t3
M=D
# t4=t2-t3
@t2
D=M
@t3
D=D-M
@t4
M=D
```