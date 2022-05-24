#include <iostream>
#include <stdlib.h>
#include "fibonacci_heap.h"

using namespace std;

//构造函数
template <typename T>
FibHeap<T>::FibHeap(){
    this->keyNum = 0;
    this->maxDegree = 0;
    this->min = NULL;
}

//析构函数
template <typename T>
FibHeap<T>::~FibHeap() 
{}

//将节点添加至根链表
template <typename T>
void FibHeap<T>::addNode(FibNode<T> *node){
    min -> left -> right = node;
    node -> left = min -> left;
    node -> right = min;
    min -> left = node;
    return;
}

//新建节点并插入
template <typename T>
void FibHeap<T>::insert(T key, T index){
    FibNode<T> *N = new FibNode<T>(key,index);
    if(keyNum == 0){
        //当前堆中无节点
        min = N;
        keyNum = 1;
        maxDegree = 1;
    }
    else{
        //将当前节点插入根节点链表中
        addNode(N);
        keyNum += 1;
        //更新根节点
        if(key < min->key){
            min = N;
        }
    }
}

//将y连接为x的子节点
template <typename T>
void FibHeap<T>::HeapLink(FibNode<T> *y, FibNode<T> *x){
    //将y添加至x
    if(x->child == NULL){
        //x的孩子指针指向链表的头结点
        x->child = y;
        y->parent = x;
        x->degree += 1;
        y->left = y;
        y->right = y;
    }
    else{
        FibNode<T> *child = x->child;
        while(child->right != child){
            child = child->right;
        }
        child->right = y;
        y->left = child;
        y->parent = x;
        x->degree += 1;
    }
}

//更新根链表
template <typename T>
void FibHeap<T>::consolidate(){
    if(min == NULL){
        return;
    }

    int degree = 2*log(this->keyNum)/log(2) + 1;

    //用于储存根链表
    FibNode<T>** merge = (FibNode<T>**)malloc(sizeof(FibHeap<T> *) *degree);//存疑
    for(int i=0;i<degree;i++){
        merge[i] = NULL;
    }
    
    //合并度相同的根节点
    FibNode<T> *temp = min;
    FibNode<T> *nextpoint = NULL;
    
    while(temp!=nextpoint){
        if(nextpoint != NULL){
            temp = nextpoint;
        }
        nextpoint = temp->right;

        //切断当前节点与根链表
        temp->left->right = temp->right;
        temp->right->left = temp->left;
        temp->left = temp;
        temp->right = temp;

        if(merge[temp->degree] == NULL){
            merge[temp->degree] = temp;
        }
        else{
            //用于判断是否有与当前节点度相同的节点
            FibNode<T> *compare_node = temp;
            //当有相同度的堆存在时，进行合并
            while(merge[compare_node->degree]!=NULL){
                //用于与当前节点合并
                FibNode<T> *merge_node = merge[compare_node->degree];
                if(merge_node->key > compare_node->key){
                    this->HeapLink(merge_node,compare_node);
                }
                else{
                    this->HeapLink(compare_node,merge_node);
                    compare_node = merge_node;
                }
                merge[compare_node->degree-1] = NULL;
            }
            merge[compare_node->degree] = compare_node;
        }
    }

    //将根节点连接为根链表
    min = NULL;
    for(int i=0;i<degree;i++){
        if(merge[i] != NULL){
            if(min == NULL){
                min = merge[i];
                min->left = min;
                min->right = min;
                maxDegree = i;
            }
            else{
                //将A[i]接入根链表
                min->left->right = merge[i];
                merge[i]->left = min->left;
                min->left = merge[i];
                merge[i]->right = min;
                //更新min指针
                if(merge[i]->key<min->key){
                    min = merge[i];
                }
                maxDegree = i;
            }
        }
    }
}

