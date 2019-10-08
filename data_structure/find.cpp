#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
using namespace std;

/* Sequntial Search
	Set a guard unit to optimize for-loop.
*/

/* Binary Search
	The sequence need to be orderd.
*/
int BinarySearch(vector<int> &seq, int target)
{
	int low = 0;
	int high = seq.size(); // if `int high = seq.size()-1`, then should use `while(low <= high)`
	while (low < high)	 // caution: cann't be <=, otherwise will result in endless loop.
	{
		int mid = low + (high - low) / 2; // if use mid=(low+high)/2 instead, overflow happens easier.
		if (seq[mid] > target)
			high = mid; // it doesn't matter wether high is set to mid or mid-1.
		else if (seq[mid] < target)
			low = mid + 1; // caution: if no +1, then will be low==mid==high-1 and trap to infinite loop
		else
			return mid;
	}
	return -1; // -1 means not found.
}

template <typename Iter, typename T>
Iter __binary_search_equal(Iter _begin, Iter _end, T target)
{
	Iter low = _begin, high = _end;

	while (low < high) // caution: cann't be <=, otherwise will result in endless loop.
	{
		Iter mid = low + (high - low) / 2; // if use mid=(low+high)/2 instead, overflow happens easier.
		if (*mid > target)
			high = mid; // it doesn't matter wether high is set to mid or mid-1.
		else if (*mid < target)
			low = mid + 1; // caution: if no +1, then will be low==mid==high-1 and trap to infinite loop
		else
			return mid;
	}
	return _end; // _end means not found.
}

template <typename Iter, typename T>
Iter __binary_search_compre(Iter _begin, Iter _end, T target, bool (*compare)(T &, T &))
{
	auto low = _begin, high = _end;

	while (low < high)
	{
		auto mid = low + (high - low) / 2;
		if (compare(*mid, target))
			high = mid;
		else
			low = mid + 1;
	}
	return low;
}

vector<int>::iterator SuperBinarySearch(
	vector<int>::iterator _begin, vector<int>::iterator _end, int target, bool (*compare)(int &, int &) = nullptr)
{
	int a = 0, b = 1;
	if (compare)
	{
		if (compare(a, b))
		{ // <= or <
			vector<int>::reverse_iterator _rbegin(_end), _rend(_begin);
			auto res = __binary_search_compre(_rbegin, _rend, target, compare);
			return res == _rend ? _end : res.base() - 1;
		}
		else if (compare(b, a))
		{ // >= or >
			return __binary_search_compre(_begin, _end, target, compare);
		}
	}
	return __binary_search_equal(_begin, _end, target);
}

vector<int>::iterator BinarySearchLess_futher(
	vector<int>::iterator _begin, vector<int>::iterator _end, int target)
{
	auto it = SuperBinarySearch(_begin, _end, target,
								(bool (*)(int &, int &))[](int &a, int &b) { return a < b; });
	if (it != _end)
		return SuperBinarySearch(_begin, it + 1, *it,
								 (bool (*)(int &, int &))[](int &a, int &b) { return a >= b; });
	return _end;
}

vector<int>::iterator BinarySearchGreater_futher(
	vector<int>::iterator _begin, vector<int>::iterator _end, int target)
{
	auto it = SuperBinarySearch(_begin, _end, target,
								(bool (*)(int &, int &))[](int &a, int &b) { return a > b; });
	if (it != _end)
		return SuperBinarySearch(_begin, it + 1, *it,
								 (bool (*)(int &, int &))[](int &a, int &b) { return a <= b; });
	return _end;
}

int main(int argc, char *argv[])
{
	int n;
	vector<int> nums = {1, 2, 2, 2, 3, 3, 3};
	while (cin >> n)
	{
		auto p = BinarySearchLess_futher(nums.begin(), nums.end(), n);
		if (p != nums.end())
			cout << "found,at " << p - nums.begin() << " : " << *p << endl;
		else
			cout << "not found." << endl;
	}

	return 0;
}
