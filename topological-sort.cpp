#include<bits/stdc++.h>
using namespace std;

vector<pair<string,int>> ans;
map<string, bool> vis;
map<string, vector<string>> adj;
map<string, double> progress;
map<string, int> inorder;
vector<pair<int, string>> inorderPair;


void dfs(string node, int level) {
    vis[node]=true;
    for(int i=0;i<adj[node].size();i++) {
        if(vis.find(adj[node][i])==vis.end()) {
            dfs(adj[node][i], level+1);
        }
    }
    ans.push_back({node, level});
}

pair<string,string> containsNumber(string s) {
    int n=s.length();
    string temp="";
    string name="";
    int i=0;
    while(i<n) {
        if(s[i]=='='){
            i++;continue;
        }
        if((s[i]>='0' && s[i]<='9') || s[i]=='.') {
            temp+=s[i];
        } else {
            name+=s[i];
        }
        i++;
    }
    return {name,temp};
}

pair<string, string> findRelation(string s) {
    pair<string, string> p;
    int flag=0;
    string first="", second="";
    
    int i=0;
    while(i<s.length()) {
        if(s[i]=='-') flag=1;
        if(s[i]=='-' || s[i]=='>') {
            i++;continue;
        } else {
            if(flag==0)first+=s[i];
            else second+=s[i];
            i++;
        }
    }
    return {first, second};
}

bool compare(pair<string,int> a, pair<string, int> b) {
    if(a.second==b.second) {
        return progress[a.first]>progress[b.first];
    }
    return a.second<b.second;
}

int main() {

    int m;
    cin>>m;
    vector<string> input;
    vector<string> nodes;
    for(int i=0;i<m;i++) {
        string s;
        cin>>s;
        input.push_back(s);
    }
    
    for(int i=0;i<m;i++) {
        pair<string, string> p = containsNumber(input[i]);
        if(p.second=="") {
            p=findRelation(input[i]);
            adj[p.first].push_back(p.second);
            if(progress.find(p.first)==progress.end())progress[p.first]=0;
            if(progress.find(p.second)==progress.end())progress[p.second]=0;
            nodes.push_back(p.first);
            nodes.push_back(p.second);
            vis[p.first]=false;
            vis[p.second]=false;
            inorder[p.second]++;
            if(inorder.find(p.first)==inorder.end())inorder[p.first]=0;
        } else {
            progress[p.first]=stod(p.second);
        }
    }
    for(auto mp: inorder) {
        inorderPair.push_back({mp.second, mp.first});
    }
    sort(inorderPair.begin(), inorderPair.end());

    for(int i=0;i<inorderPair.size();i++) {
        if(!vis[inorderPair[i].second]) {
            dfs(inorderPair[i].second, 0);
        }
    }

    sort(ans.begin(),ans.end(), compare);

    for(int i=0;i<ans.size();i++) {
        cout<<ans[i].first<<endl;
    }


    return 0;
}