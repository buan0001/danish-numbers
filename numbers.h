#ifndef NUMBERS_H
#define NUMBERS_H

typedef enum
{
    NEVER,
    EVERY,
    LAST
} occurence;

struct NumberFormat
{
    occurence og;
    occurence e;
    occurence et;
};

int number_to_danish(int number, char *buffer,struct NumberFormat format);
void handle_tens(int number, char *buffer);
void handle_hundreds(int number, char *buffer, struct NumberFormat format, int endFlag);
void handle_formatting(char *buffer, struct NumberFormat format, int endFlag, char *num_type, char *one_type, int f_amount, int s_amount);

#endif
