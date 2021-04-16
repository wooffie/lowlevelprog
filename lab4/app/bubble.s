	.file	"bubble.c"
	.option nopic
	.text
	.align	2
	.globl	bubble_sort
	.type	bubble_sort, @function
bubble_sort:
	addi	t3,a1,-1
	beqz	t3,.L1
	lui	a5,%hi(f.2552)
	lw	a4,%lo(f.2552)(a5)
	li	a5,1
	beq	a4,a5,.L1
	slli	a2,a1,2
	add	a2,a0,a2
	li	a7,0
	li	t1,1
	li	a6,0
	j	.L3
.L11:
	lui	a5,%hi(f.2552)
	li	a4,1
	sw	a4,%lo(f.2552)(a5)
	ret
.L5:
	addi	a5,a5,4
.L4:
	beq	a5,a2,.L9
	lw	a4,-4(a5)
	lw	a3,0(a5)
	bleu	a4,a3,.L5
	sw	a3,-4(a5)
	sw	a4,0(a5)
	mv	a1,a6
	j	.L5
.L9:
	addi	a7,a7,1
	beq	a7,t3,.L10
	addi	a2,a2,-4
	beq	a1,t1,.L11
.L3:
	addi	a5,a0,4
	mv	a1,t1
	j	.L4
.L10:
	lui	a5,%hi(f.2552)
	sw	a1,%lo(f.2552)(a5)
.L1:
	ret
	.size	bubble_sort, .-bubble_sort
	.section	.sbss,"aw",@nobits
	.align	2
	.type	f.2552, @object
	.size	f.2552, 4
f.2552:
	.zero	4
	.ident	"GCC: (SiFive GCC 8.2.0-2019.05.3) 8.2.0"
