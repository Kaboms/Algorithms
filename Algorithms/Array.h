#pragma once
//-----------------------------------------------------------------------------
#include "Variable.h"
//-----------------------------------------------------------------------------

template <typename T>
class Array
{
public:
	Array()
	{
		Data = nullptr;
		Size = 0;
		AccessCount = 0;
	}
	//-----------------------------------------------------------------------------

	Array(size_t size)
	{
		Data = new T[size];
		Size = size;
		AccessCount = 0;
	}
	//-----------------------------------------------------------------------------

	Array(std::initializer_list<T> list)
	{
		Data = new T[list.size()];
		Size = list.size();
		for (size_t i = 0; i < Size; i++)
		{
			Data[i] = (*list.begin() + i);
		}
	}
	//-----------------------------------------------------------------------------

	T* begin()
	{
		return Data;
	}
	//-----------------------------------------------------------------------------

	T* end()
	{
		return &(Data[Size]);
	}
	//-----------------------------------------------------------------------------

	size_t GetAccessCount()
	{
		return AccessCount;
	}
	//-----------------------------------------------------------------------------

	size_t GetSize()
	{
		return Size;
	}
	//-----------------------------------------------------------------------------

	T& operator[](size_t i)
	{
		++AccessCount;

		if (i >= Size)
			throw std::out_of_range("Out of range");

		return Data[i];
	}
	//-----------------------------------------------------------------------------

	operator T& ()
	{
		return Data[Size];
	}
	//-----------------------------------------------------------------------------

private:
	T* Data;
	size_t Size;

	size_t AccessCount;
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template <class Ty>
static void Copy(Array<Variable<Ty>> source, Array<Variable<Ty>> dest, size_t from, size_t count)
{
	if (count > source.GetSize())
		throw std::out_of_range("Out of range");

	size_t j = 0;
	for (size_t i = 0; i < count; ++i)
	{
		dest[j] = source[from + i];
		j++;
	}
}
template <class Ty>
static void Copy(Array<Variable<Ty>> source, Array<Variable<Ty>> dest)
{
	if (source.GetSize() != dest.GetSize())
		throw std::out_of_range("Different size");

	Copy(source, dest, 0, source.GetSize());
}
//-----------------------------------------------------------------------------