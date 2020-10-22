#include "../data.h"

void handle_instruction(VirtualMachine* vm);

enum OpCodes {
    NOP = 0x00,

    ADD_1 = 0x01,
    ADD_2 = 0x02,
    ADD_3 = 0x03,
    ADD_4 = 0x04,
    ADD_5 = 0x05,
    ADD_0 = 0x06,

    SUB_1 = 0x10,
    SUB_2 = 0x11,
    SUB_3 = 0x12,
    SUB_4 = 0x13,
    SUB_5 = 0x14,
    SUB_0 = 0x15,

    LD_0_1 = 0x20,
    LD_0_2 = 0x21,
    LD_0_3 = 0x22,
    LD_0_4 = 0x23,
    LD_0_5 = 0x24,
    LD_1_0 = 0x25,
    LD_1_2 = 0x26,
    LD_1_3 = 0x27,
    LD_1_4 = 0x28,
    LD_1_5 = 0x29,
    LD_2_1 = 0x2A,
    LD_2_0 = 0x2B,
    LD_2_3 = 0x2C,
    LD_2_4 = 0x2D,
    LD_2_5 = 0x2E,

    LD_N_0 = 0x2F,
    LD_0_N = 0x30,

    LD_0_I_8 = 0x40,
    LD_0_I_16 = 0x41,
    LD_0_I_32 = 0x42,
    LD_0_I_64 = 0x43,
    LD_1_I_8 = 0x44,
    LD_1_I_16 = 0x45,
    LD_1_I_32 = 0x46,
    LD_1_I_64 = 0x47,


    STORE_0 = 0x50,
    STORE_1 = 0x51,

    DEFINE_OBJ = 0x60,
    NEW_OBJ_0 = 0x61,
    LOAD_OBJ_ARG_0 = 0x62,
    STORE_OBJ_0_ARG_1 = 0x63,
    NEW_ARRAY_0 = 0x64,
    STORE_0_ARRAY_ITEMS_IMM_8 = 0x65,
    STORE_0_ARRAY_ITEM_1_8 = 0x66,
    STORE_0_ARRAY_ITEM_1_16 = 0x67,
    STORE_0_ARRAY_ITEM_1_32 = 0x68,
    STORE_0_ARRAY_ITEM_1_64 = 0x69,
    LOAD_0_ARRAY_ITEM_1_64 = 0x6A,
    LOAD_0_ARRAY_ITEM_1_32 = 0x6B,
    LOAD_0_ARRAY_ITEM_1_16 = 0x6C,
    LOAD_0_ARRAY_ITEM_1_8 = 0x6D,

    PUSH_0 = 0x70,
    PUSH_1 = 0x71,
    PUSH_2 = 0x72,
    
    POP_0 = 0x78,
    POP_1 = 0x79,
    POP_2 = 0x7A,

    JMP = 0x80,
    JMP_NZ = 0x81,
    JMP_Z = 0x82,
    LABEL_0 = 0x83,
    LABEL_1 = 0x84,

    CALL_0 = 0x88,
    RET = 0x89,

    DEFINE_METHOD = 0x90,

    PRINT_0 = 0xF0,
    PRINT_CHAR_0 = 0xF1,
    DEBUG_PRINT_HEAP = 0xFF, 
};