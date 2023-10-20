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

class node{
    public:
    node* left;
    node* right;
};

class trie{
    node* root;
    public:
    trie(){
        root = new node();
    }
    void insert(int n){
        node* temp = root;
        for(int i=31;i>=0;i--){
            int bit = (n>>i)&1;
            if(bit==0){
                if(temp->left==NULL){
                    temp->left = new node();
                }
                temp = temp->left;
            }
            else{
                if(temp->right==NULL){
                    temp->right = new node();
                }
                temp = temp->right;
            }
        }
    }
    int max_xor_helper(int value){ // the logic for this is that we will try to find the opposite bit for each bit of the number and if it is present then we will go to that side else we will go to the other side. eg if we have 101 and we are at 1st bit then we will try to find 0 at that bit and if it is present then we will go to that side else we will go to the other side.
        int current_ans = 0;
        node* temp = root;
        for(int j=31;j>=0;j--){
            int bit = (value>>j)&1;
            if(bit==0){
                if(temp->right!=NULL){
                    temp = temp->right;
                    current_ans += (1<<j);
                }
                else{
                    temp = temp->left;
                }
            }
            else{
                if(temp->left!=NULL){
                    temp = temp->left;
                    current_ans += (1<<j);
                }
                else{
                    temp = temp->right;
                }
            }
        }
        return current_ans;
    }
    int max_xor(vi a){
        int max_xor = 0;
        for(int i=0;i<a.size();i++){
            int val = a[i];
            insert(val);
            int current_xor = max_xor_helper(val);
            max_xor = max(current_xor,max_xor);
        }
        return max_xor;
    }
    int maxSubarrayXOR(vi a){
        int max_xor = 0;
        int pre_xor = 0;
        for(int i=0;i<a.size();i++){
            pre_xor = pre_xor^a[i];
            insert(pre_xor);
            max_xor = max(max_xor,max_xor_helper(pre_xor));
        }
        return max_xor;
    }
};

signed main()
{
    int n; cin>>n;
    vi a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    trie t;
    cout<<t.maxSubarrayXOR(a)<<endl;

    return 0;
}
