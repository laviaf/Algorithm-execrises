#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include<time.h>
using namespace std;

void Quick_sort(int* arr, int begin, int end){
    if(begin<end){
        int r = rand()%(end-begin) + begin;
        int left = begin, right = begin;
        int swap = arr[r];
        arr[r] = arr[end];
        arr[end] = swap;
        for(right = begin;right<end;right++){
            if(arr[right] < arr[end]){
                swap = arr[left];
                arr[left] = arr[right];
                arr[right] = swap;
                left+=1;
            }
        }
        swap = arr[left];
        arr[left] = arr[end];
        arr[end] = swap;
        Quick_sort(arr,begin,left-1);
        Quick_sort(arr,left+1,end);
    }
}

int main(){
    srand(time(0));
    int n = 0;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    Quick_sort(arr,0,n-1);
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
}
