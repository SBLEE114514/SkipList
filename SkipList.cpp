#include <bits/stdc++.h>
using namespace std;

template<typename K,typename V>
class SkipList{
	private:
	#define MAXDEP 16
	struct node{
		K Key;
		V Val;
		int h;
		node* nxt[MAXDEP];
		node(K key=K(),V val=V(),int H=0):Key(key),Val(val),h(H){
			for(int i=0;i<MAXDEP;++i) nxt[i]=nullptr;
		}
	};
	node* head;
	int lvl;
	
	int getlevel(){
		int res=0;
		while(res<MAXDEP&&rand()<(RAND_MAX>>2)) ++res;
		return res;
	}
	
	#undef MAXDEP
	public:
	SkipList(){
		head=new node();
		lvl=0;
	}
	~SkipList(){
		delete head;
	}
	node* find(K key){
		node* p=head;
		for(int i=lvl;~i;--i) while(p->nxt[i]!=nullptr&&p->nxt[i]->Key<key) p=p->nxt[i];
		if(p->nxt[0]==nullptr||p->nxt[0]->Key!=key) return nullptr;
		return p->nxt[0];		
	}
	node* ins(K key,V val){
		node* upd[lvl];
		node* p=head;
		for(int i=lvl;~i;upd[i--]=p) while(p->nxt[i]!=nullptr&&p->nxt[i]->Key<key) p=p->nxt[i];
		if(p->nxt[0]==nullptr||p->nxt[0]->Key!=key){
			p=new node(key,val,getlevel());
			if(p->h>lvl){
				p->h=++lvl;
				head->nxt[lvl]=p;
			}
			for(int i=0;i<p->h;++i) p->nxt[i]=upd[i]->nxt[i],upd[i]->nxt[i]=p;
		}else{
			p->Val=val;
		}
		return p;
	}
	bool del(K key){
		node* upd[lvl];
		if(head==nullptr) return nullptr;
		node* p=head;
		for(int i=lvl;~i;upd[i--]=p) while(p->nxt[i]!=nullptr&&p->nxt[i]->Key<key) p=p->nxt[i];
		if(p==head||p->nxt[0]==nullptr||p->nxt[0]->Key!=key){
			return false;
		}else{
			for(int i=0;i<=p->h;++i) upd[i]->nxt[i]=p->nxt[i];
			if(head->nxt[lvl]==nullptr) --lvl;
			return true;
		}
	}
	V& operator[](K key){
		node* p=find(key);
		if(p==nullptr) p=ins(key,V());
		return p->Val;
	}
};
