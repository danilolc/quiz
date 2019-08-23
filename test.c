#include <stdio.h>

int main(){
	char c;
	FILE* arquivo;
	arquivo = fopen("/dev/ttyUSB1","r");
	while(1){
		c = fgetc(arquivo);
		if(c=='A' || c=='a') printf("%c",c);
	}
	return 0;
}
