#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "bst.h"

void display (BST *tree) {
	statisticsBST(tree, stdout);
	displayBST(tree, stdout);
	displayBSTdebug(tree, stdout);
	return;
}

void testFind (BST *tree, int value) {
	printf("Finding %d... Returned ", value);
	
	INTEGER *searchValue = newINTEGER(value);
	BSTNODE *node = findBST(tree, searchValue);

	if (node != 0) {
		displayINTEGER(getBSTNODEvalue(node), stdout);
		printf("\n");
	} else {
		printf("NULL\n");
	}

	freeINTEGER(searchValue);

	return;
}
void testDelete (BST *tree, int value){
	printf("Deleting %d... Returned ", value);
	
	INTEGER *searchValue = newINTEGER(value);
	BSTNODE *node = deleteBST(tree, searchValue);
	
	if (node != 0) {
		displayINTEGER(getBSTNODEvalue(node), stdout);
		printf("\n");
		freeBSTNODE(node, freeINTEGER);
	} else {
		printf("NULL (This is correct)\n");
	}

	display(tree);
	freeINTEGER(searchValue);

	return;
}

int main () {
	BSTNODE *node = 0;
	INTEGER *searchValue = 0;

	printf("Testing balanced tree:\n");
	BST *tree1 = newBST(displayINTEGER, compareINTEGER, 0, freeINTEGER);
	insertBST(tree1, newINTEGER(4));
	insertBST(tree1, newINTEGER(2));
	insertBST(tree1, newINTEGER(6));
	insertBST(tree1, newINTEGER(1));
	insertBST(tree1, newINTEGER(3));
	insertBST(tree1, newINTEGER(7));
	insertBST(tree1, newINTEGER(5));
	display(tree1);
	//printf("Finding 2... Returned ");
	testFind(tree1, 5);
	testFind(tree1, 2);
	testFind(tree1, 4);
	testDelete(tree1, 4);
	testDelete(tree1, 6);
	testDelete(tree1, 7);
	printf("\"Finding\" 420... Returning ");
	searchValue = newINTEGER(420); //Tests nonexistent values.
	node = findBST(tree1, searchValue);
	if (node != 0) {
		displayINTEGER(getBSTNODEvalue(node), stdout);
		printf("\n");
	} else {
		printf("NULL (This is correct)\n");
	}
	freeINTEGER(searchValue);
	searchValue = newINTEGER(420);
	printf("\"Deleting\" 420... Returned ");
	node = deleteBST(tree1, searchValue);
	if (node != 0) {
		displayINTEGER(getBSTNODEvalue(node), stdout);
		printf("\n");
	} else {
		printf("NULL (This is correct)\n");
	}
	display(tree1);
	freeINTEGER(searchValue);
	
	printf("\nTesting slightly skewed tree:\n");
	BST *tree2 = newBST(displayINTEGER, compareINTEGER, 0, freeINTEGER);	
	insertBST(tree2, newINTEGER(8));
	insertBST(tree2, newINTEGER(3));
	insertBST(tree2, newINTEGER(1));
	insertBST(tree2, newINTEGER(6));
	insertBST(tree2, newINTEGER(4));
	insertBST(tree2, newINTEGER(7));
	insertBST(tree2, newINTEGER(10));
	insertBST(tree2, newINTEGER(15));
	insertBST(tree2, newINTEGER(13));
	insertBST(tree2, newINTEGER(14));
	display(tree2);
	testDelete(tree2, 6);
	testDelete(tree2, 13);
	testDelete(tree2, 10);
	testDelete(tree2, 14);
	
	printf("\nTesting all left tree:\n");
	BST *tree3 = newBST(displayINTEGER, compareINTEGER, 0, freeINTEGER);
	insertBST(tree3, newINTEGER(9));
	insertBST(tree3, newINTEGER(8));
	insertBST(tree3, newINTEGER(7));
	insertBST(tree3, newINTEGER(6));
	insertBST(tree3, newINTEGER(5));
	insertBST(tree3, newINTEGER(4));
	insertBST(tree3, newINTEGER(3));
	insertBST(tree3, newINTEGER(2));
	insertBST(tree3, newINTEGER(1));
	display(tree3);	
	testDelete(tree3, 9);
	testDelete(tree3, 4);
	testDelete(tree3, 1);
	
	printf("\nTesting all right tree:\n");
	BST *tree4 = newBST(displayINTEGER, compareINTEGER, 0, freeINTEGER);
	insertBST(tree4, newINTEGER(1));
	insertBST(tree4, newINTEGER(2));
	insertBST(tree4, newINTEGER(3));
	insertBST(tree4, newINTEGER(4));
	insertBST(tree4, newINTEGER(5));
	insertBST(tree4, newINTEGER(6));
	insertBST(tree4, newINTEGER(7));
	insertBST(tree4, newINTEGER(8));
	insertBST(tree4, newINTEGER(9));
	display(tree4);	
	testDelete(tree4, 1);
	testDelete(tree4, 7);
	testDelete(tree4, 9);
	
	printf("\nTesting zig-zag tree:\n");
	BST *tree5 = newBST(displayINTEGER, compareINTEGER, 0, freeINTEGER);
	insertBST(tree5, newINTEGER(18));
	insertBST(tree5, newINTEGER(17));
	insertBST(tree5, newINTEGER(16));
	insertBST(tree5, newINTEGER(8));
	insertBST(tree5, newINTEGER(14));
	insertBST(tree5, newINTEGER(12));
	insertBST(tree5, newINTEGER(10));
	insertBST(tree5, newINTEGER(11));
	display(tree5);
	testDelete(tree5, 8);
	
	printf("\nTesting left skewed tree:\n");
	BST *tree6 = newBST(displayINTEGER, compareINTEGER, 0, freeINTEGER);
	insertBST(tree6, newINTEGER(7));
	insertBST(tree6, newINTEGER(6));
	insertBST(tree6, newINTEGER(5));
	insertBST(tree6, newINTEGER(4));
	insertBST(tree6, newINTEGER(3));
	insertBST(tree6, newINTEGER(2));
	insertBST(tree6, newINTEGER(1));
	insertBST(tree6, newINTEGER(8));
	display(tree6);
	testDelete(tree6, 7);
	testDelete(tree6, 2);
	testDelete(tree6, 1);
	
	printf("\nTesting right skewed tree:\n");
	BST *tree7 = newBST(displayINTEGER, compareINTEGER, 0, freeINTEGER);
	insertBST(tree7, newINTEGER(2));
	insertBST(tree7, newINTEGER(3));
	insertBST(tree7, newINTEGER(4));
	insertBST(tree7, newINTEGER(5));
	insertBST(tree7, newINTEGER(6));
	insertBST(tree7, newINTEGER(7));
	insertBST(tree7, newINTEGER(8));
	insertBST(tree7, newINTEGER(1));
	display(tree7);
	testDelete(tree7, 2);
	testDelete(tree7, 7);
	testDelete(tree7, 1);
	
	printf("\nTesting empty tree:\n");
	BST *tree8 = newBST(displayINTEGER, compareINTEGER, 0, freeINTEGER);
	display(tree8);
	
	printf("\nTesting tree with only root:\n");
	BST *tree9 = newBST(displayINTEGER, compareINTEGER, 0, freeINTEGER);
	insertBST(tree9, newINTEGER(1));
	display(tree9);
	testDelete(tree9, 1);
	
	printf("\nFreeing trees\n");
	freeBST(tree1);
	freeBST(tree2);
	freeBST(tree3);
	freeBST(tree4);
	freeBST(tree5);
	freeBST(tree6);
	freeBST(tree7);
	freeBST(tree8);
	freeBST(tree9);

	return 0;
}