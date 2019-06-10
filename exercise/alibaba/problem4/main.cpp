#include <iostream>
#include <algorithm>
using namespace std;

struct ListNode{
	int val;
	ListNode* next;
	ListNode() : val(0), next(NULL) {}
};

ListNode* CreateCircleList(int n, int k=-1)
{
	if(n <= 0)
		return NULL;

	ListNode* head = NULL;
	ListNode** p = &head;
	ListNode* cross = NULL;
	ListNode* tail = NULL;
	for(int i = 0; i < n; i++){
		*p = new ListNode();
		tail = *p;
		if(k == i)
			cross = *p;
		p = &(*p)->next;
	}
	if(cross)
		tail->next = cross;

	return head;
}

void DeleteCircleList(ListNode* head, int n)
{
	ListNode* p = head;
	for(int i = 0; i < n; i++){
		ListNode* q = p;
		p = p->next;
		delete q;
	}
}

bool CircleCheck(ListNode* head)
{
	if(!head)
		return false;

	ListNode* p = head, *q = head;
	do{
		if(!p)
			return false;
		p = p->next;
		if(p)
			p = p->next;
		q = q->next;
	}while(p != q);

	return true;
}

void TestCase(int len, int k)
{
	ListNode* head = CreateCircleList(len,k);
	if(CircleCheck(head))
		cout << "List has circle !" << endl;
	else
		cout << "List don't have a circle ." << endl;
	DeleteCircleList(head,len);	
}

int main(int argc, char* argv[])
{
	TestCase(5,0); // tail->next = head;
	TestCase(5,1); // tail->next = head;
	TestCase(5,-1); // tail->next = NULL;

	return 0;
}