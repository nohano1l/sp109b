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
