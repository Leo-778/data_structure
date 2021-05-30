#define MAX_VERtEX_NUM 20                   //顶点的最大个数
#define VRType int                          //表示顶点之间的关系的变量类型
#define InfoType char                       //存储弧或者边额外信息的指针变量类型
#define VertexType int                      //图中顶点的数据类型
#define INFINITY  INT_MAX                   //最大值  无穷
typedef enum{DG,DN,UDG,UDN}GraphKind;       //枚举图的 4 种类型
typedef struct {
    VRType adj;                             //对于无权图，用 1 或 0 表示是否相邻；对于带权图，直接为权值。
    InfoType * info;                        //弧或边额外含有的信息指针
}ArcCell,AdjMatrix[MAX_VERtEX_NUM][MAX_VERtEX_NUM];

typedef struct {
    VertexType vexs[MAX_VERtEX_NUM];        //存储图中顶点数据
    AdjMatrix arcs;                         //二维数组，记录顶点之间的关系
    int vexnum,arcnum;                      //记录图的顶点数和弧（边）数
    GraphKind kind;                         //记录图的种类
}MGraph;

void visit(int v){

}

bool visited[MAX_VERtEX_NUM];

void InitQueue(LinkQueue &Q);
bool IsEmpty(LinkQueue Q);
bool DeQueue(LinkQueue &Q, BiTree &t);
void EnQueue(LinkQueue &Q, BiTree t);

void BFS(MGraph G,int V){
    visit(V);
    visited[V]=true;
    EnQueue(Q,V);
    while(!IsEmpty(Q)){
        DeQueue(Q, V);
        for (w=FirstNeighbor(G,V); w>0; w=NextNeighbor(G,V,w)){
            if (!visited[w]){
                visit(w);
                visited[w] = true;
                EnQueue(Q, V);
            }
        }
    }
}

void BFSTraverse(MGraph G){
    for (int i = 0; i < G.vexnum; ++i)
        visited[i] = false;
    InitQueue(Q);
    for (int i = 0; i < G.vexnum; ++i)
        if(!visited[i])
            BFS(G, i);
}

bool visited[MAX_VERTEX_NUM];    //访问标记数组
void DFS(MGraph G,int V){
    visit(V);                    //访问初始顶点v
    visited[V]=true;             //对v作已访问标记
    while(!IsEmpty(Q)){
        for (w=FirstNeighbor(G,V); w>0; w=NextNeighbor(G,V,w)){//检测v所有邻接点
            if (!visited[w]){           //w为v的尚未访问的临界顶点
                DFS(G,w);
            }
        }
    }
}
void DFSTraverse(MGraph G){      
    for (int i = 0; i < G.vexnum; ++i)
        visited[i] = false;      //访问标记数组初始化
    for (int i = 0; i < G.vexnum; ++i)   //从0号顶点开始遍历
        if(!visited[i])              //对每个连通分量调用依次BFS
            BFS(G, i);               //vi未访问过，从vi开始BFS
}