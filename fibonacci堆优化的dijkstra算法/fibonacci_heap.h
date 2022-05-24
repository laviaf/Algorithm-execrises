#ifndef _FIBONACCI_TREE_H_
#define _FIBONACCI_TREE_H_

#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

template <typename T>
class FibNode {
    public:
        T key;                // 关键�?(�?�?)
        T k_index;              //节点编号
        int degree;            // 度数
        FibNode<T> *left;    // 左兄�?
        FibNode<T> *right;    // 右兄�?
        FibNode<T> *child;    // �?一�?孩子节点
        FibNode<T> *parent;    // 父节�?
        bool marked;        // �?否�??删除�?一�?孩子
        //如果需要实现dijkstra算法这里�?否应该�?�录当前节点对应的编号？

        FibNode(T value, T index):key(value), k_index(index), degree(0), marked(false), 
            left(NULL),right(NULL),child(NULL),parent(NULL) {
            key    = value;
            k_index = index;
            degree = 0;
            marked = false;
            left   = this;
            right  = this;
            parent = NULL;
            child  = NULL;
        }
};

template <typename T>
class FibHeap {
    private:
        int keyNum;         // 堆中节点的总数
        int maxDegree;      // 最大度
        FibNode<T> *min;    // 最小节�?(某个最小堆的根节点)

    public:
        FibHeap();
        ~FibHeap();

        // 新建key对应的节点，并将其插入到斐波那�?�堆�?
        void insert(T key, T index);
        // 移除斐波那�?�堆�?的最小节�?
        void removeMin();
        // 将other合并到当前堆�?
        void combine(FibHeap<T> *other);
        // 获取斐波那�?�堆�?最小键值，并保存到pkey�?；成功返回true，否则返回false�?
        bool minimum(T *pkey);
        // 查找斐波那�?�堆�?�?值为key的节�?
        FibNode<T>* search(T key);
        // 将斐波那契堆�?�?值oldkey更新为newkey
        void update(T index, T newkey, int choice);
        // 删除�?值为key的节�?
        void remove(T key);
        // 斐波那�?�堆�?�?否包�?�?值key
        bool contains(T key);
        // 打印斐波那�?�堆
        void print();
        // 销�?
        void destroy();
        // 判断�?否为�?
        bool empty();
        T findMin();

    // private:
        //将节点添加至根链�?
        void addNode(FibNode<T> *node);
        //将y连接为x的子节点
        void HeapLink(FibNode<T> *y, FibNode<T> *x);
        //更新根链�?
        void consolidate();
        //提取斐波那�?�堆�?的min节点并删�?
        void extractMin(T* res);
        //将某节点值降至某�?
        void decreaseKey(FibNode<T> *node, T key);
        //将某节点值�?�至某�?
        void increaseKey(FibNode<T> *node, T key);
        //级联�?�?
        void casecadingCut(FibNode<T> *node);
};

#endif
