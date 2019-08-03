#include <iostream>
#include <vector>
#include <array>
#include <functional>
#include <algorithm>
using namespace std;

/*
	Simple Insert Sort.
	Stable.
	Time Complexity : O(n)~O(n^2)->O(n^2)
	Space Complexity : O(1)
*/
template <typename Iter>
void InsertSort(Iter _begin, Iter _end)
{
	int n = _end - _begin;
	auto r = _begin;

	for (int i = 1; i < n; i++)
	{
		if (r[i] < r[i - 1])
		{
			int tmp = r[i];
			int j = i - 1;
			// attention: j >= 0 is necassary.
			for (; j >= 0 && r[j] > tmp; j--)
				r[j + 1] = r[j];
			r[j + 1] = tmp;
		}
	}
}
/*
	Higl-level insert Sort -> ShellSort.
	Not Stable.
	Time Complexity : O(n*log2(n))~O(n^2)->O(n^1.3)
	Space Complexity : O(1)	
*/
template <typename Iter>
void ShellSort(Iter _begin, Iter _end)
{
	int n = _end - _begin;
	auto r = _begin;

	// d is increment.
	for (int d = n / 2; d >= 1; d = d / 2)
	{
		// A trip of InsertSort.
		for (int i = d; i < n; i++)
		{
			if (r[i] < r[i - d])
			{
				int tmp = r[i];
				int j = i - d;
				// attention: j >= 0 is necessary
				for (; j >= 0 && r[j] > tmp; j -= d)
				{
					r[j + d] = r[j];
				}
				r[j + d] = tmp;
			}
		}
	}
}

/*
	Simple Bubble Sort.
*/
template <typename Iter>
void BubbleSort(Iter _begin, Iter _end)
{
	int n = _end - _begin;
	auto r = _begin;

	for (int i = n; i > 1; i--)
	{
		for (int j = 1; j < i; j++)
		{
			if (r[j] < r[j - 1])
				swap(r[j], r[j - 1]);
		}
	}
}
/*
	Modified Bubble Sort.
	Stable.
	Time Complexity : O(n)~O(n^2)->O(n^2)
	Space Complexity : O(1)
*/
template <typename Iter>
void BubbleSort2(Iter _begin, Iter _end)
{
	int n = _end - _begin;
	auto r = _begin;

	int pos = n - 1;
	while (pos > 0)
	{
		int bound = pos;
		pos = 0; // attention : It's very imporant to set pos=0 here!
		// Use bound in for() instead of pos!
		for (int j = 0; j < bound; ++j)
		{
			if (r[j] > r[j + 1])
			{
				swap(r[j], r[j + 1]);
				pos = j;
			}
		}
	}
}
template <typename Iter>
void BubbleSort3(Iter _begin, Iter _end)
{
	int n = _end - _begin;
	auto r = _begin;

	int pos1 = 0;
	int pos2 = n - 1;
	while (pos2 > pos1)
	{
		// attention : It's very imporant to set pos=0 here!
		// Use bound in for() instead of pos!
		int bound = pos2;
		pos2 = 0;
		int start = pos1;
		pos1 = n;
		for (int j = start; j < bound; ++j)
		{
			if (r[j] > r[j + 1])
			{
				swap(r[j], r[j + 1]);
				pos2 = j;
				if (pos1 == n)
					pos1 = j;
			}
		}
	}
}

/*
	High-level Bubble Sort -> QuickSort
	Not Stable.
	Time Complexity : O(n*log2(n))~O(n^2)->O(n*log2(n))
	Space Complexity : O(log2(n))~O(n)
*/
template <typename Iter>
Iter Partion(Iter _begin, Iter _end)
{
	int n = _end - _begin;
	auto r = _begin;

	int i = 0, j = n - 1, pivot = r[0];
	while (i < j)
	{
		while (i < j && r[j] >= pivot)
			j--; // right-side-scanning
		r[i] = r[j];
		while (i < j && r[i] <= pivot)
			i++;
		r[j] = r[i];
	}
	r[i] = pivot;

	return r + i;
}
template <typename Iter>
void QuickSort(Iter _begin, Iter _end)
{
	if (_begin < _end)
	{
		Iter pivot = Partion(_begin, _end);
		QuickSort(_begin, pivot);
		QuickSort(pivot + 1, _end);
	}
}

