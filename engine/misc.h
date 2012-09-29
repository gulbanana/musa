#pragma once
#include <memory>
#include <functional>
#include <stdexcept>

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
#pragma endregion
