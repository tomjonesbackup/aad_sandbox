//
// Automatic Adjoint Differentation Sandbox project
// Thomas Jones                                                           
//
// Implement AAD versions of common unary and binary maths functions
//

#pragma once

#include "double_aad.h"

namespace aad_sandbox
{
	class tape_aad;

	namespace math_aad
	{
		double_aad multiply(double l, double_aad r, tape_aad* tape);
		double_aad multiply(double_aad l, double_aad r, tape_aad* tape);
		double_aad multiply(double_aad l, double r, tape_aad* tape);

		double_aad add(double l, double_aad r, tape_aad* tape);
		double_aad add(double_aad l, double_aad r, tape_aad* tape);
		double_aad add(double_aad l, double r, tape_aad* tape);

		double_aad log(double_aad x, tape_aad* tape);
	}
}

