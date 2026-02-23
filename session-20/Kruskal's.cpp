#include<bits/stdc++.h>
using namespace std;
int findParent(int node, vector<int>& parent){
    if(parent[node]==node){
        return node;
    }
    else{
        return parent[node]=findParent(parent[node],parent);
    }
}
void unionSet(int u, int v, vector<int>& parent,vector<int>& rank){
    u=findParent(u,parent);
    v=findParent(v,parent);
    if(u==v){
        return;
    }
    if(rank[u]<rank[v]){
        parent[u]=v;
    }
    else if(rank[v]<rank[u]){
        parent[v]=u;
    }
    else{
        parent[v]=u;
        rank[u]++;
    }
}
int kruskalMst(int V, vector<vector<int>>& edges){
    sort(edges.begin(),edges.end(),[](vector<int>& a,vector<int>& b){
        return a[2]<b[2];
    });
    vector<int> parent(V);
    vector<int> rank(V,0);
    for(int i=0; i<V;i++){
        parent[i]=i;
    }
        int minCost=0;
        for(auto edge:edges){
            int u=edge[0];
            int v=edge[1];
            int q=edge[2];
            if(findParent(u,parent)!=findParent(v,parent)){
                minCost+=q;
                unionSet(u,v,parent,rank);
            }
        }
        return minCost;
}