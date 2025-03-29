#include<stdlib.h>
#include<stdio.h>

#define N 12
char A[6]={'v','i','r','u','s','\0'};
char B[5]={'C','o','r','o','n','a','\0'};
char C[6];
char Test1[12];
char Test2[6]={'d','r','i','n','k','\0'};
char CQData[12];

int f = N - 1;
int r = N - 1;

int Strlen(char str[]){
	int num=0, i;
	for(i = 0; str[i] != '\0'; i++){
		num++;
	} 
	return num;
}

void ArraytoUpper(char str[]){
	int i, len;
	len = Strlen(str);
	for(i=0; i < len; i++){
		if(str[i] >= 'a' && str[i] <= 'z'){
			str[i] -= 32;
		}
	}
}

void Strcopy(char dest[], char source[]){
	int i, len;
	len = Strlen(source);
	for(i=0; i<len; i++){
		dest[i] = source[i];
	}
	dest[i] = '\0';
}

void Cat(char str1[],char str2[],char dest[]){
	int i, len1, len2;
	len1 = Strlen(str1);
	len2 = Strlen(str2);
	for(i=0; i<len1; i++){
		dest[i] = str1[i];
	}
	for(i=len1; i<len1+len2; i++){
		dest[i] = str2[i-len1];
	}
	dest[len1+len2] = '\0';
}

void CQAdd(char que[],char temp){
	int Size = (N-f+r) % N;
	if(Size == N - 1){
		printf("FullQueue\n");
	}
	else{
		r = (r+1) % N;
		que[r] = temp;
	}
} 

char CQDel(char que[]){
	if(f == r){
		printf("EmptyQueue\n");
	}
	else{
		f = (f+1) % N;
		return que[f];
	}
}

void PrintCQArray(char que[]){
	int i;
	if (r == f){
        printf("EmptyQueue\n");
    }
	if(f<r){
		for(i=f+1; i<=r; i++){
			printf("%c", que[i]);
		}
	}
	else{
		for(i=f+1; i<N; i++){
			printf("%c", que[i]);
		}
		for(i=0; i<=r; i++){
			printf("%c", que[i]);
		}
	}
	printf("\n");
}

int main()
{
	int i;
	char x;
	
	ArraytoUpper(A);
	Strcopy(C,A);
	Cat(C,B,Test1);
	ArraytoUpper(Test2);
	
	for(i=0;i<11;i++)
	{
		CQAdd(CQData,Test1[i]);
		PrintCQArray(CQData);
	}

	for(i=0;i<5;i++)
	{
		x=CQDel(CQData);
		printf("%c is deleted!\n",x);		
	}

	for(i=0;i<5;i++)
	{
		CQAdd(CQData,Test2[i]);
		PrintCQArray(CQData);
	}	
	return 0;
}
