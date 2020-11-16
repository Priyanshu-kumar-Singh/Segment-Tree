#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int A[100000],seg[4*100000],lazy[4*100000];

void Build(int ind, int low, int high){
    if(low == high){
        seg[ind] = A[low];
        return;
    }
    int mid = (low+high)/2;
    Build(2*ind+1,low,mid);
    Build(2*ind+2,mid+1,high);
    seg[ind] = seg[2*ind+1]+seg[2*ind+2];
}

void rangeupdate(int ind,int low,int high,int l,int r, int val){
    if(lazy[ind]!=0){
        seg[ind] += (high-low+1)*lazy[ind];
        if(low!=high){
            lazy[2*ind+1] += lazy[ind];
            lazy[2*ind+2] += lazy[ind];
        }
        lazy[ind] = 0;
    }

    if(r<low || l>high || low>high)return;

    if(low>=l && high<=r){
        seg[ind] += (high-low+1)*val;
        if(low!=high){
            lazy[2*ind+1] += val;
            lazy[2*ind+2] += val;
        }
        return;
    }

    int mid = (low+high)>>1;
    rangeupdate(2*ind+1,low,mid,l,r,val);
    rangeupdate(2*ind+2,mid+1,high,l,r,val);
    seg[ind] = seg[2*ind+1]+seg[2*ind+2];
}

int ans;
void queryindex(int ind, int low,int high, int val){
    if(lazy[ind]!=0){
        seg[ind] += (high-low+1)*lazy[ind];
        if(low!=high){
            lazy[2*ind+1] += lazy[ind];
            lazy[2*ind+2] += lazy[ind];
        }
        lazy[ind] = 0;
    }
    if(low==high){
        if(val>=seg[ind])ans = min(ans,low);
        return;
    }
    if(seg[ind]<=val)ans = min(ans,low);
    int mid = (low+high)>>1;
    queryindex(2*ind+1,low,mid,val);
    queryindex(2*ind+2,mid+1,high,val);
}

int main(){
    int n,q;
    cin>>n>>q;
    for(int i = 0;i < n;i++)
    {
        cin>>A[i];
    }
    Build(0,0,n-1);
    while(q--){
        int t,l,r,v;
        cin>>t;
        if(t==1){
            cin>>l>>r>>v;
            v = -v;
            rangeupdate(0,0,n-1,l,r,v);
        }
        else{
            cin>>v;
            ans = 1e6;
            queryindex(0,0,n-1,v);
            if(ans==1e6)ans = -1;
            cout<<ans<<"\n";
        }
    }
}