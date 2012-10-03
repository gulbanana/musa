#pragma once
#include <cstdint>
#include <boost/operators.hpp>

// 'strong' typedefs are not convertible implicitly to their 'base' type,
// providing a typesafe notion of "units"
// boost::strong_typedef exists, but its use case is function overloading
// and it does not provide arithmetic where typeof(D + D) == typeof(D)
#ifdef _DEBUG
    #define CHECKED_TYPEDEF(T, D)                                        \
    struct D : boost::totally_ordered1<D, boost::totally_ordered2<D, T>> \
    {                                                                    \
        T t;                                                             \
        explicit D(const T t_) : t(t_) {};                               \
        D(): t() {};                                                     \
        D(const D & t_) : t(t_.t){}                                      \
        D & operator=(const D & rhs) { t = rhs.t; return *this;}         \
        D & operator=(const T & rhs) { t = rhs; return *this;}           \
        operator const T & () const {return t; }                         \
        operator T & () { return t; }                                    \
        /* equality_comparable */                                        \
        bool operator==(const D & rhs) const { return t == rhs.t; }      \
        /* less_than_comparable */                                       \
        bool operator<(const D & rhs) const { return t < rhs.t; }        \
        /* arithmetic - cannot be boosted because of explicit cons */    \
        D operator+(D const& rhs) const{ return D(t + rhs.t); }          \
        D operator-(D const& rhs) const { return D(t - rhs.t); }         \
        D operator*(D const& rhs) const { return D(t * rhs.t); }         \
        D operator/(D const& rhs) const { return D(t / rhs.t); }         \
        D operator-() const { return D(-t); }                            \
        D operator+() const { return D(t); }                             \
    };
#else
    #define CHECKED_TYPEDEF(T, D) typedef T D;
#endif

CHECKED_TYPEDEF(float,degrees)
CHECKED_TYPEDEF(float,radians)

// C4146 is a warning for unary negation of unsigned types
// TODO: maybe i really shouldn't use an unsigned type here? the problem is that SDL_GetTicks() returns uint32..
#pragma warning(disable:4146)
CHECKED_TYPEDEF(uint64_t,microseconds)
CHECKED_TYPEDEF(uint32_t,milliseconds)
#pragma warning(default:4146)

#ifdef DOUBLE_PRECISION
    CHECKED_TYPEDEF(double,seconds)
    CHECKED_TYPEDEF(double,coord)
#else
    CHECKED_TYPEDEF(float,seconds)
    CHECKED_TYPEDEF(float,coord)
#endif