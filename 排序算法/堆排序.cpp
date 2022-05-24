#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

class Preority_queue{
    public:
        Preority_queue(){sorted = false;};//初始建堆什么都不用做；
        ~Preority_queue(){free(heap);};
        void build_min_heap(long int* arr, int n);
        void min_heapify(int pos);
        void heap_sort();
        void print_sorted_tree();
        void insert(int num);
        int minimum();
        int extract_min();
        void increase_key(int pos, int num);
        void decrease_key(int pos, int num);
    private:
        int heap_length;//堆元素个数
        long int* heap;
        bool sorted;
};

void Preority_queue::build_min_heap(long int* arr, int n){
	heap_length = n;
    heap = (long int*)calloc(n,sizeof(long int)); //动态分配空间
    for(int i=0;i<n;i++){
        heap[i] = arr[i];
    }
    for(int i=n/2-1;i>=0;i--){
        min_heapify(i);
    }
}

void Preority_queue::min_heapify(int pos){
    int left = 2*pos;
    int right = 2*pos + 1;
    if(left > heap_length-1){//后面没节点了
        return;
    }
    else if(right > heap_length-1){//有左节点无右节点
        if(heap[left] < heap[pos]){
            long int temp = heap[left];
            heap[left] = heap[pos];
            heap[pos] = temp;
            min_heapify(left);
        }
    }
    else{//左右节点都有
        if(heap[left] < heap[pos] || heap[right] < heap[pos]){
            if(heap[left] < heap[right]){
                long int temp = heap[left];
                heap[left] = heap[pos];
                heap[pos] = temp;
                min_heapify(left);
            }
            else{
                long int temp = heap[right];
                heap[right] = heap[pos];
                heap[pos] = temp;
                min_heapify(right);
            }
        }
    }
}

void Preority_queue::heap_sort(){
    int length = heap_length;
    for(int i=heap_length-1;i>=1;i--){
        long int temp = heap[i];
        heap[i] = heap[0];
        heap[0] = temp;
        heap_length -= 1;
        min_heapify(0);
    }
    heap_length = length;
    for(int i=0;i<heap_length/2;i++){
        long int temp = heap[i];
        heap[i] = heap[heap_length-i-1];
        heap[heap_length-i-1] = temp;
    }
    sorted = true;
}

void Preority_queue::print_sorted_tree(){
    if(sorted == false){
        heap_sort();
    }
    for(int i=0;i<heap_length;i++){
        printf("%ld ",heap[i]);
    }
    // printf("\n");
}

void Preority_queue::insert(int num){
    heap_length += 1;
    realloc(heap, heap_length*sizeof(int));
    heap[heap_length-1] = num;
    int i = heap_length-1;
    while(i > 0 && heap[i/2] > heap[i]){
        int temp = heap[i];
        heap[i] = heap[i/2];
        heap[i/2] = temp;
        i = i/2;
    }
    sorted = false;
}

int Preority_queue::minimum(){
    return heap[0];
}

int Preority_queue::extract_min(){
    int min = heap[0];
    heap[0] = heap[heap_length-1];
    heap_length -= 1;
    min_heapify(0);
    sorted = false;
    return min;
}

void Preority_queue::increase_key(int pos, int num){
    if(num < heap[pos]){
        printf("the num is less than current key.");
    }
    else{
        heap[pos] = num;
        min_heapify(pos);
    }    
}

void Preority_queue::decrease_key(int pos, int num){
    if(num > heap[pos]){
        printf("the num is greater than current key.");
    }
    else{
        heap[pos] = num;
        int i = pos;
        while(i > 0 && heap[i/2] > heap[i]){
            int temp = heap[i];
            heap[i] = heap[i/2];
            heap[i/2] = temp;
            i = i/2;
        }
        sorted = false;
    }
}

int main(){
	int n = 0;
	scanf("%d",&n);
	long int arr[n];
	for(int i=0;i<n;i++){
		scanf("%ld",&arr[i]);
	}
	Preority_queue queue;
	queue.build_min_heap(arr,n);
	queue.heap_sort();
	queue.print_sorted_tree();
	return 0;
}
