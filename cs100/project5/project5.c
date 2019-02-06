#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Node{
	char* string;
	struct Node* next;
} Node;

Node* List = NULL;
//List->next = NULL;

void createList(Node* List, char newString[], Node* next){
	List->string = malloc(strlen(newString) + 1);
	strcpy(List->string, newString);
	List->next = next;
}

void addBack(Node* List, Node* newOne, Node* next){ 
	Node *tempNext = NULL;
	
	tempNext = List->next;
	List->next = newOne;
	newOne->next = tempNext;
}

void printNode(Node* List){
	printf("%s\n", List->string);
}

Node* getNext(Node* List){
	return List->next;	
}


//function to shift letters
int Swap(int a, char S[a], char T[a], int num){
int count = 0;

createList(List, S, NULL);

if (strcmp (S, T) == 0) return count;
else {
	




} 


return count;
}

int main(int argc, char* argv[]){
int i = 0, num = 0, a = 0, b = 0, count = 0;
a = strlen(argv[1]);
b = strlen(argv[2]);

char S[a];
char T[b];

num = argc - 3;
int C[num];

strcpy(S, argv[1]);
strcpy(T, argv[2]);

for (i = 3; i <= argc; i++){
	C[i-3] = atoi(argv[i]);
	}
for (i = 0; i < num; i++){
	count = Swap(a, S, T, C[i]);
}
if (count > 0){
	printf("%d\n", count);
		
	}
else{
	printf("No solution");
	}	

return 0;
}

