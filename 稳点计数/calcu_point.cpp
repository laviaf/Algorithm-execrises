# include <iostream>
# include <vector>
using namespace std;

typedef struct Graph_Edge  //使用邻接表存储图
{  
    Graph_Edge *next = NULL;  //邻边
    int adj_node = -1;         //邻接点
}Graph_Edge;

typedef struct SCC_Node{
    Graph_Edge* head = NULL;    //头节点
    int out_degree = 0;       //统计出度
}SCC_Node;

//查找边(point1, point2)是否已在图中
bool find_vec(int point1, int point2, Graph_Edge** Graph){
    Graph_Edge* temp = Graph[point1];
    while(temp->next!=NULL){
        if(temp->adj_node == point2){
            return true;
        }
        temp = temp->next;
    }
    return false;
}

//预先声明变量
int N;
int index;
int top;
int* DFN;
int* LOW;
int* SCC;
int* InStack;
int* Stack;
int ComponentNumber;

//使用Tarjan算法计算SCC
void Tarjan(int N, Graph_Edge** Graph, int node, vector<int>* Component){
    DFN[node] = LOW[node] = index++;
    InStack[node] = 1;
    Stack[++top]=node;

    Graph_Edge* temp = Graph[node];
    while(temp!=NULL && temp->adj_node!=-1){
        //当前节点未被搜索过
        if(DFN[temp->adj_node] == -1){
            Tarjan(N, Graph, temp->adj_node, Component);
            LOW[node] = min(LOW[node],LOW[temp->adj_node]);
        }
        else{
            //节点如果被搜索过，查看是否在栈中，如果在栈中可以更新最早次序
            if(InStack[temp->adj_node] == 1){
                LOW[node] = min(LOW[node],LOW[temp->adj_node]);
            }
        }
        temp = temp->next;
    }

    //DFS搜索到一强联通分量，出栈该强联通分量
    if(DFN[node]==LOW[node]){
        //代表形成强联通分量
        ComponentNumber++;
        int temp_node;
        do{
            temp_node = Stack[top--];
            InStack[temp_node] = 0;
            SCC[temp_node] = ComponentNumber;
            Component[ComponentNumber-1].push_back(temp_node); //便于后续查询
        }
        while(temp_node!=node);
    }
}

//缩图
void SCC_append_edge(vector<int>& Component_i, Graph_Edge** Graph, SCC_Node* SCC_Graph, int SCC_idx){
    for(int i=0;i<Component_i.size();i++){
        //连接当前SCC内节点相邻节点对应的SCC
        int node = Component_i[i]; //当前节点
        Graph_Edge* temp = Graph[node]; //邻边

        while(temp!=NULL && temp->adj_node!=-1){
            int SCC_adj = SCC[temp->adj_node]-1; //相邻节点对应的SCC
            if(SCC_adj == SCC_idx){
                //说明是SCC的自环
                temp = temp->next;
                continue;
            }

            Graph_Edge* new_edge = new Graph_Edge;
            new_edge->adj_node = SCC_adj;
            SCC_Graph[SCC_idx].out_degree+=1;  //增加出度

            if(SCC_Graph[SCC_idx].head == NULL){
                SCC_Graph->head = new_edge;
            }
            else{
                Graph_Edge* temp = SCC_Graph[SCC_idx].head;
                while(temp->next!=NULL){
                    temp = temp->next;
                }
                temp->next = new_edge;
            }
            temp = temp->next;
        }
    }
}

// 通过计算邻接矩阵获得可达矩阵，空间代价太大
// void calcu_reachable(Graph_Edge** Graph, bool* res, vector<int>& Component_i){
//     for(int i=0;i<Component_i.size();i++){
//         int node = Component_i[i];
//         Graph_Edge* temp = Graph[node];
//         while(temp!=NULL && temp->adj_node!=-1){
//             //当前节点
//             if(res[SCC[temp->adj_node]-1]==false){
//                 res[SCC[temp->adj_node]-1] = true;
//             }
//             temp = temp->next;
//         }
//     }
// }

