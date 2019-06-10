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

bool Find(int* matrix, int rows, int cols, int num)
{
	int i = 0, j = cols-1;

	if(matrix != nullptr && rows > 0 && cols > 0)
	{
		while(i < rows && j >=0)
		{
			int index = i*rows + j;
			if(matrix[index] > num)
				j--;
			else if(matrix[index] < num)
				i++;
			else
				return true;
		}
	}

	return false;
}

int main(int argc,char *argv[])
{
	// int matrix[4][4] = {
	// 	{1,2,8,9},
	// 	{2,4,9,12},
	// 	{4,7,10,13},
	// 	{6,8,11,15}
	// };
	int* matrix = nullptr;

	if(Find(matrix,4,4,16))
		cout << "Found" << endl;
	else
		cout << "Not found" << endl;

 	return 0;
}
