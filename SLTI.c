#include "Instruction.h"

void slti_immd_assm(void) {
    // Checking that the op code matches
    if (strcmp(OP_CODE, "SLTI") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Checking the type of parameters
    */

    // The first parameter should be a register (destination, Rt)
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    // The second parameter should be a register (source, Rs)
    if (PARAM2.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    // The third parameter should be an immediate value
    if (PARAM3.type != IMMEDIATE) {
        state = INVALID_PARAM;
        return;
    }

    /*
        Checking the value of parameters
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

    // The immediate value is limited to 16 bits (signed)
    if (PARAM3.value > 0xFFFF) {
        state = INVALID_IMMED;
        return;
    }

    /*
        Putting the binary together
    */

    // Set the opcode for SLTI
    setBits_str(31, "001010");

    // Set Rs (second parameter)
    setBits_num(25, PARAM2.value, 5);

    // Set Rt (first parameter)
    setBits_num(20, PARAM1.value, 5);

    // Set the immediate value (third parameter)
    setBits_num(15, PARAM3.value, 16);

    // Indicate that the encoding is complete
    state = COMPLETE_ENCODE;
}

void slti_immd_bin(void) {
    // Check if the opcode bits match for SLTI
    if (checkBits(31, "001010") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Finding values in the binary
    */

    // Retrieve Rs, Rt, and the immediate value
    uint32_t Rs = getBits(25, 5);
    uint32_t Rt = getBits(20, 5);
    uint32_t imm16 = getBits(15, 16);

    /*
        Setting Instruction values
    */

    setOp("SLTI");
    setParam(1, REGISTER, Rt);      // Destination register
    setParam(2, REGISTER, Rs);      // Source register
    setParam(3, IMMEDIATE, imm16);  // Immediate value

    // Indicate that the decoding is complete
    state = COMPLETE_DECODE;
}
