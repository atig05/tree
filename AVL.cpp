#include<iostream>
#include<stdlib.h>
using namespace std;
struct node{
	int data;
	int bal;
	node *lchild;
	node *rchild;
};
void dot(){
	cout<<"........................................."<<endl;
}
int max(int a,int b){
	if(a>b)
		return a;
	return b;
}
class avlt{
	node* root;
	public:
	avlt(){
		root=NULL;
	}
node *newnode(int n){
		node *q=new node();
		q->data=n;
		return q;
}	
int height(node* root){
	if(root==NULL)
		return 0;
	return max(height(root->lchild),height(root->rchild))+1;
}
int get_bf(node* root){
	return height(root->lchild)-height(root->rchild);
}
node *rotate_right(node *x){
	node *y=x->lchild;
	node *t=y->rchild;
	y->rchild=x;
	x->lchild=t;
	x->bal=get_bf(x);
	y->bal=get_bf(y);
	return y;
}
node *rotate_left(node *x){
	node *y=x->rchild;
	node *t=y->lchild;
	y->lchild=x;
	x->rchild=t;
	x->bal=get_bf(x);
	y->bal=get_bf(y);
	return y;
}
node* LL(node* root){
	node *r=root->lchild;
	r->rchild=root;
	root->bal=0;
	root->lchild=NULL;
	r->bal=0;
	root=r;
	return r;
}
node* RR(node *root){
	node* r=root->rchild;
	r->lchild=root;
	root->bal=0;
	root->rchild=NULL;
	r->bal=0;
	root=r;
	return root;
}
node* LR(node *root){
	node *r=root->lchild;
	root->lchild=r->rchild;
	(root->lchild)->lchild=r;
	r->rchild=NULL;
	return LL(root);
}
node* RL(node* root){
	node*  r=root->rchild;
	(root->rchild)=r->lchild;
	(root->rchild)->rchild=r;
	r->lchild=r->rchild=NULL;
}
node* insert(node *root,int n){
	if(root==NULL){
		root=newnode(n);
		root->bal=0;
		return root;
	}
	//node* t,*parent=root,*p=root;
	if(root->data<n){
		 root->rchild=insert(root->rchild,n);
	}	
	else if(root->data>n){
		 root->lchild=insert(root->lchild,n);
	}
	else{
		cout<<"Data already in thr tree  "<<endl;
	}
	root->bal=height(root->lchild)-height(root->rchild);
	if(root->bal<-1 && n<root->rchild->data){
		root->rchild=rotate_right(root->rchild);
		root= rotate_left(root);
	}
	if(root->bal<-1 && n>root->rchild->data)
		root= rotate_left(root);
	if(root->bal>1 && n<root->lchild->data){
		root= rotate_right(root);
	}
	if(root->bal>1 && n>root->lchild->data){
		root->lchild=rotate_left(root->lchild);
		root= rotate_right(root);
	}
	return  root;
}

void inorder(node *root){
	if(root==NULL)
		return;
	inorder(root->lchild);
		cout<<"(data-"<<root->data<<"  balance factor "<<root->bal<<") ";
	inorder(root->rchild);
		
}
void postorder(node *root){
	if(root==NULL)
		return;
	postorder(root->lchild);
	postorder(root->rchild);
	cout<<"(data-"<<root->data<<"  balance factor "<<root->bal<<") ";
}
void preorder(node *root){
	if(root==NULL)
		return;
	cout<<"(data-"<<root->data<<"  balance factor "<<root->bal<<") ";
	preorder(root->lchild);
	preorder(root->rchild);
}
node *min_value_node(struct node *p)
{
	struct node *curr=p;
	while(curr->lchild!=NULL)
		curr=curr->lchild;
	return curr;
}
void insert(int n){
	root=insert(root,n);

}
 node *delete_node(struct node *root,int key)
{
	if(root==NULL)
		return root;
	if(key<root->data)
		root->lchild=delete_node(root->lchild,key);
	else if(key>root->data)
		root->rchild=delete_node(root->rchild,key);
	else
	{
		if((root->lchild==NULL)||(root->rchild==NULL))
		{
			struct node *temp=root->lchild ? root->lchild : root->rchild;
			if(temp==NULL)
			{
				temp=root;
				root=NULL;
			}
			else
			{
				*root=*temp;
			}
			free(temp);
		}
		else
		{
			struct node *temp=min_value_node(root->rchild);
			root->data=temp->data;
			root->rchild=delete_node(root->rchild,temp->data);
		}
	}
	if(root==NULL)
		return root;

	int balance=get_bf(root);
	if(balance>1 && get_bf(root->lchild)>=0)
	{
		return rotate_right(root);
	}
	if(balance>1 && get_bf(root->lchild)<0)
	{
		root->lchild=rotate_left(root->lchild);
		return rotate_right(root);
	}
	if(balance<-1 && get_bf(root->rchild)<=0)
		return rotate_left(root);
	if(balance<-1 && get_bf(root->rchild)>0)
	{
		root->rchild=rotate_right(root->rchild);
		return rotate_left(root);
	}
	return root;
}//
void del(int n){
	if(root==NULL)
	{
		cout<<"underflow.."<<endl;
		return;
	}
	root=delete_node(root,n);
	//root=balance(root);
}
void search(int n){
	
	dot();
	if(root==NULL)
		{
			cout<<"Underflow..";
			dot();
			return;
		}
	node *p=root;
	while(1){
		if(p==NULL){
			cout<<"NOT FOUND..";
			break;
		}
			
		if(p->data==n){
			cout<<"item found..";
			break;
		}
			
		else if(p->data<n)
			p=p->rchild;
		else
			p=p->lchild;
			
	}
	cout<<endl;
	dot();
	
}
void show(){
	int n;
	cout<<"ENTER 1 to inorder "<<endl;
	cout<<"ENTER 2 to preorder "<<endl;
	cout<<"ENTER 3 to postorder "<<endl;
	cin>>n;
	dot();
	switch(n){
		case 1:
			cout<<"INorder"<<endl;
			inorder(root);
			break;
		case 2:
			cout<<"preorder "<<endl;
			preorder(root);
			break;
		case 3:
			cout<<"Postorder"<<endl;
			postorder(root);
	}
	
//	postorder(root);
	cout<<endl;
	dot();
	return;
}
int height(){
	return height(root);
}	
};
int main(void){
	avlt a;

	int m=1;
	while(m!=0){
		
		cout<<endl;
		cout<<"            AVL TREE OPERATION"<<endl;
		dot();
		cout<<"1 to insert "<<endl;
		cout<<"2 to show"<<endl;
		cout<<"3 to find height"<<endl;
		cout<<"4 to search item"<<endl;
		cout<<"5 to delete"<<endl;
		cout<<"0 to close "<<endl<<endl;
		cout<<"Enter choice-";
		cin>>m;
		system("CLS");
		int n,k;
		switch(m){
			case 1:
				
				cout<<"enter value-";
				cin>>n;					
				a.insert(n);
				break;	
			case 2:
				a.show();
				break;
		
			case 3:

				cout<<"height  "<<a.height()<<endl;
				break;		
			case 4:
				
				cout<<"What to search -";
				cin>>n;
				a.search(n);
				break;
			case 5:
				
				cout<<"What to delete -";
				cin>>n;
				a.del(n);
				break;											/*	*/																																					
		}
		cout<<endl<<endl;
	}		
}
