.section .text
.globl kefel
kefel: movl %edi,%eax
shl $1,%eax
movl %edi,%ecx
shl $7,%ecx
addl %ecx,%eax
movl %edi,%ecx
shl $3,%ecx
subl %ecx,%eax
movl %edi,%ecx
shl $8,%ecx
addl %ecx,%eax
movl %edi,%ecx
shl $10,%ecx
addl %ecx,%eax
movl %edi,%ecx
shl $12,%ecx
addl %ecx,%eax
movl %edi,%ecx
shl $18,%ecx
addl %ecx,%eax
movl %edi,%ecx
shl $15,%ecx
subl %ecx,%eax
ret