/*
	Simple Select Sort.
	The least times to move elements.
	Not Stable. 
	Time Complexity : O(n^2)
	Space Complexity : O(1)
*/
template <typename Iter>
void SelectSort(Iter _begin, Iter _end)
{
	int n = _end - _begin;
	Iter r = _begin;
	for (int i = 0; i < n; i++)
	{
		int minIdx = 0;
		for (int j = i + 1; j < n; j++)
		{
			if (r[minIdx] > r[j])
			{
				minIdx = j;
			}
		}
		swap(r[i], r[minIdx]);
	}
}

/*
	Heap Sort.
		r[0] is the root of heap,
		r[k] is the value to sift,
		m is the last index of the current heap.
	Not Stable.
	Time Complexity : O(n*log2(n))
	Space Complexity : O(1)
*/
template <typename Iter>
void Sift(Iter r, int k, int m)
{
	int i = k, j = 2 * i + 1;
	while (j <= m)
	{
		if (j < m && r[j] < r[j + 1])
			j++;
		if (r[i] >= r[j])
			// Attention : must break here !
			// otherwise j will not be renewed, resulting in dead-loop!
			break;
		else
		{
			swap(r[i], r[j]);
			i = j;
			j = 2 * i + 1;
		}
	}
}
template <typename Iter>
void HeapSort(Iter _begin, Iter _end)
{
	int n = _end - _begin;
	auto r = _begin;
	if (n < 2)
		return;
	// Create heap
	for (int i = (n - 1) / 2; i >= 0; i--)
		Sift(r, i, n - 1);
	// Sift the max-element from the heap
	for (int i = n - 1; i > 0; i--)
	{
		swap(r[0], r[i]);
		Sift(r, 0, i - 1);
	}
}

/*
	Merge Sort
*/
template <typename Iter>
void Merge(Iter r1, int len1, Iter r2, int len2)
{
	if (len1 >= 0 && len2 >= 0)
	{
		int i = 0, j = 0, k = 0;
		int n = len1 + len2;
		using T = decltype(*r1 + 0);
		T tmp[n];

		while (i < len1 && j < len2)
		{
			T x = r1[i] < r2[j] ? r1[i++] : r2[j++];
			tmp[k++] = x;
		}
		while (i < len1)
			tmp[k++] = r1[i++];
		while (j < len2)
			tmp[k++] = r2[j++];

		for (int i = 0; i < n; i++)
			r1[i] = tmp[i];
	}
}

template <typename Iter>
void MergeSort(Iter _begin, Iter _end)
{
	int n = _end - _begin;
	int d = 1;
	while (d < n)
	{
		for (int i = 0; i < n; i += 2 * d)
		{
			if (2 * d <= n - i)
				Merge(_begin + i, d, _begin + i + d, d);
			else if (d <= n - i)
				Merge(_begin + i, d, _begin + i + d, n - i - d);
		}
		d *= 2;
	}
}
template <typename Iter>
void MergeSortR(Iter _begin, Iter _end)
{
	int n = _end - _begin;
	if (n > 1)
	{
		int m = n / 2;
		MergeSortR(_begin, _begin + m);
		MergeSortR(_begin + m, _end);

		Merge(_begin, m, _begin + m, n - m);
	}
}

template <typename Iter>
void MySort(Iter _begin, Iter _end)
{
	InsertSort(_begin, _end);

	for (Iter it = _begin; it != _end; it++)
		cout << *it << " ";
	cout << endl;
}

int main(int argc, char *argv[])
{
	vector<vector<int>> vecs = {
		{},
		{1},
		{2, 1},
		{3, 1, 7, -3, 4, 9, 0, 3},
		{1, 3, 7, -3, 4, 9, 0, 3, 6},
	};

	int nums[7] = {3, 1, 6, -2, 5, 8, 9};

	MySort(begin(nums), end(nums));

	for (auto &v : vecs)
		MySort(v.begin(), v.end());

	return 0;
}