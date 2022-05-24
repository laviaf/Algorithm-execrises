#include <stdlib.h>
#include <stdio.h>
#include<time.h>
using namespace std;

void get_rand(int arr[], int k, int n){
    int i = 0, r = 0;
    for(i=0;i<k;i++){
        r = rand()%(n-i);
        int swap = arr[i];
        arr[i] = arr[i+r];
        arr[i+r] = swap;
    }
}

int main(){
    srand(time(0));
    int n = 0,i = 0;
    printf("please input the length of the array.\n");
    scanf("%d",&n);
    int arr[n];
    printf("please input the array, ' ' for sepreation.\n");
    for(i=0;i<n;i++){
        int a = 0;
        scanf("%d",&a);
        arr[i]=a;
    }
    printf("please input the length you want to sample.\n");
    int length_k = 0;
    scanf("%d",&length_k);
    get_rand(arr,length_k,n);
    printf("The sampled array is:\n");
    for(i=0;i<length_k;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}