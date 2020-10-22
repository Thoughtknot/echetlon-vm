#include "memory.h"
#include <stdio.h>

void write_bytes(VirtualMachine* v, uint64_t address, uint64_t value, uint8_t bytes) {
    for (uint8_t i = 0; i < bytes; i++) {
        if (i > 0) {
            v->memory->heap[address + i] = (value >> (8 * i)) & 0xFF;
        }
        else {
            v->memory->heap[address] = value & 0xFF;
        }
    } 
}

void write64(VirtualMachine* v, uint64_t address, uint64_t value) {
    v->memory->heap[address] = (uint8_t) value & 0xFF;
    v->memory->heap[address + 1] = (value >> 8) & 0xFF;
    v->memory->heap[address + 2] = (value >> 16) & 0xFF;
    v->memory->heap[address + 3] = (value >> 24) & 0xFF;
    v->memory->heap[address + 4] = (value >> 32) & 0xFF;
    v->memory->heap[address + 5] = (value >> 40) & 0xFF;
    v->memory->heap[address + 6] = (value >> 48) & 0xFF;
    v->memory->heap[address + 7] = (value >> 56) & 0xFF;
}

uint64_t read64(VirtualMachine* v, uint64_t address) {
    uint64_t b0 = v->memory->heap[address];
    uint64_t b1 = v->memory->heap[address + 1];
    uint64_t b2 = v->memory->heap[address + 2];
    uint64_t b3 = v->memory->heap[address + 3];
    uint64_t b4 = v->memory->heap[address + 4];
    uint64_t b5 = v->memory->heap[address + 5];
    uint64_t b6 = v->memory->heap[address + 6];
    uint64_t b7 = v->memory->heap[address + 7];
    uint64_t val = b0 | (b1 << 8) | (b2 << 16) | (b3 << 24)  | (b4 << 32)  | (b5 << 40)  | (b6 << 48)  | (b7 << 56);
    return val;
}

uint64_t read_bytes(VirtualMachine* v, uint64_t address, uint8_t bytes) {
    uint64_t val = 0;
    for (int i = 0; i < bytes; i++) {
        uint64_t value = v->memory->heap[address + i];
        if (i > 0) {
            val |= value << (8 * i);
        }
        else {
            val |= value;
        }
    }
    return val;
}

void copy_bytes(VirtualMachine* vm, uint64_t source_address, uint64_t dest_address, uint8_t bytes) {
    for (int i = 0; i < bytes; i++) {
        vm->memory->heap[dest_address + i] = vm->memory->heap[source_address + i];
    }
}

