//
// Automatic Adjoint Differentation Sandbox project
// Thomas Jones                                                           
//
// AAD double type
//

#include "double_aad.h"
#include "math_aad.h"

namespace aad_sandbox
{
	// Operator overloads that delegate to the math_add namespace 
	double_aad operator+(double_aad l, double_aad r)
	{
		return math_aad::add(l, r, l.get_tape());
	}

	double_aad operator*(double_aad l, double_aad r)
	{
		return math_aad::multiply(l, r, l.get_tape());
	}

	double_aad operator*(const double& l, double_aad r)
	{
		return math_aad::multiply(l, r, r.get_tape());
	}

	double_aad log(double_aad x)
	{
		return math_aad::log(x, x.get_tape());
	}
}
