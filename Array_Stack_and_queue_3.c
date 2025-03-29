#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

int top = -1;
char stack[MAX_SIZE];

void initialize(){
	top = -1;
}

bool isEmpty(){
	return top == -1;
}

void push(char value){
    if (top == MAX_SIZE - 1){
	    printf("Stack overflow!\n");
	    return;
    }
	stack[++top] = value;
}

char pop(){
    if (isEmpty()){
        printf("Stack underflow!\n");
        return '\0';
    }
	return stack[top--];
}

int priority(char op){
	switch(op){
		case '+':
		case '-':
			return 1;
		
		case '*':
		case '/':
		case '%':
			return 2;
			
		default:
			return 0;
	}
}

void InfixtoPostfix(char *infix, char *postfix){
	initialize();
	int i=0, j=0;
	
	while(infix[i]){
		if(infix[i] >= '0' && infix[i] <= '9'){
			postfix[j++] = infix[i++];
		}
		else if(infix[i] == ' '){
			infix[i++];
		}
		else{
			if(isEmpty() || priority(infix[i])> priority(stack[top])){
				push(infix[i++]);
			}
			else{
				postfix[j++] = pop();
			}
		}
	}
	while(!isEmpty()){
		postfix[j++] = pop();
	}
	postfix[j++] = '\0';
}

int PostfixExp(char *postfix){
	initialize();
	int i;
	for(i=0; postfix[i]; ++i){
		if(postfix[i] >= '0' && postfix[i] <= '9'){
			push(postfix[i]);
		}
		else{
			int operand2 = pop() - '0';
			int operand1 = pop() - '0';
			switch(postfix[i]){
				case '+':
					push((operand1 + operand2) + '0');
					break;
				case '-':
					push((operand1 - operand2) + '0');
					break;
				case '*':
					push((operand1 * operand2) + '0');
					break;
				case '/':
					push((operand1 / operand2) + '0');
					break;
				case '%':
					push((operand1 % operand2) + '0');
					break;
			}
		}
	}
	return pop() - '0';
}

int main(){
	char infix[] = "5*3-2+6/2-9%5+1";
	char postfix[MAX_SIZE];
	InfixtoPostfix(infix, postfix);
	printf("Postfix Expression: %s\n", postfix);
	int result = PostfixExp(postfix);
	printf("Result: %d\n", result);
	return 0;
}
