# 擴充for功能

```
// F = (E) | Number | Id | Increase | Decrease
int F() {
  int f;
  if (isNext("(")) { // '(' E ')'
    next(); // (
    f = E();
    next(); // )
  } 
  else { // Number | Id | Increase | Decrease
    f = nextTemp();
    char *item = next();
    if(isNext("++")){
      emit("%s = %s + 1\n", item, item);  //%s 字串符
      next(); // )
    }
    else if(isNext("--")){
      emit("%s = %s - 1\n", item, item);
      next();
    }
    else{
      emit("t%d = %s\n", f, item);
    }
  }
  return f;
}

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
  F();
  skip(")");
  STMT();
  emit("goto L%d\n", forBegin);
  emit("(L%d)\n", forEnd);
}

// STMT = WHILE | IF | FOR | BLOCK | ASSIGN
void STMT() {
  if (isNext("while"))
    return WHILE();
  else if (isNext("if"))
    IF();
  else if (isNext("for"))
    FOR();
  else if (isNext("{"))
    BLOCK();
  else
    ASSIGN();
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
i = i + 1
t5 = a
t6 = 1
t7 = t5 + t6
a = t7
goto L0
(L1)
```

## (第五周)上次compiler for功能的改良

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