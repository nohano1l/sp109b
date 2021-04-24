# 第六周筆記

## gcc編譯流程

![](https://nohano1l.github.io/sp109b/note/week6/picture/1.jpg)

```
直接編譯連結，產生執行檔
$ gcc main.c sum.c -o run    //-o:指定輸出檔
$ gcc main.c sum.c           //輸出檔檔名為a.exe(Windows)、a.out(Mac)

產生組合語言(-S)
$ gcc -S main.c -o main.s

組譯後連結,產生執行檔
$ gcc main.c sum.s -o run

產生目的檔(-c)
$ gcc -c sum.c -o sum.o

連結目的檔,產生執行檔
$ gcc main.o sum.o -o run
```

連結時，會在連結器使用ar、ld

![](https://nohano1l.github.io/sp109b/note/week6/picture/2.jpg)

![](https://nohano1l.github.io/sp109b/note/week6/picture/3.jpg)

### 補充-權利區分
```
著作權(版權):作者終生+50年,須具有獨創性
專利:20年,須具有首創性(新穎、進步、可實行)
商標:10年(可續展),須具有識別性
```

## 堆疊段

* power2.c
```
#include <stdio.h>

int power2(int n){
    if(n==0){
        return 1;
    }
    return power2(n-1)*2;
}

int main(){
    int p=power2(3);
    printf("p=%d\n",p);
}
```

![](https://nohano1l.github.io/sp109b/note/week6/picture/1.png)

```
EBP(框架暫存器):指著目前函數的進入點
ESP(堆疊暫存器):指著目前堆疊的最後一個
```