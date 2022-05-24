#include <stdio.h>
using namespace std;
//分治策略

int CheckMajority(int arr[], int begin,int end,int LM, int RM){
    if(LM==RM){
        return LM;
    }
    else if(LM==0){
        return RM;
    }
    else if(RM==0){
        return LM;
    }
    int LC = 0, RC = 0;
    int i = 0;
    for(i=begin;i<end+1;i++){
        if(arr[i] == LM){
            LC++;
        }
        else if(arr[i] == RM){
            RC++;
        }
        else{
            continue;
        }
    }
    if(LC > RC){
        return LM;
    }
    else{
        return RM;
    }
}

int MergeMajority(int arr[],int begin,int end){
    if(end == begin){
        return arr[begin];
    }
    int mid = (begin + end)/2;
    int LMajority = MergeMajority(arr,begin,mid);
    int RMajority = MergeMajority(arr,mid+1,end);
    int Majority = CheckMajority(arr, begin, end, LMajority, RMajority);
    return Majority;
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
    majority = MergeMajority(arr,0,n-1);
    printf("%d",majority);
}
