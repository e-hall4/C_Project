#include "Instruction.h"

void mfhi_reg_assm(void) {
    // Checking that the op code matches
    if (strcmp(OP_CODE, "MFHI") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Checking the type of parameters
    */

    // The first parameter should be a register (destination)
    if (PARAM1.type != REGISTER) {
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

    /*
        Putting the binary together
    */

    // Set the opcode for R-type (always 000000)
    setBits_num(31, 0, 6);

    // Set the function code for MFHI (010000)
    setBits_str(5, "010000");

    // Set Rd (destination register)
    setBits_num(15, PARAM1.value, 5);

    // Set Rs and Rt to 0, since they’re unused
    setBits_num(25, 0, 5);  // Rs
    setBits_num(20, 0, 5);  // Rt

    // Set shamt to 0, as it’s unused
    setBits_num(10, 0, 5);  // shamt

    // Indicate that the encoding is complete
    state = COMPLETE_ENCODE;
}

void mfhi_reg_bin(void) {
    // Check if the opcode and function code bits match for MFHI
    if (checkBits(31, "0000000000000000") != 0 || checkBits(10, "00000010000") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Finding values in the binary
    */

    // Retrieve Rd (destination register) from the binary
    uint32_t Rd = getBits(15, 5);

    /*
        Setting Instruction values
    */

    setOp("MFHI");
    setParam(1, REGISTER, Rd);  // Destination register

    // Indicate that the decoding is complete
    state = COMPLETE_DECODE;
}
