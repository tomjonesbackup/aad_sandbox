//
// Automatic Adjoint Differentation Sandbox project
// Thomas Jones                                                           
//
//  An entry in the tape
//

#pragma once

#include "operation_type_aad.h"

namespace aad_sandbox
{
	struct tape_entry_aad
	{
		tape_entry_aad(operation_type_aad operation_type, size_t index_arg_1, size_t index_arg_2, double value, double extra_value = -1.)
			: operation_type_(operation_type),
			index_arg_1_(index_arg_1),
			index_arg_2_(index_arg_2),
			value_(value),
			extra_value_(extra_value),
			value_adjoint_(0.)
		{
		}

		const operation_type_aad operation_type_;
		// Indices of operand(s)
		const size_t index_arg_1_;
		const size_t index_arg_2_;
		const double value_;
		// Used for binary operations where one is a constant
		const double extra_value_;
		// Populated with adjoints during backward pass
		double value_adjoint_;
	};
}
