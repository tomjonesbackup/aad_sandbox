//
// Automatic Adjoint Differentation Sandbox project
// Thomas Jones                                                           
//
// Implement AAD versions of common unary and binary maths functions
//

#include <math.h>

#include "math_aad.h"
#include "tape_aad.h"
#include "double_aad.h"
#include "operation_type_aad.h"
#include "tape_entry_aad.h"

namespace aad_sandbox
{
	// Each function calculates the value, adds a new entry to the tape containing
	// - the value
	// - the operation type
	// - the indices of the operands
	// - some additional data if required

	namespace math_aad
	{
		double_aad multiply(double l, double_aad r, tape_aad* tape)
		{

			double value = l * r.value();

			size_t idx = tape->add_entry(
				std::make_shared<tape_entry_aad>(
					operation_type_aad::MULTIPLY_CONSTANT,
					r.tape_idx(),
					-1,
					value,
					l));

			return double_aad(value, tape, idx);
		}

		double_aad multiply(double_aad l, double_aad r, tape_aad* tape)
		{
			double value = l.value() * r.value();

			size_t idx = tape->add_entry(
				std::make_shared<tape_entry_aad>(
					operation_type_aad::MULTIPLY,
					l.tape_idx(),
					r.tape_idx(),
					value));

			return double_aad(value, tape, idx);
		}

		double_aad multiply(double_aad l, double r, tape_aad* tape);

		double_aad add(double l, double_aad r, tape_aad* tape);

		double_aad add(double_aad l, double_aad r, tape_aad* tape)
		{
			double value = l.value() + r.value();

			size_t idx = tape->add_entry(
				std::make_shared<tape_entry_aad>(
					operation_type_aad::ADDITION,
					l.tape_idx(),
					r.tape_idx(),
					value));

			return double_aad(value, tape, idx);
		}


		double_aad add(double_aad l, double r, tape_aad& tape);

		double_aad log(double_aad x, tape_aad* tape)
		{
			double value = std::log(x.value());

			size_t idx = tape->add_entry(
				std::make_shared<tape_entry_aad>(
					operation_type_aad::LOG,
					x.tape_idx(),
					-1,
					value));

			return double_aad(value, tape, idx);
		}
	}
}
