#include <stdio.h>
#include <stdlib.h>

#define HEADER ".section .text\n.globl kefel\nkefel: mov %%edi,%%eax\n"
#define FOOTER "ret\n"
#define RET_0 "mov $0,%%eax\n"
#define RET_MINUS "neg %%eax\n"
#define LEA_N "lea (%%eax,%%eax,%d),%%eax\n"
#define SHL_N "shl $%d,%%eax\n"
#define SEVEN_EAX "sal $3,%%eax\nsub %%edi,%%eax\n"
#define ADD_SELF "add %%edi,%%eax\n"
#define SUB_SELF "sub %%edi,%%eax\n"

void create_asm(int);
void print_op(FILE *, int);

int isPowerOf2(int i)
{
    if (i == 1)
        return 1;
    if (i % 2)
        return 0;
    return isPowerOf2(i >> 1);
}
int main(int argc, char *argv[])
{
    int k;
    if (argc <= 1)
    {
        printf("Please provide input for k.\n");
        return 1;
    }
    create_asm(atoi(argv[1]));
    return 0;
}

void create_asm(int k)
{
    FILE *fp;
    fp = fopen("kefel.s", "w");
    fprintf(fp, HEADER);
    print_op(fp, k);
    fprintf(fp, FOOTER);
    fclose(fp);
}

void print_op(FILE *fp, int i)
{
    int count = 0;
    switch (i)
    {
    case 1:
        break;
    case 0:
        fprintf(fp, RET_0);
        break;
    case -1:
        fprintf(fp, RET_MINUS);
        break;
    case 3:
    case 5:
    case 9:
        fprintf(fp, LEA_N, i - 1);
        break;
    case 7:
        fprintf(fp, SEVEN_EAX);
        break;
    default:
        if (i % 2)
        {
            if (isPowerOf2(i + 1))
            {
                print_op(fp, i + 1);
                fprintf(fp, SUB_SELF);
            }
            else
            {
                print_op(fp, i - 1);
                fprintf(fp, ADD_SELF);
            }
        }
        else
        {
            for (; i % 2 == 0; i >>= 1, count++)
            {
            }
            printf("%d\n", i);
            print_op(fp, i);
            count > 0 ? fprintf(fp, SHL_N, count) : 0;
        }
        break;
    }
}
