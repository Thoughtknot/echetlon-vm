#include "instructions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../memory/memory.h"

uint8_t read_next_8(VirtualMachine* vm);
uint16_t read_next_16(VirtualMachine* vm);
uint32_t read_next_32(VirtualMachine* vm);
uint64_t read_next_64(VirtualMachine* vm);

void add(VirtualMachine* vm, uint8_t opcode) {
    switch (opcode) {
        case ADD_1:
            vm->registers[0] += vm->registers[1];
            break;
        case ADD_2:
            vm->registers[0] += vm->registers[2];
            break;
        case ADD_3:
            vm->registers[0] += vm->registers[3];
            break;
        case ADD_4:
            vm->registers[0] += vm->registers[4];
            break;
        case ADD_5:
            vm->registers[0] += vm->registers[5];
            break;
        case ADD_0:
            vm->registers[0] += vm->registers[0];
            break;
    }
    vm->memory->zero = vm->registers[0] == 0;
}

void sub(VirtualMachine* vm, uint8_t opcode) {
    switch (opcode) {
        case SUB_1:
            vm->registers[0] -= vm->registers[1];
            break;
        case SUB_2:
            vm->registers[0] -= vm->registers[2];
            break;
        case SUB_3:
            vm->registers[0] -= vm->registers[3];
            break;
        case SUB_4:
            vm->registers[0] -= vm->registers[4];
            break;
        case SUB_5:
            vm->registers[0] -= vm->registers[5];
            break;
        case SUB_0:
            vm->registers[0] -= vm->registers[0];
            break;
    }
    vm->memory->zero = vm->registers[0] == 0;
}

void ldreg(VirtualMachine* vm, uint8_t opcode) {
    switch (opcode) {
        case LD_0_1:
            vm->registers[0] = vm->registers[1];
            break;
        case LD_0_2:
            vm->registers[0] = vm->registers[2];
            break;
        case LD_0_3:
            vm->registers[0] = vm->registers[3];
            break;
        case LD_0_4:
            vm->registers[0] = vm->registers[4];
            break;
        case LD_0_5:
            vm->registers[0] = vm->registers[5];
            break;
        case LD_1_0:
            vm->registers[1] = vm->registers[0];
            break;
        case LD_1_2:
            vm->registers[1] = vm->registers[2];
            break;
        case LD_1_3:
            vm->registers[1] = vm->registers[3];
            break;
        case LD_1_4:
            vm->registers[1] = vm->registers[4];
            break;
        case LD_1_5:
            vm->registers[1] = vm->registers[5];
            break;
        case LD_2_1:
            vm->registers[2] = vm->registers[1];
            break;
        case LD_2_0:
            vm->registers[2] = vm->registers[0];
            break;
        case LD_2_3:
            vm->registers[2] = vm->registers[3];
            break;
        case LD_2_4:
            vm->registers[2] = vm->registers[4];
            break;
        case LD_2_5:
            vm->registers[2] = vm->registers[5];
            break;
        case LD_N_0:
            vm->registers[read_next_8(vm)] = vm->registers[0];
            break;
        case LD_0_N:
            vm->registers[0] = vm->registers[read_next_8(vm)];
            break;
    }
}

void ldimm(VirtualMachine* vm, uint8_t opcode) {
    switch (opcode) {
        case LD_0_I_8:
            vm->registers[0] = read_next_8(vm);
            break;
        case LD_0_I_16:
            vm->registers[0] = read_next_16(vm);
            break;
        case LD_0_I_32:
            vm->registers[0] = read_next_32(vm);
            break;
        case LD_0_I_64:
            vm->registers[0] = read_next_64(vm);
            break;
        case LD_1_I_8:
            vm->registers[1] = read_next_8(vm);
            break;
        case LD_1_I_16:
            vm->registers[1] = read_next_16(vm);
            break;
        case LD_1_I_32:
            vm->registers[1] = read_next_32(vm);
            break;
        case LD_1_I_64:
            vm->registers[1] = read_next_64(vm);
            break;
    }
}

