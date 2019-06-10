#include <iostream>
#include <vector>
using namespace std;

#define DEBUG(func) do { \
	##ifdef __DEBUG__ \
		func();\
	##endif \
} while(0) \

#define __DEGBUG__

int main()
{

	DEBUG([]{
		cout << "Test" << endl;
	});

    return 0;
}