# 📖第十二周筆記

## fork

[01-hello/fork2.c](https://github.com/nohano1l/sp109b/blob/main/note/week12/fork2-1.c)

[02-child/fork2.c](https://github.com/nohano1l/sp109b/blob/main/note/week12/fork2-2.c)

![](https://nohano1l.github.io/sp109b/note/week12/picture/1.png)

以02-child的fork2為例，74550(getpid)fork出另外一個父行程74551，在各自fork出子行程74552、74553

## execvp

[execvp1.c](https://github.com/nohano1l/sp109b/blob/main/note/week12/execvp1.c)

[system1.c](https://github.com/nohano1l/sp109b/blob/main/note/week12/system1.c)

[mysystem1.c](https://github.com/nohano1l/sp109b/blob/main/note/week12/mysystem1.c)

![](https://nohano1l.github.io/sp109b/note/week12/picture/2.png)

## zombie

![](https://nohano1l.github.io/sp109b/note/week12/picture/3.png)

## echo

[echo1.c](https://github.com/nohano1l/sp109b/blob/main/note/week12/echo1.c)

[fecho1.c](https://github.com/nohano1l/sp109b/blob/main/note/week12/fecho1.c)

![](https://nohano1l.github.io/sp109b/note/week12/picture/4.png)

* gets可能會造成[緩衝區溢位](https://zh.wikipedia.org/wiki/%E7%BC%93%E5%86%B2%E5%8C%BA%E6%BA%A2%E5%87%BA?fbclid=IwAR0AMd9Obb24-ykQNm7KC_rF3BNLOrYBOZkZ8q7SQusNeaeuqh-Ck1Exi9M)，建議使用[fget](http://tw.gitbook.net/c_standard_library/c_function_fgets.html)

## myshell

![](https://nohano1l.github.io/sp109b/note/week12/picture/5.png)