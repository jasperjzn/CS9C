#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSTRLEN 80
#define MAXNUMQS 32

typedef char **TreeType;
typedef int PositionType;

/*
 * Function prototypes.
 */
TreeType InitTree ( );
void PrintTree (TreeType tree);
PositionType Top (TreeType tree);
bool IsLeaf (TreeType tree, PositionType pos);
bool Answer (char *question);
char *Question (TreeType tree, PositionType pos);
char *Guess (TreeType tree, PositionType pos);
PositionType YesNode (TreeType tree, PositionType pos);
PositionType NoNode (TreeType tree, PositionType pos);
void ReplaceNode (TreeType tree, PositionType pos, char *newA, char *newQ);
void GetNewInfo (TreeType tree, PositionType pos, char **newA, char **newQ);

/*
 *  Play the "animal" game, in which the program attempts to guess an animal
 *  that the user is thinking of by asking yes or no questions. Eventually,
 *  the program either will guess the user's animal or run out of questions
 *  to ask. In the latter case, the program will ask the user to provide a
 *  yes-or-no question that would distinguish between the user's animal and
 *  the program's best guess.
 *  The data structure of questions and guesses is essentially a binary tree,
 *  with each internal node having a "yes" branch and a "no" branch. Leaves
 *  of the tree represent animals to be guessed by the program. If the program
 *  fails to guess the user's animal, it replaces one of the leaves of the tree
 *  by a node containing the new question, whose children are the program's
 *  best guess and the animal provided by the user.
 *  The structure of the program is simple. It initializes the question/guess
 *  data structure, then plays games as long as the user is interested. In each
 *  game, the program starts at the top of the tree (the root) and progresses 
 *  toward the bottom (the leaves) depending on the user's responses. Once it
 *  reaches a leaf, it either has won or lost, and handles the situation as
 *  described above.
 */
int main ( ) {
	TreeType tree;
	PositionType pos;
	char *newQuestion, *newAnswer;
	tree = InitTree ( );
	printf("%s", "Think of an animal. I will try to guess what it is.\n"
	"Please answer my questions with yes or no.\n");
    PrintTree(tree);

	while (true) {
		pos = Top (tree);
		while (!IsLeaf (tree, pos)) {
			pos = Answer (Question (tree, pos))? 
				YesNode (tree, pos): NoNode (tree, pos);
		}
		if (Answer (Guess (tree, pos))) {
			printf ("I got it right!\n");
		} else {
			GetNewInfo (tree, pos, &newAnswer, &newQuestion);
			ReplaceNode (tree, pos, newAnswer, newQuestion);
            PrintTree(tree);
		}
		if (!Answer ("Want to play again? ")) {
			return 0;
		}
	}
}

/*
 *	Return an animal tree.
 */
TreeType InitTree ( ) {
    /* Your code goes here -- delete this line */
    TreeType tree;
    tree = (TreeType)malloc(MAXNUMQS * sizeof(TreeType));
    for (int i=0; i<MAXNUMQS; i++){
    	tree[i] = (char *) malloc(MAXSTRLEN * sizeof(char));
    	strcpy(tree[i], "\0");
    }
    strcpy(tree[0], "Is it funny?");
    strcpy(tree[1], "Does it meow?");
    strcpy(tree[2], "Does it have tusks?");
    strcpy(tree[3], "a cat");
    strcpy(tree[4], "a dog");
    strcpy(tree[5], "Does it have big ears?");
    strcpy(tree[6], "an alligator");
    strcpy(tree[11], "an elephant");
    strcpy(tree[12], "a rhinoceros");
    return tree;
}

/*
 *	Print an animal tree (useful for debugging).
 */
void PrintTree (TreeType tree) {
    for (int i=0; i<MAXNUMQS; i++){
        printf("%d: %s\n",i ,tree[i]);
    }
}

/*
 *	Return the position of the "top" node in the animal tree.
 */
PositionType Top (TreeType tree) {
    return 0;
}

/*
 *	Return true exactly when pos is a "leaf" of the animal tree, that is,
 *	when the string stored at pos is a guess rather than a question.
 */
bool IsLeaf (TreeType tree, PositionType pos) {
    return ((strlen(tree[2*pos+1]) == 0) && (strlen(tree[2*pos+2]) == 0))? true: false;
}

/*
 *	Print the given question, read the user's answer; return true 
 *	if the answer supplied starts with"y", false otherwise.
 */
bool Answer (char *question) {
    char *str = (char *) malloc(MAXSTRLEN * sizeof(char));
    printf("%s\n", question);
    fgets(str, MAXSTRLEN, stdin);

   if(strncmp(str, "y", 1) == 0) {
        return true;
    }
    return false;
}

/*
 *	Form a question out of the string stored at position pos in the given
 *	animal tree, and return the string that contains the question.
 */
char *Question (TreeType tree, PositionType pos) {
    return tree[pos];
}

/*
 *	Form a guess out of the string stored at position pos in the given
 *	animal tree, and return the string that contains the guess. 
 *	(IsLeaf(tree, pos) must be true.)
 */
char *Guess (TreeType tree, PositionType pos) {
    char * animal = (char *)malloc(MAXSTRLEN * sizeof(char));
    strcpy(animal, "Is it ");
    strcat(animal, tree[pos]);
    strcat(animal, "?");
    return animal;
}


 /*	Return the position of the node that corresponds to a "yes" answer
 *	to the question stored at position pos in the animal tree.
 */
 
PositionType YesNode (TreeType tree, PositionType pos) {
    return 2*pos+1;
}

/*
 *	Return the position of the node that corresponds to a "no" answer
 *	to the question stored at position pos in the animal tree.
 */
PositionType NoNode (TreeType tree, PositionType pos) {
    return 2*pos+2;
}

/*
 *	Replace the node at position pos in the given animal tree by a node
 *	containing the given new question whose left child (down the tree in 
 *	the "yes" direction) contains the string stored at position pos, and 
 *	whose right child contains the new answer newA. Example:
before replacement
after replacement


 *	It's ok to copy the guess from the old node into the new node, and
 *	to copy the new question into the guess node.
 */
void ReplaceNode (TreeType tree, PositionType pos, char *newA, char *newQ) {
    char *tempString = malloc(MAXSTRLEN * sizeof(char));
    strcpy(tempString, tree[pos]);
    strcpy(tree[pos], newQ);
    strcpy(tree[2*pos+1], tempString);
    strcpy(tree[2*pos+2], newA);
}

/*
 *	Admit that you guessed wrong, ask the player what animal he/she was 
 *	thinking of, and return this in *newA.  Also ask for a question that 
 *	would be answered "yes" for what you guessed and "no" for what the 
 *	player was thinking of, and return this in *newQ.  (The node with
 *	your guess is at position pos in the tree.)
 */
void GetNewInfo (TreeType tree, PositionType pos, char **newA, char **newQ) {
    char* tempString = malloc(MAXSTRLEN * sizeof(char));
    char* str = malloc(MAXSTRLEN * sizeof(char));
    printf("%s\n", "I give up. What is it?");
    *newA = malloc(MAXSTRLEN * sizeof(char));
    fgets(*newA, MAXSTRLEN, stdin);
    tempString = *newA;
    tempString[strlen(tempString) - 1] = '\0';
    printf("%s %s %s %s %s\n", "Provide a question whose answer is yes for" ,tree[pos], "and no for", *newA, ".");
    *newQ = malloc(MAXSTRLEN * sizeof(char));
    fgets(*newQ, MAXSTRLEN, stdin);
    tempString = *newQ;
    tempString[strlen(tempString) - 1] = '\0';
}




