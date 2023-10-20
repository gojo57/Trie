#include<bits/stdc++.h>
#define pb push_back
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define ones(x) __builtin_popcountll(x)
#define int long long
#define pii pair<int,int>
#define mii map<int,int>
#define vi vector<int>
#define vvi vector<vector<int>>
#define vpii vector<pair<int, int>>
using namespace std;
const int mod = 1e9+7;
const int N = 2e5+5;

class Node{
    public:
    char data;
    unordered_map<char, Node*> children;
    bool terminal;
    int cnt;
    Node(char d){
        data = d;
        terminal = false;
        cnt = 0;
    }
};

class Trie{
    Node* root;
    int cnt;
    public:
    Trie(){
        root = new Node('\0');
        cnt = 0;
    }
    void insert(string s){
        Node* temp = root;
        for(int i=0;i<s.size();i++){
            char ch = s[i];
            if(temp->children.count(ch)){
                temp = temp->children[ch];
            }
            else{
                Node* n = new Node(ch);
                temp->children[ch] = n;
                temp = n;
            }
            temp->cnt++;
        }
        temp->terminal = true;
    }
    bool find(string s){
        Node* temp = root;
        for(int i=0;i<s.size();i++){
            char ch = s[i];
            if(temp->children.count(ch)==0){
                return false;
            }
            else{
                temp = temp->children[ch];
            }
        }
        return temp->terminal;
    }
    void erase(string s){
        Node* temp = root;
        for(int i=0;i<s.size();i++){
            char ch = s[i];
            temp = temp->children[ch];
            temp->cnt--;
        }
        temp->terminal = false;
    }
    string prefix(string s){
        Node* temp = root;
        string ans = "";
        for(int i=0;i<s.size();i++){
            char ch = s[i];
            if(temp->children.count(ch)==1){
                temp = temp->children[ch];
                ans += ch;
            }
            else {
                return ans;
            }
            if(temp->terminal==true){
                return ans;
            }
        }
        return ans;
    }
    string unique_prefix(string s){ // count no. of words starting from a given node
        Node* temp = root;
        string ans = "";
        for(int i=0;i<s.size();i++){
            char ch = s[i];
            temp = temp->children[ch];
            ans += ch;
            if(temp->cnt==1){
                return ans;
            }
        }
        return ans;
    }
    string longestCommonPrefix(vector<string> &A) {
        for(int i=0;i<A.size();i++){
            if(A[i]=="") return "";
            insert(A[i]);
        }
        string ans = "";
        Node* temp = root;
        while(temp->children.size()==1){
            auto it = temp->children.begin();
            ans += it->first;
            temp = it->second;
        }
        return ans;
    }
};

signed main()
{
    Trie t;
    int n;
    cin>>n;
    vector<string> v(n);
    while(n--){
        string s;
        cin>>s;
        // t.insert(s);
        v.push_back(s);
    }
    cout<<t.longestCommonPrefix(v)<<"\n";


    return 0;
}
