#include "Instruction.h"

void mult_reg_assm(void) {
    // Checking that the op code matches
    if (strcmp(OP_CODE, "MULT") != 0) {
        state = WRONG_COMMAND;
        return;
    }


    // First parameter should be a register
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    // This is MULT register, so param 2 needs to be a register
    if (PARAM2.type != REGISTER) {
        state = MISSING_REG;
        return;
    }


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

   

    // Set the opcode
    setBits_num(31, 0, 6);

    // Set the funct 
    setBits_str(5, "011000"); 

    // set Rs
    setBits_num(25, PARAM1.value, 5);

    // set Rt
    setBits_num(20, PARAM2.value, 5);

    // Rd and shamt are not used, so set them to 0
    setBits_num(15, 0, 5); // Rd
    setBits_num(10, 0, 5); // shamt

    // tell the system the encoding is done
    state = COMPLETE_ENCODE;
}

void mult_reg_bin(void) {
    // Check if the op code bits match
    if (checkBits(31, "000000") != 0 || checkBits(15, "0000000000011000") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    
    uint32_t Rs = getBits(25, 5);
    uint32_t Rt = getBits(20, 5);

    setOp("MULT");
    setParam(1, REGISTER, Rs); // first source register operand
    setParam(2, REGISTER, Rt); // second source register operand

    // tell the system the decoding is done
    state = COMPLETE_DECODE;
}



