
#include "Math.h"

namespace sml
{

	double Math<double>::pi_value = static_cast<double>(4. * std::atan(1.));

	bool Math<double>::eps_state = false;

	double Math<double>::epsilon =  Math<double>::reset_eps();

}

