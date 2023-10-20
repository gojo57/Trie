// #include<bits/stdc++.h>
// #define pb push_back
// #define all(x) x.begin(),x.end()
// #define rall(x) x.rbegin(),x.rend()
// #define ones(x) __builtin_popcountll(x)
// #define int long long
// #define pii pair<int,int>
// #define mii map<int,int>
// #define vi vector<int>
// #define vvi vector<vector<int>>
// #define vpii vector<pair<int, int>>
// using namespace std;
// const int mod = 1e9+7;
// const int N = 2e5+5;

// struct node{
//     node *nxt[2];
//     int cnt;
//     node(){
//         nxt[0] = nxt[1] = NULL;
//         cnt = 0;
//     }
// };

// node *root;
// void insert(int x){
//     node *cur = root;
//     cur->cnt++;
//     for(int i=20;i>=0;i--){
//         int b = (x>>i)&1;
//         if(cur->nxt[b]==NULL) cur->nxt[b] = new node();
//         cur = cur->nxt[b];
//         cur->cnt++;
//     }
// }

// // returns maximum xor of x with any number in trie
// int maximise_xor(int x){
//     node *cur = root;
//     int ans = 0;
//     for(int i=20;i>=0;i--){
//         int b = (x>>i)&1;
//         if(cur->nxt[b^1]){
//             ans += (b^1)*(1<<i);
//             cur = cur->nxt[b^1];
//         }
//         else {
//             ans += b*(1<<i);
//             cur = cur->nxt[b];
//         }
//     }
//     return ans;
// }

// // returns count of numbers less than or equal to x in trie
// int less_than_equal_to(int x){
//     node *cur = root;
//     int ans = 0;
//     for(int i=20;i>=0;i--){
//         if(cur==NULL) return ans;
//         int b = (x>>i)&1;
//         if(b && cur->nxt[0]!=NULL) ans += cur->nxt[0]->cnt;
//         cur = cur->nxt[b];
//     }
//     if(cur!=NULL) ans += cur->cnt;
//     return ans;
// }

// // returns kth smallest number in trie
// int kth_smallest(int k){
//     node *cur = root;
//     int ans = 0;
//     for(int i=20;i>=0;i--){
//         if(cur->nxt[0]!=NULL && cur->nxt[0]->cnt>=k){
//             // go left
//             cur = cur->nxt[0];
//         }
//         else {
//             // go right
//             if(cur->nxt[0]!=NULL) k -= cur->nxt[0]->cnt;
//             cur = cur->nxt[1];
//             ans += (1<<i);
//         }
//     }
//     return ans;
// }

// signed main()
// {
//     root = new node();
//     int n; cin>>n;
//     int a[n];
//     for(int i=0;i<n;i++) {
//         cin>>a[i];
//         insert(a[i]);
//     }
//     // for(int i = 0; i<n; i++){
//     //     cout<<a[i]<<" "<<maximise_xor(a[i])<<"\n";
//     // }
//     // for(int i = 0; i<n; i++){
//     //     cout<<a[i]<<" "<<less_than_equal_to(a[i])<<"\n";
//     // }
//     for(int i = 0; i<n; i++){
//         cout<<i+1<<" "<<kth_smallest(i+1)<<"\n";
//     }

//     return 0;
// }

#include<bits/stdc++.h>
#define pb push_back
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define ones(x) __builtin_popcountll(x)
#define pii pair<int,int>
#define mii map<int,int>
#define vi vector<int>
#define vvi vector<vector<int>>
#define vpii vector<pair<int, int>>
using namespace std;
const int mod = 1e9+7;
const int N = 2e5+5;

struct node{
    int lf, rt, cnt;
};

node trie[N*90];
int new_ptr;
int root[N*90];

int insert(int prev, int x){
    int temp = new_ptr++;
    int cur = temp;
    trie[cur] = trie[prev];
    for(int i=21;i>=0;i--){
        int b = (x>>i)&1;
        if(b){
            trie[cur].rt = new_ptr++;
            trie[trie[cur].rt] = trie[trie[prev].rt];
            trie[trie[cur].rt].cnt++;
            cur = trie[cur].rt;
            prev = trie[prev].rt;
        }
        else {
            trie[cur].lf = new_ptr++;
            trie[trie[cur].lf] = trie[trie[prev].lf];
            trie[trie[cur].lf].cnt++;
            cur = trie[cur].lf;
            prev = trie[prev].lf;
        }
    }
    return temp;
}

int givekth(int prev,int cur,int k){
    int ans=0;
    for(int i=21;i>=0;i--){
        if(trie[trie[cur].lf].cnt-trie[trie[prev].lf].cnt>=k){
            cur=trie[cur].lf;
            prev=trie[prev].lf;
        }
        else{
            k-=trie[trie[cur].lf].cnt-trie[trie[prev].lf].cnt;
            ans+=(1<<i);
            cur=trie[cur].rt;
            prev=trie[prev].rt;
        }
    }
    return ans;
}

int maxxor(int prev,int cur,int num){
    int ans=0;
    for(int i=21;i>=0;i--){
        if((num>>i)&1){
            if(trie[trie[prev].lf].cnt<trie[trie[cur].lf].cnt){
                prev=trie[prev].lf;
                cur=trie[cur].lf;
            }
            else{
                ans+=(1<<i);
                prev=trie[prev].rt;
                cur=trie[cur].rt;
            }
        }   
        else{
            if(trie[trie[prev].rt].cnt<trie[trie[cur].rt].cnt){
                ans+=(1<<i);
                prev=trie[prev].rt;
                cur=trie[cur].rt;
            }
            else{
                prev=trie[prev].lf;
                cur=trie[cur].lf;
            }
        }
    }
    return ans;
}

int numberofintergerslessthanorequal(int prev,int cur,int num){
    int ans=0;
    for(int i=21;i>=0;i--){
        if((num>>i)&1){
            ans+=(trie[trie[cur].lf].cnt-trie[trie[prev].lf].cnt);
            cur=trie[cur].rt;
            prev=trie[prev].rt;
        }             
        else{
            cur=trie[cur].lf;   
            prev=trie[prev].lf;
        }           
    }
    ans+=trie[cur].cnt-trie[prev].cnt;
    return ans;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    root[0] = 0;
    trie[0].lf = trie[0].rt = trie[0].cnt = 0;
    new_ptr = 1;
    int n = 1;

    int m; cin>>m;
    while(m--){
        int type; cin>>type;
        if(type==0){
            int x; cin>>x;
            root[n] = insert(root[n-1], x);
            n++;
        }
        else if(type==1){
            int l,r,k;
            cin>>l>>r>>k;           
            cout<<maxxor(root[l-1],root[r],k)<<'\n';
        }
        else if(type==2){
            int k;
            cin>>k;
            n-=k;
        }
        else if(type==3){
            int l,r,x;
            cin>>l>>r>>x;
            cout<<numberofintergerslessthanorequal(root[l-1],root[r],x)<<'\n';
        }   
        else{
            int l,r,k;
            cin>>l>>r>>k;      
            cout<<givekth(root[l-1],root[r],k)<<'\n';   
        }
    }

    return 0;
}