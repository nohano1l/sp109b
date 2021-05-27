#include <stdio.h>

int main() {
  char buf[] = "aaa bbb ccc ddd eee fff ggg";
  FILE *fp = popen("wc -w", "w");  //wc算字數 //-l：行；-w：詞；-c：字；//popen( ,"w")管線做寫入fwrite
  fwrite(buf, sizeof(buf), 1, fp);
  pclose(fp);
}
