#include<iostream>
#include<stdlib.h>
using namespace std;
struct Node
{
	int key;
	Node* left;
	Node* right;
};
class BST
{
	Node* root;
	public:
		BST()
		{
			root=NULL;
		}
        void insert(int n)
        {
        	if(root==NULL)
        	{
        		Node* node=(Node*)malloc(sizeof(Node));
        		node->key=n;
        		node->left=NULL;
        		node->right=NULL;
        		root=node;
        		return;
			}
			Node* node=(Node*)malloc(sizeof(Node));
			node->key=n;
        	node->left=NULL;
        	node->right=NULL;
			Node* t=root;
			Node* p=t;
			while(t!=NULL)
			{
				p=t;
				if(n<t->key)
					t=t->left;
				else if(n>t->key)
					t=t->right;
				else
				{
					cout<<n<<" is already present"<<endl;
					return;
				}
			}
			if(p->key<n)
				p->right=node;
			else
				p->left=node;
		}
		void inorder(Node* root)
		{
			if(root==NULL)
				return;
			inorder(root->left);
			cout<<root->key<<" ";
			inorder(root->right);
		}
		void inorder()
		
		{   
			
			inorder(root);
		
		}
		void preorder(Node* root)
		{
			if(root==NULL)
			return;
			cout<<root->key<<" ";
			preorder(root->left);			
			preorder(root->right);
		}
		void preorder()
		{
			preorder(root);
		}
		void postorder(Node* root)
		{
			if(root==NULL)
			return;
			postorder(root->left);			
			postorder(root->right);
			cout<<root->key<<" ";
		}
		void postorder()
		{
			postorder(root);
		}
		void countnode(Node* root, int *c)
		{
			if(root==NULL)
				return;
			else
			{
				*c=(*c)+1;
				countnode(root->left,c);
				countnode(root->right,c);
			}
		}
		int countnode()
		{
			int c=0;
			countnode(root,&c);
			return c;
		}
		void countleaf(Node* root, int *c)
		{
			if(root==NULL)
			return;
			else 			
			{
				if(root->left==NULL && root->right==NULL)
					*c=(*c)+1;
				countleaf(root->left,c);
				countleaf(root->right,c);
			}
		}
		int countleaf()
		{
			int c=0;
			countleaf(root,&c);
			return c;
		} 
		bool search(Node* root, int n)
		{
			if(root==NULL)
		      return false;
		    if(n>root->key)
		      return search(root->right,n);
		    else if(n<root->key)
		      return search(root->left,n);
		    else if( n==root->key )
		      return true;
		      
		
		}
		bool search(int n)
		{
			return search(root,n);
		}
		int max1(int a, int b)
		{
			if(a>b)
			return a;
			else
			return b;
		}
		int max(Node* root)
		{
			if(root==NULL)
			   return INT_MIN;
			return max1(root->key,max(root->right));
		}
		int max()
		{
			return max(root);
		}
		int min1(int a, int b)
		{
			if(a<b)
			return a;
			else
			return b;
		}
		int min(Node* root)
		{
			if(root==NULL)
			   return INT_MAX;
			return min1(root->key,min(root->left));
		}
		int min()
		{
			return min(root);
		}
		void nodedelete(int n)
		{
			if(!search(n))
			{
				cout<<n<<" not present"<<endl;
				return;
			}
			Node* t=root;
			Node* p=t;
			while(t->key!=n)
			{
				p=t;
				if(n>t->key)
				  t=t->right;
				else if(n<t->key)
				  t=t->left;
				else
				  break;
			}
			if(t->left==NULL and t->right==NULL)
			{
				if(p->key>t->key)
				{
					p->left=NULL;
					delete t;
				}
				else
				{
					p->right=NULL;
					delete t;
				}
				return;
			}
			if(t->left==NULL)
			{
				if(p->key>t->key)
				{
					p->left=t->right;
					delete t;
				}
				else
				{
					p->right=t->right;
					delete t;
				}
				return;
			}
			if(t->right==NULL)
			{
				if(p->key>t->key)
				{
					p->left=t->left;
					delete t;
				}
				else
				{
					p->right=t->left;
					delete t;
				}
				return;
			}
			else
			{
				int left_max;
				left_max=max(t->left);
				nodedelete(left_max);
				t->key=left_max;
			}
		}
	};
int main()
{
	BST c=BST();
	int m=1,n;
	while(m)
	{
	    cout<<endl<<"1 to insert"<<endl;
		cout<<"2 to inorder"<<endl;	
		cout<<"3 to preorder"<<endl;
		cout<<"4 to postorder"<<endl;
		cout<<"5 to count node"<<endl;
		cout<<"6 to count leaf"<<endl;
		cout<<"7 to search"<<endl;
		cout<<"8 to find max node"<<endl;
		cout<<"9 to find min node"<<endl;
		cout<<"10 to delete node"<<endl;
		cout<<"0 to close"<<endl;
		cin>>m;
		system("CLS");
		switch(m)
		{
			case 1:
				cout<<"Enter value-";
				cin>> n;
				c.insert(n);
				break;				
			case 2:
				c.inorder();
				break;
			case 3:
				c.preorder();
				break;				
			case 4:
			    c.postorder();
				break;
			case 5:
				n=c.countnode();
				cout<<n<<endl;
				break;
			case 6:
				n=c.countleaf();
				cout<<n<<endl;
				break;
			case 7:
				cout<<"Enter value-";
				cin>>n;
				cout<<c.search(n);
				break;
			case 8:
				n=c.max();
				cout<<n<<endl;
				break;
			case 9:
				n=c.min();
				cout<<n<<endl;
				break;
			case 10:
				cout<<"Enter value-";
				cin>> n;
				c.nodedelete(n);
				break;
			case 0:
				cout<<"Closing"<<endl;
				break;
			default:
				cout<<"Choice is wrong"<<endl;
				break;
			}
		}
	}

			

		
		

		
		
		
