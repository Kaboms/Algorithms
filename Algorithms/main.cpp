#include <iostream>
#include <assert.h>
#include <list>
#include <string>
#include <ctime>
#include <functional>
#include <algorithm>
#include <vector>
#include <thread>
#include <mutex>
//-----------------------------------------------------------------------------
#include "Algorithms.h"
#include "Array.h"
#include "Variable.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------

class ThreadManager
{
public:
	template <typename T>
	void ExecAsyncTask(const T& task)
	{
		std::thread thread(task);

		Threads.push_back(move(thread));
	}

	void JoinAll()
	{
		for (size_t i = 0; i < Threads.size(); i++)
		{
			Threads[i].join();
		}
	}

	std::vector<std::thread> Threads;
};

template <class T>
void FillRandom(Array<Variable<T>> arr, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		arr[i] = rand() % size;
}
//-----------------------------------------------------------------------------

std::mutex cout_mutex;

template <class F>
void TestAlgorithm(const F& algorithm, Array<Variable<int>> input, std::string algorithm_name, bool show_result = false)
{
	std::clock_t start;
	start = std::clock();

	Array<Variable<int>> result = algorithm();

	size_t compare_count = 0;

	std::lock_guard<std::mutex> guard(cout_mutex);
	cout << endl;
	for (size_t i = 0; i < input.GetSize(); ++i)
	{
		if(show_result && i < 20)
			cout << to_string(result[i]) << ", ";

		compare_count += result[i].GetCompareCount();
	}

	std::cout << "=============================" << endl;
	cout << algorithm_name << endl;
	cout << "Array access count: " << to_string(result.GetAccessCount()) << endl;
	std::cout << "Compare count: " << compare_count << std::endl;
	std::cout << "Time: " << (std::clock() - start) << std::endl;
	std::cout << "=============================" << endl;
}
//-----------------------------------------------------------------------------

template <class F>
Array<Variable<int>> ExecSortAlgorithm(const F& algorithm, Array<Variable<int>> input)
{
	Array<Variable<int>> input_copy = Array<Variable<int>>(input.GetSize());
	Copy(input, input_copy, 0, input.GetSize());

	algorithm(input_copy);

	return input_copy;
}

void TestAllSortingAlgorithms(Array<Variable<int>> input, bool show_result)
{
	cout << "Test All Sorting Algorithms" << endl;

	std::function<void(Array<Variable<int>>)> foo;

	ThreadManager thread_manager;

	thread_manager.ExecAsyncTask([&]() {
		TestAlgorithm([&]()
			{
				return ExecSortAlgorithm([](Array<Variable<int>>& input) {Algorithms::Sorting::BubleSort<int>(input); }, input);
			}, input, "BubleSort", show_result);
		});

	thread_manager.ExecAsyncTask([&]() {
		TestAlgorithm([&]()
			{
				return ExecSortAlgorithm([](Array<Variable<int>>& input) {Algorithms::Sorting::SelectionSort<int>(input); }, input);
			}, input, "SelectionSort", show_result);
		});

	thread_manager.ExecAsyncTask([&]() {
		TestAlgorithm([&]()
			{
				return ExecSortAlgorithm([](Array<Variable<int>>& input) {Algorithms::Sorting::InsertionSort<int>(input); }, input);
			}, input, "InsertionSort", show_result);
		});

	thread_manager.ExecAsyncTask([&]() {
		TestAlgorithm([&]()
			{
				return ExecSortAlgorithm([](Array<Variable<int>>& input) {Algorithms::Sorting::MergeSort<int>(input); }, input);
			}, input, "MergeSort", show_result);
		});

	thread_manager.ExecAsyncTask([&]() {
		TestAlgorithm([&]()
			{
				return ExecSortAlgorithm([](Array<Variable<int>>& input) {Algorithms::Sorting::HeapSort<int>(input); }, input);
			}, input, "HeapSort", show_result);
		});

	thread_manager.ExecAsyncTask([&]() {
		TestAlgorithm([&]()
			{
				return ExecSortAlgorithm([](Array<Variable<int>>& input) {Algorithms::Sorting::QuickSort<int>(input); }, input);
			}, input, "QuickSort", show_result);
		});

	thread_manager.JoinAll();
}
//-----------------------------------------------------------------------------

int main()
{
	cout << "Input test array size: ";

	size_t ArrayTestSize = 0;
	cin >> ArrayTestSize;

	Array<Variable<int>> input = Array<Variable<int>>(ArrayTestSize);
	FillRandom(input, ArrayTestSize);

	cout << "Elements amount: " << ArrayTestSize << endl;
	
	TestAllSortingAlgorithms(input, false);

	system("pause");
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
