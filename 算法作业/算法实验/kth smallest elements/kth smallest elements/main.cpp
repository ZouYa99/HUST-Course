#include<iostream>
#include<algorithm>
#include<unordered_set>
using namespace std;
int findKthElement(int* array,int kth,int low,int high,int size);
int getMedian(int* array,int begin,int end){
    sort(array+begin,array+end+1);
    int mid = (begin+end)>>1;
    return array[mid];
}
int secondaryExtraction(int* array,int low,int high){
    int length = high-low+1;
    int size = (length/5) + ((length%5==0)?0:1);
    int median[size];
    for (int i=0; i<size; i++) {
        int begin = low+5*i;
        median[i]=getMedian(array, begin, min(begin+4,high));
    }
    return findKthElement(median, size/2, 0, size-1 , size-1);
}
int findIndex(int* array,int low,int high,int number){
    for (int i=low; i<=high; i++) {
        if (array[i]==number) {
            return i;
        }
    }
    return -1;
}
int partition(int* array,int low,int high){
    int i = low,j = high;
    int k = array[low];
    while (i<j) {
        while (i<j&&array[j]>k) {
            j--;
        }
        if (i<j) {
            array[i++]=array[j];
        }
        while (i<j&&array[i]<k) {
            i++;
        }
        if (i<j) {
            array[j--]=array[i];
        }
    }
    array[i] = k;
    return i;
}
int findKthElement(int* array,int kth,int low,int high,int size){
    if (low==high) {
        return array[low];
    }
    int divide = secondaryExtraction(array, low, high);
    int index = findIndex(array, 0, size, divide);
    array[index]=array[low];
    array[low]=divide;
    int pivot = partition(array,low,high);
    if (pivot==kth-1) {
        return array[pivot];
    }
    else if (pivot<kth-1) {
        return findKthElement(array,kth, pivot+1, high,size);
    }else{
        return findKthElement(array,kth, low, pivot,size);
    }
}
int main(){
    int n,k;
    cin>>n;
    cin>>k;
    int array[n];
    for(int i=0;i<n;i++){
        cin>>array[i];
    }
    int size = unique(array, array + n) - array;
    if(k>size){
        cout<<"NO!";
    }else{
        cout<<findKthElement(array,k,0,size-1,size-1);
    }
    return 0;
} 
