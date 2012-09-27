#pragma once
#include <memory>

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
