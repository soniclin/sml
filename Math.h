#ifndef MATH_H_H
#define MATH_H_H

#include <cmath>
#include "./VectorX/VectorX.hpp"

namespace sml
{

template<typename T>
class Math
{
public:
	
	static const T& resetEps();

	static const T& eps();

	static const T& pi();

	static const bool is_zero(const T& input)
	{
		return std::abs(input - static_cast<T>(0)) < Math<T>::eps();
	}

private:

	Math();

	void initialize();

	static T epsilon;

	static bool eps_reset;

	static T pi_value;

};
	

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