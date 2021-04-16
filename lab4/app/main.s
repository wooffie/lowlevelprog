	.file	"main.c"
	.option nopic
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sw	ra,28(sp)
	sw	s0,24(sp)
	sw	s1,20(sp)
	sw	s2,16(sp)
	sw	s3,12(sp)
	lui	s0,%hi(.LANCHOR0)
	addi	s1,s0,%lo(.LANCHOR0)
	addi	s2,s1,24
	addi	s0,s0,%lo(.LANCHOR0)
	lui	s3,%hi(.LC0)
.L2:
	lw	a1,0(s0)
	addi	a0,s3,%lo(.LC0)
	call	printf
	addi	s0,s0,4
	bne	s0,s2,.L2
	li	a0,10
	call	putchar
	li	a1,6
	lui	a0,%hi(.LANCHOR0)
	addi	a0,a0,%lo(.LANCHOR0)
	call	bubble_sort
	lui	s0,%hi(.LC0)
.L3:
	lw	a1,0(s1)
	addi	a0,s0,%lo(.LC0)
	call	printf
	addi	s1,s1,4
	bne	s1,s2,.L3
	li	a0,0
	lw	ra,28(sp)
	lw	s0,24(sp)
	lw	s1,20(sp)
	lw	s2,16(sp)
	lw	s3,12(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.data
	.align	2
	.set	.LANCHOR0,. + 0
	.type	array, @object
	.size	array, 24
array:
	.word	1337
	.word	1488
	.word	228
	.word	42
	.word	2048
	.word	0
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
.LC0:
	.string	"%u "
	.ident	"GCC: (SiFive GCC 8.2.0-2019.05.3) 8.2.0"