void push(VirtualMachine* vm, uint64_t value) {
    vm->memory->stack[vm->memory->stack_counter++] = value & 0xFF;
    vm->memory->stack[vm->memory->stack_counter++] = (value >> 8) & 0xFF;
    vm->memory->stack[vm->memory->stack_counter++] = (value >> 16) & 0xFF;
    vm->memory->stack[vm->memory->stack_counter++] = (value >> 24) & 0xFF;
    vm->memory->stack[vm->memory->stack_counter++] = (value >> 32) & 0xFF;
    vm->memory->stack[vm->memory->stack_counter++] = (value >> 40) & 0xFF;
    vm->memory->stack[vm->memory->stack_counter++] = (value >> 48) & 0xFF;
    vm->memory->stack[vm->memory->stack_counter++] = (value >> 56) & 0xFF;
    //printf("Push: %lld, sp: %lld\n", value, vm->program->stack_counter);
}

uint64_t pop(VirtualMachine* vm) {
    uint64_t b7 = (uint64_t) vm->memory->stack[--vm->memory->stack_counter];
    uint64_t b6 = (uint64_t) vm->memory->stack[--vm->memory->stack_counter];
    uint64_t b5 = (uint64_t) vm->memory->stack[--vm->memory->stack_counter];
    uint64_t b4 = (uint64_t) vm->memory->stack[--vm->memory->stack_counter];
    uint64_t b3 = (uint64_t) vm->memory->stack[--vm->memory->stack_counter];
    uint64_t b2 = (uint64_t) vm->memory->stack[--vm->memory->stack_counter];
    uint64_t b1 = (uint64_t) vm->memory->stack[--vm->memory->stack_counter];
    uint64_t b0 = (uint64_t) vm->memory->stack[--vm->memory->stack_counter];
    uint64_t val = b0 | (b1 << 8) | (b2 << 16) | (b3 << 24)  | (b4 << 32)  | (b5 << 40)  | (b6 << 48)  | (b7 << 56);
    //printf("Pop: %lld, sp: %lld\n", val, vm->program->stack_counter);
    return val;
}

void pop_push(VirtualMachine* vm, uint8_t opcode) {
    switch (opcode) {
        case PUSH_0:
            push(vm, vm->registers[0]);
            break;
        case PUSH_1:
            push(vm, vm->registers[1]);
            break;
        case POP_0:
            vm->registers[0] = pop(vm);
            break;
        case POP_1:
            vm->registers[1] = pop(vm);
            break;
    }
}

