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
	printf("*** �������������򔵣�GCD������С��������LCM�� ***\n\n");
	printf("Ոݔ��ɂ����������ÿո���_����");
	scanf("%d%d", &num1,&num2);
	
	if(num1 <= 0 || num2 <= 0){
		printf("�e�`��Ոݔ�����_����������\n");
		return 1;
	}
	int gcd_value = gcd(num1, num2);
	int lcm_value = lcm(num1, num2);
	int result = (gcd_value * gcd_value) + lcm_value;
	printf("\nӋ��Y��\n");
	printf("%d , %d �������(GCD)�� %d\n", num1, num2, gcd_value);
	printf("%d , %d ����С������(LCM)�� %d\n", num1, num2, lcm_value);
	printf("%d , %d ����K�Y���� %d\n", num1, num2, result);
	return 0;
}
