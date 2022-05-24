#include <stdio.h>
using namespace std;
//只过一遍数组的解法 O(n)时间复杂度 O(n)空间复杂度 （是否可以到O(1)空间复杂度？）

int get_majority(int arr[], int present_count,int n,int pre_num){
    int j = present_count;
    int c = arr[present_count];
    int count = 1;
    while(j < n-1 && count >= 0){
        j++;
        if(arr[j] == c){
            count+=1;
        }
        else{
            count-=1;
        }
    }
    if(j == n-1){
        return c;
    }
    else{
        return get_majority(arr, j+1, n, c);
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
    majority = get_majority(arr,0,n,0);
    printf("%d",majority);
}
