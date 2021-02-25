	
	.text
	.globl main
 
	la $s0, array
	li $s1, 10
	jal bubbleSort
	li $s1, 11
	jal print
	li $v0, 10
	syscall

bubbleSort:
	beq  $0, $s1, out
	add  $s2, $s1, $0
	j loop

loop:
	beq $0, $s2, jmp
	lw  $t0, 0($s0)
	lw  $t1, 4($s0)

	slt $t2, $t0, $t1
	bne $0, $t2, jump
	sw  $t0, 4($s0)
	sw  $t1, 0($s0)
	j jump

jump:
	addi $s0, $s0, 4
	sub $s2, $s2, 1 
	j loop

	.data
array:  .word 10, 5, 18, 7, -9, 0, 56, 3, 7, 200, 8
	

jmp:
	sub $s1, $s1, 1 
	la $s0, array
	j bubbleSort 
	
out:
	jr $ra

	.data
space:  .asciiz " "

print:
	beq $0, $s1, out
	li $v0, 1
	lw $a0, 0($s0)
	syscall
	li $v0, 4
	la $a0, space
	syscall
	addi $s0, $s0, 4
	sub $s1, $s1, 1
	j print
	
	

		








