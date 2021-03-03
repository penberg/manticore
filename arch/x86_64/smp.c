#include <arch/apic.h>

#include <assert.h>
#include <stdio.h>

int maxcpus, num_cpus;

#define IPI_INIT		0x000C4500U
#define IPI_SIPI		0x000C4600U
#define SIPI_VECTOR(addr)	(((unsigned long) addr) >> 12)

extern void start16(void);

void smp_init(void)
{
	if (!apic_is_bsp()) {
		assert(0);
		/* This is an AP, no need to do anything.  */
		return;
	}

	// Intel Manuals: Section 8.4 ("Multiple-Processor (MP) initialization")

	// 8.4.4.1 Typical BSP Initialization Sequence

	printf("AP vector = %p\n", start16);

	apic_ipi_allbutself(IPI_INIT);
	apic_ipi_allbutself(IPI_SIPI | SIPI_VECTOR(start16));
	apic_ipi_allbutself(IPI_SIPI | SIPI_VECTOR(start16));

	while (true /*num_cpus != maxcpus*/) {
		asm volatile("": : :"memory");
	}
}
