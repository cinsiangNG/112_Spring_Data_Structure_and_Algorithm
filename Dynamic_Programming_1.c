#include <stdio.h>
#define MAX_LENGTH 100

int price[MAX_LENGTH] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

int Max(int a, int b){
	return (a > b ? a : b);
}

int max_price(int length, int price[], int cut[]){
	int dp[length];
	dp[0] = 0;
	int i;
	for(i=1; i <= length; i++){
		int max_val = -1;
		int j;
		for(j=1; j <= i; j++){
			max_val = Max(max_val, price[j] + dp[i - j]);
			if(max_val == price[j] + dp[i - j]){
				cut[i] = j;
			}
		}
		dp[i] = max_val;
	}
	return dp[length];
}

void Printcut(int length, int cut[]){
	printf("The cutting plan: ");
	while(length > 0){
		printf("%d ", cut[length]);
		length -= cut[length];
	}
	printf("\n");
}

int main(){
	int length;
	int cut[MAX_LENGTH];
	while(1){
		printf("Please enter the length of the rod (from 0 to 99): ");
		scanf("%d", &length);
		if(length < 100 && length > 0){
			int max_val = max_price(length, price, cut);
			printf("Maximum price for rod of length: %d\n", max_val);
			Printcut(length, cut);
			printf("\n");
		}
		else{
			if(length == 0){
				printf("Invalid length entered. Please enter a length between 1 and 99.\n");
				break;
			} 
			printf("Invalid length entered. Please enter a length between 1 and 99.\n\n");
		}
	} 
	return 0;
}
