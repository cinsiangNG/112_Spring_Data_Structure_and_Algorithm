#include <stdio.h>
#include <stdlib.h>
int gcd(int a, int b){
	int temp;
	while(b != 0){
		temp = b;
		b = a % b;
		a  = temp; 
	}
	return a;
}

int lcm(int a, int b){
	return (a * b / gcd(a, b));
}

int main(){
	int num1, num2;
	printf("*** 求兩整數的最大公因數（GCD）和最小公倍數（LCM） ***\n\n");
	printf("請輸入兩個正整數（用空格隔開）：");
	scanf("%d%d", &num1,&num2);
	
	if(num1 <= 0 || num2 <= 0){
		printf("錯誤，請輸入正確的正整數。\n");
		return 1;
	}
	int gcd_value = gcd(num1, num2);
	int lcm_value = lcm(num1, num2);
	int result = (gcd_value * gcd_value) + lcm_value;
	printf("\n計算結果\n");
	printf("%d , %d 的最大公因數(GCD)為 %d\n", num1, num2, gcd_value);
	printf("%d , %d 的最小公倍數(LCM)為 %d\n", num1, num2, lcm_value);
	printf("%d , %d 的最終結果為 %d\n", num1, num2, result);
	return 0;
}
