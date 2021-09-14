#pragma once

#include <string>

template <typename T>
class Variable
{
public:
	Variable(T value)
	{
		Value = value;
		CompareCount = 0;
	}

	Variable()
	{
		Value = T();
		CompareCount = 0;
	}

	size_t GetCompareCount()
	{
		return CompareCount;
	}

	operator T() const
	{
		return Value;
	}

	operator T&()
	{
		return Value;
	}

	void operator=(const T& value)
	{
		Value = value;
	}

	bool operator==(T& value)
	{
		++CompareCount;
		return Value == value;
	}

	bool operator!=(T& value)
	{
		++CompareCount;
		return Value != value;
	}

	bool operator>(T& value)
	{
		++CompareCount;
		return Value > value;
	}

	bool operator>=(T& value)
	{
		++CompareCount;
		return Value >= value;
	}

	bool operator<(const T& value)
	{
		++CompareCount;
		return Value < value;
	}

	bool operator<=(T& value)
	{
		++CompareCount;
		return Value <= value;
	}

private:
	T Value;

	size_t CompareCount;
};