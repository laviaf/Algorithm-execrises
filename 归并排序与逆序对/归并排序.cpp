#include <iostream>
using namespace std;

template <typename T> void Sort(T arr[], int start, int end, int mid){
    int i, j;
    int k = 0;
    int n1 = mid - start + 1;
    int n2 = end - mid;
    //深拷贝
    T *L = new T[n1], *R = new T[n2];
    for(i = 0; i < n1; i++)
        L[i] = arr[start+i];
    for(j = 0; j < n2; j++)
        R[j] = arr[mid+j+1];
    i = 0;
    j = 0;
    k = start;
    //对左右两端数组进行排序
    while(i < n1 && j < n2){
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        //说明左列有剩余
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2){
        //说明右列有剩余
        arr[k] = R[j];
        j++;
        k++;
    }
    // int m = 0;
    // for(m=start;m<end;m++){
    //     cout<<arr[m]<<' ';
    // }
    // cout<<'\n';
    delete[] L;
    delete[] R;
}

template <typename T> void sort_array(T arr[], int start, int end){
    int mid = (end + start)/2;
    if(start >= end){
        return;
    }
    sort_array(arr, start, mid);
    sort_array(arr, mid+1, end);
    Sort(arr,start,end,mid);
}

int main(){
    int n,i;
    cin>>n;
    int arr[n];
    for(i=0;i<n;i++){
        int a;
        cin>>a;
        arr[i]=a;
    }
    sort_array(arr,0,n-1);
    for(i=0;i<n;i++){
        cout<<arr[i]<<' ';
    }
}