#include<stdio.h>
#include<stdlib.h>

char AAindex[22]="GAVLISTCMPFYWKRHDNEQX";

int BLOSUM62[21][21]={{ 6, 0,-3,-4,-4, 0,-2,-3,-3,-2,-3,-3,-2,-2,-2,-2,-1, 0,-2,-2,-1 }, //G
 		    		  { 0, 4, 0,-1,-1, 1, 0, 0,-1,-1,-2,-2,-3,-1,-1,-2,-2,-2,-1,-1,-1 }, //A
 					  {-3, 0, 4, 1, 3,-2, 0,-1, 1,-2,-1,-1,-3,-2,-3,-3,-3,-3,-2,-2,-1 }, //V
 					  {-4,-1, 1, 4, 2,-2,-1,-1, 2,-3, 0,-1,-2,-2,-2,-3,-4,-3,-3,-2,-1 }, //L
 					  {-4,-1, 3, 2, 4,-2,-1,-1, 1,-3, 0,-1,-3,-3,-3,-3,-3,-3,-3,-3,-1 }, //I
 					  { 0, 1,-2,-2,-2, 4, 1,-1,-1,-1,-2,-2,-3, 0,-1,-1, 0, 1, 0, 0,-1 }, //S
 					  {-2, 0, 0,-1,-1, 1, 5,-1,-1,-1,-2,-2,-2,-1,-1,-2,-1, 0,-1,-1,-1 }, //T
 				      {-3, 0,-1,-1,-1,-1,-1, 9,-1,-3,-2,-2,-2,-3,-3,-3,-3,-3,-4,-3,-1 }, //C
 				      {-3,-1, 1, 2, 1,-1,-1,-1, 5,-2, 0,-1,-1,-1,-1,-2,-3,-2,-2, 0,-1 }, //M
 				      {-2,-1,-2,-3,-3,-1,-1,-3,-2, 7,-4,-3,-4,-1,-2,-2,-1,-2,-1,-1,-1 }, //P
 				      {-3,-2,-1, 0, 0,-2,-2,-2, 0,-4, 6, 3, 1,-3,-3,-1,-3,-3,-3,-3,-1 }, //F
 				      {-3,-2,-1,-1,-1,-2,-2,-2,-1,-3, 3, 7, 2,-2,-2, 2,-3,-2,-2,-1,-1 }, //Y
 				      {-2,-3,-3,-2,-3,-3,-2,-2,-1,-4, 1, 2,11,-3,-3,-2,-4,-4,-3,-2,-1 }, //W
 		 		      {-2,-1,-2,-2,-3, 0,-1,-3,-1,-1,-3,-2,-3, 5, 2,-1,-1, 0, 1, 1,-1 }, //K
 		 		      {-2,-1,-3,-2,-3,-1,-1,-3,-1,-2,-3,-2,-3, 2, 5, 0,-2, 0, 0, 1,-1 }, //R
 				      {-2,-2,-3,-3,-3,-1,-2,-3,-2,-2,-1, 2,-2,-1, 0, 8,-1, 1, 0, 0,-1 }, //H
					  {-1,-2,-3,-4,-3, 0,-1,-3,-3,-1,-3,-3,-4,-1,-2,-1, 6, 1, 2, 0,-1 }, //D
 		 		      { 0,-2,-3,-3,-3, 1, 0,-3,-2,-2,-3,-2,-4, 0, 0, 1, 1, 6, 0, 0,-1 }, //N
 		    		  {-2,-1,-2,-3,-3, 0,-1,-4,-2,-1,-3,-2,-3, 1, 0, 0, 2, 0, 5, 2,-1 }, //E
 		      		  {-2,-1,-2,-2,-3, 0,-1,-3, 0,-1,-3,-1,-2, 1, 1, 0, 0, 0, 2, 5,-1 }, //Q
 				      {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 }};//X

char S1[21]="GIVEQCCAGVCSLYQLENYCN";
char S2[21]="GIVERCCKKSCDMKALREYCS";

int Score[22][22];
int Path[22][22];
int OGap = -11;
int EGap = -1;
int length1 = 0;
int length2 = 0;

int SearchAAindex(char x){
	int i;
	for(i=0; i<=21; i++){
		if (AAindex[i] == x){
			return i;
		}
	}
	return -1;
}
int length(char matrix[]){
	int i;
	int num = 0;
	for(i=0; matrix[i] != '\0'; i++){
		num++;
	} 
	return num;
}

void FillMatrix(){
	int i, j;
	int a, b, c, m, n;
	length1 = length(S1);
	length2 = length(S2);
	
	Score[0][0] = 0;
	Path [0][0] = 0;
	for(i=1;i<=length1;i++){ // Matrix initialization
		Score[i][0] = OGap + (i-1) * EGap;
		Path[i][0] = 0;
	}
	for(j=1;j<=length2;j++){
		Score[0][j] = OGap + (j-1) * EGap;
		Path[0][j] = 1;
	}
	for(i=1;i<=length1;i++){
		for(j=1;j<=length2;j++){
			if(Path[i-1][j] != 0){
				a = Score[i-1][j] + OGap;
			}
			else{
				a = Score[i-1][j] + EGap;			
			}
			if(Path[i][j-1] != 1){
				b = Score[i][j-1] + OGap;	
			}
			else{
				b = Score[i][j-1] + EGap;	
			}
			
			m = SearchAAindex(S1[i-1]);
			n = SearchAAindex(S2[j-1]);
//			printf("%d %d\n", m, n); 
			c = Score[i-1][j-1] + BLOSUM62[m][n]; //leftup (-1 == from 0)
			
			if(c>=a){
				if(c>=b){
					Score[i][j] = c;
					Path[i][j] = 2;  // path 2 right down
				}
				else{
					Score[i][j] = b;
					Path[i][j] = 1;  // path 1 down 
				}
			} 
			else{
				if(a>=b){
					Score[i][j] = a;
					Path[i][j] = 0;  // path 0 right
 				}
				else{
					Score[i][j] = b;
					Path[i][j] = 1;
				}
			}
		}
	}
}

void PrintMatirx(){
	int i,j;
	length1 = length(S1);
	length2 = length(S2);
	for(j=0; j<length2 + 1; j++){
		for(i=0; i<length1 + 1; i++){
			printf("%3d", Score[i][j]);
		}
		printf("\n");
	}
}

void PrintSequence(){
	printf("S1: %s\n", S1);
	printf("S2: %s\n", S2);
	 
}

void TraceBack(){
	int i,j,k;
	length1 = length(S1);
	length2 = length(S2);
	i = length1 - 1;
	j = length2 - 1;
	while((i!=0)||(j!=0)){
		if(Path[i][j] == 2){
			i--;              // left up   
			j--;              
		}
		else if(Path[i][j] == 1){
			for(k=length1; k>i; k--){  // or k=length2 
				S1[k] = S1[k-1];
			}
			S1[i] = '-';
			length1++;
			S1[length1] = '\0';
			j--;              // up
		}
		else{
			for(k=length2; k>j; k--){  // or k=length2 
				S2[k] = S2[k-1];
			}
			S2[j] = '-';
			length2++;
			S2[length2] = '\0';
			i--;              // left
		}
	}
}

int main()
{
	PrintSequence();
	FillMatrix();
	PrintMatirx();
	printf("\nScoring of sequence alignment: %d\n", Score[length1][length2]);
	TraceBack();
	PrintSequence();
	return 0;
}

