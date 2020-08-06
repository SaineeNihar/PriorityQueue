#include<bits/stdc++.h>
using namespace std;
class heap{
    public:
    int *array;
    int count,capacity,heap_type;
    heap(int cap,int typ){
        count=0;
        capacity=cap;
        array=new int[cap];
        heap_type=typ;
    }
};
int getTop(heap *h)
{
    if(h->count==0)
        return 0;
    return h->array[0];
}
int leftChild(heap *h,int i){
    int lc=2*i+1;
    if(lc>h->count)
        return -1;
    return lc;
}
int rightChild(heap *h,int i){
    int rc=2*i+2;
    if(rc>h->count)
        return -1;
    return rc;
}
int parentLocation(heap *h,int node)
{
    if(node<=0 or node>h->count)
        return -1;
    return (node-1)/2;
}
void heapifyDown(heap *h,int i){
    int l=leftChild(h,i);
    int r=rightChild(h,i);
    int max=i;
    if(l!=-1 and h->array[l]>h->array[max])
        max=l;
    if(r!=-1 and h->array[r]>h->array[max])
        max=r;
    if(max!=i){
        int temp=h->array[i];
        h->array[i]=h->array[max];
        h->array[max]=temp;
        heapifyDown(h,max);
    }
}
int  deleteTop(heap *h){
    if(h->count==0)
        return -1;
    int data=h->array[0];
    h->array[0]=h->array[h->count-1];
    h->count--;
    heapifyDown(h,0);
    return data;
}
void resizeHeap(heap *h){
    int *oldArr=h->array;
    h->array=new int[h->capacity];
    for(int i=0;i<h->capacity;i++)
        h->array[i]=oldArr[i];
    delete oldArr;
    h->capacity=h->capacity*2;
}
void insert(heap *h, int data){
    if(h->count==h->capacity)
        resizeHeap(h);
    h->count++;
    int i=h->count-1;
    while(i>0 and data>h->array[(i-1)/2]){
        h->array[i]=h->array[(i-1)/2];
        i=(i-1)/2;
    }
    h->array[i]=data;
}
void printHeap(heap *h)
{
    if(h->count==0){
        cout<<"Empty Heap :-("<<endl;
        return;
    }
    for(int i=0;i<h->count;i++)
        cout<<h->array[i]<<"  ";
    cout<<endl;
}
int main(){
    cout<<"hey1";
    heap *h=new heap(10,1);
    
    insert(h,10);
    insert(h,20);
    insert(h,5);
    insert(h,40);
    insert(h,30);
    insert(h,22);
    printHeap(h);
    return 0;
}