#ifndef __data
#define __data
#include <stdint.h>
#include <stdbool.h>

typedef struct Method Method;
struct Method {
    uint16_t length;
    uint8_t* program;
};

typedef struct ObjDef ObjDef;
struct ObjDef {
    uint8_t id;
    uint8_t num_args;
    uint8_t* arg_sizes;
    Method* methods[0x10];
};

typedef struct Memory Memory;
struct Memory {
    uint8_t* heap;
    uint8_t* stack;
    uint64_t stack_counter;
    uint64_t heap_counter;
    bool zero;
    bool carry;
};

typedef struct ObjDefList ObjDefList;
struct ObjDefList {
    ObjDef* self;
    ObjDefList* next;
    ObjDefList* prev;
};

typedef struct StackFrame StackFrame;
struct StackFrame {
    uint64_t registers[0x100];
    uint8_t* program;
    long program_size;
    uint64_t program_counter;
};

typedef struct Callstack Callstack;
struct Callstack {
    StackFrame* current;
    Callstack* prev;
};

typedef struct VirtualMachine VirtualMachine;
struct VirtualMachine {
    Memory* memory;
    Callstack* callstack;
    uint64_t registers[0x100];
    bool is_running;
    ObjDefList* objDefs;
};

#endif