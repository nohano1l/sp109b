# 擴充if功能

* 用03b-compiler2的compiler.c,並參考while的寫法,加以修改

```
// if (E) STMT (else STMT)?
void IF() {
  int ifBegin = nextLabel();
  int ifMid = nextLabel();
  int ifEnd = nextLabel();
  emit("(L%d)\n", ifBegin);
  skip("if");
  skip("(");
  int e = E();
  emit("if not t%d goto L%d\n", e, ifMid);  //未滿足上一個式子，將跳到下一個條件式
  skip(")");
  STMT();
  emit("goto L%d\n", ifEnd);  //符合條件，執行完，離開if
  emit("(L%d)\n", ifMid);  //下一個條件式
  if (isNext("else")) {
    skip("else");
    STMT();
    emit("(L%d)\n", ifEnd);  //離開if
  }
}
```

* elif.c

```
if(a>5){
    t=1;
}
else if(a>3){
    t=2;
}
else {
    t=3;
}
```

* Run

```
cxz1d@MSI MINGW64 ~/OneDrive/桌面/nohano1l/sp/03-compiler/03b-compiler2 (master)
$ ./compiler 'test/elif.c'
if(a>5){
    t=1;
}
else if(a>3){
    t=2;
}
else {
    t=3;
}
`
`
`
============ parse =============
(L0)
t0 = a
t1 = 5
t2 = t0 > t1
if not t2 goto L1
t3 = 1
t = t3
goto L2
(L1)
(L3)
t4 = a
t5 = 3
t6 = t4 > t5
if not t6 goto L4
t7 = 2
t = t7
goto L5
(L4)
t8 = 3
t = t8
(L5)
(L2)
```