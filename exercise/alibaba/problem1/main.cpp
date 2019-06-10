#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode* father;
	TreeNode() : val(0), left(NULL), right(NULL), father(NULL) {}
	TreeNode(int x) : val(x), left(NULL), right(NULL), father(NULL) {}
};

void CreateTree(TreeNode* & root, TreeNode* father, int i, int v[], int len)
{
	if(!v || len <= 0 || i >= len)
		return;

	root = new TreeNode(v[i]);
	root->father = father;
	CreateTree(root->left, root, 2*i+1, v, len);
	CreateTree(root->right, root, 2*i+2, v, len);
}

void DeleteTree(TreeNode* root)
{
	if(root)
	{
		DeleteTree(root->left);
		DeleteTree(root->right);
		delete root;
	}
}

void PreOrder(TreeNode* root)
{
	if(root)
	{
		cout << root->val << " ";
		PreOrder(root->left);
		PreOrder(root->right);
	}
}

TreeNode* GetTreeNodeById(TreeNode* root, int n)
{
	if(root)
	{
		queue<TreeNode*> q;
		q.push(root);
		int id = 0;
		while(!q.empty())
		{
			TreeNode* p = q.front();
			q.pop();
			// cout << "(" << id << "," << p->val << ") ";
			if(id++ == n)
				return p;

			if(p->left)
				q.push(p->left);
			if(p->right)
				q.push(p->right);
		}
	}
	return NULL;
}

int Distance_helper(TreeNode* p, TreeNode* q, set<TreeNode*>& flag)
{
	if(!p || !q)
		return -1;
	else if(p == q)
		return 0;

	flag.insert(p);
	int a[3] = {-1,-1,-1};
	TreeNode* vec[3] = {p->left, p->right, p->father};
	for(int i = 0; i < 3; i++){
		if(vec[i] && !flag.count(vec[i])){
			flag.insert(vec[i]);
			int tmp = Distance_helper(vec[i], q, flag);
			if(tmp != -1)
				a[i] = tmp + 1;
		}
	}
	for(int i = 0; i < 3; i++){
		if(a[i] >= 0)
			return a[i];
	}

	return -1;
}

int Distance(TreeNode* p, TreeNode* q)
{
	if(!p || !q)
		return -1;

	set<TreeNode*> flag;
	return Distance_helper(p, q ,flag);
}

void TestCase(TreeNode* root, int id1, int id2)
{
	TreeNode* p = GetTreeNodeById(root,id1);
	TreeNode* q = GetTreeNodeById(root,id2);
	cout << Distance(p, q) << endl;
}

int main(int argc, char* argv[])
{
	int nums[6] = {0,1,2,3,4,5};
	TreeNode* root = NULL;
	CreateTree(root, NULL, 0, nums, 6);
	// PreOrder(root);
	// cout << endl;
	TestCase(root,0,5);
	TestCase(root,1,5);
	TestCase(root,4,5);
	TestCase(root,5,5);
	TestCase(root,1,2);

	DeleteTree(root);
	return 0;
}