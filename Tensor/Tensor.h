#ifndef TENSOR_H
#define TENSOR_H

#include <cmath>
#include <iostream>

namespace sml
{

template<typename T, unsigned data_dim>
class Tensor
{


public:

	virtual T& get(unsigned i);

	virtual const T& get(unsigned i) const;

	Tensor& operator=(const Tensor& rhs);

	Tensor& operator*=(const T& rhs);

	Tensor& operator/=(const T& rhs);

	Tensor& operator+=(const Tensor& rhs);

	Tensor& operator-=(const Tensor& rhs);

	Tensor& abs();

	virtual T sum() const;

	std::ostream& print(std::ostream& ostr) const;
protected:

	T* raw_data;

};


}
#endif // TENSOR_H