
#include "Math.h"

namespace sml
{

	template<>
	double Math<double>::pi_value = static_cast<double>(4. * std::atan(1.));

	template<>
	bool Math<double>::eps_state = false;

	template<>
	double Math<double>::epsilon =  Math<double>::reset_eps();

}

