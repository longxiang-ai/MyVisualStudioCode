#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 500

typedef int WeightType;
typedef int Vertex;
typedef int DisjSet[MaxVertexNum + 1];

/*图相关结构的定义*/
struct ENode
{
    Vertex V1, V2;
    WeightType Length;
    int lab;
};
typedef struct ENode *Edge; //边的结构定义

typedef struct AdjVNode *PAdjVNode;
struct AdjVNode
{
    Vertex AdjV;
    WeightType Length;
    PAdjVNode Next;
}; //邻接点的结构定义

typedef struct Vnode
{
    PAdjVNode FirstEdge;
} AdjList_1[MaxVertexNum + 1]; //邻接表1的结构定义

struct GNode
{
    int Nv;
    int Ne;
    AdjList_1 G;
};
typedef struct GNode *LGraph; //用邻接表实现的图的结构定义

void Initialize(DisjSet S, int size);
void Sort(Edge E, int num);
Vertex find(Vertex V, DisjSet S);
void SetUnion(DisjSet S, Vertex Uset, Vertex Vset);
int partition(Edge E, int left, int right);

void sort(Edge E, int left, int right)
{
    if (left < right)
    {
        int p = partition(E, left, right);
        sort(E, left, p);
        sort(E, p + 1, right);
    }
}

/*图相关函数声明*/
LGraph CreateGraph(int VertexNum);     //生成具有一定定点数的图
void InsertEdge(LGraph Graph, Edge E); //向图中插入边
void Kruskal(LGraph Graph, Edge E);

int main()
{
    int VertexNum;
    scanf("%d", &VertexNum); //读入顶点数
    LGraph Graph = CreateGraph(VertexNum);
    scanf("%d", &Graph->Ne); //读入边数
    struct ENode Ed[Graph->Ne];
    if (Graph->Ne != 0)
    {
        Edge E = (Edge)malloc(sizeof(struct ENode));
        for (int i = 0; i < Graph->Ne; i++)
        {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Length);
            Ed[i].V1 = E->V1;
            Ed[i].V2 = E->V2;
            Ed[i].Length = E->Length;
            Ed[i].lab = 0;
            InsertEdge(Graph, Ed);
        }
    }
    Kruskal(Graph, Ed);
    return 0;
}

LGraph CreateGraph(int VertexNum)
{
    /*创建一个顶点数为VertexNum的空图（没有边）并返回*/
    Vertex V;
    LGraph Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Ne = 0; //边数为0
    Graph->Nv = VertexNum;
    for (V = 1; V <= VertexNum; V++)
    {
        Graph->G[V].FirstEdge = NULL; //每一个顶点的邻接表为空
    }
    return Graph;
}

void InsertEdge(LGraph Graph, Edge E)
{
    PAdjVNode NewNode1 = (PAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode1->AdjV = E->V2;
    NewNode1->Length = E->Length;
    NewNode1->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode1;

    PAdjVNode NewNode2 = (PAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode2->AdjV = E->V1;
    NewNode2->Length = E->Length;
    NewNode2->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode2;
}

void Kruskal(LGraph Graph, Edge E)
{
    int Uset, Vset, i = 0, flag = 1;
    int WeightSum = 0;
    int EdgesAccepted = 0;
    DisjSet S;
    Initialize(S, Graph->Nv);
    sort(E, 0, Graph->Ne);
    while (i < Graph->Ne)
    {
        if (EdgesAccepted == Graph->Nv - 1 && E[i].lab == 0)
            break;
        for (int j = 1; j < Graph->Ne - i && E[i + j].Length == E[i].Length && E[i + j].lab == 0; j++)
        {
            Uset = find(E[i + j].V1, S);
            Vset = find(E[i + j].V2, S);
            if (Uset != Vset)
                E[i + j].lab = 1;
        }
        Uset = find(E[i].V1, S);
        Vset = find(E[i].V2, S);
        if (Uset != Vset)
        {
            WeightSum += E[i].Length;
            EdgesAccepted++;
            SetUnion(S, Uset, Vset);
        }
        else if (E[i].lab == 1)
        {
            flag++;
        }
        i++;
    }
    if (EdgesAccepted != Graph->Nv - 1)
    {
        printf("No MST\n");
        int num = 0;
        for (i = 1; i <= Graph->Nv; i++)
            if (S[i] == 0)
                num++;
        printf("%d", num);
    }
    else
    {
        printf("%d\n", WeightSum);
        if (flag != 1)
            printf("No");
        else
            printf("Yes");
    }
}

void Initialize(DisjSet S, int size)
{
    for (int i = size; i > 0; i--)
        S[i] = 0;
}

void Sort(Edge E, int num)
{
    for (int i = 0; i < num; i++)
        for (int j = num - 1; j > i; j--)
            if (E[j].Length < E[j - 1].Length)
            {
                struct ENode temp = E[j];
                E[j] = E[j - 1];
                E[j - 1] = temp;
            }
}

Vertex find(Vertex V, DisjSet S)
{
    if (S[V] <= 0)
        return V;
    else
        return S[V] = find(S[V], S);
}
void SetUnion(DisjSet S, Vertex Uset, Vertex Vset)
{
    S[Uset] = Vset;
}

int partition(Edge E, int left, int right)
{
    int i, j, x, t, p = left, q = right, flag = 1;
    for (i = left; i < right - 1; i++)
    {
        if (E[i].Length > E[i + 1].Length)
        {
            flag = 0;
            break;
        }
    }
    if (flag == 0)
        for (flag = 1, i = left; i < right - 1; i++)
        {
            if (E[i].Length < E[i + 1].Length)
            {
                flag = 0;
                break;
            }
        }
    if (flag != 0 && (right - left > 100))
        return (left + right) / 2;
    x = E[p].Length;
    i = p;
    j = q;
    while (1)
    {
        for (; i < q && E[i].Length < x; i++)
            ;
        for (; j > p && E[j].Length >= x; j--)
            ;
        if (i < j)
        {
            struct ENode temp = E[i];
            E[i] = E[j];
            E[j] = temp;
        }
        else
        {
            return j;
        }
    }
}
