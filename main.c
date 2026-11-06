#include <stdio.h>

#define MAX_CODE 256
#define STACK_SIZE 256
#define OP_HALT 0
#define OP_PRINT 1
#define OP_PUSH 2
#define OP_POP 3
#define OP_ADD 4
#define OP_SUB 5
#define OP_MUL 6
#define OP_DIV 7
#define OP_PRINT_STACK 8
#define OP_MOD 9
#define OP_NEG 10
#define OP_EQUAL 11
#define OP_LESS 12
#define OP_GREATER 13
#define OP_NOT_EQUAL 14
#define OP_LESS_EQUAL 15
#define OP_GREATER_EQUAL 16
#define OP_NOT 17
#define OP_AND 18
#define OP_OR 19
#define OP_JUMP 20
#define OP_JUMP_IF_FALSE 21
#define OP_DUP 22
#define OP_SWAP 23
#define OP_PRINT_VALUE 24
#define OP_LOAD_CONST 25
#define OP_STORE_VAR 26
#define OP_LOAD_VAR 27
#define OP_INC_VAR 28
#define OP_DEC_VAR 29
#define OP_NEG_VAR 30




typedef struct {
	int ip;
	int code_count;

	unsigned char code[MAX_CODE];

	int stack[STACK_SIZE];
	int sp;
	
	int constants[STACK_SIZE];
	int constants_count;

	int variables[STACK_SIZE];
	int variable_count;
} VM;

int push(VM *vm, int value) {
	if (vm->sp >= STACK_SIZE - 1) {
		printf("Runtime Error: Stack overflow!\n");
		return 0;
	}

	vm->stack[++vm->sp] = value;
	return 1;
}

int pop(VM *vm, int *value) {
	if (vm->sp < 0) {
		printf("Runtime Error: Stack underflow!\n");
		return 0;
	}

	*value = vm->stack[vm->sp--];
	return 1;
}

int read_byte(VM *vm, unsigned char *value) {
	if (vm->ip < 0 || vm->ip >= vm->code_count) {
		printf("Runtime Error: Missing instruction operand!\n");
		return 0;
	}

	*value = vm->code[vm->ip];
	vm->ip++;

	return 1;
}


