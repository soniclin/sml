#ifndef LINEAR_EQUATION_H
#define LINEAR_EQUATION_H

#include <map>
#include <utility>

namespace sml
{

typedef std::size_t Index;

template<typename T>
class LinearEquation
{
public:

	LinearEquation();

	LinearEquation(const T& b);

	const std::size_t size() const;

	void add( std::pair< Index, T >& parameter );

	void addParameter( std::pair< Index, T >& parameter );

	const T& operator[](Index index) const;

	const T& get(Index index) const;

	//T& get(Index index);

	const T& getParameter(Index index) const;

	void setParameter(Index index, T& parameter);

	//T& getParameter(Index index);

	const T& value() const;

	void setValue(const T& v);

private:

	std::map< Index, T > parameters;

	T b_value;

};



}

#endif // LINEAR_EQUATION_H