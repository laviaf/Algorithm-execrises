#include <stdio.h>
using namespace std;
//暴力解法

int get_majority(int arr[],int n){
    int M = 1, i = 0, j = 1;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(arr[i] != arr[j] && i != j){
                M+=1;
            }
        }
        if(M>n/2){
            return arr[i];
        }
    }
}

int main(){
    int n = 0,i = 0;
    scanf("%d",&n);
    int arr[n];
    for(i=0;i<n;i++){
        int a;
        scanf("%d",&a);
        arr[i]=a;
    }
    int majority = 0;
    majority = get_majority(arr,n);
    printf("%d",majority);
}
