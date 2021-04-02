.text

.global __start

__start:

la a3, lenght # a3 = adress of lenght
lw a3, 0(a3) # a3 = lenght value
slli a3, a3, 2 # a3 = lenght value << 2 (multiply by 4 for addresing of words)
la a4, array  # a4 = array adress
add a3, a3, a4 # a3 = end of array adress
li a5, 1
lw a6, 0(a3)
# now we can use a4

#a4 = adress
#a3 = end
outter_loop:
  beqz a5, finish # if = zero
  li a5, 0# F , 1 if unsorted, 0 if sorted
  la a4, array # a6 = start of array
  addi a3, a3, -4 # I-- for exit
  # if start adress array's part equals last adress -> we cant take j+1 -> end of sorting
  bltu a3, a4,finish # exit if <=  
    inner_loop:
      lw t2, 0(a4) # value of a[j]
      lw t3, 4(a4) # valye of a[j+1]
    
      bltu t2,t3,skip_swap # if a[j] < a[j+1] -> skip
        li a5, 1     # F = 1 (array is unsorted)
        sw t3, 0(a4) # \ S A
        sw t2, 4(a4) # /  W P   
        
      skip_swap:
        addi a4, a4, 4 # like j++
        bltu a4, a3, inner_loop # if j < i -> continue
        j outter_loop # to start

finish:
  li a0, 10 # calling x10 = 10 for exit
  ecall # exit

.rodata
  lenght:
    .word 10
    
.data
array:
    .word 5,52,51,42,56,0,12,23,42,4
#sorted_array:
#    .word 1,2,3,4,5,6,7,8,9,10

  
  
  
  