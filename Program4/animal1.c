typedef int boolean;

#define MAXSTRLEN 80
#define MAXNUMQS 32

#include "animal.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct treeStruct {
    char *nodes[MAXNUMQS];
};

struct positionStruct {
    int nodeIndex;
};

/*s
 *  Return an animal tree.
 */
TreeType InitTree (char *file) {
    TreeType tree;
    tree = (TreeType)malloc(MAXNUMQS * MAXSTRLEN * sizeof(char));
    for (int i=0; i<MAXNUMQS; i++){
        tree->nodes[i] = (char *) malloc(MAXSTRLEN * sizeof(char));
        strcpy(tree->nodes[i], "\0");
    }
    FILE *f;
    f = fopen(file, "r");
    if (f == NULL) {
        tree->nodes[0] = "Is it furry?";
        tree->nodes[1] = "Does it meow?";
        tree->nodes[2] = "Does it have tusks?";
        tree->nodes[3] = "a cat";
        tree->nodes[4] = "a dog";
        tree->nodes[5] = "Does it have big ears";
        tree->nodes[6] = "an alligator";
        tree->nodes[11] = "an elephant";
        tree->nodes[12] = "a rhinoceros";    
    } else {
        for (int i=0; i < MAXNUMQS; i++) {
            char *eachline = (char*) malloc(MAXSTRLEN);
            fgets(eachline, MAXSTRLEN+1, f);
            eachline[strlen(eachline)-1] = 0;
            tree->nodes[i] = eachline;
        }
        fclose(f);
    }
    return tree;
}

/*
 *  Print an animal tree (useful for debugging).
 */
void PrintTree (TreeType tree) {
    int i;
    for (i=0; i < MAXNUMQS; i++) {
        if(tree->nodes[i] != NULL){
            printf("%d: %s\n", i, tree->nodes[i]);
        }
        else{
            printf("%d:\n", i);
        }
    }
}

/*
 *  Return the position of the "top" node in the animal tree.
 */
PositionType Top (TreeType tree) {
    PositionType pos = (PositionType)malloc(sizeof(PositionType));
    pos->nodeIndex = 0;
    return pos;
}

/*
 *  Return true exactly when pos is a "leaf" of the animal tree,
 *  that is, when the string stored at pos is a guess rather than
 *  a question.
 */
boolean IsLeaf (TreeType tree, PositionType pos) {
    /* Your code goes here -- delete this line */
    int po = pos->nodeIndex;
    if (strcmp(tree->nodes[2*po+1], "") == 0){
        if (strcmp(tree->nodes[2*po+2], "") == 0){
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
    return tree->nodes[pos->nodeIndex];
}

/*
 *  Form a guess out of the string stored at position pos in the given
 *  animal tree.  (IsLeaf(tree, pos) must be true.)
 */
char *Guess (TreeType tree, PositionType pos) {
    char * animal = (char *)malloc(MAXSTRLEN * sizeof(char));
    strcpy(animal, "Is it ");
    strcat(animal, tree->nodes[pos->nodeIndex]);
    strcat(animal, "?");
    return animal;
}

/*
 *  Return the position of the node that corresponds to a "yes" answer
 *  to the question stored at position pos in the animal tree.
 */
PositionType YesNode (TreeType tree, PositionType pos) {
    PositionType temp = (PositionType) malloc(sizeof(PositionType));
    temp->nodeIndex = (2 * (pos->nodeIndex)) + 1;
    return temp;
}

/*
 *  Return the position of the node that corresponds to a "no" answer
 *  to the question stored at position pos in the animal tree.
 */
PositionType NoNode (TreeType tree, PositionType pos) {
    PositionType temp = (PositionType) malloc(sizeof(PositionType));
    temp->nodeIndex = (2 * (pos->nodeIndex)) + 2;
    return temp;
}

/*
 *  Replace the node at position pos in the given animal tree by a node
 *  containing the given new question whose left child (down the tree in 
 *  the "yes" direction) contains the string stored at position pos, and 
 *  whose right child contains the new answer newA.
 */
void ReplaceNode (TreeType tree, PositionType pos, char *newA, char *newQ) {
    strcpy(tree->nodes[NoNode(tree, pos)->nodeIndex], newA);
    strcpy(tree->nodes[YesNode(tree,pos)->nodeIndex], tree->nodes[pos->nodeIndex]);
    strcpy(tree->nodes[pos->nodeIndex], newQ);
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
    printf("%s %s %s %s %s\n", "Provide a question whose answer is yes for" ,tree->nodes[pos->nodeIndex], "and no for", *newA, ".");
    *newQ = malloc(MAXSTRLEN * sizeof(char));
    fgets(*newQ, MAXSTRLEN, stdin);
    tempString = *newQ;
    tempString[strlen(tempString) - 1] = '\0';
}

void freeTree(TreeType tree){
    for(int i = 0; i < MAXNUMQS; i++){
        free(tree->nodes[i]);
    }
    free(tree);
}

/*
 *  write tree struct to temp.text
 */
void WriteTree(TreeType tree, char *file) {
    FILE *f;
    f = fopen(file, "w");
    int i;
    for (i=0; i < MAXNUMQS; i++) {
        if (tree->nodes[i] != NULL) {
            fputs(tree->nodes[i], f);
        }
        fputs("\n", f);
    }
    fclose(f);
    freeTree(tree);
}






