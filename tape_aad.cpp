//
// Automatic Adjoint Differentation Sandbox project
// Thomas Jones                                                           
//
// AAD tape
//

#include "tape_aad.h"
#include "tape_entry_aad.h"
#include "double_aad.h"

namespace aad_sandbox
{
	void tape_aad::register_input(double_aad& x)
	{
		// Add input as an entry to the tape
		x.tape_idx_ = add_entry(
			std::make_shared<tape_entry_aad>(
				operation_type_aad::INPUT,
				-1,
				-1,
				x.value()));

		// Store the input's index for later retrival of its derivatives
		input_index_[&x] = x.tape_idx_;

		// double_aad carry pointer to tape for convenience
		x.tape_ = this;
	}

	std::shared_ptr<tape_entry_aad> tape_aad::get_entry(size_t idx) const { return tape_.at(idx); }

	double tape_aad::derivative(double_aad& x)
	{
		// Get the index of the input and return the adjoint, which is is derivative
		return tape_.at(input_index_[&x])->value_adjoint_;
	}

	size_t tape_aad::add_entry(const std::shared_ptr<tape_entry_aad>& entry) {
		// Add and return new index
		tape_.push_back(entry);
		return tape_.size() - 1;
	}

	size_t tape_aad::size() const { return tape_.size(); }

}
