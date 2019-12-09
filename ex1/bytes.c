#include <stdlib.h>
#include <stdio.h>
#include "bytes.h"

byte_t create_byte(char *);
byte_t set_bit(byte_t, int, int);

int count = 0;
byte_t *create_bytes(char *file_name)
{
    FILE *filePtr = fopen(file_name, "r");
    if (!filePtr)
    {
        printf("Cannot Open File!");
        exit(1);
    }
    char answer[10];
    byte_t *byteArr = NULL;
    while (fgets(answer, 10, filePtr))
    {
        if (!byteArr)
        {
            byteArr = malloc(sizeof(byte_t));
        }
        else
        {
            byteArr = realloc(byteArr, sizeof(byte_t) * count);
        }
        byteArr[count++] = create_byte(answer);
    }
    fclose(filePtr);
    return byteArr;
}

byte_t create_byte(char *data)
{
    byte_t b = 0;
    for (int i = 0; i < 8; i += 2)
    {
        b += data[i] - '0' << i;
    }
    return b;
}

void print_bytes(byte_t *byte_array, FILE *out)
{
    if (!out)
    {
        printf("Unable to print to output file!");
        exit(1);
    }
    for (int i = 0; i < count; i++)
    {
        fprintf(out, "%02x", byte_array[i]);
    }
    fprintf(out, "\n");
}

void set_stud(byte_t *byte_array, int i, int j, int k)
{
    int pos = 2 * j - 1;
    byte_array[i - 1] = set_bit(byte_array[i - 1], pos, k / 2);
    byte_array[i - 1] = set_bit(byte_array[i - 1], pos - 1, k % 2);
}

byte_t set_bit(byte_t o, int pos, int b)
{
    byte_t mask = 1 << pos;
    return (o & ~mask) | ((b << pos) & mask);
}

float average_stud(byte_t *byte_array, int i)
{
    float sum = 0;
    byte_t answers = byte_array[i - 1];
    for (int k = 0; k < 4; k++)
    {
        sum += answers % 4;
        answers /= 4;
    }

    return sum / 4;
}

float average_ans(byte_t *byte_array, int j)
{
    float sum = 0;
    for (int i = 0; i < count; i++)
    {
        sum += (byte_array[i] >> (2 * (j - 1))) % 4;
    }
    return sum / count;
}