.section .text
.globl kefel
kefel: movl %edi,%eax
shl $4,%eax
movl %edi,%ecx
shl $2,%ecx
subl %ecx,%eax
movl %edi,%ecx
shl $7,%ecx
addl %ecx,%eax
movl %edi,%ecx
shl $14,%ecx
addl %ecx,%eax
movl %edi,%ecx
shl $10,%ecx
subl %ecx,%eax
ret
