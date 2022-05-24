#include "fibonacci_heap.h"
#include "fibonacci_heap.cpp"
#include<algorithm>
#include <stack>
#include <fstream>
#include <sstream>
#include <queue>
#include <iostream>
#include<algorithm>
using namespace std;

#define MAX_VNODE_NUM 200000
#define MAX_DISTANCE 1246382666
#define INF 10000000

typedef struct ArcNode  //弧
{  
    int next_airport;    //该弧所指向尾节点的位置，其实保存的就是数组的下标
    ArcNode *nextarc;  //指向下一条弧的指针
    int weight;        //权重
}ArcNode;

typedef struct VNode   //节点
{
    // int airport_id;
    ArcNode* firstarc;
}VNode,AdjList[MAX_VNODE_NUM];

typedef struct         //图
{
    AdjList vertices;
    int vexnum; //节点数 （=200000
    int arcnum; //边数 （=30000000
}ALGraph;

//初始化结点
void initALGraph(ALGraph* GPt,int vec_num)
{
    GPt->arcnum = 0;
    GPt->vexnum = vec_num;
    for(int i=0;i<vec_num;i++){
        GPt->vertices[i].firstarc = NULL;
    }
}

//增加图结点
void insertArc(ALGraph* GPt,int vhead,int vtail,int w)
{
    ArcNode* arcNodePt = new ArcNode;
    arcNodePt->nextarc = NULL;
    arcNodePt->next_airport = vtail;
    arcNodePt->weight = w;

    //将边添加至对应机场
    ArcNode* tailPt = GPt->vertices[vhead].firstarc;
    if(tailPt==NULL){
        GPt->vertices[vhead].firstarc = arcNodePt;
    }
    else{
        while(tailPt->nextarc!=NULL){
            tailPt = tailPt->nextarc;
        }
        tailPt->nextarc = arcNodePt;
    }
    GPt->arcnum ++;
}

//实现dijkstra算法，s为搜索起点，d为起点到其他点的最短距离，p表示节点是否已达
//heap在此代码中为0到其他节点最短距离搜索过程中，联通与非联通点间的可达距离堆
void Dijkstra(int s, int d[], int p[], FibHeap<int>* heap, ALGraph* G){     
    //获取最短距离
    int min_node[2];
    heap->extractMin(min_node);

    //该节点已达
    p[min_node[0]] = 1;

    //松弛操作
    //min_node[0]为当前新搜到的最短路径节点
    ArcNode* avaliable_node = G->vertices[min_node[0]].firstarc;
    while(avaliable_node != NULL){
        int temp_node = avaliable_node->next_airport;
        if(d[temp_node] > d[min_node[0]] + avaliable_node->weight){
            d[temp_node] = d[min_node[0]] + avaliable_node->weight;
            if(p[temp_node] == 0){
                //如果avaliable_node->weight大于temp_node，则不会更新
                heap->update(temp_node,avaliable_node->weight,1);
            }
        }
        avaliable_node = avaliable_node->nextarc;
    }
}

int main(){
    int d[MAX_VNODE_NUM]; //储存0到其他节点的最短距离
    int p[MAX_VNODE_NUM]; //表示节点是否已达
    d[0] = 0;
    for(int i=1;i<MAX_VNODE_NUM;i++){
        d[i] = MAX_DISTANCE;
        p[i] = 0;
    }

    cout << "load data" << endl;

    //构建图并进行初始化
    ALGraph* G = new ALGraph;
    initALGraph(G,MAX_VNODE_NUM);
    //读入文件
    ifstream in("graph_super.txt");
	string filename;
	string line;
    if(in) // 有该文件
	{
        getline (in, line);//第一行是节点数及边数
		while (getline (in, line)) // line中不包括每行的换行符
		{ 
            //储存最终分割而得字符串
            vector<string> res;
            string result;
            stringstream input(line);
            while(input>>result){
                res.push_back(result);
            }
            //插入节点
            insertArc(G,atoi(res[0].c_str()),atoi(res[1].c_str()),atoi(res[2].c_str()));
        }
    }

    cout << "initialize" << endl;


    //构建fibonacci堆并进行初始化
    FibHeap<int>* heap = new FibHeap<int>{};
    heap->insert(0,0);
    for(int i=1;i<MAX_VNODE_NUM;i++){
        heap->insert(MAX_DISTANCE,i); //最开始所有节点均不联通
    }

    cout << "calculate" << endl;

    for(int i=0;i<MAX_VNODE_NUM;i++){
        //使用dijkstra算法获取最短路径
        Dijkstra(0,d,p,heap,G);
    }
    
    //写入文件
    fstream outfile;
    outfile.open("./fibonacci_res.txt",ios::out);
    if(!outfile){
        cout<<"file can not open"<<endl;
        abort();
    }
    for(int i=0;i<200000;i++){
        outfile<< i << " " << d[i] << endl;
    }

    outfile.close();

    return 0;
}