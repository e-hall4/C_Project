// Ashurs Code

#include "Instruction.h"

void slt_reg_assm(void) {
	// Checking that the op code matches
	if (strcmp(OP_CODE, "SLT") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/

	// First parameter should always be a register (destination)
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// SLT requires both operands to be registers
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}


	/*
		Checking the value of parameters
	*/

	// Rd should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rt should be 31 or less
	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}


	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_num(31, 0, 6);

	// Set the funct for SLT (typically "101010")
	setBits_str(5, "101010");

	// Set Rd
	setBits_num(15, PARAM1.value, 5);

	// Set Rs
	setBits_num(25, PARAM2.value, 5);

	// Set Rt
	setBits_num(20, PARAM3.value, 5);

	// Tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void slt_reg_bin(void) {
	// Check if the op code bits match
	if (checkBits(31, "000000") != 0 || checkBits(10, "00000101010") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Finding values in the binary
	*/
	uint32_t Rd = getBits(15, 5);
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);


	/*
		Setting Instruction values
	*/

	setOp("SLT");
	setParam(1, REGISTER, Rd); // destination
	setParam(2, REGISTER, Rs); // first source register operand
	setParam(3, REGISTER, Rt); // second source register operand


	// Tell the system the decoding is done
	state = COMPLETE_DECODE;
}
