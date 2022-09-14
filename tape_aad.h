//
// Automatic Adjoint Differentation Sandbox project
// Thomas Jones                                                           
//
// AAD tape
//

#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

namespace aad_sandbox
{
	class double_aad;
	struct tape_entry_aad;

	class tape_aad
	{
	public:
		tape_aad() = default;
		tape_aad(const tape_aad&) = delete;
		tape_aad& operator=(const tape_aad&) = delete;

		// Register an input with the tape
		void register_input(double_aad& x);
		std::shared_ptr<tape_entry_aad> get_entry(size_t idx) const;
		// Extract an input's derivative
		double derivative(double_aad& x);
		// Add an entry to the tape, return the index of the added item
		size_t add_entry(const std::shared_ptr<tape_entry_aad>& entry);
		size_t size() const;

	private:
		std::unordered_map<double_aad*, size_t> input_index_;
		std::vector<std::shared_ptr<tape_entry_aad>> tape_;
	};
}