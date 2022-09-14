//
// Automatic Adjoint Differentation Sandbox project
// Thomas Jones                                                           
//
// AAD double type
//

#include "interpret.h"
#include "tape_aad.h"
#include "tape_entry_aad.h"
#include "operation_type_aad.h"

namespace aad_sandbox
{
	void interpret(tape_aad& tape)
	{
		const size_t count = tape.size();
		// Initialise output adjoint to 1.0
		tape.get_entry(count - 1)->value_adjoint_ = 1.0;

		// Walk through tape backwards
		for (size_t i = 1; i <= count; ++i)
		{
			// For each entry propagate adjoint * derivatives to operands

			auto entry = tape.get_entry(count - i);
			switch (entry->operation_type_)
			{
			// One of the inputs, nothing to do
			case operation_type_aad::INPUT:
				break;

			case operation_type_aad::ADDITION:
			{
				// y = x1 + x2
				// dy/dx1 = 1
				// dy/dx2 = 1

				auto l = tape.get_entry(entry->index_arg_1_);
				auto r = tape.get_entry(entry->index_arg_2_);
				tape.get_entry(entry->index_arg_1_)->value_adjoint_ += entry->value_adjoint_;
				tape.get_entry(entry->index_arg_2_)->value_adjoint_ += entry->value_adjoint_;
				break;
			}

			case operation_type_aad::MULTIPLY:
			{
				// y = x1 * x2
				// dy/dx1 = x2
				// dy/dx2 = x1

				auto l = tape.get_entry(entry->index_arg_1_);
				auto r = tape.get_entry(entry->index_arg_2_);
				l->value_adjoint_ += r->value_ * entry->value_adjoint_;
				r->value_adjoint_ += l->value_ * entry->value_adjoint_;
				break;
			}

			case operation_type_aad::MULTIPLY_CONSTANT:
			{
				// y = C * x1
				// dy/dx1 = C

				auto l = tape.get_entry(entry->index_arg_1_);
				// Constant stored in extra value
				l->value_adjoint_ += entry->extra_value_ * entry->value_adjoint_;
				break;
			}

			case operation_type_aad::LOG:
			{
				// y = log(x1)
				// dy/dx1 = 1/x1

				auto x = tape.get_entry(entry->index_arg_1_);
				x->value_adjoint_ += (1. / x->value_) * entry->value_adjoint_;
				break;
			}
			};
		}
	}
}
