#include <iostream>
#include <assert.h>
#include <list>
#include <string>
#include <ctime>
#include <functional>
#include <algorithm>
#include <vector>
//-----------------------------------------------------------------------------
#include "Algorithms.h"
#include "Array.h"
#include "Variable.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
#define INPUT_SIZE 100000
//-----------------------------------------------------------------------------

template <class T>
void FillRandom(Array<Variable<T>> arr, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		arr[i] = rand() % size;
}
//-----------------------------------------------------------------------------

template <class F, class T>
void TestAlgorithm(std::function<F(Array<Variable<T>>)>* foo, Array<Variable<T>> input, bool show_result = false)
{
	Array<Variable<T>> input_c = Array<Variable<T>>(INPUT_SIZE);
	Copy(input, input_c, 0, INPUT_SIZE);

	std::clock_t start;
	start = std::clock();

	(*foo)(input_c);

	size_t compare_count = 0;
	
	cout << endl;
	for (size_t i = 0; i < INPUT_SIZE; ++i)
	{
		if(show_result && i < 20)
			cout << to_string(input_c[i]) << ", ";

		compare_count += input_c[i].GetCompareCount();
	}

	cout << endl;

	cout << "Array access count: " << to_string(input_c.GetAccessCount()) << endl;
	std::cout << "Compare count: " << compare_count << std::endl;
	std::cout << "Time: " << (std::clock() - start) << std::endl;
	std::cout << "=============================" << endl;
}
//-----------------------------------------------------------------------------

template <class F, class T>
void TestAlgorithm(std::function<F(Array<Variable<T>>, size_t i)>* foo, Array<Variable<T>> input, size_t i, bool show_result = false)
{
	Array<Variable<T>> input_c = Array<Variable<T>>(INPUT_SIZE);
	Copy(input, input_c, 0, INPUT_SIZE);

	std::clock_t start;
	start = std::clock();

	(*foo)(input_c, i);

	size_t compare_count = 0;

	cout << endl;
	for (size_t i = 0; i < INPUT_SIZE; ++i)
	{
		if (show_result && i < 20)
			cout << to_string(input_c[i]) << ", ";

		compare_count += input_c[i].GetCompareCount();
	}

	cout << endl;

	cout << "Array access count: " << to_string(input_c.GetAccessCount()) << endl;
	std::cout << "Compare count: " << compare_count << std::endl;
	std::cout << "Time: " << (std::clock() - start) << std::endl;
	std::cout << "=============================" << endl;
}
//-----------------------------------------------------------------------------

int main()
{
	Array<Variable<int>> input = Array<Variable<int>>(INPUT_SIZE);
	FillRandom(input, INPUT_SIZE);

	cout << "Element count : " << INPUT_SIZE << endl;
	
	std::function<void(Array<Variable<int>>)> foo;
	std::function<void(Array<Variable<int>>, size_t i)> s_foo;

	//foo = [](Array<Variable<int>> input) { return Algorithms::Sorting::BubleSort<int>(input, INPUT_SIZE); };
	//TestAlgorithm(&foo, input, true);

	//foo = [](Array<Variable<int>> input) { return Algorithms::Sorting::SelectionSort<int>(input, INPUT_SIZE); };
	//TestAlgorithm(&foo, input, true);

	//foo = [](Array<Variable<int>> input) { return Algorithms::Sorting::InsertionSort<int>(input, INPUT_SIZE); };
	//TestAlgorithm(&foo, input, true);

	//foo = [](Array<Variable<int>> input) { return Algorithms::Sorting::MergeSort<int>(input); };
	//TestAlgorithm(&foo, input, true);

	//foo = [](Array<Variable<int>> input) { return Algorithms::Sorting::HeapSort<int>(input); };
	//TestAlgorithm(&foo, input, true);

	//foo = [](Array<Variable<int>> input) { return Algorithms::Sorting::QuickSort<int>(input); };
	//TestAlgorithm(&foo, input, true);

	foo = [](Array<Variable<int>> input) { return Algorithms::Search::Min<int>(input); };
	TestAlgorithm(&foo, input, true);

	s_foo = [](Array<Variable<int>> input, size_t i) { cout << Algorithms::Search::RandomizedSelect<int>(input, i); };
	TestAlgorithm(&s_foo, input, 5, true);

	system("pause");
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
