# MIPS_byTechieTribe

Code in phase1.cpp(latest update).

/***** Syntax Restrictions when compared to Qtspim *****/
1. Space is must between registers used in instructions
2. .data segment at the beginning of code and then .text
3. Code in the next line after label i.e only label names should be there in that line, no other instruction(for .text segment).
4. Currently .word, .asciiz are only implemented.
5. .word only stores decimal integers.
6. Memory size limit - (1024 * 4) bytes.
7. There must be a syscall for exit else there will be an error(with $v0 == 10).
8. Currently no comments are allowed in program.
9. Elements in array that are initialized in .data, needs to be separated by ','.
10. lw, sw will currently work only for integers(will not work for strings). // lw format : lw $r1, n($r2) sw format : sw  $r1, n($r2) ,where n is integer
11. for lw/sw, we can load/store if address fetched is multiple of 4.
12. .data can only be written at start of program and only one .data is considered.
13. Data(values, array names, etc.) in same line as label(for .data segment). // label_name: .word  1,2,4,6
14. Registers can be addressed/accessed only by their equivalent names. // e.g $zero should be used instead of $0

// output format....
