/*
    @author Elijah Hall
*/

#include "Instruction.h"

void beq_immd_assm(void) {
    // Verify the correct op code
    if (strcmp(OP_CODE, "BEQ") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    // Check the parameter types

    // The first parameter should be a register
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    // The second parameter should be a register
    if (PARAM2.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    // The third parameter should be an immediate value (branch offset)
    if (PARAM3.type != IMMEDIATE) {
        state = INVALID_PARAM;
        return;
    }

    // Check parameter values

    // Rs should be 31 or less
    if (PARAM1.value > 31) {
        state = INVALID_REG;
        return;
    }

    // Rt should be 31 or less
    if (PARAM2.value > 31) {
        state = INVALID_REG;
        return;
    }

    // The immediate value is limited to 16 bits
    if (PARAM3.value > 0xFFFF) {
        state = INVALID_IMMED;
        return;
    }

    // Assemble the binary

    // Set the opcode for BEQ (000100 in binary)
    setBits_str(31, "000100");

    // Set Rs (first register)
    setBits_num(25, PARAM1.value, 5);

    // Set Rt (second register)
    setBits_num(20, PARAM2.value, 5);

    // Set the immediate offset (third parameter)
    setBits_num(15, PARAM3.value, 16);

    // Indicate that the encoding is complete
    state = COMPLETE_ENCODE;
}

void beq_immd_bin(void) {
    // Verify BEQ op code bits
    if (checkBits(31, "000100") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    // Extract values from binary

    // Get Rs, Rt, and the immediate offset
    uint32_t Rs = getBits(25, 5);
    uint32_t Rt = getBits(20, 5);
    uint32_t imm16 = getBits(15, 16);

    // Set instruction values

    setOp("BEQ");
    setParam(1, REGISTER, Rs);      // First source register
    setParam(2, REGISTER, Rt);      // Second source register
    setParam(3, IMMEDIATE, imm16);  // Immediate offset

    // Indicate that the decoding is complete
    state = COMPLETE_DECODE;
}