int main(){
    int E;
    scanf("%d",&N);
    scanf("%d",&E);
    Graph_Edge** Graph = new Graph_Edge*[N];
    for(int i=0;i<N;i++){
        Graph[i] = new Graph_Edge;
        Graph[i]->adj_node = -1;  //初始化为-1，若没有邻接边则保持为-1
    }   
    //使用邻接表储存图
    for(int i=0;i<E;i++){
        //由于最终只需计算稳点数量，在构建图时，去除重边和自环
        int point1, point2;
        scanf("%d",&point1);
        scanf("%d",&point2);
        point1 -= 1;
        point2 -= 1;
        //去除自环
        if(point1==point2){
            continue;
        }
        //去除重边
        else if(find_vec(point1, point2, Graph)){
            continue;
        }
        else{
            if(Graph[point1]->adj_node == -1){
                Graph[point1]->adj_node = point2;
            }
            else{
                Graph_Edge* new_edge = new Graph_Edge;
                new_edge->adj_node = point2;
                Graph_Edge* temp = Graph[point1];
                while(temp->next!=NULL){
                    temp = temp->next;
                }
                temp->next = new_edge;
            }
        }
    }

    //初始化
    index = 0; //当前Tarjan算法经历的节点数
    top = -1; //栈顶
    ComponentNumber = 0; //强联通分量个数
    SCC = (int*)malloc(sizeof(int)*N); // 储存SCC结果
    DFN = (int*)malloc(sizeof(int)*N); //储存访问次序
    LOW = (int*)malloc(sizeof(int)*N); //储存最早次序
    InStack = (int*)calloc(N,sizeof(int)); //使用“栈”维护当前递归搜索节点，初始值为0
    Stack = (int*)malloc(sizeof(int)*N); //出栈时获取节点出栈顺序
    for(int i=0;i<N;i++){
        DFN[i] = -1;
    }

    //获取每个强联通分量中的节点，便于后续查询
    vector<int> Component[N];

    //使用Tarjan算法计算SCC
    for(int i=0;i<N;i++){
        if(DFN[i] == -1){
            Tarjan(N, Graph, i, Component);
        }
    }

    //缩图，得到SCC的有向无环图，只需统计出度为0的强联通分量
    SCC_Node* SCC_Graph = new SCC_Node[ComponentNumber];
    for(int i=0;i<ComponentNumber;i++){
        SCC_append_edge(Component[i],Graph,SCC_Graph,i);
    }

    int num_0_degree = 0; //统计出度为0的个数
    int idx_0_degree;  //记录最后一个出度为0的SCC
    for(int i=0;i<ComponentNumber;i++){
        if(SCC_Graph[i].out_degree==0){
            num_0_degree+=1;
            idx_0_degree=i;
        }
    }

    if(num_0_degree>1){
        cout<<0<<endl;
    }
    else{
        cout<<Component[idx_0_degree].size()<<endl;
    }

    // 占用空间过大
    // //已经得到了强联通分量的划分，求其邻接矩阵，再由邻接矩阵求可达矩阵
    // bool reachable[ComponentNumber][ComponentNumber] = {false};

    // for(int i=0;i<ComponentNumber;i++){
    //     calcu_reachable(Graph,reachable[i],Component[i]);
    //     reachable[i][i] = true; //自身是强联通的
    // }

    // //由邻接矩阵求可达矩阵
    // for(int i=0;i<ComponentNumber;i++){
    //     for(int j=0;j<ComponentNumber;j++){
    //         if(i==j){
    //             continue;
    //         }
    //         if(reachable[j][i] == true){
    //             for(int k=0;k<ComponentNumber;k++){
    //                 reachable[j][k] = reachable[j][k] + reachable[i][k];
    //             }
    //         }
    //     }
    // }

    // int res[ComponentNumber];
    // for(int i=0;i<ComponentNumber;i++){
    //     res[i] = 1;
    //     for(int j=0;j<ComponentNumber;j++){
    //         res[i]*=reachable[j][i];
    //     }
    // }

    // int sum = 0;
    // for(int i=0;i<ComponentNumber;i++){
    //    sum+=res[i]*Component[i].size();
    // }

    // printf("%d",sum);

    return 0;
}