//删除最小节点
template <typename T>
void FibHeap<T>::removeMin(){
    if(min == NULL){
        //链表为空
        return;
    }

    //将min节点的子节点连接到根链表中
    FibNode<T> *child = NULL;
    FibNode<T> *temp = min->child; // 头结点
    while(temp != NULL){
        child = temp;
        //切断父节点与左右兄弟节点
        child->parent = NULL;
        // if(child->right == child){
        //     child->left->right = child->left;
        //     child->right->left = child->right;
        // }
        // else{
        //     child->left->right = child->right;
        //     child->right->left = child->left;
        // }
        if(child->right == child){
            temp = NULL;
        }
        else{
            temp = child->right;
        }
        //把节点接入根链表
        addNode(child);
    }

    // 删除min节点
    min->left->right = min->right;
    min->right->left = min->left;
    keyNum-=1;

    // temp = min;
    // delete temp; //存疑
    
    //当堆中无节点时，初始化堆
    if(keyNum == 0){
        maxDegree = 0;
        min = NULL;
        return;
    }

    //堆中有节点时，合并斐波那契堆
    min = min->right;
    consolidate();
    return;
}

//提取斐波那契堆中的min节点并删除
template <typename T>
void FibHeap<T>::extractMin(T* res){
    //若最小值不存在，触发异常
    if(min != NULL){
        res[0] = min->k_index;
        res[1] = min->key;
        removeMin();
        return;
    }
    printf("error! this heap does not contain any node.\n");
}

//级联剪枝
template <typename T>
void FibHeap<T>::casecadingCut(FibNode<T> *node){
    FibNode<T> *temp = node;
    while(temp != NULL){
        if(temp->parent != NULL){
            //说明temp不在根链表中
            //将当前节点从原位置取出，temp的父节点在后边处理
            if(temp->left == temp){
                //temp为头节点
                if(temp->right != temp){
                    temp->parent->child = temp->right;
                    temp->right->left = temp->right;
                    temp->right = temp;
                }
                else{
                    temp->parent->child = NULL;
                }
            }
            else if(temp->right == temp){ //非根链表做成了双向非循环链表
                temp->left->right = temp->left;
                temp->left = temp;
            }
            else{
                temp->left->right = temp->right;
                temp->right->left = temp->left;
            }

            //将当前节点接入根链表
            min->left->right = temp;
            temp->left = min->left;
            min->left = temp;
            temp->right = min;

            //维护最小值节点
            if(temp->key < min->key){
                min = temp;
            }
        }

        temp->marked = false;

        //处理temp的父节点
        if(temp->parent == NULL){
            temp = NULL;
        }
        else{
            if(temp->parent->marked == true){
                FibNode<T> *parent = temp->parent;
                temp->parent = NULL;
                temp = parent;
            }
            else{
                temp->parent->marked = true;
                temp->parent = NULL;
                temp = NULL;
            }
        }
    }
}

//将某节点值将至某值
template <typename T>
void FibHeap<T>::decreaseKey(FibNode<T> *node, T key){
    if(key >= node->key){
        printf("invalid value.");
        return;
    }

    node->key = key;
    casecadingCut(node);    
}

//将某节点值增至某值
template <typename T>
void FibHeap<T>::increaseKey(FibNode<T> *node, T key){
    if(node->key < key){
        printf("invalid value.");
        return;
    }

    node->key = key;
    while(node != NULL){
        //temp遍历当前node的子节点，交换node与其子节点中值最小的节点
        FibNode<T>* temp = node->child;
        FibNode<T>* exc = NULL;
        while(temp != NULL){
            if(temp->key < node->key){
                if(exc == NULL || temp->key < exc->key){
                    exc = temp;
                }
            }
            temp = temp->right;
        }

        if(exc != NULL){
            T k = node->key;
            node->key = exc->key;
            exc->key = k;
            T i = node->k_index;
            node->k_index = exc->k_index;
            exc->k_index = i;
            node = exc;
        }
        else{
            //当exc为空，说明没有子节点或无需交换，跳出循环
            break;
        }
    }
}

//给定节点索引，递归对节点进行查找
template <typename T>
FibNode<T>* search_node(FibNode<T>* node, T index){
    if(node == NULL){
        return NULL;
    }

    //判断该节点
    if(node->k_index == index){
        return node;
    }
    
    //对该节点的子节点进行DFS搜索
    FibNode<T>* temp = NULL;
    FibNode<T>* breakpoint = NULL;
    FibNode<T>* search = node->child;
    while(search!=breakpoint){
        breakpoint = search; //记录循环中上一个节点
        // if(search->k_index == index){
        //     temp = search;
        //     break;
        // }
        if((temp = search_node(search,index)) != NULL){
            break;
        }
        search = search->right;
    }
    return temp;
}

