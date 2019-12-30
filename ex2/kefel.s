.section .text
.globl kefel
kefel: movl %edi,%eax
shl $2,%eax
subl %edi,%eax
movl %edi,%ecx
shl $7,%ecx
addl %ecx,%eax
movl %edi,%ecx
shl $4,%ecx
subl %ecx,%eax
ret
