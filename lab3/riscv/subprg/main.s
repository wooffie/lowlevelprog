#main.s
.text

.global main

main:
la a0, array # array pointer
lw a1, array_length # length

  addi sp, sp, -16       
  sw ra, 12(sp)          

call sort

la a0, array_2
lw a1, array_length_2

call sort

  lw ra, 12(sp)          
  addi sp, sp, 16        

ret

.rodata
array_length:
 .word 10
array_length_2:
  .word 5

.data
array:
 .word 12,32,42,24,5,52,42,2,6,2
array_2:
  .word 23,42,4,2,0
 
 