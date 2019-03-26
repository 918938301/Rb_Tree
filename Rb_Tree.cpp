#include<iostream>
using namespace std;
bool red=true;
bool black=false;
class TreeNode{
public:
	int key;//键值 
	int val;//映射值 
	TreeNode* left,*right;//左右子树 
	int N;//这棵子树中的结点总数 
	bool color;//父节点指向它的链接的颜色 
	TreeNode(int x,int y,int n,bool color) :key(x),val(y),left(NULL),right(NULL),color(color){}
};
class Rb_Tree{
private:
	bool isRed(TreeNode* x) {
		if(x==NULL) return false;
		return x->color==red;
	}
	 int size(TreeNode* x) {
		if(x==NULL) return 0;
		else return x->N+1;
	}
	TreeNode* rotateLeft(TreeNode* h) {
		TreeNode* x=h->right;
		h->right=x->left;
		x->left=h;
		x->color=h->color;
		h->color=red;
		x->N=h->N;
		h->N=1+size(h->left)+size(h->right);
		return x;
	}
	TreeNode* rotateRight(TreeNode* h){
		TreeNode* x=h->left;
		h->left=x->right;
		x->right=h;
		x->color=h->color;
		h->color=red;
		x->N=h->N;
		h->N=1+size(h->left)+size(h->right);
		return x;
	}
	void flipColors(TreeNode* h) {
		h->color=red;
		h->left->color=black;
		h->right->color=black;
	}
	TreeNode* put(TreeNode* h,int key,int val) {
		if(h==NULL)
			return new TreeNode(key,val,1,red);
		if(h->key>key) h->left=put(h->left,key,val);
		else if(h->key<key) h->right=put(h->right,key,val);
		else h->val=val;
		if(isRed(h->right)&&!isRed(h->left)) h=rotateLeft(h);
		if(isRed(h->left)&&isRed(h->left->left)) h=rotateRight(h);
		if(isRed(h->left)&&isRed(h->right)) flipColors(h);
		h->N=size(h->left)+size(h->right)+1;
		return h;
		
	}
public:
	TreeNode* root;
	Rb_Tree(TreeNode* root){
		root=root;
	}
	void put(int key,int val) {
		root=put(root,key,val);
		root->color=black;
	}
	int search(TreeNode* root,int key) {
		if(root==NULL) return -1;
		else if(key==root->key) return root->val;
		else if(key<root->key) return search(root->left,key);
		else if(key>root->key) return search(root->right,key);
	}
	
}; 
int main() {
	int key[10]={2,3,1,4,6,7,5,8,9,0};
	int val[10]={1,2,3,4,5,6,7,8,9,0};
	TreeNode* root=NULL;
	Rb_Tree tree(root);
	for(int i=0;i<10;i++) {
		tree.put(key[i],val[i]);
	}
	cout<<tree.search(tree.root,2);
}
