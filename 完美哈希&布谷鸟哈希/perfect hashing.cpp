#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <iostream>
#include <string>
#include <assert.h>
#include <bits/stdc++.h>
using namespace std;

typedef struct rand_hash_fun{
    int a;
    int b;
    int num; //哈希列表长度
} HASH_FUNC;

// 返回一个哈希映射函数的参数信息
rand_hash_fun random_hash(int num, int p){
    rand_hash_fun node;
    node.a = rand()%(p-1) + 1; //a非零
    node.b = rand()%p;
    node.num = num;
    return node;
}

int hash_map(int a, int b, int m, int value, int p){
    return (((a*value+b)%p)%m);
}

// 初始化哈希散列表空间，并初始化第一层哈希函数
void init_hash(int num, int p, int* value, int n, int* hash_table[], rand_hash_fun* hash){
    // 进行第一轮分配，看有无冲突
    int first_map_count[num];
    rand_hash_fun fisrt_hash = random_hash(num,p);
    hash->a = fisrt_hash.a;
    hash->b = fisrt_hash.b;
    hash->num = fisrt_hash.num;
    for(int i=0;i<num;i++){
        first_map_count[i] = 0;
    }

    for(int i=0;i<n;i++){
        first_map_count[hash_map(fisrt_hash.a,fisrt_hash.b,fisrt_hash.num,value[i],p)]++;
    }

    // 第二轮分配，若有冲突进行扩容
    for(int i=0;i<num;i++){
        if(first_map_count[i] == 1){
            // 仅有一个元素 则a=b=0，m=1
            hash_table[i] = (int*)malloc(sizeof(HASH_FUNC) + sizeof(int));
            *(hash_table[i]) = 0;
            *(hash_table[i]+1) = 0;
            *(hash_table[i]+2) = 1;
            *(hash_table[i]+3) = 0;
        }
        else if(first_map_count[i] > 2*log(float(n))){
            // 二层链表过长，重新构建
            cout << "reconstruct the link" << endl;
            
            return;
        }
        else if(first_map_count[i] > 1){
            // 有冲突元素
            rand_hash_fun second_hash = random_hash(first_map_count[i]*first_map_count[i],p);
            hash_table[i] = (int*)malloc(sizeof(HASH_FUNC) + sizeof(int)*first_map_count[i]);
            *(hash_table[i]) = second_hash.a;
            *(hash_table[i]+1) = second_hash.b;
            *(hash_table[i]+2) = second_hash.num;
            for(int j=0;j<first_map_count[i];j++){
                *(hash_table[i]+3+j) = 0;
            }
        }
        else{
            hash_table[i] = NULL;
        }
    }
}

// 插入一个值到哈希表中，可能会发生碰撞
void insert(int p, int value, int* hash_table[], rand_hash_fun hash){
    int first_pos = hash_map(hash.a,hash.b,hash.num,value,p);
    int second_pos = hash_map(*(hash_table[first_pos]),*(hash_table[first_pos]+1), *(hash_table[first_pos]+2),value,p);
    assert(*(hash_table[first_pos]+3+second_pos)==0); // 查询碰撞
    // *(hash_table[first_pos]+3+second_pos) = value;
    return;
}

// 插入值到哈希表中
void init_insert(int p, int* value, int n, int* hash_table[], rand_hash_fun hash){
    for(int i=0;i<n;i++){
        insert(p,value[i],hash_table,hash);
    }    
}

int main(){
    srand(time(0));
    int p = 91;
    int num = 20;
    int n = 10;
    int value[n] = {1,2,3,4,8,44,99,32,12,22};
    rand_hash_fun* hash = new rand_hash_fun;
    int* hash_table[num];

    init_hash(num,p,value,n,hash_table,hash);
    init_insert(p,value,n,hash_table,*hash);

    for(int i=0;i<num;i++){
        if(hash_table[i]){
            cout << " a: " << *(hash_table[i]) << " b: " << *(hash_table[i]+1) << " num: " << *(hash_table[i]+2) << endl;
        }
    }
}