// 查找斐波那契堆中索引为index的节点
template <typename T>
FibNode<T>* FibHeap<T>::search(T index){
    if(min == NULL){
        return NULL;
    }

    //对根链表中每个节点进行DFS搜索
    FibNode<T>* brother = min;
    FibNode<T>* breakpoint = NULL;
    FibNode<T>* temp = NULL;
    while(brother != min || breakpoint == NULL){
        breakpoint = min;
        if((temp = search_node(brother,index)) != NULL){
            break;
        }
        brother = brother->right;
    }

    return temp;
}

// 将斐波那契堆中索引为index的节点的值更新为newkey
template <typename T>
void FibHeap<T>::update(T index, T newkey, int choice = 0){
    FibNode<T>* node = search(index);
    if(node == NULL){
        printf("index dose not exist in Fibonacci tree. ");
        cout << index << endl;
        return;
    }

    //加了一个模式判断
    if(choice == 1){
        if(newkey >= node->key){
            printf("newkey larger than oldkey. ");
            return;
        }
    }

    if(newkey < node->key){
        decreaseKey(node, newkey);
    }
    else{
        increaseKey(node, newkey);
    }
}

//删除索引为index的节点
template <typename T>
void FibHeap<T>::remove(T index){
    FibNode<T>* node = search(index);
    if(node == NULL){
        printf("this key dose not exist in Fibonacci tree.");
        return;
    }

    T k = min->key;
    decreaseKey(node,k-1);
    removeMin();
}

// 斐波那契堆中是否包含索引index
template <typename T>
bool FibHeap<T>::contains(T index){
    FibNode<T>* node = search(index);
    if(node == NULL){
        return false;
    }
    return true;
}

// 将other合并到当前堆中
template <typename T>
void FibHeap<T>::combine(FibHeap<T> *other){
    if(other == NULL || other->min == NULL){
        return;
    }

    if(this->min == NULL){
        this->min = other->min;
        this->maxDegree = other->maxDegree;
        this->keyNum = other->keyNum;
    }

    else{
        this->min->left->right = other->min;
        other->min->left->right = this->min;
        FibNode<T> *left = this->min->left;
        this->min->left = other->min->left;
        other->min->left = left;

        if(this->min->key > other->min->key){
            this->min = other->min;
        }
        if(this->maxDegree < other->maxDegree){
            this->maxDegree = other->maxDegree;
        }
        this->keyNum += other->keyNum;
    }
}

// 获取斐波那契堆中最小键值，并保存到pkey中；成功返回true，否则返回false。
template <typename T>
bool FibHeap<T>::minimum(T *pkey){
    if(this.min != NULL && pkey != NULL){
        pkey = this->min->key;
        return true;
    }
    return false;
}

// 打印斐波那契堆
template <typename T>
void FibHeap<T>::print(){
    FibNode<T>* node = min;
    while(node != NULL){
        print(node);
        node = node->right;
    }
}

//打印一个节点及其子节点
template <typename T>
void print(FibNode<T> *node){
    if(node == NULL){
        return;
    }
    cout << node->k_index << ' ' << node->key << endl;
    FibNode<T>* child = node->child;
    while(child != NULL){
        print(child);
        child = child->right;
    }
}

// 判断是否为空
template <typename T>
bool FibHeap<T>::empty(){
    if(min == NULL){
        return true;
    }
    return false;
}

template <typename T>
T FibHeap<T>::findMin(){
    return min->key;
}

// int main(){
//     FibHeap<int> Tree{};
//     Tree.insert(983,0);
//     Tree.insert(637,1);
//     Tree.insert(231,2);
//     Tree.insert(352,3);
//     Tree.insert(392,4);
//     Tree.insert(392,5);
//     Tree.insert(392,6);
//     Tree.insert(392,7);
//     Tree.insert(392,8);
//     Tree.insert(392,9);
//     Tree.insert(392,10);
//     Tree.insert(392,11);
//     Tree.insert(392,12);
//     int tmin = Tree.extractMin();
//     printf("%d\n",tmin);
//     Tree.update(4,50);
//     Tree.update(5,100);
//     Tree.update(11,100);
//     tmin = Tree.extractMin();
//     printf("%d\n",tmin);
//     tmin = Tree.extractMin();
//     printf("%d\n",tmin);
//     Tree.update(12,1);
//     Tree.update(10,15);
//     tmin = Tree.extractMin();
//     printf("%d\n",tmin);
// }