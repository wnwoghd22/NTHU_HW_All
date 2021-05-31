.global codegen
codegen:
// BEGIN PROLOGUE
	sw s0, -4(sp) // save frame pointer
	addi sp, sp, -4
	addi s0, sp, 0 // set new frame
	sw sp, -4(s0)
	sw s1, -8(s0)
	sw s2, -12(s0)
	sw s3, -16(s0)
	sw s4, -20(s0)
	sw s5, -24(s0)
	sw s6, -28(s0)
	sw s7, -32(s0)
	sw s8, -36(s0)
	sw s9, -40(s0)
	sw s10, -44(s0)
	sw s11, -48(s0)
	addi sp, s0, -48 // update stack pointer
// END PROLOGUE
// declare a at -8(s0) 
        li t0, 2147483647
        sw t0, -4(sp)
        addi sp, sp, -4
        li t0, 1
        sw t0, -4(sp)
        addi sp, sp, -4
        lw t0, 0(sp)
        addi sp, sp, 4
        lw t1, 0(sp)
        addi sp, sp, 4
        sub t0, t1, t0
        sw t0, -4(sp)
        addi sp, sp, -4
        li t0, 2147483646
        sw t0, -4(sp)
        addi sp, sp, -4
        lw t0, 0(sp)
        addi sp, sp, 4
        lw t1, 0(sp)
        addi sp, sp, 4
        div t0, t1, t0
        sw t0, -4(sp)
	addi sp, sp, -4
	lw t0, 0(sp)
	sw t0, -8(s0)
	addi sp, sp, 4
WHILE0:
        li t0, 27
        sw t0, -4(sp)
        lw a0, -4(sp)
        li t0, 1
        sw t0, -4(sp)
        lw a1, -4(sp)
        sw ra, -4(sp)
        addi sp, sp, -4
        jal ra, digitalWrite
        lw ra, 0(sp)
        addi sp, sp, 4
        lw t0, -8(s0)
        sw t0, -4(sp)
        addi sp, sp, -4
        li t0, 1000
        sw t0, -4(sp)
        addi sp, sp, -4
        lw t0, 0(sp)
        addi sp, sp, 4
        lw t1, 0(sp)
        addi sp, sp, 4
        mul t0, t0, t1
        sw t0, -4(sp)
        lw a0, -4(sp)
        sw ra, -4(sp)
        addi sp, sp, -4
        jal ra, delay
        lw ra, 0(sp)
        addi sp, sp, 4
        li t0, 27
        sw t0, -4(sp)
        lw a0, -4(sp)
        li t0, 0
        sw t0, -4(sp)
        lw a1, -4(sp)
        sw ra, -4(sp)
        addi sp, sp, -4
        jal ra, digitalWrite
        lw ra, 0(sp)
        addi sp, sp, 4
        li t0, 10
        sw t0, -4(sp)
        addi sp, sp, -4
        lw t0, -8(s0)
        sw t0, -4(sp)
        addi sp, sp, -4
        lw t0, 0(sp)
        addi sp, sp, 4
        lw t1, 0(sp)
        addi sp, sp, 4
        sub t0, t1, t0
        sw t0, -4(sp)
        addi sp, sp, -4
        li t0, 1000
        sw t0, -4(sp)
        addi sp, sp, -4
        lw t0, 0(sp)
        addi sp, sp, 4
        lw t1, 0(sp)
        addi sp, sp, 4
        mul t0, t0, t1
        sw t0, -4(sp)
        lw a0, -4(sp)
        sw ra, -4(sp)
        addi sp, sp, -4
        jal ra, delay
        lw ra, 0(sp)
        addi sp, sp, 4
        lw t0, -8(s0)
        addi t0, t0, 1
        sw t0, -8(s0)
        sw t0, -4(sp)
        addi sp, sp, -4
        li t0, 9
        sw t0, -4(sp)
        addi sp, sp, -4
        lw t0, 0(sp)
        addi sp, sp, 4
        lw t1, 0(sp)
        addi sp, sp, 4
        blt t0, t1, ELSE1
        li t0, 1
        sw t0, -4(sp)
        j EXIT1
ELSE1:
        li t0, 0
        sw t0, -4(sp)
EXIT1:
        lw t0, -4(sp)
        li t1, 0
        beq t0, t1, EXIT0
        j WHILE0
EXIT0:
// BEGIN EPILOGUE
	lw s11, -48(s0)
	lw s10, -44(s0)
	lw s9, -40(s0)
	lw s8, -36(s0)
	lw s7, -32(s0)
	lw s6, -28(s0)
	lw s5, -24(s0)
	lw s4, -20(s0)
	lw s3, -16(s0)
	lw s2, -12(s0)
	lw s1, -8(s0)
	lw sp, -4(s0)
	addi sp, sp, 4
	lw s0, -4(sp)
// END EPILOGUE

	jalr zero, 0(ra) // return
