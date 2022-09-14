//
// Automatic Adjoint Differentation Sandbox project
// Thomas Jones                                                           
//
// For playing the tape backwards, propagating adjoints and ultimately calculating derivatives
//

#pragma once

namespace aad_sandbox
{
	class tape_aad;

	void interpret(tape_aad& tape);
}
