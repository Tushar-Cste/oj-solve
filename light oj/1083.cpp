#include <iostream>
#include <cstdio>
#define Max 30005
#define inf 1<<30
using namespace std;
 
int ara[Max];
int seg[4*Max] = {0};
 
//build a segment tree
int build_segment_tree(int cur, int lf, int r){
    if(lf == r){
        seg[cur] = ara[lf];
        return seg[cur];
    }
 
    seg[cur] = min(build_segment_tree(cur*2, lf, (lf+r)/2),build_segment_tree(cur*2 + 1, (lf+r)/2 +1, r));
    return seg[cur];
}
 
 
 
int query(int cur, int lf_l, int r_l, int lf, int r){
    if(r < lf_l || lf > r_l)
        return inf;
    else if(lf<= lf_l && r >=r_l)
        return seg[cur];
    else {
        return min(query(cur*2, lf_l,(lf_l + r_l)/2, lf, r), query(cur*2+1, (lf_l+r_l)/2 +1, r_l, lf, r));
    }
}
 
int range_query(int cur, int lf_l, int r_l, int lf, int r, int val){
    int x=-1, y=-1;
    if(lf_l > r || r_l <lf)
        return -1;
    if(lf_l == r_l && seg[cur] == val)
        return lf_l;
    int mid = (lf_l + r_l)/2;
    if(mid >= lf && seg[cur*2] <= val){
         x = range_query(cur*2, lf_l, mid, lf, r, val);
         if(x!=-1)
            return x;
    }
    if(mid <=r && seg[cur*2 +1] <= val && x == -1){
         y = range_query(cur*2 +1, mid+1, r_l,lf, r, val);
         if(y!=-1)
            return y;
    }
    return -1;
}
long long histogram(long long maxa, int n, int lf, int r){
    int mina = query(1,1,n,lf,r);
 
 
    long long sum = (long long)mina* (long long)((r-lf) +1);
    if(sum > maxa)
        maxa = sum;
    int x = range_query(1,1,n,lf,r,mina);
    if(lf != r && x == lf){
        sum = histogram(maxa,n,x+1,r);
        if(sum>maxa)
            maxa = sum;
    }
    else if(lf!=r && x == r){
        sum = histogram(maxa, n, lf, x-1);
        if(sum>maxa)
            maxa = sum;
    }
    else if(lf!=r){
        sum = histogram(maxa,n,lf,x-1);
        if(sum>maxa)
            maxa = sum;
        sum = histogram(maxa,n,x+1,r);
        if(sum>maxa)
            maxa = sum;
    }
    return maxa;
}
int main(){
    int n, num, lf_l, r_l, sum, index, data, ts;
    scanf("%d",&ts);
    for(int t = 1; t<=ts; t++){
        scanf("%d",&n);
        for(int i = 1; i<=n; i++){
            scanf("%d",&num);
            ara[i] = num;
        }
        build_segment_tree(1, 1, n);
        long long result = histogram(0,n,1,n);
        printf("Case %d: %lld\n",t,result);
    }
    return 0;
}
