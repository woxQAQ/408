#include<stdlib.h>
#define MAXVERTEXNUM 100
typedef struct{
    char vex[MAXVERTEXNUM];
    int Edge[MAXVERTEXNUM][MAXVERTEXNUM];
    int vexnum, arcnum;
}MGraph;//邻接矩阵表示图

typedef struct{
    char data;
    ArcNode* firstNode;
}vexNode;//邻接表-顶点节点

typedef struct ArcNode{
    int adjvex;
    struct ArcNode* next;
}ArcNode;//邻接表--边节点

typedef struct{
    vexNode vertices[MAXVERTEXNUM];
    int vexnum, arcnum;
}ALgraph;