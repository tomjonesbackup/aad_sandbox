//
// Automatic Adjoint Differentation Sandbox project
// Thomas Jones                                                           
//
// AAD double type
//

#pragma once

namespace aad_sandbox
{
	class tape_aad;

	class double_aad
	{
	public:
		// Used when initialising with the input value
		// Non-explict for convenience
		double_aad(const double& value)
			: value_(value),
			tape_(nullptr),
			tape_idx_(-1)
		{
		}

		// Used when a variable is registered with the tape
		double_aad(const double& value, tape_aad* tape, size_t idx)
			: value_(value),
			tape_(tape),
			tape_idx_(idx)
		{
		}

		const double& value() const { return value_; }
		tape_aad* get_tape() { return tape_; }
		size_t tape_idx() const { return tape_idx_; }

	private:
		friend class tape_aad;

		// The double it represents
		const double value_;
		// Our way to the AAD tape
		tape_aad* tape_;
		// This variables index in the tape
		size_t tape_idx_;
	};

	double_aad operator+(double_aad l, double_aad r);
	double_aad operator*(double_aad l, double_aad r);
	double_aad operator*(const double& l, double_aad r);
	double_aad log(double_aad x);
}
