#ifndef TENSOR2D_H
#define TENSOR2D_H

#include <cmath>
#include <iostream>
#include "Tensor.hpp"

namespace sml
{

template<typename T, unsigned data_dim>
class Tensor2D: public Tensor<T>
{


public:

	Tensor2D();

	Tensor2D(const Tensor2D& rhs);

	~Tensor2D();

	T& get(unsigned i, unsigned j);

	const T& get(unsigned i, unsigned j) const;

	Tensor2D& operator=(const Tensor2D& rhs);

	Tensor2D& operator*=(const T& rhs);

	Tensor2D& operator/=(const T& rhs);

	Tensor2D& operator+=(const Tensor2D& rhs);

	Tensor2D& operator-=(const Tensor2D& rhs);

	Tensor2D& transpose();

	Tensor2D& abs();

	T sum() const;
	
	std::ostream& print(std::ostream& ostr) const;

protected:

	void allocateMemory();

	void releaseMemory();

	void initialize(T initial_value);

private:

	unsigned sq_dim;

	
	T** grid;

};


template<typename T, unsigned data_dim>
VectorX<T, data_dim> operator*(const Tensor2D<T, data_dim>& lhs, const VectorX<T, data_dim>& rhs);


template<typename T, unsigned data_dim>
Tensor2D<T, data_dim> operator*(const Tensor2D<T, data_dim>& lhs, const Tensor2D<T, data_dim>& rhs);


template<typename T, unsigned data_dim>
Tensor2D<T, data_dim> operator+(const Tensor2D<T, data_dim>& lhs, const Tensor2D<T, data_dim>& rhs);

template<typename T, unsigned data_dim>
Tensor2D<T, data_dim> operator-(const Tensor2D<T, data_dim>& lhs, const Tensor2D<T, data_dim>& rhs);


}
#endif // TENSOR2D_H