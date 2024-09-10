#if !defined NUMBERS_H
#define NUMBERS_H

void print_numbers(int* numbers, int digits);
void print_arrays();
void handle_tens(char* result, int* numbers, int* digits);
// void handle_tens(char* result, int* numbers, int digits);
void handle_hundreds(char* result, int* numbers, int digits);
void and_space(char* result);
int number_to_danish(int number, char* result);

#endif // MACRO
