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

BinaryTreeNode* CreateTree(int i, int v[], int len)
{
	if(!v || len <= 0 || i >= len)
		return nullptr;

	auto root = new BinaryTreeNode(v[i]);
	root->left = CreateTree(2*i+1,v,len);
	root->right = CreateTree(2*i+2,v,len);

	return root;
}

/*
	use reference.
*/
void CreateTree(int i, int v[], int len, BinaryTreeNode* & root)
{
	if(!v || len <= 0 || i >= len)
		return;
	root = new BinaryTreeNode(v[i]);
	CreateTree(2*i+1,v,len, root->left);
	CreateTree(2*i+2,v,len, root->right);
}

/*
	Refer to PreOrder1().
*/
BinaryTreeNode* CreateTree(int v[], int len)
{
	if(!v || len <= 0)
		return nullptr;

	auto root = new BinaryTreeNode(v[0]);
	stack<BinaryTreeNode*> s;
	s.push(root);
	int i = 0;
	int flag[len] = {0};
	while(!s.empty())
	{
		auto p = s.top();
		if(0 == flag[i])
		{
			flag[i] = 1;
			if(2*i+1 < len)
			{
				i = 2*i+1;
				p->left = new BinaryTreeNode(v[i]);
				s.push(p->left); 
			}
		}
		else if(1 == flag[i])
		{
			flag[i] = 2;
			if(2*i+2 < len)
			{
				i = 2*i+2;
				p->right = new BinaryTreeNode(v[i]);
				s.push(p->right);
			} 
		}
		else{
			i = (i-1)/2;
			s.pop();
		}
	}

	return root;
}

/*
	Refer to PreOrderNR().
*/
BinaryTreeNode* CreateTreeDF(int v[], int len)
{
	if(!v || len <= 0)
		return nullptr;

	using Node = pair<int,BinaryTreeNode*>;
	stack<Node> s;
	int i = 0;
	BinaryTreeNode* root = nullptr;
	BinaryTreeNode** p = &root;
	while(i < len || !s.empty())
	{
		if(i < len)
		{
			*p = new BinaryTreeNode(v[i]);
			s.push(Node(i,*p));
			p = &((*p)->left);
			i = 2*i+1;
		}
		else{
			p = &(s.top().second->right);
			i = 2*(s.top().first)+2;
			s.pop();
		}
	}

	return root;
}

/*
	Refer to BFS().
	About the reference and pointer:
		If p wouldn't be changed after it was assigned,
		then you can use *& to insteat **. 
*/
BinaryTreeNode* CreateTreeBF(int v[], int len)
{
	if(!v || len <= 0)
		return nullptr;

	BinaryTreeNode* root = nullptr;
	// using Node = pair<int,BinaryTreeNode**>;
	using Node = pair<int,BinaryTreeNode*&>;
	queue<Node> q;
	// q.push(Node(0,&root));
	q.push(Node(0,root));
	while(!q.empty())
	{
		// BinaryTreeNode** p = q.front().second;
		BinaryTreeNode* & p = q.front().second;
		int i = q.front().first;
		q.pop();
		// (*p) = new BinaryTreeNode(v[i]);
		p = new BinaryTreeNode(v[i]);
		if(2*i+1 < len)
			// q.push(Node(2*i+1,&(*p)->left));
			q.push(Node(2*i+1,p->left));
		if(2*i+2 < len)
			// q.push(Node(2*i+2,&(*p)->right));
			q.push(Node(2*i+2,p->right));
	}

	return root;
}

/*
	Refer to BFS_Floor().
*/
BinaryTreeNode* CreateTreeWithNull(int numbers[], int len)
{
	if(!numbers || len <= 0)
		return nullptr;

	BinaryTreeNode* root = new BinaryTreeNode(numbers[0]);

	queue<BinaryTreeNode*> q;
	q.push(root);
	int k = 1;
	while(!q.empty())
	{
		vector<BinaryTreeNode*> v;
		while(!q.empty())
		{
			v.push_back(q.front());
			q.pop();
		}

		bool finish = false;
		for(int i = 0; i < v.size(); i++)
		{
			BinaryTreeNode** ptr[] = { &(v[i]->left), &(v[i]->right) };
			for(auto p : ptr)
			{
				if(k < len)
				{
					if(numbers[k] != INT_MAX){
						*p = new BinaryTreeNode(numbers[k]);
						q.push(*p);
					}
					k++;
				}
				else{
					finish = true;
					break;
				}
			}
		}

		if(finish)
			break;
	}

	return root;
}

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

