#include <iostream>
#include <algorithm>
using namespace std;

void myPrint(string num)
{
	int i = 0;
	for(; i < num.size(); i++){
		if(num[i] > '0')
			break;
	}
	cout << num.substr(i) << " ";	
}

bool next(string& num, const string& _max)
{
	if(num < _max){
		int i = num.size()-1;
		bool carry = 1;
		while(carry){
			if(num[i] == '9'){
				carry = 1;
				num[i] = '0';
			}
			else{
				num[i] += 1;
				carry = 0;
			}
			i--;
		};
		return true;
	}
	return false;
}

void printAll(int n)
{
	string _max(n,'9');
	string num(n,'0');
	while(next(num,_max)){
		myPrint(num);
	}
	cout << endl;
}

void printAll2(string s, int n)
{
	if(s.size() == n){
		myPrint(s);
		return;
	}
	for(int i = 0; i <= 9; i++){
		printAll2(s+string(1,'0'+i),n);
	}
}

int main(int argc,char *argv[])
{
	printAll2("0",3);
 	return 0;
}
