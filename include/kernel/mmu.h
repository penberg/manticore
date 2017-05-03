#ifndef KERNEL_MMU_H
#define KERNEL_MMU_H 1

#include <arch/vmem.h>

#include <stddef.h>
#include <stdint.h>

void mmu_invalidate_tlb(void);
int mmu_map_range(virt_t vaddr, phys_t paddr, size_t size, uint64_t flags);
int mmu_map_small_page(virt_t vaddr, phys_t paddr, uint64_t flags);
int mmu_map_large_page(virt_t vaddr, phys_t paddr, uint64_t flags);
void mmu_dump_pgtable(void);

#endif