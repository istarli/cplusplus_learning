#include <iostream>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;

void* MyMemcpy(void* dst, const void* src, unsigned int count)
{
	if(nullptr == src || nullptr == dst)
		return nullptr;

	void *ret = dst; // save at first if dst is changed
	int add = 1; // default copy from low to high
	if(dst > src && (char*)dst < ((char*)src + count)){
		// bad overlap, copy from high to low
		src = (char*)src + count - 1;
		dst = (char*)dst + count - 1;
		add = -1;		
	}

	int rem = count%4;
	count -= rem;
	while(count){
		// copy 4 bytes once
		count -= 4;
		*(int*)dst = *(int*)src;
		src = (int*)src + add;
		dst = (int*)dst + add;		
	}
	while(rem--){
		// copy 1 byte once
		*(char*)dst = *(char*)src;
		src = (char*)src + add;
		dst = (char*)dst + add;	
	}

	return ret;
}

int MyStrlen(const char* s)
{
	if(nullptr == s)
		return -1;

	const char* eos = s;
	while(*eos++);
	return (eos - s - 1);
}

char* MyStrcpy(char* dst, const char* src)
{
	if(nullptr == src || nullptr == dst)
		return nullptr;
	// use memcpy to solve overlap
	return (char*)MyMemcpy(dst,src,MyStrlen(src)+1);
}

int main(int argc,char *argv[])
{
	char a[40] = "hello world!";
	char b[40];
	cout << (char*)MyMemcpy(a+5,a,20) << endl;
	cout << a << endl;
	cout << MyStrcpy(b,a) << endl;

 	return 0;
}
