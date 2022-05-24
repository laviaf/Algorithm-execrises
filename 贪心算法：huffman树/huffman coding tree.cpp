#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

typedef struct Tree_node  //树中节点
{  
    Tree_node *leftchild = NULL;  //左子节点
    Tree_node *rightchild = NULL; //右子节点
    Tree_node *parent = NULL; //双亲节点
    int weight;        //权重
    int depth = 0;
}Tree_node;

//定义优先队列的排序规则
struct cmp{ 
    bool operator()(Tree_node* a ,Tree_node* b ){ 
        return a->weight > b->weight;
    } 
}; 

//对树中每个节点增加深度
void increase_depth(Tree_node* node){
    if(node == NULL){
        return;
    }
    node->depth += 1;
    increase_depth(node->leftchild);
    increase_depth(node->rightchild);
}

Tree_node* huffman_coding(int* weight,int n){
    priority_queue<Tree_node*,vector<Tree_node*>,cmp> queue;
    //构建树中初始叶子节点，按节点从小到大顺序
    for(int i=n-1;i>=0;i--){
        Tree_node* node = new Tree_node;
        node->weight = weight[i];
        queue.push(node);
    }

    //最终vector中只剩余一个根节点
    while(queue.size() > 1){
        Tree_node* a = queue.top();
        queue.pop();
        Tree_node* b = queue.top();
        queue.pop();

        Tree_node* root = new Tree_node;
        root->weight = a->weight + b->weight;
        root->leftchild = a;
        root->rightchild = b;
        a->parent = root;
        b->parent = root;

        //对root的下层子节点增加路径深度
        increase_depth(a);
        increase_depth(b);

        queue.push(root);
    }

    Tree_node* root = queue.top();
    return root;
}

//对一haffman树求外部路径和
int sum_path(Tree_node* node){
    int temp_sum = 0;
    //两个子节点只要有任一为空则在haffman树中可说明为叶子结点
    if(node->leftchild == NULL){
        temp_sum = node->depth*node->weight;
        return temp_sum;
    }
    else{
        //计算其子节点的外部路径和
        temp_sum += sum_path(node->leftchild);
        temp_sum += sum_path(node->rightchild);
        return temp_sum;
    }
}

int main(){
    int n;
    scanf("%d",&n);
    int weight[n];
    for(int i=0;i<n;i++){
        scanf("%d",&weight[i]);
    }
    Tree_node* huffman_tree = huffman_coding(weight,n);
    int external_length = sum_path(huffman_tree);
    printf("%d", external_length);

    return 0;
}