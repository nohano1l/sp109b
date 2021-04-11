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
========== lex ==============
token=for
token=(
token=i
token==
token=0
token=;
token=i
token=<=
token=3
token=;
token=i
token=++
token=)
token={
token=a
token==
token=a
token=+
token=1
token=;
token=}
========== dump ==============
0:for
1:(
2:i
3:=
4:0
5:;
6:i
7:<=
8:3
9:;
10:i
11:++
12:)
13:{
14:a
15:=
16:a
17:+
18:1
19:;
20:}
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