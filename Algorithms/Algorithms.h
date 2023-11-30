#pragma once
#include <algorithm>
#include <thread>

#include "Array.h"
#include "Variable.h"
#include "ComparePredicts.h"

template <class T>
using Predicate = std::function<bool(Variable<T>&, T&)>;

template <class T>
using AlgorithmFoo = std::function<void(Array<Variable<T>> input, size_t size, const Predicate<T>& predicate = Less{})>;

namespace Algorithms
{
	uint8_t* AddBinnary(uint8_t* binnary_a, uint8_t* binnary_b, size_t n)
	{
		uint8_t* result = new uint8_t[n + 1];
		memset(result, 0, sizeof(result));

		for (int i = n - 1; i >= 0; i--)
		{
			if (binnary_a[i] & binnary_b[i])
			{
				result[i + 1] = result[i + 1] | 0;
				result[i] = 1;
			}
			else
				result[i + 1] = binnary_a[i] ^ binnary_b[i];
		}
		return result;
	}
	//-----------------------------------------------------------------------------

	namespace Sorting
	{
		template <class T>
		void BubleSort(Array<Variable<T>>& input, const Predicate<T>& predicate = Less{})
		{
			for (size_t i = 0; i < input.GetSize(); i++)
			{
				for (int j = input.GetSize() - 1; j > i; j--)
				{
					if (predicate(input[j], input[j - 1]))
						std::swap(input[j], input[j - 1]);
				}
			}
		}
		//-----------------------------------------------------------------------------

		template <class T>
		void SelectionSort(Array<Variable<T>>& input, const Predicate<T>& predicate = Less{})
		{
			for (size_t i = 0; i < input.GetSize() - 1; i++)
			{
				int compare_index = i;
				for (size_t j = i + 1; j < input.GetSize(); j++)
				{
					if (predicate(input[j], input[compare_index]))
						compare_index = j;
				}
				std::swap(input[i], input[compare_index]);
			}
		}
		//-----------------------------------------------------------------------------

		template <class T>
		void InsertionSort(Array<Variable<T>>& input, const Predicate<T>& predicate = Less{})
		{
			for (size_t i = 1; i < input.GetSize(); i++)
			{
				int value = input[i];
				int j = i - 1;
				while (j >= 0 && !predicate(input[j], value))
				{
					input[j + 1] = input[j];
					j--;
				}
				input[j + 1] = value;
			}
		}
		//----------------------------------------------------------------------------

		template <class T>
		void Merge(Array<Variable<T>>& input, size_t p, size_t q, size_t r, const Predicate<T>& predicate)
		{
			size_t n1 = q - p + 1;
			size_t n2 = r - q;

			Array<Variable<T>> l_array = Array<Variable<T>>(n1);
			Copy(input, l_array, p, n1);

			Array<Variable<T>> r_array = Array<Variable<T>>(n2);
			Copy(input, r_array, q + 1, n2);

			size_t i = 0;
			size_t j = 0;

			for (size_t k = p; k <= r; k++)
			{
				if ((i < n1 && j < n2 && predicate(l_array[i], r_array[j])) || (i < n1 && j >= n2))
				{
					input[k] = l_array[i];
					i++;
				}
				else if (j < n2)
				{
					input[k] = r_array[j];
					j++;
				}
			}

			input.AccessCount += l_array.AccessCount + r_array.AccessCount;
		}

		template <class T>
		void MergeSort(Array<Variable<T>>& input, size_t p, size_t r, const Predicate<T>& predicate = Less{})
		{
			if (p < r)
			{
				size_t q = (p + r) / 2;
				MergeSort(input, p, q, predicate);
				MergeSort(input, q + 1, r, predicate);
				Merge(input, p - 1, q - 1, r - 1, predicate);
			}
		}

		template <class T>
		void MergeSort(Array<Variable<T>>& input, const Predicate<T>& predicate = Less{})
		{
			MergeSort(input, 1, input.GetSize(), predicate);
		}
		//-----------------------------------------------------------------------------

#define LEFT(i) 2 * i
#define RIGHT(i) 2 * i + 1
#define PARENT(i) i / 2

