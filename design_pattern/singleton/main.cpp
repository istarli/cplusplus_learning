#include <iostream>
// #include <thread>
#include <unistd.h>
// #include <functional>
#include <vector>
#include <queue>
#include <sys/time.h>
#include <signal.h>
#include <fstream>
// #include <mutex>
// #include <memory>
#include <string.h>
using namespace std;

class Singleton {
private:
	Singleton();
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

	static Singleton instance;

public:
	Singleton* Instance()
	{
		return &instance;
	}
};
Singleton Singleton::instance;

int main(int argc,char *argv[])
{
	Singleton* p_ins1 = Singleton::Instance();
	Singleton* p_ins2 = Singleton::Instance();
	cout << p_ins1 << "," << p_ins2 << endl;

 	return 0;
}