int run_vm(VM *vm) {
	printf("CSls VM created!\n");


		while (1) {

			if (vm->ip < 0 || vm->ip >= vm->code_count) {
				printf("Runtime Error: Invalid instruction address!\n");
				break;
			}

			unsigned char instruction = vm->code[vm->ip];

			vm->ip++;

			if (instruction == OP_PUSH) {
				unsigned char operand;

				if (!read_byte(vm, &operand)) {
					break;
				}

				int value = operand;

				if (!push(vm, value)) {
					break;
				}

			}
			else if (instruction == OP_POP) {
				int value;
				if (!pop(vm, &value)) {
				
					break;
				}

			}
			else if (instruction == OP_ADD) {
				int a, b;

				if (!pop(vm, &b) || !pop(vm, &a)) {
					break;
				}

				int result = a + b;

				if (!push(vm, result)) {
					break;
				}

			}
			else if (instruction == OP_SUB) {
				int a, b;

				if (!pop(vm, &b)) {
					break;
				}

				if (!pop(vm, &a)) {
					break;
				}

				int result = a - b;

				if (!push(vm, result)) {
					break;
				}

			}
			else if (instruction == OP_MUL) {
				int a, b;

				if (!pop(vm, &b)) {
					break;
				}

				if (!pop(vm, &a)) {
					break;
				}

				int result = a * b;

				if (!push(vm, result)) {
					break;
				}

			}
			else if (instruction == OP_DIV) {
				int a, b;

				if (!pop(vm, &b)) {
					break;
				}

				if (!pop(vm, &a)) {
					break;
				}

				if (b == 0) {
					printf("Runtime Error: Division by zero!\n");
					break;
				}

				int result = a / b;

				if (!push(vm, result)) {
					break;
				}

				printf("Divided: %d / %d = %d\n", a, b, result);
			}
			else if (instruction == OP_MOD) {
				int a, b;

				if (!pop(vm, &b)) {
					break;
				}

				if (!pop(vm, &a)) {
					break;
				}

				if (b == 0) {
					printf("Runtime Error: Modulus by zero!\n");
					break;
				}

				int result = a % b;

				if (!push(vm, result)) {
					break;
				}

			}
			else if (instruction == OP_NEG) {
				int value;

				if (!pop(vm, &value)) {
					break;
				}

				int result = -value;

				if (!push(vm, result)) {
					break;
				}

			}
			else if (instruction == OP_EQUAL) {
				int a, b;

				if (!pop(vm, &b)) {
					break;
				}

				if (!pop(vm, &a)) {
					break;
				}

				int result = (a == b);

				if (!push(vm, result)) {
					break;
				}

			}
			else if (instruction == OP_LESS) {
				int a, b;

				if (!pop(vm, &b)) {
					break;
				}

				if (!pop(vm, &a)) {
					break;
				}

				int result = (a < b);

				if (!push(vm, result)) {
					break;
				}

			}
			else if (instruction == OP_GREATER) {
				int a, b;

				if (!pop(vm, &b)) {
					break;
				}

				if (!pop(vm, &a)) {
					break;
				}

				int result = (a > b);

				if (!push(vm, result)) {
					break;
				}

			}
			else if (instruction == OP_NOT_EQUAL) {
				int a, b;

				if (!pop(vm, &b)) {
					break;
				}

				if (!pop(vm, &a)) {
					break;
				}

				int result = (a != b);

				if (!push(vm, result)) {
					break;
				}

			}
			else if (instruction == OP_LESS_EQUAL) {
				int a, b;

				if (!pop(vm, &b)) {
					break;
				}

				if (!pop(vm, &a)) {
					break;
				}

				int result = (a <= b);

				if (!push(vm, result)) {
					break;
				}

			}
			else if (instruction == OP_GREATER_EQUAL) {
				int a, b;

				if (!pop(vm, &b)) {
					break;
				}

				if (!pop(vm, &a)) {
					break;
				}

				int result = (a >= b);

				if (!push(vm, result)) {
					break;
				}

			}
			else if (instruction == OP_NOT) {
				int value;

				if (!pop(vm, &value)) {
					break;
				}

				int result = !value;

				if (!push(vm, result)) {
					break;
				}

			}
			else if (instruction == OP_AND) {
				int a, b;

				if (!pop(vm, &b)) {
					break;
				}

				if (!pop(vm, &a)) {
					break;
				}

				int result = a && b;

				if (!push(vm, result)) {
					break;
				}

			}
			else if (instruction == OP_OR) {
				int a, b;

				if (!pop(vm, &b)) {
					break;
				}

				if (!pop(vm, &a)) {
					break;
				}

				int result = a || b;

				if (!push(vm, result)) {
					break;
				}

				printf("Or: %d || %d -> %d\n", a, b, result);
			}
			else if (instruction == OP_JUMP) {
				unsigned char address;

				if (!read_byte(vm, &address)) {
					break;
				}

				vm->ip = address;
			}
			else if (instruction == OP_JUMP_IF_FALSE) {
				unsigned char address;

				if (!read_byte(vm, &address)) {
					break;
				}

				int condition;
				if (!pop(vm, &condition)) {
					break;
				}

				if (condition == 0) {
					vm->ip = address;
				}
			}
			else if (instruction == OP_DUP) {
				if (vm->sp < 0) {
					printf("Runtime Error: Stack is empty, cannot duplicate!\n");
					break;
				}

				int value = vm->stack[vm->sp];
				if (!push(vm, value)) {
					break;
				}

			}
			else if (instruction == OP_SWAP) {
				if (vm->sp < 1) {
					printf("Runtime Error: Not enough values on stack to swap!\n");
					break;
				}

				int top = vm->stack[vm->sp];
				int second = vm->stack[vm->sp - 1];

				vm->stack[vm->sp] = second;
				vm->stack[vm->sp - 1] = top;

			}
			else if (instruction == OP_LOAD_CONST) {
				unsigned char operand;

				if (!read_byte(vm, &operand)) {
					break;
				}

				int index = operand;

				if (index >= vm->constants_count) {
					printf("Runtime Error: Invalid constant index!\n");
					break;
				}

				int value = vm->constants[index];
				if (!push(vm, value)) {
					break;
				}

			}
			else if (instruction == OP_STORE_VAR) {
				unsigned char operand;

				if (!read_byte(vm, &operand)) {
					break;
				}

				int index = operand;

				if (index >= STACK_SIZE) {
					printf("Runtime Error: Invalid variable index!\n");
					break;
				}

				int value;
				if (!pop(vm, &value)) {
					break;
				}

				vm->variables[index] = value;

				if (index >= vm->variable_count) {
					vm->variable_count = index + 1;
				}

			}
			else if (instruction == OP_LOAD_VAR) {
				unsigned char operand;

				if (!read_byte(vm, &operand)) {
					break;
				}

				int index = operand;

				if (index >= vm->variable_count) {
					printf("Runtime Error: Invalid variable index!\n");
					break;
				}

				int value = vm->variables[index];
				if (!push(vm, value)) {
					break;
				}

			}
			else if (instruction == OP_INC_VAR) {
				unsigned char operand;

				if (!read_byte(vm, &operand)) {
					break;
				}

				int index = operand;

				if (index >= vm->variable_count) {
					printf("Runtime Error: Undefined variable!\n");
					break;
				}

				vm->variables[index] += 1;

			}
			else if (instruction == OP_DEC_VAR) {
				unsigned char operand;

				if (!read_byte(vm, &operand)) {
					break;
				}

				int index = operand;

				if (index >= vm->variable_count) {
					printf("Runtime Error: Undefined variable!\n");
					break;
				}

				vm->variables[index]--;

			}
			else if (instruction == OP_NEG_VAR) {
				unsigned char operand;

				if (!read_byte(vm, &operand)) {
					break;
				}

				int index = operand;

				if (index >= vm->variable_count) {
					printf("Runtime Error: Undefined variable!\n");
					break;
				}

				vm->variables[index] = -vm->variables[index];

			}











			else if (instruction == OP_PRINT_VALUE) {
				int value;
				if (!pop(vm, &value)) {
					break;
				}

				printf("Output: %d\n", value);
			}
			else if (instruction == OP_PRINT_STACK) {
				if (vm->sp < 0) {
					printf("Runtime Error: Stack is empty!\n");
					break;
				}

				printf("Stack top: %d\n", vm->stack[vm->sp]);
			}
			else if (instruction == OP_PRINT) {
				unsigned char value;

				if (!read_byte(vm, &value)) {
					break;
				}

				printf("VM value: %d\n", value);
			}
			else if (instruction == OP_HALT) {
				printf("VM stopped!\n");
				break;
			}
			else {
				printf("Runtime Error: Unknown instruction %d at address %d!\n",
					instruction, vm->ip - 1);
			}
		}

		return 0;
}