		template <class T>
		void Heapify(Array<Variable<T>>& input, int i, int heap_size, const Predicate<T>& predicate = Less{})
		{
			int left = LEFT(i);
			int right = RIGHT(i);
			int n = i;

			if (left < heap_size && predicate(input[i], input[left]))
				n = left;

			if (right < heap_size && predicate(input[n], input[right]))
				n = right;

			if (n != i)
			{
				std::swap(input[i], input[n]);
				Heapify(input, n, heap_size, predicate);
			}
		}

		template <class T>
		void BuildHeap(Array<Variable<T>>& input, const Predicate<T>& predicate = Less{})
		{
			for (int i = input.GetSize() / 2; i >= 0; i--)
			{
				Heapify(input, i, input.GetSize(), predicate);
			}
		}

		template <class T>
		void HeapSort(Array<Variable<T>>& input, const Predicate<T>& predicate = Less{})
		{
			int heap_size = input.GetSize();

			BuildHeap(input, predicate);
			for (int i = input.GetSize() - 1; i > 0; i--)
			{
				std::swap(input[0], input[i]);
				heap_size--;
				Heapify(input, 0, heap_size, predicate);
			}
		}
		//-----------------------------------------------------------------------------

		template <class T>
		int Partition(Array<Variable<T>>& input, int p, int r, const Predicate<T>& predicate = Less{})
		{
			T x = input[r];
			int i = p - 1;

			for (size_t j = p; j < r; j++)
			{
				if (predicate(input[j], x))
				{
					i++;
					
					if (i != j)
						std::swap(input[i], input[j]);
				}
			}
			std::swap(input[i + 1], input[r]);
			return i + 1;
		}

		template <class T>
		int RandomizedPartition(Array<Variable<T>>& input, int p, int r, const Predicate<T>& predicate = Less{})
		{
			srand(time(NULL));

			int i = rand() % (r - p) + p;
			std::swap(input[r], input[i]);

			return Partition(input, p, r, predicate);
		}

		template <class T>
		void QuickSort(Array<Variable<T>>& input, int p, int r, const Predicate<T>& predicate = Less{})
		{
			if (p < r)
			{
				int q = Partition(input, p, r, predicate);

				QuickSort(input, p, q - 1, predicate);
				QuickSort(input, q + 1, r, predicate);
			}
		}
		template <class T>
		void RandomizedQuickSort(Array<Variable<T>>& input, int p, int r, const Predicate<T>& predicate = Less{})
		{
			if (p < r)
			{
				int q = RandomizedPartition(input, p, r, predicate);

				RandomizedQuickSort(input, p, q - 1, predicate);
				RandomizedQuickSort(input, q + 1, r, predicate);
			}
		}

		template <class T>
		void QuickSort(Array<Variable<T>>& input, const Predicate<T>& predicate = Less{})
		{
			QuickSort(input, 0, input.GetSize() - 1, predicate);
		}		
		template <class T>
		void RandomizedQuickSort(Array<Variable<T>>& input, const Predicate<T>& predicate = Less{})
		{
			RandomizedQuickSort(input, 0, input.GetSize() - 1, predicate);
		}
		//-----------------------------------------------------------------------------

	}
	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------

	namespace Search
	{
		template <class T>
		long long LinearSearch(Array<Variable<T>>& input, size_t size, T search_value)
		{
			for (size_t i = 0; i < size; i++)
			{
				if (Equal<T>(input[i], search_value))
					return i;
			}
			return -1;
		}
		//-----------------------------------------------------------------------------

		template <class T>
		long long RandomizedSelect(Array<Variable<T>>& input, size_t p, size_t r, size_t i)
		{
			if (p == r)
				return input[p];

			size_t q = Sorting::RandomizedPartition(input, p, r);
			size_t k = q - p + 1;

			if (i == k)
				return input[q];
			else if (i < k)
				return RandomizedSelect(input, p, q - 1, i);
			else
				return RandomizedSelect(input, q + 1,r, i - k);

		}
		template <class T>
		long long RandomizedSelect(Array<Variable<T>>& input, size_t i)
		{
			return RandomizedSelect(input, 0, input.GetSize() - 1, i);
		}
		//-----------------------------------------------------------------------------

		template <class T>
		long long Min(Array<Variable<T>>& input)
		{
			T min = input[0];
			for (size_t i = 1; i < input.GetSize(); i++)
			{
				if (input[i] < min)
					min = input[i];
			}
			return min;
		}
	}
	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------

}
