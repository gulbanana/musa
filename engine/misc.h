#pragma once
#include <memory>
#include <functional>
#include <stdexcept>

namespace std
{
#pragma region make_unique
	template<typename T>
	std::unique_ptr<T> make_unique()
	{
		return std::unique_ptr<T>(new T());
	}

	template<typename T, typename A1>
	std::unique_ptr<T> make_unique(A1&& arg1)
	{
		return std::unique_ptr<T>(new T(std::forward<A1>(arg1)));
	}

	template<typename T, typename A1, typename A2>
	std::unique_ptr<T> make_unique(A1&& arg1, A2&& arg2)
	{
		return std::unique_ptr<T>(new T(std::forward<A1>(arg1), std::forward<A2>(arg2)));
	}

	template<typename T, typename A1, typename A2, typename A3>
	std::unique_ptr<T> make_unique(A1&& arg1, A2&& arg2, A3&& arg3)
	{
		return std::unique_ptr<T>(new T(std::forward<A1>(arg1), std::forward<A2>(arg2), std::forward<A3>(arg3)));
	}

	template<typename T, typename A1, typename A2, typename A3, typename A4>
	std::unique_ptr<T> make_unique(A1&& arg1, A2&& arg2, A3&& arg3, A4&& arg4)
	{
		return std::unique_ptr<T>(new T(std::forward<A1>(arg1), std::forward<A2>(arg2), std::forward<A3>(arg3), std::forward<A4>(arg4)));
	}

	template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5>
	std::unique_ptr<T> make_unique(A1&& arg1, A2&& arg2, A3&& arg3, A4&& arg4, A5&& arg5)
	{
		return std::unique_ptr<T>(new T(std::forward<A1>(arg1), std::forward<A2>(arg2), std::forward<A3>(arg3), std::forward<A4>(arg4), std::forward<A5>(arg5)));
	}

	template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	std::unique_ptr<T> make_unique(A1&& arg1, A2&& arg2, A3&& arg3, A4&& arg4, A5&& arg5, A6&& arg6)
	{
		return std::unique_ptr<T>(new T(std::forward<A1>(arg1), std::forward<A2>(arg2), std::forward<A3>(arg3), std::forward<A4>(arg4), std::forward<A5>(arg5), std::forward<A6>(arg6)));
	}
#pragma endregion

#pragma region unique pointer_cast
	template <class U, class T> 
	unique_ptr<U> static_pointer_cast(unique_ptr<T> &&ptr)
	{
		return unique_ptr<U>(static_cast<U*>(ptr.release()));
	}

	template <class U, class T> 
	unique_ptr<U> const_pointer_cast(unique_ptr<T> &&ptr)
	{
		return unique_ptr<U>(const_cast<U*>(ptr.release()));
	}

	template <class U, class T> 
	unique_ptr<U> dynamic_pointer_cast(unique_ptr<T> &&ptr)
	{
		if(U *p = dynamic_cast<U*>(ptr.get()))
		{
			ptr.release();
			return unique_ptr<U>(p);
		}
		else
			return unique_ptr<U>();
	}
#pragma endregion
}
