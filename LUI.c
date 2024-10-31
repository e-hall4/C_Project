#include "Instruction.h"

void lui_immd_assm(void) {
    // Checking that the op code matches
    if (strcmp(OP_CODE, "LUI") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    // Checking the type of parameters
    if (PARAM1.type != REGISTER) { // Rt (destination register)
        state = MISSING_REG;
        return;
    }

    if (PARAM2.type != IMMEDIATE) { // Immediate value
        state = INVALID_REG;
        return;
    }

    // Checking the value of parameters
    if (PARAM1.value > 31) {
        state = INVALID_REG;
        return;
    }

    // Putting the binary together
    // Set the opcode for LUI (001111)
    setBits_str(26, "001111");

    // Set Rt (destination register)
    setBits_num(21, PARAM1.value, 5);

    // Set the immediate value (16 bits)
    setBits_num(0, PARAM2.value, 16); // Assuming PARAM2.value is a signed 16-bit integer

    // Tell the system the encoding is done
    state = COMPLETE_ENCODE;
}

void lui_immd_bin(void) {
    // Check if the op code bits match
    if (checkBits(26, "001111") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    // If the op code bits match, then the rest can be read as correctly

    // Finding values in the binary
    uint32_t Rt = getBits(21, 5); // destination register
    uint32_t immediate = getBits(0, 16); // immediate value

    // Setting Instruction values
    setOp("LUI");
    setParam(1, REGISTER, Rt); // destination
    setParam(2, IMMEDIATE, immediate); // immediate value

    // Tell the system the decoding is done
    state = COMPLETE_DECODE;
}



