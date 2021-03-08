	.text
	.file	"offset.c"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	xorl	%eax, %eax
	movl	%eax, %esi
	movl	$0, -4(%rbp)
	leaq	.L.str(%rip), %rdi
	movb	$0, %al
	callq	printf@PLT
	xorl	%ecx, %ecx
	movl	%ecx, %edx
	addq	$4, %rdx
	leaq	.L.str.1(%rip), %rdi
	movq	%rdx, %rsi
	movl	%eax, -8(%rbp)                  # 4-byte Spill
	movb	$0, %al
	callq	printf@PLT
	leaq	.L.str.2(%rip), %rdi
	movl	$8, %esi
	movl	%eax, -12(%rbp)                 # 4-byte Spill
	movb	$0, %al
	callq	printf@PLT
	xorl	%ecx, %ecx
	movl	%eax, -16(%rbp)                 # 4-byte Spill
	movl	%ecx, %eax
	addq	$16, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"offset of x1: %lu\n"
	.size	.L.str, 19

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	"offset of x2: %lu\n"
	.size	.L.str.1, 19

	.type	.L.str.2,@object                # @.str.2
.L.str.2:
	.asciz	"offset of x3: %lu\n"
	.size	.L.str.2, 19

	.ident	"clang version 11.1.0"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym printf
