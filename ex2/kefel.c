#include <stdio.h>
#include <stdlib.h>

#define HEADER ".section .text\n.globl kefel\nkefel: "
#define MOV_SELF "movl %%edi,%%eax\n"
#define RET_0 "movl $0,%%eax\n"
#define RET_MINUS "neg %%eax\n"
#define LEA_N "leal (%%eax,%%eax,%d),%%eax\n"
#define SHL_N "shl $%d,%%eax\n"
#define MOV_SHL_NC "movl %%edi,%%ecx\nshl $%d,%%ecx\n"
#define SUB_SELF "subl %%edi,%%eax\n"
#define ADD_SELF "addl %%edi,%%eax\n"
#define SELF_ADD_SUB_NEG !negative ? ADD_SELF : SUB_SELF
#define SELF_ADD_SUB_NEG_INVERT negative ? ADD_SELF : SUB_SELF
#define SUB_EAXC "subl %%ecx,%%eax\n"
#define ADD_EAXC "addl %%ecx,%%eax\n"
#define EAXC_ADD_SUB_NEG !negative ? ADD_EAXC : SUB_EAXC
#define EAXC_ADD_SUB_NEG_INVERT negative ? ADD_EAXC : SUB_EAXC
#define FOOTER "ret\n"

void create2(FILE *fp, int k)
{
    fprintf(fp, HEADER);
    int negative = (k < 0);
    !k ? fprintf(fp, RET_0) : 0;
    k && (k != -1) ? fprintf(fp, MOV_SELF) : 0;
    if (negative)
        k *= -1;
    if (k > 1)
    {
        int factors[] = {9, 5, 3};
        int f = 0;
        int count = 0;
        for (; f < 3; f++)
        {
            count = 0;
            if (!(k % factors[f]))
            {
                int factor = factors[f];
                int temp = k;
                for (; !(temp % 2); temp >>= 1, count++)
                    ;
                if (temp == factor)
                {
                    fprintf(fp, LEA_N, factor - 1);
                    count > 0 ? fprintf(fp, SHL_N, count) : 0;
                    negative ? fprintf(fp, RET_MINUS) : 0;
                    break;
                }
            }
        }
        int addone = 0;
        if (f == 3) //for ended without printing anything, assuming k is not in the form f*2^n (f in [9,5,3]).
        {
            int first = 1;
            while (k)
            {
                int mask = 1;
                int m, n;
                for (m = 0; (k ^ mask) > k; mask <<= 1, m++)
                    ;
                for (n = m - 1; (k ^ mask) < k; mask <<= 1, n++)
                    ;
                if (negative)
                {
                    int temp = n;
                    n = m;
                    m = temp;
                }
                if (!n)
                {
                    addone = 1;
                    k--;
                }
                else
                {
                    if (first)
                    {
                        fprintf(fp, SHL_N, negative || !(n - m) ? n : n + 1);
                        (negative && n == m) ? fprintf(fp, RET_MINUS) : 0;
                    }
                    else
                    {
                        fprintf(fp, MOV_SHL_NC, negative || !(n - m) ? n : n + 1);
                        fprintf(fp, negative && n == m ? SUB_EAXC : ADD_EAXC);
                    }
                    if (n - m)
                    {
                        if (m > 0)
                        {
                            fprintf(fp, MOV_SHL_NC, negative ? m + 1 : m);
                            fprintf(fp, SUB_EAXC);
                        }
                        else
                        {
                            fprintf(fp, SUB_SELF);
                        }
                    }
                    k += !negative ? (1 << m) - (1 << n + 1) : (1 << n) - (1 << m + 1);
                    first = 0;
                }
            }
        }
        addone ? fprintf(fp, SELF_ADD_SUB_NEG) : 0;
        fprintf(fp, FOOTER);
    }
    else
    {
        negative ? fprintf(fp, RET_MINUS) : 0;
        fprintf(fp, FOOTER);
    }
    fclose(fp);
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("Please provide input for k.\n");
        return 1;
    }
    FILE *fp = fopen("kefel.s", "w");
    create2(fp, atoi(argv[1]));
    return 0;
}
