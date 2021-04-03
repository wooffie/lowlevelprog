.text

.global start

start:

la a1, length # a1 = adress of length
lw a1, 0(a1) # a1 = length value
slli a1, a1, 2 # a1 = length value << 2 (multiply by 4 for addresing of words)
la a0, array  # a0 = array adress
add a1, a1, a0 # a1 = end of array adress
li a3, 1

addi a1, a1, -4 # I-- for exit
beq a1, a0,finish # if lenght = 1

# now we can use a0

#a0 = adress
#a1 = end
outter_loop:
  beqz a3, finish # if = zero
  li a3, 0# F , 1 if unsorted, 0 if sorted
  la a0, array 
  
    inner_loop:
      lw t2, 0(a0) # value of a[j]
      lw t3, 4(a0) # value of a[j+1]
    
      bltu t2,t3,skip_swap # if a[j] < a[j+1] -> skip
        li a3, 1     # F = 1 (array is unsorted)
        sw t3, 0(a0) # \ S A
        sw t2, 4(a0) # /  W P   
        
      skip_swap:
        addi a0, a0, 4 # like j++
        bltu a0, a1, inner_loop # if j < i -> continue
  addi a1, a1, -4 # I-- for exit
  # if start adress array's part equals last adress -> we cant take j+1 -> end of sorting
   bne a1, a0,outter_loop

finish:
  li a0, 10 # calling x10 = 10 for exit
  ecall # exit

.rodata
  length:
    .word 10
    
.data
array:
    .word 5,1,51,42,56,0,12,23,42,4
