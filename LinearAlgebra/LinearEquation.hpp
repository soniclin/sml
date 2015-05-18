#ifndef LINEAR_EQUATION_HPP
#define LINEAR_EQUATION_HPP

#include "LinearEquation.h"

namespace sml
{

template<typename T>
LinearEquation<T>::LinearEquation()
	:b_value((T)0)
{

}

template<typename T>
LinearEquation<T>::LinearEquation(const T& b)
	:b_value(b)
{

}

template<typename T>
const std::size_t LinearEquation<T>::size() const
{
	return parameters.size();
}


template<typename T>
void LinearEquation<T>::add( std::pair< Index, T >& parameter )
{
	parameters.insert(parameter);
}



template<typename T>
void LinearEquation<T>::addParameter( std::pair< Index, T >& parameter )
{
	add(parameter);
}


template<typename T>
const T& sml::LinearEquation<T>::operator[]( Index index ) const
{
	return parameters.at(index);
}


template<typename T>
const T& sml::LinearEquation<T>::get( Index index ) const
{
	return (*this)[index];
}

template<typename T>
const T& LinearEquation<T>::getParameter( Index index ) const
{
	return (*this)[index];
}


template<typename T>
void LinearEquation<T>::setParameter( Index index, T& parameter )
{
	parameters.at(index) = parameter;
}


template<typename T>
const T& LinearEquation<T>::value() const
{
	return b_value;
}

template<typename T>
void LinearEquation<T>::setValue( const T& v )
{
	b_value = v;
}



}

#endif // LINEAR_EQUATION_HPP