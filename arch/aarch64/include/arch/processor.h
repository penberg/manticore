#ifndef ARM64_PROCESSOR_H
#define ARM64_PROCESSOR_H

#include <kernel/const.h>

/*
 * Saved Program Status Registers (SPSRs):
 */
#define ARM64_SPSR_A		_UL_BIT(8)	/* SError interrupt mask bit */
#define ARM64_SPSR_I		_UL_BIT(7)	/* IRQ mask bit */
#define ARM64_SPSR_F		_UL_BIT(6)	/* FIQ mask bit */

#define msr(reg, value)			\
({					\
	asm volatile(			\
		"msr " #reg ", %0"	\
		:			\
		: "r" (value)		\
		);			\
})

#define mrs(reg)			\
({					\
 	unsigned long __val;		\
	asm volatile(			\
		"mrs %0, " #reg		\
		: "=r" (__val)		\
		);			\
	__val;				\
})

#endif
