#sort.s
.text

sort:
.globl sort
# a1 - length
# a0 - array pointer

mv a3, a1 # a3 - length
slli a3, a3, 2  # shift for multiply
add a3, a3, a0 # end of array+4
li a5, 1 # for exit
addi a3, a3, -4 # end of array
beq a3, a0,finish # if length = 1


outter_loop:
  beqz a5, finish # if sorted
  li a5, 0 # for exit
  mv a4, a0 # restore pointer j = 0

    inner_loop:
      lw t2, 0(a4) # t2 = a[j]
      lw t3, 4(a4) # t3 = a[j+1]
    
      bltu t2,t3,skip_swap 
        li a5, 1     # for exit
        sw t3, 0(a4) # swap
        sw t2, 4(a4) #swap
        
      skip_swap:
        addi a4, a4, 4 # j++
        bltu a4, a3, inner_loop # j < end 
        
      addi a3, a3, -4 # end--
      bne a3, a0, outter_loop # end = start
        
finish:
  ret
 