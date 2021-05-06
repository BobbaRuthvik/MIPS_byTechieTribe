https://docs.google.com/spreadsheets/d/12PiLKiLYvmdKcy4POBE31EGX6sucR8nDNE4RUI8ccZA/edit?usp=sharing
A video quick peek: https://drive.google.com/file/d/1FPbimk58vlMeyfudLroX6Ci86oybfFcg/view?usp=sharing
# MIPS_byTechieTribe

GUI interface code in "mips" folder(latest update).(PHASE - 1)
--------------------------------------------------------------
/***** Syntax Restrictions when compared to Qtspim *****/

1. Registers can be addressed/accessed only by their equivalent names. // e.g $zero should be used instead of $0
2. .data segment at the beginning of code and then .text
3. Code in the next line after label i.e only label names should be there in that line, no other instruction(for .text segment).
4. Currently .word, .asciiz are only implemented.
5. using .word only decimal integers are stored.
6. There must be a syscall for exit else there will be an error(with $v0 == 10).
7. Currently no comments are allowed in program.
8. Elements in array that are initialized in .data, needs to be separated by ','.
9. lw, sw will currently work only for integers(will not work for strings). // lw format : lw $r1, n($r2) sw format : sw  $r1, n($r2) ,where n is integer
10. for lw/sw, we can load/store if address fetched is multiple of 4.
11. .data can only be written at start of program and only one .data is considered.
12. Data(values, array names, etc.) in same line as label(for .data segment). // e.g label_name: .word  1,2,4,6

GUI interface code in "mips_phase2" folder(latest update).(PHASE - 2)
---------------------------------------------------------------------

1. psuedo instruction "la" is assumned as a single instruction( Asummed number to be stored in register is less than 2^16 )
2. We assumed no branch predictors, and therefore after every branch instruction there will be one stall.

GUI interface code in "phase3.cpp" file(latest update).(PHASE - 3)
---------------------------------------------------------------------
1. Only restriction here is block sizes are to be given in multiples of 4(all sizes are assumed to be in bytes).
2. Only applied cache mechanism on "lw" and "sw"(not on "la").


STEPS TO RUN THROUGH GUI INTERFACE:
----------------------------------
1. Download QT creator, open version.
2. Download unziped folders of Techie Tribe code.
3. Open folder through QT creator.
4. Reference for installing qt creator: https://www.youtube.com/watch?v=hQSuM1uCdXE

NOTE: Stepwise execution is exclusive for phase-1(not implemented in GUI but in "phase1.cpp" file).