void define_object(VirtualMachine* vm) {
    ObjDef* obj = (ObjDef*) malloc(sizeof(ObjDef));
    obj->id = read_next_8(vm);
    obj->num_args = read_next_8(vm);
    obj->arg_sizes = malloc(obj->num_args);
    printf("Defining object %02x, with %02x parameters of size [", obj->id, obj->num_args);
    for (int i = 0; i < obj->num_args; i++) {
        obj->arg_sizes[i] = read_next_8(vm);
        printf("%02x", obj->arg_sizes[i]);
        if (i < obj->num_args - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    
    if (vm->objDefs->self == NULL) {
        vm->objDefs->self = obj;
    }
    else {
        ObjDefList* objList = (ObjDefList*) malloc(sizeof(ObjDefList));
        objList->self = obj;
        objList->next = NULL;
        objList->prev = vm->objDefs;
        vm->objDefs->next = objList; 
        vm->objDefs = objList;
    }
}

void print_registers(VirtualMachine* vm) {
    printf("Registers[");
    for (int i = 0; i < 6; i++) {
        printf("%d: %016x ", i, vm->registers[i]);
    }
    printf("]\n");
}

void print_heap(VirtualMachine* vm) {
    print_registers(vm);
    printf("Heap:\n");
    for (int i = 0; i < vm->memory->heap_counter; i++) {
        if (i % 16 == 0) {
            printf("\n");
        }
        printf("%02x ", vm->memory->heap[i]);
    } 
    printf("\n");
    printf("Stack:\n");
    for (int i = 0; i < vm->memory->stack_counter; i++) {
        if (i % 16 == 0) {
            printf("\n");
        }
        printf("%02x ", vm->memory->stack[i]);
    } 
    printf("\n");
}

void allocate_object(VirtualMachine* vm, ObjDef* def) {
    uint16_t size = 0;
    for (int i = 0; i < def->num_args; i++) {
        size += def->arg_sizes[i];
    }
    vm->registers[0] = vm->memory->heap_counter;
    vm->memory->heap_counter += size;
}

void allocate_array(VirtualMachine* vm, uint8_t size) {
    vm->registers[0] = vm->memory->heap_counter;
    vm->memory->heap_counter += size;
    printf("Allocating an array of size %d from %d to %d\n", size, vm->registers[0], vm->memory->heap_counter);
}

ObjDef* get_def_from_id(VirtualMachine* vm, uint8_t obj_id) {
    ObjDefList* def = vm->objDefs;
    while (true) {
        if (def->self->id == obj_id)
            return def->self;
        else
            def = def->prev;
    }
    return NULL;
}

void load_obj_arg(VirtualMachine* vm, uint64_t address, ObjDef* def, uint8_t arg_id) {
    uint16_t offset = 0;
    for (int i = 0; i < arg_id; i++) {
        offset += def->arg_sizes[i];
    }
    if (def->arg_sizes[arg_id] <= 8) {
        uint64_t val = read_bytes(vm, address + offset, def->arg_sizes[arg_id]);
        vm->registers[0] = val;
    }
    else {
        vm->registers[0] = address + offset;
    }
}

void store_obj_arg(VirtualMachine* vm, uint64_t address, uint64_t arg_value, ObjDef* def, uint8_t arg_id) {
    uint16_t offset = 0;
    for (int i = 0; i < arg_id; i++) {
        offset += def->arg_sizes[i];
    }
    if (def->arg_sizes[arg_id] <= 8) {
        printf("Storing %d of size %d at %d\n", arg_value, def->arg_sizes[arg_id], address);
        write_bytes(vm, address + offset, arg_value, def->arg_sizes[arg_id]);
    }
    else {
        // what is in reg0 is just an address - copy the dest values
        copy_bytes(vm, address + offset, arg_value, def->arg_sizes[arg_id]);
    }
}

void run_method(VirtualMachine* vm, Method* method, ObjDef* def) {
    Callstack* stack = (Callstack*) malloc(sizeof(Callstack));
    stack->current = (StackFrame*) malloc(sizeof(StackFrame));
    stack->current->program_counter = 0;
    stack->current->program_size = method->length;
    stack->current->program = malloc(stack->current->program_size);
    memcpy(stack->current->program, method->program, stack->current->program_size);
    stack->prev = vm->callstack;
    vm->callstack = stack;
}

void jumps(VirtualMachine* vm, uint8_t opcode) {
    switch (opcode) {
        case LABEL_0: {
            vm->registers[0] = vm->callstack->current->program_counter;
            break;
        }
        case LABEL_1: {
            vm->registers[1] = vm->callstack->current->program_counter;
            break;
        }
        case CALL_0: {
            uint8_t obj_id = read_next_8(vm);
            ObjDef* def = get_def_from_id(vm, obj_id);
            uint8_t method_id = read_next_8(vm);
            Method* method = def->methods[method_id];
            printf("Running method: obj: %d meth: %d \n", obj_id, method_id);
            fflush(stdout);
            run_method(vm, method, def);
            break;
        }
        case JMP: {
            vm->callstack->current->program_counter = vm->registers[0];
            break;
        }
        case JMP_Z: {
            if (vm->memory->zero) {
                vm->callstack->current->program_counter = vm->registers[0];
            }
            break;
        }
        case JMP_NZ: {
            printf("Jumping to %d\n", vm->registers[0]);
            if (!vm->memory->zero) {
                vm->callstack->current->program_counter = vm->registers[0];
            }
            break;
        }
    }
}

void methods(VirtualMachine* vm, uint8_t opcode) {
    switch (opcode) {
        case DEFINE_METHOD: {
            uint8_t obj_id = read_next_8(vm);
            ObjDef* def = get_def_from_id(vm, obj_id);
            uint8_t method_id = read_next_8(vm);
            uint16_t length = read_next_16(vm);
            def->methods[method_id] = (Method*) malloc(sizeof(Method));
            def->methods[method_id]->length = length;
            def->methods[method_id]->program = (uint8_t*) malloc(length);
            for (uint16_t i = 0; i < length; i++) {
                def->methods[method_id]->program[i] = read_next_8(vm);
            }
            printf("Defining method {obj %d, meth %d, len %d }\n", obj_id, method_id, length);
            fflush(stdout);
            break;
        }
    }
}

void store(VirtualMachine* vm, uint8_t opcode) {
    switch (opcode) {
        case STORE_0: {
            uint64_t address = vm->memory->heap_counter;
            write64(vm, vm->memory->heap_counter, vm->registers[0]);
            vm->memory->heap_counter += 8;
            vm->registers[0] = address;
            break;
        }
        case STORE_1: {
            uint64_t address = vm->memory->heap_counter;
            write64(vm, vm->memory->heap_counter, vm->registers[1]);
            vm->memory->heap_counter += 8;
            vm->registers[1] = address;
            break;
        }
        case DEFINE_OBJ:
            define_object(vm);
            break;
        case NEW_OBJ_0: {
            uint8_t obj_id = read_next_8(vm);
            ObjDef* def = get_def_from_id(vm, obj_id);
            allocate_object(vm, def);
            break;
        }
        case LOAD_OBJ_ARG_0: {
            uint8_t obj_id = read_next_8(vm);
            ObjDef* def = get_def_from_id(vm, obj_id);
            uint8_t arg_id = read_next_8(vm);
            load_obj_arg(vm, vm->registers[0], def, arg_id);
            break;
        }
        case STORE_OBJ_0_ARG_1: {
            uint8_t obj_id = read_next_8(vm);
            ObjDef* def = get_def_from_id(vm, obj_id);
            uint8_t arg_id = read_next_8(vm);
            printf("Storing arg %d of object %d, #args: %d, arg_size: %d\n", arg_id, obj_id, def->num_args, def->arg_sizes[arg_id]);
            store_obj_arg(vm, vm->registers[0], vm->registers[1], def, arg_id);
            break;
        }
        case NEW_ARRAY_0: {
            uint8_t num_bytes = read_next_8(vm);
            allocate_array(vm, num_bytes);
            break;
        }
        case LOAD_0_ARRAY_ITEM_1_64: {
            uint8_t offset = vm->registers[1];
            uint64_t address = vm->registers[0];
            vm->registers[0] = read_bytes(vm, address + offset * 8, 8);
            break;
        }
        case STORE_0_ARRAY_ITEMS_IMM_8: {
            uint64_t address = vm->registers[0];
            uint8_t num_items = read_next_8(vm);
            printf("Writing %d items to array.\n", num_items);
            for (int i = 0; i < num_items; i++) {
                write_bytes(vm, address + i, read_next_8(vm), 1);
            }
            break;
        }
        case STORE_0_ARRAY_ITEM_1_8: {
            uint8_t offset = read_next_8(vm);
            uint64_t address = vm->registers[0];
            uint64_t value = vm->registers[1];
            write_bytes(vm, address, value, 1);
            break;
        }
        case STORE_0_ARRAY_ITEM_1_16: {
            uint8_t offset = read_next_8(vm);
            uint64_t address = vm->registers[0];
            uint64_t value = vm->registers[1];
            write_bytes(vm, address, value, 2);
            break;
        }
        case STORE_0_ARRAY_ITEM_1_32: {
            uint8_t offset = read_next_8(vm);
            uint64_t address = vm->registers[0];
            uint64_t value = vm->registers[1];
            write_bytes(vm, address, value, 4);
            break;
        }
        case STORE_0_ARRAY_ITEM_1_64: {
            uint8_t offset = read_next_8(vm);
            uint64_t address = vm->registers[0];
            uint64_t value = vm->registers[1];
            printf("Storing val: %d at address: %d and offset: %d\n", value, address, offset);
            write_bytes(vm, address + offset, value, 8);
            print_heap(vm);
            break;
        }
    }
}

void handle_instruction(VirtualMachine* vm) {
    uint8_t opcode = read_next_8(vm);
    if (opcode != 0x00) {
        printf("Opcode: %02x at %x, sp: %x\n", opcode, vm->callstack->current->program_counter, vm->memory->stack_counter);
       //print_heap(vm);
    }
    if (opcode < 0x10) {
        add(vm, opcode);
    }
    else if (opcode < 0x20) {
        sub(vm, opcode);
    }
    else if (opcode < 0x40) {
        ldreg(vm, opcode);
    }
    else if (opcode < 0x50) {
        ldimm(vm, opcode);
    }
    else if (opcode < 0x70) {
        store(vm, opcode);
    }
    else if (opcode < 0x80) {
        pop_push(vm, opcode);
    }
    else if (opcode < 0x90) {
        jumps(vm, opcode);
    }
    else if (opcode < 0xA0) {
        methods(vm, opcode);
    }
    else if (opcode == PRINT_0) {
        uint64_t address = vm->registers[0];
        printf("¤¤ PRINT ¤¤\n");
        for (int i = 0; i < 100; i++) {
            uint8_t byte = read_bytes(vm, address++, 1);
            if (byte == 0x00)
                break;
            printf("%c", byte);
        }
        printf("\n");
    }
    else if (opcode == PRINT_CHAR_0) {
        uint64_t address = vm->registers[0];
        printf("¤¤ PRINTC ¤¤\n");
        printf("%c\n", vm->registers[0]);
    }
    else if (opcode == DEBUG_PRINT_HEAP) {
        print_heap(vm);
    }
    else {
        printf("Unhandled operation %02x at %lld\n", opcode, vm->callstack->current->program_counter);
    }
}

uint8_t read_next_8(VirtualMachine* vm) {
    return vm->callstack->current->program[vm->callstack->current->program_counter++];
}

uint16_t read_next_16(VirtualMachine* vm) {
    uint16_t b1 = read_next_8(vm);
    uint16_t b0 = read_next_8(vm);
    return b0 | (b1 << 8);
}

uint32_t read_next_32(VirtualMachine* vm) {
    uint32_t b1 = read_next_16(vm);
    uint32_t b0 = read_next_16(vm);
    return b0 | (b1 << 16);
}

uint64_t read_next_64(VirtualMachine* vm) {
    uint64_t b7 = (uint64_t) vm->callstack->current->program[vm->callstack->current->program_counter++];
    uint64_t b6 = (uint64_t) vm->callstack->current->program[vm->callstack->current->program_counter++];
    uint64_t b5 = (uint64_t) vm->callstack->current->program[vm->callstack->current->program_counter++];
    uint64_t b4 = (uint64_t) vm->callstack->current->program[vm->callstack->current->program_counter++];
    uint64_t b3 = (uint64_t) vm->callstack->current->program[vm->callstack->current->program_counter++];
    uint64_t b2 = (uint64_t) vm->callstack->current->program[vm->callstack->current->program_counter++];
    uint64_t b1 = (uint64_t) vm->callstack->current->program[vm->callstack->current->program_counter++];
    uint64_t b0 = (uint64_t) vm->callstack->current->program[vm->callstack->current->program_counter++];
    uint64_t val = b0 | (b1 << 8) | (b2 << 16) | (b3 << 24)  | (b4 << 32)  | (b5 << 40)  | (b6 << 48)  | (b7 << 56);
    return val;
}