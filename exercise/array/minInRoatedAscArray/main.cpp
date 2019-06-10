#include <iostream>
#include <algorithm>
using namespace std;

template<typename Iter>
int minInRotatedAscArray(Iter _begin, Iter _end)
{
	int n = _end-_begin;
	Iter r = _begin;
	if(n > 1){
		int i = 0, j = n-1;
		while(i < j){
			if(r[i] > r[i+1])
				return r[i+1];
			if(r[j] < r[j-1])
				return r[j];
			i++;j--;
		}
		return r[0];
	}
	return -1;
}

template<typename Iter>
int minInRotatedAscArray2(Iter _begin, Iter _end)
{
	int n = _end-_begin;
	Iter r = _begin;
	if(n > 1){
		int low = 0, high = n-1, mid = low;
		while(r[low] >= r[high]){
			if(high-low == 1)
				break;
			mid = low + (high-low)/2;
			if(r[mid] == r[low] && r[mid] == r[high])
				return minInRotatedAscArray(r+low,r+high+1);
			
			if(r[mid] >= r[low]){
				low = mid;
			}
			else if(r[mid] <= r[high]){
				high = mid;
			}
		}
		return r[mid];
	}
	return -1;
}

int main(int argc,char *argv[])
{
	int nums[] = {3,4,5,1,2};
	vector<vector<int>> v = {
		{1,2,3,4,5},
		{3,4,5,1,2},
		{1,0,1,1,1},
		// {5,3,3,2,1} is not a roatedAscArray
	};
	for(auto& vec : v)
		cout << minInRotatedAscArray2(std::begin(vec),std::end(vec)) << endl;

 	return 0;
}
