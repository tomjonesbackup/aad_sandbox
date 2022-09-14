//
// Automatic Adjoint Differentation Sandbox project
// Thomas Jones                                                           
//
//  Supported AAD unary and binary maths functions
//

#pragma once

namespace aad_sandbox
{
	enum class operation_type_aad
	{
		INPUT,
		ADDITION,
		MULTIPLY,
		MULTIPLY_CONSTANT,
		LOG
	};
}
