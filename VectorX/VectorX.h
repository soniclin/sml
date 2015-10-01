#ifndef VECTORX_H
#define VECTORX_H
#include <iostream>
#include <memory>
#include <initializer_list>
#include <array>
#include <cmath>

namespace sml
{

template<typename T, std::size_t N>
class VectorX : private std::array<T, N>
{

	using Base = std::array < T, N > ;

public:

	using std::array<T, N>::begin;
	using std::array<T, N>::end;

	using std::array<T, N>::cbegin;
	using std::array<T, N>::cend;

	using std::array<T, N>::rbegin;
	using std::array<T, N>::rend;

	using std::array<T, N>::crbegin;
	using std::array<T, N>::crend;


	using std::array<T, N>::size;
	using std::array<T, N>::empty;


	using std::array<T, N>::operator[];
	using std::array<T, N>::at;
	using std::array<T, N>::front;
	using std::array<T, N>::back;
	using std::array<T, N>::data;

	using std::array<T, N>::fill;
	using std::array<T, N>::swap;



#pragma region Constructors


	VectorX(const T& value = 0)
	{
		this->initialize(value);
	}


	VectorX(const std::initializer_list<T>& list)
	{
		auto iter = list.begin();
		auto end = list.end();
		
		for (auto this_iter = this->begin(); this_iter != this->end() && iter != end; ++this_iter)
		{
			*this_iter = *iter++;
		}
	}


	void initialize(const T& value)
	{
		for (auto iter = begin(); iter != end(); ++iter)
		{
			*iter = value;
		}
	}

#pragma endregion

	/// Return copy of self
	VectorX<T, N> clone() const
	{
		return VectorX<T, N>(*this);
	}


public:

	/// Assignment operators

	template<typename T2, size_type N2>
	VectorX<T, N>& operator=(const VectorX<T2, N2>& rhs)
	{
		Base::size_type d = N > N2 ? N : N2;
		auto iter = begin();
		for (Base::size_type index = 0; index != d; ++index)
		{
			*iter++ = rhs[index];
		}

		return *this;
	}

	template<typename T2, Base::size_type N2>
	VectorX<T, N>& operator+=(const VectorX<T2, N2>& rhs)
	{
		Base::size_type d = N > N2 ? N : N2;
		auto iter = begin();
		for (Base::size_type index = 0; index != d; ++index)
		{
			*iter++ += rhs[index];
		}

		return *this;
	}

	VectorX<T, N>& operator+=(const T& rhs)
	{
		auto iter = begin();
		for (Base::size_type index = 0; index != N; ++index)
		{
			*iter++ += rhs;
		}

		return *this;
	}

	template<typename T2, Base::size_type N2>
	VectorX<T, N>& operator-=(const VectorX<T2, N2>& rhs)
	{
		Base::size_type d = N > N2 ? N : N2;
		auto iter = begin();
		for (Base::size_type index = 0; index != d; ++index)
		{
			*iter++ -= rhs[index];
		}

		return *this;
	}

	VectorX<T, N>& operator-=(const T& rhs)
	{
		auto iter = begin();
		for (Base::size_type index = 0; index != N; ++index)
		{
			*iter++ -= rhs;
		}

		return *this;
	}


	template<typename T2>
	VectorX<T, N>& operator*=(const T2& rhs)
	{
		auto iter = begin();
		for (Base::size_type index = 0; index != N; ++index)
		{
			*iter++ *= rhs;
		}

		return *this;
	}

	template<typename T2>
	VectorX<T, N>& operator/=(const T2& rhs)
	{
		try
		{
			if (std::abs(rhs) < static_cast<T2>(1e-20))
			{
				throw "Error{VectorX::operator/=}: The divisor is too small!";
			}

		}
		catch (const char* err)
		{

			std::cout << err << std::endl;

			std::exit(1);
		}

		auto iter = begin();
		for (Base::size_type index = 0; index != N; ++index)
		{
			*iter++ /= rhs;
		}

		return *this;
	}

	const VectorX<T, N> VectorX<T, N>::operator-() const
	{
		auto ret(*this);

		for (unsigned index = 0; index != N; ++index)
			ret[index] = -ret[index];

		return ret;
	}

	/// Iterator
	


	/// Explicit arithmetic operators
	const T dot(const VectorX& rhs) const
	{
		auto ret = T();

		for (unsigned index = 0; index != N; ++index)
			ret += this->operator[](index) * rhs[index];

		return ret;
	}

	/// Abs, only for double, float, int
	const T abs() const
	{
		return std::sqrt(this->normSqr());
	};

