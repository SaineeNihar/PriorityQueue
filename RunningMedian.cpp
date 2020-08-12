#include <bits/stdc++.h>
using namespace std;
class heap{
    public:
    int *arr;
    int cap, count; 
    int type;
    heap(int c,int t)
    {
        cap=c;
        count=0;
        arr=new int[c];
        type=t;
    }
};
int getTop(heap *h)
{
    if(h->count==0)
        return 0;
    return h->arr[0];
}
int getParant(heap *h, int i)
{
    if(i>=0 or h->count<i)
        return -1;
    return (i-1)/2;
}
int lc(heap *h,int i)
{
    int l=2*i+1;
    if(l>h->count)
        return -1;
    return l;
}
int rc(heap *h, int i)
{
    int r=2*i+2;
    if(r>h->count)
        return -1;
    return r;
}
void heapifyDown(heap *h, int i){
    int l=lc(h,i);
    int r=rc(h,i);
    if(h->type==0)
    {
        int min=i;
        if(l!=-1 and h->arr[l]<h->arr[min])
            min=l;
        if(r!=-1 and h->arr[r]<h->arr[min])
            min=r;
        if(min!=i)
        {
            int tmp=h->arr[i];
            h->arr[i]=h->arr[min];
            h->arr[min]=tmp;
            heapifyDown(h,min);
        }
    }
    else if(h->type==1)
    {
        int max=i;
        if(l!=-1 and h->arr[l]>h->arr[max])
            max=l;
        if(r!=-1 and h->arr[r]>h->arr[max])
            max=r;
        if(max!=i)
        {
            int tmp=h->arr[i];
            h->arr[i]=h->arr[max];
            h->arr[max]=tmp;
            heapifyDown(h,max);
        }
    }
}
void deleteTop(heap *h)
{  
    h->arr[0]=h->arr[h->count-1];
    h->count--;
    heapifyDown(h,0);
}
void resizeHeap(heap *h)
{   
    int *old=h->arr;
    h->arr=new int[h->cap*2];
    for(int i=0;i<h->cap;i++)
    {
        h->arr[i]=old[i];
    }
    h->cap=h->cap*2;
}
void insert(heap *h,int v){
    if(h->count==h->cap)
        resizeHeap(h);
    h->count++;
    int i=h->count-1;
    if(h->type==0)
    {
        while(i>0 and v<h->arr[(i-1)/2])
        {
            h->arr[i]=h->arr[(i-1)/2];
            i=(i-1)/2;
        }
    }
    else if(h->type==1)
    {
        while(i>0 and v>h->arr[(i-1)/2])
        {
            h->arr[i]=h->arr[(i-1)/2];
            i=(i-1)/2;
        }
    }
    h->arr[i]=v;
}
vector<double> runningMedian(vector<int> a) 
{
    heap *min=new heap(10,0);
    heap *max=new heap(10,1);  
    //a[0]  
    vector<double> res;
    insert(max,a[0]);
    res.push_back((double)getTop(max));
    for(int i=1;i<a.size();i++)
    {
        if(a[i]>getTop(max)){
            insert(min,a[i]);
            //cout<<a[i]<<"inserting into min\n";
            }
        else{
            insert(max,a[i]);
            //cout<<a[i]<<"inserting into max\n";
            }
        if(max->count-min->count>1)
        {
            int tmp=getTop(max);
            deleteTop(max);
            insert(min,tmp);
        }
        if(min->count-max->count>0)
        {
            int tmp=getTop(min);
            deleteTop(min);
            insert(max,tmp);
        }
        if(max->count==min->count)
        {
            double x=(double)(getTop(min)+getTop(max))/2;
            x = floor(10*x + 0.5) / 10;
            res.push_back(x);
        }
        else
            res.push_back((double)getTop(max));
    }
    return res;
}

int main()
{
    int a_count;
    cin >> a_count;
    vector<int> a(a_count);
    for (int a_itr = 0; a_itr < a_count; a_itr++) 
    {
        int a_item;
        cin >> a_item;
        a[a_itr] = a_item;
    }
    vector<double> result = runningMedian(a);
    for (int result_itr = 0; result_itr < result.size(); result_itr++)
      cout<<result[result_itr];
    return 0;
}
