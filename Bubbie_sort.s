.data
array:  .word 10, 5, 18, 7, -9, 0, 56, 3, 7, 200, 8
space:  .asciiz " "

	.text
	.globl main
main:
	la $s0, array
	addi $s1, $zero, 10
	j bubbleSort
	
bubbleSort:
	beq  $zero, $s1, out
	add  $s2, $s1, $zero
	j loop

loop:
	beq $zero, $s2, jmp
	lw  $t0, 0($s0)
	lw  $t1, 4($s0)

	slt $t2, $t0, $t1
	bne $zero, $t2, jump
	sw  $t0, 4($s0)
	sw  $t1, 0($s0)
	j jump

jump:
	addi $s0, $s0, 4
	sub $s2, $s2, 1 
	j loop

jmp:
	sub $s1, $s1, 1 
	la $s0, array
	j bubbleSort 
	
out:
	addi $s1, $zero, 11
	j print
	
print:
	beq $zero, $s1, jmpp
	addi $v0, $zero, 1
	lw $a0, 0($s0)
	syscall
	addi $v0, $zero, 4
	la $a0, space
	syscall
	addi $s0, $s0, 4
	sub $s1, $s1, 1
	j print

jmpp:
	addi $v0, $zero, 10
	syscall
