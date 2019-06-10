#include <iostream>
#include <algorithm>
using namespace std;

int random1(){
	return rand()%2;
}

int random2(int n){
	if(n <= 0)
		return 0;

	int k = 0;
	int tmp = n;
	while(tmp > 0){
		tmp >>= 1;
		k++;
	}

	int res = 0;
	do{
		res = 0;
		int num = 1;
		for(int i = 0; i < k; i++){
			res += random1()*num;
			num <<= 1;
		}
	}while(res > n);

	return res;
}

int main(int argc, char* argv[])
{
	for(int i = -10; i < 10; i++){
		cout << random2(i) << endl;
	}

	return 0;
}