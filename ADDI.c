/*
	@author Elijah Hall
*/

#include "Instruction.h"

void addi_immd_assm(void) {
	// Verify the correct op code
	if (strcmp(OP_CODE, "ADDI") != 0) {
		// If op code doesn't match, this isn't the correct cmd
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of params
	*/

	// The first param should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Param 2 needs to be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Param 3 needs to be an immediate
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	/*
		Checking the value of params
	*/

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

	// The immediate value is limited to 16 bits, this is 0xFFFF
	if (PARAM3.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_str(31, "001000");

	// set Rt
	setBits_num(20, PARAM1.value, 5);

	// set Rs
	setBits_num(25, PARAM2.value, 5);

	// set immediate
	setBits_num(15, PARAM3.value, 16);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void addi_immd_bin(void) {
	// Verify addi op code bits
	if (checkBits(31, "001000") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// Extract values from binary

	// getBits(start_bit, width)
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);

	// Set instruction values

	setOp("ADDI");
	setParam(1, REGISTER, Rt); // destination
	setParam(2, REGISTER, Rs); // register operand
	setParam(3, IMMEDIATE, imm16); // immediate

	// Tell the system the decoding is done
	state = COMPLETE_DECODE;
}