void InsertToSortTree(int val, BinaryTreeNode** root)
{
	if(*root == nullptr)
		*root = new BinaryTreeNode(val);
	else if(val < (*root)->val)
		InsertToSortTree(val,&(*root)->left);
	else
		InsertToSortTree(val,&(*root)->right);	
}
/*
	use reference to instead pointer.
*/
void InsertToSortTree(int val, BinaryTreeNode* & root)
{
	if(root == nullptr)
		root = new BinaryTreeNode(val);
	else if(val < root->val)
		InsertToSortTree(val,root->left);
	else
		InsertToSortTree(val,root->right);	
}

/*
	Called by DeleteFromSortTree().
	To delete the matched node.
	Caution: reference of pointer is necesarry.
*/
bool DeleteSortTreeNode(BinaryTreeNode* & root)
{
	BinaryTreeNode *q, *s;
	if(!root->left){
		q = root;
		root = root->right;
		delete q;
	}
	else if(!root->right){
		q = root;
		root = root->left;
		delete q;
	}
	else{
		q = root;
		s = root->left;
		while(s->right){
			q = s;
			s = s->right;
		}
		root->val = s->val;
		if(q != root)
			q->right = s->left;
		else
			root->right = s->left;
		delete s;
	}
}
/*
	To find the matched node and call DeleteSortTreeNode().
*/
bool DeleteFromSortTree(int val, BinaryTreeNode* & root)
{
	if(root == nullptr)
		return false;
	else if(root->val == val)
		// the reference of pointer need to be used,
		// or use the two-dimension pointer instead.
		return DeleteSortTreeNode(root); 
	else if(root->val > val)
		return DeleteFromSortTree(val,root->left);
	else
		return DeleteFromSortTree(val,root->right);

	return false;
}

