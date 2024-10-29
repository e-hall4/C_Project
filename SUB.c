#include "Instruction.h"

void sub_reg_assm(void) {
	// Checking that the op code matches
	if (strcmp(OP_CODE, "SUB") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

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
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set the opcode for R-type instruction (for SUB, it's "000000")
	setBits_num(31, 0, 6);

	// Set the funct for SUB ("100000")
	setBits_str(5, "100010");

	// set Rd (destination register)
	setBits_num(15, PARAM1.value, 5);

	// set Rs (first source register)
	setBits_num(25, PARAM2.value, 5);

	// set Rt (second source register)
	setBits_num(20, PARAM3.value, 5);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void sub_reg_bin(void) {
	// Check if the op code bits match
	if (checkBits(31, "000000") != 0 || checkBits(5, "100010") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// If the op code bits match, then the rest can be read as correctly

	/*
		Finding values in the binary
	*/
	uint32_t Rd = getBits(15, 5); // destination register
	uint32_t Rs = getBits(25, 5); // first source register
	uint32_t Rt = getBits(20, 5); // second source register

	/*
		Setting Instruction values
	*/
	setOp("SUB");
	setParam(1, REGISTER, Rd); // destination
	setParam(2, REGISTER, Rs); // first source
	setParam(3, REGISTER, Rt); // second source

	// tell the system the decoding is done
	state = COMPLETE_DECODE;
}


