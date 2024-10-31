#include "Instruction.h"

void bne_immd_assm(void) {
    // Checking that the op code matches
    if (strcmp(OP_CODE, "BNE") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Checking the type of parameters
    */

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

    /*
        Checking the value of parameters
    */

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

    /*
        Putting the binary together
    */

    // Set the opcode for BNE (00101 in binary)
    setBits_str(31, "000101");

    // Set Rs (first register)
    setBits_num(25, PARAM1.value, 5);

    // Set Rt (second register)
    setBits_num(20, PARAM2.value, 5);

    // Set the immediate offset (third parameter)
    setBits_num(15, PARAM3.value, 16);

    // Indicate that the encoding is complete
    state = COMPLETE_ENCODE;
}

void bne_immd_bin(void) {
    // Check if the op code bits match for BNE
    if (checkBits(31, "000101") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Finding values in the binary
    */
    // Get Rs, Rt, and the immediate offset
    uint32_t Rs = getBits(25, 5);
    uint32_t Rt = getBits(20, 5);
    uint32_t imm16 = getBits(15, 16);

    /*
        Setting Instruction values
    */

    setOp("BNE");
    setParam(1, REGISTER, Rs);      // First source register
    setParam(2, REGISTER, Rt);      // Second source register
    setParam(3, IMMEDIATE, imm16);  // Immediate offset

    // Indicate that the decoding is complete
    state = COMPLETE_DECODE;
}