BinaryTreeNode* CreateSortTree(int v[], int len)
{
	if(!v || len < 0) 
		return nullptr;
	auto root = new BinaryTreeNode(v[0]);
	for(int i = 1; i < len; i++)
		InsertToSortTree(v[i],root);
		// InsertToSortTree(v[i],&root);
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

/*
	Refer to PreOrderNR.
*/
void DeleteTreeNR(BinaryTreeNode* root)
{
	using Node = pair<bool,BinaryTreeNode*>;
	stack<Node> s;
	auto p = root;
	do{
		if(p)
		{
			s.push(Node(false,p));
			p = p->left;
		}
		else if(!s.top().first)
		{
			p = s.top().second->right;
			s.top().first = true;
		}
		else{
			delete s.top().second;
			s.pop();
		}
	}while(!s.empty());
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

/*
The direct think way:
	get-current-from-stack-top and push-left or push-right or pop-top due to flag.
	current-pop is after both-visited.
Flag to mark the cases: 
	(no-child-visited, left-child-visited,both-child-visited)
*/
void PreOrder1(BinaryTreeNode* root)
{
	if(!root)
		return;

	using Node = pair<int,BinaryTreeNode*>;
	stack<Node> s;
	s.push(Node(0,root));
	while(!s.empty())
	{
		Node& p = s.top();
		
		if(0 == p.first)
		{
			cout << p.second->val << " ";
			p.first = 1;
			if(p.second->left)
				s.push(Node(0,p.second->left));
		}
		else if(1 == p.first)
		{
			p.first = 2;
			if(p.second->right)
				s.push(Node(0,p.second->right));
		}
		else
			s.pop();
	}
}

/*
Improve PreOrder1:
	get-current-from-stack-top and push-left or pop-top-and-push-right due to flag.
	current-pop is after left-visited and before right-visited.
Flag to mark the cases: 
	(no-child-visited, left-child-visited)
*/
void PreOrder2(BinaryTreeNode* root)
{
	if(!root)
		return;

	using Node = pair<int,BinaryTreeNode*>;
	stack<Node> s;
	s.push(Node(0,root));
	while(!s.empty())
	{
		Node& p = s.top();
		
		if(0 == p.first)
		{
			cout << p.second->val << " ";
			p.first = 1;
			if(p.second->left)
				s.push(Node(0,p.second->left));
		}
		else
		{
			auto right = p.second->right;
			s.pop();
			if(right)
				s.push(Node(0,right));
		}
	}
}

/*
Improve PreOrder2:
	push-current-and-move-to-left or move-to-right or pop-top.
	current-pop is after both-visited.
Flag to mark the cases: 
	(no-child-visited, both-visited)
*/
void PreOrder3(BinaryTreeNode* root)
{
	if(!root)
		return;

	using Node = pair<bool,BinaryTreeNode*>;
	stack<Node> s;
	auto p = root;
	do{
		if(p)
		{
			s.push(Node(false,p));
			cout << p->val << " ";
			p = p->left;
		}
		else if(!s.top().first){
			p = s.top().second->right;
			s.top().first = true;
		}
		else
			s.pop();

	}while(!s.empty());
}

/*
Improve PreOrder3:
	push-current-and-move-to-left or move-to-right-and-pop-top.
	current-pop is after left-visited and before right-visited.
Don't need flag and pay attention to:
	"while(p || !s.empty())", the check of p is essential.
*/
void PreOrder4(BinaryTreeNode* root)
{
	if(!root)
		return;

	stack<BinaryTreeNode*> s;
	auto p = root;
	do{
		if(p)
		{
			s.push(p);
			cout << p->val << " ";
			p = p->left;
		}
		else{
			p = s.top()->right;
			s.pop();
		}

	}while(p || !s.empty());
}

/*
Improve PreOrder4:
	use while{} to replace do{}while().
*/
void PreOrderNR(BinaryTreeNode* root)
{
	stack<BinaryTreeNode*> s;
	auto p = root;
	while(p || !s.empty())
	{
		if(p)
		{
			s.push(p);
			cout << p->val << " ";
			p = p->left;
		}
		else
		{
			p = s.top()->right;
			s.pop();
		}
	}
}

void InOrder(BinaryTreeNode* root)
{
	if(root)
	{
		InOrder(root->left);
		cout << root->val << " ";
		InOrder(root->right);
	}
}

/*
	Refer to PreOrderNR.
*/
void InOrderNR(BinaryTreeNode* root)
{
	stack<BinaryTreeNode*> s;
	auto p = root;
	while(p || !s.empty())
	{
		if(p)
		{
			s.push(p);
			p = p->left;
		}
		else
		{
			cout << s.top()->val << " ";
			p = s.top()->right;
			s.pop();
		}
	}
}

void PostOrder(BinaryTreeNode* root)
{
	if(root)
	{
		PostOrder(root->left);
		PostOrder(root->right);
		cout << root->val << " ";
	}
}

/*
	Refer to PreOrder3.
	Cann't refer to PreOrderNR.
*/
void PostOrderNR(BinaryTreeNode* root)
{
	if(!root) return; // Caution : to avoid visit s.top() when s is empty.
	using Node = pair<bool,BinaryTreeNode*>;
	stack<Node> s;
	auto p = root;
	do{
		if(p)
		{
			s.push(Node(false,p));
			p = p->left;
		}
		else if(!s.top().first)
		{
			p = s.top().second->right;
			s.top().first = true;
		}
		else{
			cout << s.top().second->val << " ";
			s.pop();
		}
	}while(!s.empty());
}

void BFS(BinaryTreeNode* root)
{
	if(!root)
		return;

	queue<BinaryTreeNode*> q;
	q.push(root);
	while(!q.empty())
	{
		auto p = q.front();
		q.pop();

		cout << p->val << " ";
		if(p->left)
			q.push(p->left);
		if(p->right)
			q.push(p->right);
	}
}

void BFS_Floor(BinaryTreeNode* root)
{
	if(!root)
		return;

	queue<BinaryTreeNode*> q;
	q.push(root);
	while(!q.empty())
	{
		vector<BinaryTreeNode*> v;
		while(!q.empty())
		{
			v.push_back(q.front());
			q.pop();
		}

		for(auto p : v)
		{
			cout << p->val << " ";
			if(p->left)
				q.push(p->left);
			if(p->right)
				q.push(p->right);
		}
		cout << endl;
	}	
}

void BFS_Floor_R_helper(BinaryTreeNode* root, vector<vector<int>>& v, int depth)
{
	if(!root)
		return;

	if(depth+1 > v.size())
		v.push_back(vector<int>());
	v[depth].push_back(root->val);

	BFS_Floor_R_helper(root->left,v,depth+1);
	BFS_Floor_R_helper(root->right,v,depth+1);
}

void BFS_Floor_R(BinaryTreeNode* root)
{
	vector<vector<int>> v;
	BFS_Floor_R_helper(root,v,0);
	for(auto row : v)
	{
		for(auto x : row)
			cout << x << " ";
		cout << endl;
	}
}

int main(int argc,char *argv[])
{
	// int a[] = {1,2,4,7,3,5,6,8};
	// int b[] = {4,7,2,1,5,3,8,6};
	// auto root = CreateTreeByPreOrderAndInOrderNR(a,b,8);

	// int v[] = {0,1,2,INT_MAX,4,5,6,7};
	// auto root = CreateTreeWithNull(v,8);
	
	int v[] = {5,7,8,3,1,9,6,0};
	auto root = CreateSortTree(v,8);
	DeleteFromSortTree(5,root);

	PreOrder(root);
	cout << endl;
	PreOrderNR(root);
	cout << endl << endl;

	InOrder(root);
	cout << endl;
	InOrderNR(root);
	cout << endl << endl;

	PostOrder(root);
	cout << endl;
	PostOrderNR(root);
	cout << endl << endl;

	BFS_Floor(root);
	cout << endl;
	BFS_Floor_R(root);
	cout << endl;

	DeleteTreeNR(root);


 	return 0;
}
