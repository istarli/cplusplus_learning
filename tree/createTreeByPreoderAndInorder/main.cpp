#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits.h>
using namespace std;

struct BinaryTreeNode {
	int val;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	BinaryTreeNode()
	 : val(0), left(nullptr), right(nullptr) {}
	BinaryTreeNode(int x)
	 : val(x), left(nullptr), right(nullptr) {}
};

BinaryTreeNode* CreateTreeByPreOrderAndInOrder(int pre[], int in[], int len)
{
	if(!pre || !in || len <=0)
		return nullptr;

	BinaryTreeNode* root = new BinaryTreeNode(pre[0]);
	
	int i = 0;
	for(; i < len; i++)
	{
		if(in[i] == pre[0])
			break;
	}
	int* pre_left = pre+1;
	int* pre_right = pre+i+1;
	int* in_left = in;
	int* in_right = in+i+1;
	int len_left = i;
	int len_right = len-i-1;

	root->left = CreateTreeByPreOrderAndInOrder(pre_left,in_left,len_left);
	root->right = CreateTreeByPreOrderAndInOrder(pre_right,in_right,len_right);

	return root;
}

BinaryTreeNode* CreateTreeByPreOrderAndInOrderNR(int pre[], int in[], int len)
{
	if(!pre || !in || len <=0)
		return nullptr;

	struct Node
	{
		int* pre;
		int* in;
		int len;
		int i;
		BinaryTreeNode* p;
		Node(int* _pre, int* _in, int _len, int _i, BinaryTreeNode* _p)
			: pre(_pre), in(_in), len(_len), i(_i), p(_p) {}
	};

	BinaryTreeNode* root = nullptr;
	BinaryTreeNode** p = &root;
	stack<Node> s;
	while((pre && in && len > 0) || !s.empty())
	{
		if(pre && in && len > 0)
		{
			*p = new BinaryTreeNode(pre[0]);

			int i = 0;
			for(; i < len; i++)
			{
				if(in[i] == pre[0])
					break;
			}
			s.push(Node(pre,in,len,i,*p));

			pre = pre+1;
			// int* pre_ = pre+i+1;
			in = in;
			// int* in_right = in+i+1;
			len = i;
			// int len_right = len-i-1;
			p = &(*p)->left;
		}
		else{
			int i = s.top().i;
			pre = s.top().pre+i+1;
			in = s.top().in+i+1;
			len = s.top().len-i-1;
			p = &s.top().p->right;
			s.pop();
		}
	}

	return root;
}

void DeleteTree(BinaryTreeNode* root)
{
	if(root)
	{
		DeleteTree(root->left);
		DeleteTree(root->right);
		delete root;
	}
}

void PreOrder(BinaryTreeNode* root)
{
	if(root)
	{
		cout << root->val << " ";
		PreOrder(root->left);
		PreOrder(root->right);
	}
}

void InOrder(BinaryTreeNode* root)
{
	if(root)
	{
		PreOrder(root->left);
		cout << root->val << " ";
		PreOrder(root->right);
	}
}

int main(int argc,char *argv[])
{
	int len = 8;
	int a[len] = {1,2,4,7,3,5,6,8};
	int b[len] = {4,7,2,1,5,3,8,6};
	
	auto root = CreateTreeByPreOrderAndInOrder(a,b,len);

	PreOrder(root);
	cout << endl;
	InOrder(root);
	cout << endl;

	DeleteTree(root);

 	return 0;
}
