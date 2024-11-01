#include "Instruction.h"

void sw_immd_assm(void) {
    // Checking that the op code matches
    if (strcmp(OP_CODE, "SW") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    // Checking the type of parameters
    if (PARAM1.type != REGISTER) { // Rs (base register)
        state = MISSING_REG;
        return;
    }

    if (PARAM2.type != REGISTER) { // Rt (source register)
        state = MISSING_REG;
        return;
    }

    if (PARAM3.type != IMMEDIATE) { // Offset
        state = INVALID_PARAM;
        return;
    }

    // Checking the value of parameters
    if (PARAM1.value > 31) {
        state = INVALID_REG;
        return;
    }

    if (PARAM2.value > 31) {
        state = INVALID_REG;
        return;
    }

    // Putting the binary together
    // Set the opcode for SW (101011)
    setBits_str(31, "101011");

    // Set Rs (base register)
    setBits_num(20, PARAM1.value, 5);

    // Set Rt (source register)
    setBits_num(25, PARAM2.value, 5);

    // Set the immediate value (offset)
    setBits_num(15, PARAM3.value, 16); // Assuming PARAM3.value is a signed 16-bit integer

    // Tell the system the encoding is done
    state = COMPLETE_ENCODE;
}

void sw_immd_bin(void) {
    // Check if the op code bits match
    if (checkBits(31, "101011") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    // If the op code bits match, then the rest can be read as correctly

    // Finding values in the binary
    uint32_t Rs = getBits(25, 5); // base register
    uint32_t Rt = getBits(20, 5); // source register
    uint32_t offset = getBits(15, 16); // immediate value (offset)

    // Setting Instruction values
    setOp("SW");
    setParam(1, REGISTER, Rs); // base
    setParam(2, REGISTER, Rt); // source
    setParam(3, IMMEDIATE, offset); // immediate value (offset)

    // Tell the system the decoding is done
    state = COMPLETE_DECODE;
}