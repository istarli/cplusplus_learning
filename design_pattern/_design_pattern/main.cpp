#include <iostream>
using namespace std;


int main(int argc,char *argv[])
{
	Singleton* p_ins1 = Singleton::Instance();
	Singleton* p_ins2 = Singleton::Instance();
	cout << p_ins1 << "," << p_ins2 << endl;

 	return 0;
}
