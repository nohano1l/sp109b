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
### [genExp.c](https://github.com/nohano1l/sp109b/blob/main/note/week2/00-gen/genExp.c)

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

### [genEnglish.c](https://github.com/nohano1l/sp109b/blob/main/note/week2/00-gen/genEnglish.c)

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

### [exp0.c](https://github.com/nohano1l/sp109b/blob/main/note/week2/01-exp0/exp0.c)

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
### [exp0hack.c](https://github.com/nohano1l/sp109b/blob/main/note/week2/01-exp0/exp0hack.c)

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

### [exp0var.c](https://github.com/nohano1l/sp109b/blob/main/note/week2/01-exp0/exp0var.c)

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