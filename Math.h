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
	
	static bool eps_state;

	static const T& reset_eps()
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
		if (!eps_state)
		{
			reset_eps();
			eps_state = true;
		}

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
		Math<T>::reset_eps();

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

	
	/// Shift
	template<typename T, unsigned dimension> inline
	VectorX<T, dimension>& shift (VectorX<T, dimension>& input, const std::size_t index, const T& offset)
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

		return input;
	}

	template<typename T, unsigned dimension> inline
	VectorX<T, dimension>& shift(VectorX<T, dimension>& input, const T& offset)
	{
		for(auto& e : input)
			e += offset;

		return input;
	}

	template<typename T, unsigned dimension>
	const T shift_from(const T& point, const T& offset)
	{
		return point + offset;
	}

	template<typename T, std::size_t dimension>
	const VectorX<T, dimension> shift_from(const VectorX<T, dimension>& point, const T& offset)
	{
		return point + offset;
	}
}

#endif // UTILITIES_H_H
