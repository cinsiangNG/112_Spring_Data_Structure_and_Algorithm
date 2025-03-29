#include <stdio.h>
#include <stdlib.h>

int prime(int n){
	int i;
	for(i=2; i*i<=n; i++){
		if(n%i == 0)
			return 0;
	}
	return 1;
} 

int main(){
	int i;
	int sum = 0;
	for(i=2; i<=300; i++){
		if (prime(i)){
			sum += i;
		}
	}
	printf("The summation of the prime numbers between 2 and 300 is %d.\n", sum);
	return 0;
}
 
