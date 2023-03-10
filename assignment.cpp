#include<bits/stdc++.h>
#include<fstream>
#include<iostream>
using namespace std;
namespace fs = std::filesystem;

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


    ifstream inputFile("/usr/src/app/input.txt");
    string line;

    if (!inputFile.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }

    if(!inputFile) {
        cout<<"Error opening input file"<<endl;
        return 1;
    }

    while(getline(inputFile, line)) {
        if (inputFile.fail()) {
            cout<< "Error reading from file"<< endl;
            return 1;
        }
        stringstream ss(line);

        string token,child;

        pair<string, string> p = containsNumber(line);
        if(p.second=="") {
            pair<string, string> p1 = findRelation(line);
            token = p1.first;
            child = p1.second;
            adj[token].push_back(child);
            vis[token]=false;
            vis[child]=false;
            if(progress.find(token)==progress.end())progress[token]=0;
            if(progress.find(child)==progress.end())progress[child]=0;
            inorder[child]++;
            if(inorder.find(token)==inorder.end())inorder[token]=0;
        } else {
            token = p.first;
            progress[token]=stod(p.second);
        }
    }

    inputFile.close();

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
