#pragma once

struct Less
{
	template <class T>
	constexpr auto operator()(Variable<T>& left, T& right) const
	{
		return left < right;
	}
};

struct LessEqual
{
	template <class T>
	constexpr auto operator()(Variable<T>& left, T& right) const
	{
		return left <= right;
	}
};


struct Greater
{
	template <class T>
	constexpr auto operator()(Variable<T>& left, T& right) const
	{
		return left > right;
	}
};

struct GreaterEqual
{
	template <class T>
	constexpr auto operator()(Variable<T>& left, T& right) const
	{
		return left >= right;
	}
};

struct Equal
{
	template <class T>
	constexpr auto operator()(Variable<T>& left, T& right) const
	{
		return left == right;
	}
};