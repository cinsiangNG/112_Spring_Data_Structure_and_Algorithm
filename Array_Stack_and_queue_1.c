#include <stdio.h>
#include <stdlib.h>

double fib(int n){
	if(n == 0){
		return 0;
	}
	else if(n == 1){
		return 1;
	}
	else if(n >= 2){
		return fib(n-1) + fib(n-2);
	}
}

int main(){	
	printf("fib(6)/fib(5) = %.6f\n", fib(6)/fib(5));
	printf("fib(9)/fib(8) = %.6f\n", fib(9)/fib(8));
	printf("fib(12)/fib(11) = %.6f\n", fib(12)/fib(11));
	return 0;
}
