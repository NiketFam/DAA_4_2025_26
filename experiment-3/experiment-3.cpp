#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    if(!(cin>>n)){
        return 0;
    }
    vector<char> attend(n);
    for(int i=0;i<n;i++){
        cin>>attend[i];
    }
    unordered_map<int,int> mp;
    int curr_sum=0;
    int max_len=0;
    mp[0]=-1;
    for(int i=0;i<n;i++){
        if(attend[i]=='p'){
            curr_sum+=1;
        }
        else{
            curr_sum-=1;
        }
        if(mp.find(curr_sum)!=mp.end()){
            int len=i-mp[curr_sum];
            max_len=max(max_len,len);
        }
        else{
            mp[curr_sum]=i;
        }
    }
    cout<<max_len<<endl;
    return 0;
}