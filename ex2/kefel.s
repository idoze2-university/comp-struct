.section .text
.globl kefel
kefel: mov %edi,%eax
lea (%eax,%eax,2),%eax
shl $3,%eax
add %edi,%eax
shl $1,%eax
add %edi,%eax
ret
