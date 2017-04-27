typedef int boolean;

#define MAXSTRLEN 80
#define MAXNUMQS 32

#include "animal.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct treeStruct {
	char *string;
	struct treeStruct *left;
	struct treeStruct *right;
};

struct positionStruct {
	struct treeStruct* node;
};

TreeType helper (char *str) {
	TreeType tree = (TreeType) malloc(MAXNUMQS*sizeof(TreeType));
	tree->string = (char *) malloc(MAXSTRLEN*sizeof(char));
	strcpy(tree->string, str);
	tree->left = NULL;
	tree->right = NULL;
	return tree;
}

/*s
 *  Return an animal tree.
 */
TreeType InitTree (char *file) {
	TreeType top = helper("Is it furry?");
	top->left = helper("Does it meow?");
	top->right = helper("Does it have tusks?");
	(top->left)->left = helper("a cat");
	(top->left)->right = helper("a dog");
	(top->right)->left = helper("Does it have big ears?");
	(top->right)->right = helper("an alligator");
	((top->right)->left)->left = helper("an elephat");
	((top->right)->left)->right = helper("a rhinoceros");
	return top;
}

/*
 *  Print an animal tree (useful for debugging).
 */
void PrintTree (TreeType tree) {
	if (tree == NULL) {
		return;
	}
	printf("%s\n", tree->string);
	if (tree->left != NULL) {
		PrintTree(tree->left);
	}
	if(tree->right != NULL) {
		PrintTree(tree->right);
	}
}

/*
 *  Return the position of the "top" node in the animal tree.
 */
PositionType Top (TreeType tree) {
	PositionType pos = (PositionType) malloc(sizeof(PositionType));
	pos->node = tree;
	return pos;
}

/*
 *  Return true exactly when pos is a "leaf" of the animal tree,
 *  that is, when the string stored at pos is a guess rather than
 *  a question.
 */
boolean IsLeaf (TreeType tree, PositionType pos) {
	if (((pos->node)->left) == NULL){
		if (((pos->node)->left) == NULL){
			return 1;
		}
	}
	return 0;
}

/*
 *  Return true if the answer supplied by the user to the given question
 *  starts with 'y', false otherwise.
 */
boolean Answer (char *question) {
	char str[MAXSTRLEN];
    printf("%s\n", question);
    fgets(str, MAXSTRLEN, stdin);
    if(strncmp(str, "y", 1) == 0) {
        return 1;
    }
    return 0;
}

/*
 *  Form a question out of the string stored at position pos in the given
 *  animal tree.
 */
char *Question (TreeType tree, PositionType pos) {
	return (pos->node)->string;
}

/*
 *  Form a guess out of the string stored at position pos in the given
 *  animal tree.  (IsLeaf(tree, pos) must be true.)
 */
char *Guess (TreeType tree, PositionType pos) {
	char * animal = (char *)malloc(MAXSTRLEN * sizeof(char));
    strcpy(animal, "Is it ");
    strcat(animal, (pos->node)->string);
    strcat(animal, "?");
    return animal;
}

/*
 *  Return the position of the node that corresponds to a "yes" answer
 *  to the question stored at position pos in the animal tree.
 */
PositionType YesNode (TreeType tree, PositionType pos) {
	PositionType temp = (PositionType) malloc(sizeof(PositionType));
	temp->node = (pos->node)->left;
	return temp;
}

/*
 *  Return the position of the node that corresponds to a "no" answer
 *  to the question stored at position pos in the animal tree.
 */
PositionType NoNode (TreeType tree, PositionType pos) {
	PositionType temp = (PositionType) malloc(sizeof(PositionType));
	temp->node = (pos->node)->right;
	return temp;
}

/*
 *  Replace the node at position pos in the given animal tree by a node
 *  containing the given new question whose left child (down the tree in 
 *  the "yes" direction) contains the string stored at position pos, and 
 *  whose right child contains the new answer newA.
 */
void ReplaceNode (TreeType tree, PositionType pos, char *newA, char *newQ) {
	TreeType newRight = (TreeType) malloc(MAXNUMQS*sizeof(TreeType));
	newRight->string = newA;
	TreeType newLeft = (TreeType) malloc(MAXNUMQS*sizeof(TreeType));
	newLeft->string = pos->node->string;
	pos->node->string = newQ;
	pos->node->left = newLeft;
	pos->node->right = newRight;
}

/*
 *  Admit that you guessed wrong, ask the player what animal he/she was 
 *  thinking of, and return this in *newA.  Also ask for a question that 
 *  would be answered "yes" for what you guessed and "no" for what the 
 *  player was thinking of, and return this in *newQ.  (The node with
 *  your guess is at position pos in the tree.)
 */
void GetNewInfo (TreeType tree, PositionType pos, char **newA, char **newQ) {
	char* tempString = malloc(MAXSTRLEN * sizeof(char));
    char* str = malloc(MAXSTRLEN * sizeof(char));
    printf("%s\n", "I give up. What is it?");
    *newA = malloc(MAXSTRLEN * sizeof(char));
    fgets(*newA, MAXSTRLEN, stdin);
    tempString = *newA;
    tempString[strlen(tempString) - 1] = '\0';
    printf("%s %s %s %s %s\n", "Provide a question whose answer is yes for" , (pos->node)->string, "and no for", *newA, ".");
    *newQ = malloc(MAXSTRLEN * sizeof(char));
    fgets(*newQ, MAXSTRLEN, stdin);
    tempString = *newQ;
    tempString[strlen(tempString) - 1] = '\0';
}

void freeTree(TreeType tree){
	if(tree != NULL){
		freeTree(tree->left);
		freeTree(tree->right);
		free(tree->string);
		free(tree);
	}
}

void WriteTree(TreeType tree, char *file) {
	freeTree(tree);
}