int main(void) {
		VM vm;

		vm.sp = -1;
		vm.ip = 0;
		vm.constants_count = 0;
		vm.variable_count = 0;

		vm.code_count = 21;

		vm.constants[0] = 0;
		vm.constants_count = 1;

		vm.code[0] = OP_LOAD_CONST;
		vm.code[1] = 0; // Load constant at index 0 (value 0)
		vm.code[2] = OP_STORE_VAR;
		vm.code[3] = 0; // Store in variable at index 0

		vm.code[4] = OP_LOAD_VAR;
		vm.code[5] = 0; // Load constant at index 0 (value 0)

		vm.constants[1] = 5; // Add a constant value 5
		vm.constants_count = 2;

		vm.code[6] = OP_LOAD_CONST;
		vm.code[7] = 1; // Load constant at index 1 (value 5)

		vm.code[8] = OP_LESS; // Compare the two values on the stack

		vm.code[9] = OP_JUMP_IF_FALSE;
		vm.code[10] = 20; // Jump to instruction at index 20 if false

		vm.code[11] = OP_LOAD_VAR;
		vm.code[12] = 0; // Load variable at index 0

		vm.code[13] = OP_PRINT_VALUE; // Print the value of the variable

		vm.code[14] = OP_INC_VAR;
		vm.code[15] = 0; // Increment variable at index 0

		vm.code[16] = OP_JUMP;
		vm.code[17] = 4; // Jump back to instruction at index 4

		

		vm.code[20] = OP_HALT;



		return run_vm(&vm);
}
