#ifndef SIZE_H
#define SIZE_H

#include "VectorX/VectorX.h"
#include <initializer_list>

namespace sml
{
	template<std::size_t DIMENSION = 3>
	class Size
	{
	private:

		VectorX<std::size_t, DIMENSION> raw_data;

	public:

		Size() = default;

		Size(const Size<DIMENSION>& rhs) = default;

		Size(const std::initializer_list<std::size_t>& list)
		{
			const auto iter = list.cbegin();

			for (std::size_t index = 0; index != DIMENSION; ++index)
			{
				raw_data[index] = *iter++;
			}
		}

		Size(const VectorX<std::size_t, DIMENSION>& list)
			:raw_data(list)
		{

		}

		const std::size_t size() const
		{
			std::size_t ret = 1;
			for (std::size_t index = 0; index != DIMENSION; ++index)
			{
				ret *= raw_data[index];
			}
		}

		const std::size_t& width() const
		{
			return raw_data[0];
		}

		const std::size_t& height() const
		{
			return raw_data[1];
		}


		Size<DIMENSION>& operator=(const Size<DIMENSION>& rhs) = default;
		
		const std::size_t& operator[](const std::size_t& index) const
		{
			return raw_data[index];
		}

		std::size_t& operator[](const std::size_t& index)
		{
			return raw_data[index];
		}


	};

} // namespace sml


#endif // SIZE_H