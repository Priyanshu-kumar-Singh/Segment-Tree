#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int A[100000],seg[100000];

void Build(int ind, int low, int high){
    if(low == high){
        seg[ind] = A[low];
        return;
    }
    int mid = (low+high)/2;
    Build(2*ind+1,low,mid);
    Build(2*ind+2,mid+1,high);
    seg[ind] = max(seg[2*ind+1],seg[2*ind+2]);
}

int query(int ind, int low, int high, int l, int r){
    if(low>=l && high<=r)//segment lying fully inside the given range
    {
        return seg[ind];
    }
    if(high<l || low>r)//segment lying fully outside l and r
    {
        return 0;
    }
    // else case if segment is overlapping with l and r
    int mid = (low+high)/2;
    int left = query(2*ind+1,low,mid,l,r);
    int right = query(2*ind+2,mid+1,high,l,r);
    return max(left,right);
}

int main(){
    int n;
    cin>>n;
    for(int i = 0;i < n;i++)
    {
        cin>>A[i];
    }
    Build(0,0,n-1);
    int q;
    cin>>q;
    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<query(0,0,n-1,l,r)<<"\n";
    }
}