	/// NormSqr
	T normSqr() const
	{
		auto ret = T();
		for (int index = 0; index != N; ++index)
			ret += this->operator[](index) * this->operator[](index);

		return ret;
	};

	T distance(const VectorX<T, N>& rhs) const
	{
		auto ret = T();
		for (int index = 0; index != N; ++index)
		{
			const T dist = this->operator[](index) - rhs[index];
			ret += dist * dist;
		}
		return std::sqrt(ret);
	}


	// For debug (low performance)
	std::ostream& print(std::ostream& ostr)
	{
		ostr << "(";
		for (unsigned index = 0; index != N; ++index)
		{
			if (index != N - 1)
				ostr << this->operator[](index) << ", ";
			else
				ostr << this->operator[](index) << ")";
		}
		return ostr;
	};

	//T volume() const;

};

template<typename T, unsigned N>
bool operator<(const sml::VectorX<T, N>& lhs, const sml::VectorX<T, N>&  rhs)
{
	return lhs.abs() < rhs.abs();
}

template<typename T, unsigned N>
bool operator<(const sml::VectorX<T, N>& lhs, const T& rhs)
{
	return lhs.abs() < rhs;
}

template<typename T, unsigned N>
bool operator>(const sml::VectorX<T, N>& lhs, const sml::VectorX<T, N>&  rhs)
{
	return lhs.abs() > rhs.abs();
}

template<typename T, unsigned N>
bool operator>(const sml::VectorX<T, N>& lhs, const T& rhs)
{
	return lhs.abs() > rhs;
}

/// Arithmetic operators
template<typename T, unsigned N>
const VectorX<T, N> operator+(const sml::VectorX<T, N>& lhs, const sml::VectorX<T, N>& rhs)
{
	VectorX<T, N> ret(lhs);

	ret += rhs;

	return ret;
}

template<typename T, unsigned N>
const VectorX<T, N> operator+(const sml::VectorX<T, N>& lhs, const T& rhs)
{
	VectorX<T, N> ret(lhs);

	ret += rhs;

	return ret;
}

template<typename T, unsigned N>
const VectorX<T, N> operator+(const T& lhs, const sml::VectorX<T, N>& rhs)
{
	VectorX<T, N> ret(rhs);

	ret += lhs;

	return ret;
}

template<typename T, unsigned N>
const VectorX<T, N> operator-(const sml::VectorX<T, N>& lhs, const sml::VectorX<T, N>& rhs)
{
	VectorX<T, N> ret(lhs);

	ret -= rhs;

	return ret;
}

template<typename T, unsigned N>
const VectorX<T, N> operator-(const sml::VectorX<T, N>& lhs, const T& rhs)
{
	VectorX<T, N> ret(lhs);

	ret -= rhs;

	return ret;
}

template<typename T, unsigned N>
const VectorX<T, N> operator-(const T& lhs, const sml::VectorX<T, N>& rhs)
{
	VectorX<T, N> ret(rhs);

	ret -= lhs;

	return ret;
}

template<typename T, unsigned N>
const VectorX<T, N> operator*(const sml::VectorX<T, N>& lhs, const T& rhs)
{
	sml::VectorX<T, N> ret(lhs);

	ret *= rhs;

	return ret;
}

template<typename T, typename T2, unsigned N> inline
const VectorX<T, N> operator/(const sml::VectorX<T, N>& lhs, const T2& rhs)
{
	try
	{
		if (std::abs(rhs - 0) < std::numeric_limits<T>::epsilon())
			throw std::string("VectorX<T, N> operator/(VectorX, T) Divided by zero !");
	}
	catch (const std::string& message)
	{
		std::cerr << message << std::endl;
	}

	sml::VectorX<T, N> ret(lhs);

	ret /= rhs;

	return ret;
}

template<typename T, unsigned N>
std::ostream& operator<<(std::ostream& ostr, const VectorX<T, N>& rhs)
{
	for (unsigned index = 0; index != N; ++index)
	{
		ostr << rhs[index] << " ";
	}
	return ostr;
}

template<typename T, unsigned N>
std::ostream& print(std::ostream& ostr, const VectorX<T, N>& rhs)
{
	ostr << "(";
	for (unsigned index = 0; index != N; ++index)
	{
		if (index != N - 1)
			ostr << rhs[index] << ", ";
		else
			ostr << rhs[index] << ")";
	}
	return ostr;
}

template<typename T, unsigned N>
std::istream& operator>>(std::istream& istr, VectorX<T, N>& rhs)
{
	for (unsigned index = 0; index != N; ++index)
	{
		istr >> rhs[index];
	}
	return istr;
}


} // sml



#endif // VECTORX_H
