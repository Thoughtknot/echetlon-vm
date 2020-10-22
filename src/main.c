#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "instructions/instructions.h"
#define HEAPSIZE 0x100000
#define STACKSIZE 0x1000

void read_image(StackFrame* frame, const char* image_path) {
	printf("Reading program\n");
    FILE* file = fopen(image_path, "rb");
    if (!file) 
        exit(1);
    
    fseek(file, 0L, SEEK_END);
    long size = ftell(file);
    frame->program = (uint8_t*) malloc(size);
    frame->program_size = size;
    rewind(file);

    size_t read = fread(frame->program, sizeof(uint8_t), size, file);
    printf("Read %ld bytes - size %d\n", read, size);
    fclose(file);
}

void free_frame(StackFrame* frame) {
    free(frame->program);
    free(frame);
}

VirtualMachine* initialize(const char* image_path) {
    VirtualMachine* vm = (VirtualMachine*) malloc(sizeof(VirtualMachine));
    vm->memory = (Memory*) malloc(sizeof(Memory));
    vm->callstack = (Callstack*) malloc(sizeof(Callstack));
    vm->callstack->current = (StackFrame*) malloc(sizeof(StackFrame));
    vm->callstack->prev = NULL;
    vm->memory->heap = (uint8_t*) malloc(HEAPSIZE);
    vm->memory->stack = (uint8_t*) malloc(STACKSIZE);
    vm->memory->stack_counter = 0;
    vm->is_running = true;
    vm->objDefs = (ObjDefList*) malloc(sizeof(ObjDefList));
    vm->objDefs->self = NULL;
    vm->objDefs->next = NULL;
    vm->objDefs->prev = NULL;
    read_image(vm->callstack->current, image_path);
    vm->callstack->current->program_counter = 0;
    return vm;
}

int main(int argc, char* argv[]) {
    printf("Echetlon starting\n");
    if (argc != 2) {
        printf("No file supplied\n");
        exit(2);
    }
    VirtualMachine* vm = initialize(argv[1]);
    while (vm->is_running) {
        handle_instruction(vm);
        if (vm->callstack->current->program_counter >= vm->callstack->current->program_size) {
            if (vm->callstack->prev == NULL) {
                vm->is_running = false;
            }
            else {
                free_frame(vm->callstack->current);
                vm->callstack = vm->callstack->prev;
            }
        }
    }
    return 0;
}