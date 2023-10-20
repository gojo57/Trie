#include<iostream>
#include<queue>
#include<map>
#define hashmap map<char,node*>
using namespace std;
class node{
	public:
	char data;
	hashmap h;
	bool terminal;
	node(char d){
		data=d;
		terminal=false;
	}
};
class trie{
	public:
	node *root;
	trie(){
		root=new node('\0');
	}
	void addword(string s){
		node* temp=root;
		for(int i=0;s[i]!='\0';i++){
			char ch=s[i];
			if(temp->h.count(ch)==0){
				node *child=new node(ch);
				temp->h[ch]=child;
				temp=child;
			}
			else{
				temp=temp->h[ch];
			}
		}
		temp->terminal=true;
	}
	void print(node * temp,string word){
        if(temp->terminal){
           cout<<word<<endl;
        }
        node * t;
        string w;
        for(auto  it=temp->h.begin();it!=temp->h.end();it++){
            t=temp->h[it->first];
            w=word+it->first;
            print(t,w);  
        }
        return ;
    }
	bool search(string word){
        node * temp=root;
        char ch;
        for(int i=0;word[i]!='\0';i++){
            ch=word[i]; 
            if(temp->h.count(ch)){
               temp=temp->h[ch];  
            }
            else{
               return false;
            }
        }
        print(temp,word);
        return true;
    }
};
int main() {
	int n;
    cin>>n;
	string s;
	trie t;
	for(int i=0;i<n;i++){
		cin>>s;
		t.addword(s);
	}
	int q;
	cin>>q;
	for(int i=0;i<q;i++){
		cin>>s;
        int val=t.search(s);
        if(val==false){
            cout<<"No suggestions"<<endl;  
            t.addword(s); //  this is where the update was necessary
        }
	}
	return 0;
}