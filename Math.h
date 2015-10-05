#ifndef MATH_H_H
#define MATH_H_H

#include <cmath>
#include "./VectorX/VectorX.h"

namespace sml
{

template<typename T>
class Math
{
public:
	
	static const T& resetEps()
	{
		epsilon = 1;
		while( (static_cast<T>(1)+epsilon) > static_cast<T>(1) )
		{
			epsilon /= 2;
		}

		epsilon *= 2;

		return epsilon;
	}

	static const T& eps()
	{
		return epsilon;
	}

	static const T& pi()
	{
		return Math<T>::pi_value;
	}	

	static const bool is_zero(const T& input)
	{
		return std::abs(input - static_cast<T>(0)) < Math<T>::eps();
	}

private:

	Math()
	{
		initialize();
	}

	void initialize()
	{
		Math<T>::resetEps();

		Math<T>::pi_value = static_cast<T>(4. * std::atan(1.));
	}

	static T epsilon;

	static bool eps_reset;

	static T pi_value;

};

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

	

	template<typename T, unsigned dimension>
	static T shiftFrom(T& point, T& offset);

	/// Shift
	template<typename T, unsigned dimension> inline
	T shift(int index, T& offset) 
	{
		try
		{
			if(index > dimension-1)
				throw "index is larger than total elements number.";
		}
		catch(const char* err)
		{
			std::cout << err << std::endl;

			return 1;
		}

		return raw_data[index] + offset;
	}

	template<typename T, unsigned dimension> inline
	VectorX<T, dimension> shift(T offsetX, T offsetY, T offsetZ) 
	{
		VectorX<T, dimension> ret;
		ret[0] = offsetX+this->x();
		ret[1] = offsetY+this->y();
		ret[2] = offsetZ+this->z();
		return ret;
	}

	template<typename T, unsigned dimension>
	T shiftFrom(T& point, T& offset)
	{
		return point + offset;
	}
}

#endif // UTILITIES_H_H
