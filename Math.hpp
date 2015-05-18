#ifndef MATH_H_HPP
#define MATH_H_HPP

#include <cmath>
#include "./Math.h"

namespace sml
{
/// class Math
template<typename T> 
T Math<T>::epsilon = Math<T>::resetEps();

template<typename T>
void Math<T>::initialize()
{
	Math<T>::resetEps();

	Math<T>::pi_value = static_cast<T>(4. * std::atan(1.));
}

#include <iostream>

template<typename T>
const T& Math<T>::resetEps()
{
	std::cout << "reset eps" << std::endl;
	epsilon = 1;
	while( (static_cast<T>(1)+epsilon) > static_cast<T>(1) )
	{
		epsilon /= 2;
	}

	epsilon *= 2;

	return epsilon;
}

template<typename T>
const T& Math<T>::eps()
{
	return epsilon;
}

template<typename T>
const T& Math<T>::pi()
{
	return Math<T>::pi_value;
}

template<typename T>
Math<T>::Math()
{
	initialize();
}



/// Cross production
template<typename T, unsigned dimension>
VectorX<T, dimension> cross(const VectorX<double, 3>& lhs, const VectorX<double, 3>& rhs);

/// 3D volume
template<typename T, unsigned dimension>
T volume(const VectorX<T, dimension>& input)
{
	return input[0]*input[1]*input[2];
}

template<typename T, unsigned dimension>
void set3D(VectorX<T, dimension>& v, T x, T y, T z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

}

#endif // UTILITIES_H_HPP