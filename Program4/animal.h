typedef struct treeStruct *TreeType;
typedef struct positionStruct *PositionType;

TreeType InitTree (char *file);
void WriteTree (TreeType tree, char *file);
void PrintTree (TreeType tree);
PositionType Top (TreeType tree);
boolean IsLeaf (TreeType tree, PositionType pos);
boolean Answer (char *q);
char *Question (TreeType tree, PositionType pos);
char *Guess (TreeType tree, PositionType pos);
PositionType YesNode (TreeType tree, PositionType pos);
PositionType NoNode (TreeType tree, PositionType pos);
void ReplaceNode (TreeType tree, PositionType pos, char *newA, char *newQ);
void GetNewInfo (TreeType tree, PositionType pos, char **newA, char **newQ);