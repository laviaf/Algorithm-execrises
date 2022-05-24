#include <stdio.h>
#include <iostream>
using namespace std;

int dynamic_programming(int* weight, int* value, int n, int total_weight){
    int dynamic_matrix[n+1][total_weight+1];
    for(int i=0;i<n+1;i++){
        for(int j=0;j<total_weight+1;j++){
            dynamic_matrix[i][j] = 0;
        }
    }
    for(int i=1;i<n+1;i++){
        //i代表当前搜索的物品
        for(int j=1;j<total_weight+1;j++){
            //j代表当前搜索的重量
            if(j >= weight[i-1]){
                //当前重量能承载物品i，使用迭代式进行计算
                int v = value[i-1] + dynamic_matrix[i-1][j-weight[i-1]];
                if(v >= dynamic_matrix[i-1][j]){
                    dynamic_matrix[i][j] = v;
                }
                else{
                    dynamic_matrix[i][j] = dynamic_matrix[i-1][j];
                }
            }
            else{
                dynamic_matrix[i][j] = dynamic_matrix[i-1][j];
            }
        }
    }

    return dynamic_matrix[n][total_weight];
}

int main(){
    int N;
    int W;
    scanf("%d",&N);
    scanf("%d",&W);
    int Weight[N];
    int Value[N];
    for(int i=0;i<N;i++){
        scanf("%d",&Weight[i]);
        scanf("%d",&Value[i]);
    }
    
    int max_value = dynamic_programming(Weight, Value, N, W);
    printf("%d",max_value);
    return 0;
}