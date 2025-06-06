/*
 * (C) Copyright 2018
* SPDX-License-Identifier:	GPL-2.0+
 * wangwei <wangwei@allwinnertech.com>
 */

.globl _start
_start:
	/*disable interrupt*/
	csrw mie, zero

	/*enable theadisaee*/
	li t1, (0x1 << 22)
	csrs 0x7c0, t1 /* mxstatus */

	/*invaild ICACHE/DCACHE/BTB/BHT*/
	li t2, 0x30013
	csrs 0x7c2, t2 /* mcor */

	li sp, (0x28000+(128 << 10))
	jal clear_bss
	jal  main
	j .

clear_bss:
	la	t0, __bss_start
	la	t1, __bss_end

clbss_1:
	sw zero, 0(t0)
	addi t0, t0, 4
	blt t0, t1, clbss_1
	ret

