//
// Automatic Adjoint Differentation Sandbox project
// Thomas Jones                                                           
//
// Main test harness
//

#include <iostream>
#include <math.h>

#include "math_aad.h"
#include "tape_aad.h"
#include "interpret.h"
#include "double_aad.h"

namespace
{
	// Function template can work with both primative doubles or double_aad
	template<typename DoubleT>
	DoubleT f(DoubleT x1, DoubleT x2, DoubleT x3)
	{
		return 2*x1 + log(x1*x2 + x3);
	}

}

int main()
{
	using namespace aad_sandbox;

	// Initialise x1, x2 and x3 inputs
	double_aad x1 = 2.;
	double_aad x2 = 3.;
	double_aad x3 = 4.;

	// Register with the AAD tape
	tape_aad tape;
	tape.register_input(x1);
	tape.register_input(x2);
	tape.register_input(x3);

	// Works with ordinary doubles
	const auto& ans = f(2., 3., 4.);
	std::cout << "Ordinary double function result = " << ans << std::endl;
	
	// Also works with double_add, gives same answer
	double_aad result = f(x1, x2, x3);
	std::cout << "AAD type function result = " << result.value() << std::endl;

	// Play tape backwards, propagating adjoints
	interpret(tape);

	// Extract the derivatives
	std::cout << "dy/dx1 = " << tape.derivative(x1) << std::endl;
	std::cout << "dy/dx2 = " << tape.derivative(x2) << std::endl;
	std::cout << "dy/dx3 = " << tape.derivative(x3) << std::endl;
}
