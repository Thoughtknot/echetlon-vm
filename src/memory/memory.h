#include "../data.h"

void write64(VirtualMachine* v, uint64_t address, uint64_t value);
void write_bytes(VirtualMachine* v, uint64_t address, uint64_t value, uint8_t bytes);
uint64_t read64(VirtualMachine* v, uint64_t address);
uint8_t read8(VirtualMachine* v, uint64_t address);
uint64_t read_bytes(VirtualMachine* v, uint64_t address, uint8_t bytes);
void copy_bytes(VirtualMachine* vm, uint64_t source_address, uint64_t dest_address, uint8_t bytes);
