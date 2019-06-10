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

class MyString {
public:
	MyString(char* pData=nullptr);
	MyString(const MyString& str);
	~MyString();
	MyString& operator=(const MyString& str) {
		if(&str != this){
			/*
			delete[] m_pData;
			m_pData = new char[strlen(str.m_pData)+1];
			strcpy(m_pData,str.m_pData);
			*/
			MyString tmp(str);
			char* p = tmp.m_pData;
			tmp.m_pData = m_pData;
			m_pData = p;
		}
		return *this;
	}

private:
	char* m_pData;
};

int main(int argc,char *argv[])
{
	char str1[6] = "hello";
	char* p1 = new char[strlen(str1)];
	strcpy(p1,str1);
	cout << p1 << "," << strlen(str1) << "," << strlen(p1) << endl;

	char* p2 = new char[strlen(p1)];
	strcpy(p2,p1);
	cout << p2 << "," << strlen(p2) << endl;

 	return 0;
}
