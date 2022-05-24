#include <iostream>
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

void insert(int temp_list,int n,int* hash_table[2],int temp_round,int value,rand_hash_fun* f1,rand_hash_fun* f2, int p){
    if (temp_round > log(float(n))){
        // 插入次数过多 重新开始
        cout<<"insert failed"<<endl;
        return;
    }

    int pos[2];
    pos[0] = hash_map(f1->a,f1->b,f1->num,value,p);
    pos[1] = hash_map(f2->a,f2->b,f2->num,value,p);

    //若当前位置已有元素
    if (hash_table[temp_list][pos[temp_list]]!=-1){
        int ori = hash_table[temp_list][pos[temp_list]];
        hash_table[temp_list][pos[temp_list]]=value;
        insert(1-temp_list,n,hash_table,temp_round+1,ori,f1,f2,p); //将原有元素挪走
    }
    else{
        hash_table[temp_list][pos[temp_list]]=value;
    }
}

void cuckoo_hashing(int n,int* hash_table[2],int* value,rand_hash_fun* f1,rand_hash_fun* f2, int p){
    for (int i=0;i<n;i++){
        insert(0,n,hash_table,0,value[i],f1,f2,p);
    }
}

// 查找元素
void lookup(int* hash_table[2],int value,int temp_list,rand_hash_fun* f1,rand_hash_fun* f2,int p){
    // 若能插入成功，不存在查找不成功    
    int pos[2];
    pos[0] = hash_map(f1->a,f1->b,f1->num,value,p);
    pos[1] = hash_map(f2->a,f2->b,f2->num,value,p);

    //若当前位置已有元素
    if (hash_table[temp_list][pos[temp_list]]!=value){
        int ori = hash_table[temp_list][pos[temp_list]];
        hash_table[temp_list][pos[temp_list]]=value;
        lookup(hash_table,value,1-temp_list,f1,f2,p); //将原有元素挪走
    }
    else{
        cout << "position is:" << temp_list << ' ' << pos[temp_list] << endl;
    }
}

int main(){
    srand(time(0));
    int n = 10;
    int p = 91;
    int num = 10;
    int value[n] = {1,2,3,4,8,44,99,32,12,22};
    int* hash_table[2]; //哈希表为2列
    for(int i=0;i<2;i++){
        hash_table[i] = (int*)malloc(sizeof(int)*n);
        for (int j=0;j<n;j++){
            hash_table[i][j]=-1;
        }
    }

    rand_hash_fun func1 = random_hash(num,p);
    rand_hash_fun func2 = random_hash(num,p);
    rand_hash_fun *f1,*f2;
    f1 = &func1;
    f2 = &func2;

    cuckoo_hashing(n,hash_table,value,f1,f2,p);
    for(int i=0;i<2;i++){
        for (int j=0;j<n;j++){
            cout << hash_table[i][j] << ' ';
        }
        cout << endl;
    }
}