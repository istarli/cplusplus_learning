#include <iostream>
#include <thread>
#include <unistd.h>
#include <functional>
#include <vector>
#include <queue>
#include <sys/time.h>
#include <signal.h>
#include <fstream>
#include <mutex>
#include <memory>
#include <string.h>
using namespace std;

void ReplaceBlank(char s[])
{
	if(s == nullptr)
		return;

	int i = 0;
	int count = 0;
	while(s[i] != '\0')
	{
		if(s[i] == ' ')
			count++;
		i++;
	}
	int len = i+1;
	int new_len = len + 2*count;
	int p1 = len-1;
	int p2 = new_len-1;
	while(p1 < p2)
	{
		if(s[p1] != ' ')
			s[p2--] = s[p1--];
		else
		{
			s[p2--] = '0';
			s[p2--] = '2';
			s[p2--] = '%';
			p1--;
		}
	}
}

int main(int argc,char *argv[])
{
	char s[100] = " W e ";
	cout << s << endl;
	ReplaceBlank(s);
	cout << s << endl;

 	return 0;
}
