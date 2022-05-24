#include <stdio.h>
using namespace std;

int dynamic_find_path(int block[][2],int N,int M){
    int path[N+1][N+1];
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            path[i][j] = -1;
        }
    }
    //辅助计算
    for(int i=0;i<N+1;i++){
        path[N][i] = 0;
    }
    for(int i=0;i<N+1;i++){
        path[i][N] = 0;
    }
    //若该点不通，置为0
    for(int i=0;i<M;i++){
        path[block[i][0]-1][block[i][1]-1] = 0;
    }

    //动态规划，从右下角到左上角
    path[N-1][N-1] = 1;
    for(int i=1;i<N;i++){
        for(int j=0;j<i+1;j++){
            if(path[N-j-1][N-i+j-1]==0){
                //说明此路不通
                continue;
            }
            else{
                path[N-j-1][N-i+j-1] = (path[N-j][N-i+j-1] + path[N-j-1][N-i+j])%100003;
            }
        }
    }
    for(int i=0;i<N-1;i++){
        for(int j=0;j<N-i-1;j++){
            if(path[N-i-j-2][j]==0){
                //说明此路不通
                continue;
            }
            else{
                path[N-i-j-2][j] = (path[N-i-j-1][j] + path[N-i-j-2][j+1])%100003;
            }
        }
    }

    int res = path[0][0]%100003;
    return res;
}

int main(){
    int N;
    int M;
    scanf("%d",&N);
    scanf("%d",&M);
    int block[M][2];
    for(int i=0;i<M;i++){
        scanf("%d",&block[i][0]);
        scanf("%d",&block[i][1]);
    }

    int res = dynamic_find_path(block,N,M);
    printf("%d",res);
    return 0;
}