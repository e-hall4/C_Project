/*
	@author Elijah Hall
*/

#include "Instruction.h"

void lw_immd_assm(void) {
	// Verify the correct op code
	if (strcmp(OP_CODE, "LW") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// Check the type of parameters

	// Param 1 meeds to be Rt (destination)
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Param 2 needs to be Rs (contains mem address)
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Param 3 needs to be an immediate
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	// Check the value of the parameters

	// Rt should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Put the binary together

	// Set the opcode
	setBits_str(31, "100011");

	// set Rt
	setBits_num(20, PARAM1.value, 5);

	// set Rs
	setBits_num(25, PARAM2.value, 5);

	// set immediate
	// Assumes PARAM3.value is a signed 16-bit int
	setBits_num(15, PARAM3.value, 16);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void lw_immd_bin(void) {
	// Verify LW op code bits
	if (checkBits(31, "100011") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// Extract values from binary

	// getBits(start_bit, width)
	uint32_t Rs = getBits(21, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(0, 16);


	// Set instruction values

	setOp("LW");
	// Set parameters
	setParam(1, REGISTER, Rt); //destination
	setParam(2, REGISTER, Rs); //first source register operand
	setParam(3, IMMEDIATE, imm16); //second source register operand


	// Indicate decoding is complete
	state = COMPLETE_DECODE;
}
