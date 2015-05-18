#ifndef TENSOR_HPP
#define TENSOR_HPP

#include "Tensor2D.h"
namespace sml
{

template<typename T, unsigned data_dim>
Tensor2D<T, data_dim>::Tensor2D()
{
	allocateMemory();

	initialize((T)0);
}


template<typename T, unsigned data_dim>
Tensor2D<T, data_dim>::Tensor2D(const Tensor2D<T, data_dim>& rhs)
{
	allocateMemory();
	*this = rhs;
}

template<typename T, unsigned data_dim>
Tensor2D<T, data_dim>::~Tensor2D()
{
	releaseMemory();
}

template<typename T, unsigned data_dim>
T& Tensor2D<T, data_dim>::get(unsigned index_1, unsigned index_2)
{
	return grid[index_1][index_2];
}

template<typename T, unsigned data_dim>
const T& Tensor2D<T, data_dim>::get(unsigned index_1, unsigned index_2) const
{
	return grid[index_1][index_2];
}

template<typename T, unsigned data_dim>
Tensor2D<T, data_dim>& Tensor2D<T, data_dim>::operator=(const Tensor2D<T, data_dim>& rhs)
{
	for(unsigned index = 0; index != sq_dim; ++index)
		raw_data[index] = rhs.raw_data[index];
	return *this;
}

template<typename T, unsigned data_dim>
Tensor2D<T, data_dim>& Tensor2D<T, data_dim>::operator*=(const T& rhs)
{
	for(unsigned index = 0; index != sq_dim; ++index)
		raw_data[index] *= rhs;
	return *this;
}

template<typename T, unsigned data_dim>
Tensor2D<T, data_dim>& Tensor2D<T, data_dim>::operator/=(const T& rhs)
{
	for(unsigned index = 0; index != sq_dim; ++index)
		raw_data[index] /= rhs;
	return *this;
};

template<typename T, unsigned data_dim>
Tensor2D<T, data_dim>& Tensor2D<T, data_dim>::operator+=(const Tensor2D<T, data_dim>& rhs)
{
	for(unsigned index = 0; index != sq_dim; ++index)
		raw_data[index] += rhs;
	return *this;
};

template<typename T, unsigned data_dim>
Tensor2D<T, data_dim>& Tensor2D<T, data_dim>::operator-=(const Tensor2D<T, data_dim>& rhs)
{
	for(unsigned index = 0; index != sq_dim; ++index)
		raw_data[index] -= rhs;
	return *this;
}

template<typename T, unsigned data_dim>
Tensor2D<T, data_dim>& Tensor2D<T, data_dim>::transpose()
{
	Tensor2D tmp(*this);

	for(unsigned index_1 = 0; index_1 != data_dim; ++index_1)
		for(unsigned index_2 = 0; index_2 != data_dim; ++index_2)
			grid[index_1][index_2] = tmp.grid[index_2][index_1];
	
	return *this;
}

template<typename T, unsigned data_dim>
Tensor2D<T, data_dim>& Tensor2D<T, data_dim>::abs()
{
	for(unsigned index = 0; index != sq_dim; ++index)
		raw_data[index] = std::abs(raw_data[index]);	
	return *this;
}

template<typename T, unsigned data_dim>
T Tensor2D<T, data_dim>::sum() const
{
	T ret = (T)0;
	for(unsigned index = 0; index != sq_dim; ++index)
		ret += raw_data[index];
	return ret;
}

template<typename T, unsigned data_dim>
std::ostream& Tensor2D<T, data_dim>::print(std::ostream& ostr) const
{
	ostr << std::endl;
	for(unsigned index_1 = 0; index_1 != data_dim; ++index_1)
	{
		ostr << "[";
		for(unsigned index_2 = 0; index_2 != data_dim; ++index_2)
		{
			 grid[index_1][index_2] << ", ";
		}
		ostr << "]" << std::endl;
	}
	
	return ostr;
}

template<typename T, unsigned data_dim>
void Tensor2D<T, data_dim>::allocateMemory()
{
	sq_dim = data_dim*data_dim;
	raw_data = new T [(unsigned)sq_dim];
	grid    = new T* [(unsigned)data_dim];
	for (int iX=0; iX<data_dim; ++iX)
	{
		grid[iX] = raw_data + (unsigned)iX*(unsigned)data_dim;
	}
}

template<typename T, unsigned data_dim>
void Tensor2D<T, data_dim>::releaseMemory()
{
	delete [] raw_data;

	delete [] grid;
}

template<typename T, unsigned data_dim>
void Tensor2D<T, data_dim>::initialize(T initial_value)
{
	for(unsigned index = 0; index != sq_dim; ++index)
		raw_data[index] = (T)initial_value;
}

template<typename T, unsigned data_dim>
VectorX<T, data_dim> operator*(const Tensor2D<T, data_dim>& lhs, const VectorX<T, data_dim>& rhs)
{
	VectorX<T, data_dim> ret;

	for(unsigned index_1 = 0; index_1 != data_dim; ++index_1)
		for(unsigned index_2 = 0; index_2 != data_dim; ++index_2)
			ret[index_1] += lhs.get(index_1, index_2)*rhs[index_2];

	return ret;
}

template<typename T, unsigned data_dim>
Tensor2D<T, data_dim> operator*(const Tensor2D<T, data_dim>& lhs, const Tensor2D<T, data_dim>& rhs)
{
	Tensor2D<T, data_dim> ret;

	for(unsigned index_1 = 0; index_1 != data_dim; ++index_1)
		for(unsigned index_2 = 0; index_2 != data_dim; ++index_2)
			for(unsigned index_3 = 0; index_3 != data_dim; ++index_3)
				ret.get(index_1, index_2) = lhs.get(index_1, index_3) * rhs.get(index_3, index_2);

	return ret;
}

template<typename T, unsigned data_dim>
Tensor2D<T, data_dim> operator+(const Tensor2D<T, data_dim>& lhs, const Tensor2D<T, data_dim>& rhs)
{
	Tensor2D<T, data_dim> ret;
	for(unsigned index_1 = 0; index_1 != data_dim; ++index_1)
		for(unsigned index_2 = 0; index_2 != data_dim; ++index_2)
			ret.get(index_1, index_2) = lhs.get(index_1, index_2) + rhs.get(index_1, index_2);
	return ret;
}

template<typename T, unsigned data_dim>
Tensor2D<T, data_dim> operator-(const Tensor2D<T, data_dim>& lhs, const Tensor2D<T, data_dim>& rhs)
{
	Tensor2D<T, data_dim> ret;
	for(unsigned index_1 = 0; index_1 != data_dim; ++index_1)
		for(unsigned index_2 = 0; index_2 != data_dim; ++index_2)
			ret.get(index_1, index_2) = lhs.get(index_1, index_2) - rhs.get(index_1, index_2);
	return ret;
}


}

#endif // TENSOR_HPP