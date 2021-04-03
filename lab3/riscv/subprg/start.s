#start.s
.text

start:
.global start

	call main
finish:
	li a0, 10
	ecall
 