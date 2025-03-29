#include <stdlib.h>
#include <stdio.h>

int main(){
	int year;
	printf("The leap years between 1923 and 2023 :\n");
	for(year=1923; year<=2023; year++){
		if(year%4 == 0 && year%100 != 0 || year%400 == 0 || year%400 == 0){
			printf("%d\n", year);
		}
	}
	return 0;
} 
