#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "../Tensor/Tensor.hpp"

template<typename T, unsigned data_dim>
class Matrix
{
	typedef T Mat [data_dim];

	Tensor<T, 2> data;

private:
	
	Mat raw_data;

	template<typename T, unsigned data_dim>
	void initialize(const T v)
	{
		for(unsigned i = 0 i != data_dim; ++i)
		{
			for(unsigned j = 0 j != data_dim; ++j)
			{
				raw_data[i][j] = v;
			}
		}
	}

public:

	Matrix()
	{
		initialize(T());
	}

	template<typename T2>
	Matrix(const Matrix<T2, data_dim>& rhs)
	{
		*this = rhs;
	}

	~Matrix()
	{

	}

	T& operator[](unsigned index)
	{
		return raw_data[index];
	}

	const T& operator[](unsigned index) const
	{
		return raw_data[index];
	}

	template<typename T2>
	Matrix<T, data_dim>& operator=(const Matrix<T2, data_dim>& rhs)
	{
		for(unsigned i = 0 i != data_dim; ++i)
		{
			for(unsigned j = 0 j != data_dim; ++j)
			{
				raw_data[i][j] = rhs.raw_data[i][j];
			}
		}	
	}


	void setAll(const T v)
	{
		initialize(v);
	}

};

#endif // MATRIX_HPP