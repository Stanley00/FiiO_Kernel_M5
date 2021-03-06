#ifndef __CACHE_H__
#define __CACHE_H__

#define K0BASE			0x80000000
#define CFG_DCACHE_SIZE		16384
#define CFG_ICACHE_SIZE		16384
#define CFG_CACHELINE_SIZE	32
#define Index_Store_Tag_I	0x08
#define Index_Store_Tag_D	0x09
#define Index_Invalidate_I	0x00
#define Index_Writeback_Inv_D	0x01
#define Index_Writeback_Inv_SD	0x03

void blast_l1cache_all(void)
{
	unsigned int addr;
	for (addr = K0BASE; addr < (K0BASE + CFG_ICACHE_SIZE); addr += CFG_CACHELINE_SIZE)
	{
		__asm__ __volatile__(
				".set push      \n\t"
				".set noreorder \n\t"
				".set mips3	\n\t"
				"cache %2, 0x000(%0);\n\t"
				"cache %1, 0x000(%0);\n\t"
				".set pop \n\t"
				: : "r" (addr), "i" (Index_Writeback_Inv_D) ,"i" (Index_Invalidate_I));
	}
	__asm__ __volatile__(
                        ".set	push\n\t"
			".set	noreorder\n\t"
			".set	mips2\n\t"
			"sync   \n\t"
			".set	pop");

}

void flush_cache_all(void)
{
	blast_l1cache_all();
}
static void __jz_cache_init(void)
{
	register unsigned long addr;
	asm volatile ("mtc0 $0, $28\n\t"::);

	for (addr = K0BASE; addr < (K0BASE + CFG_DCACHE_SIZE); addr += CFG_CACHELINE_SIZE) {
		asm volatile (".set mips32\n\t"
				" cache %0, 0(%1)\n\t"
				".set mips32\n\t"
				:
				: "I" (Index_Store_Tag_D), "r"(addr));
	}

	for (addr = K0BASE; addr < (K0BASE + CFG_ICACHE_SIZE); addr += CFG_CACHELINE_SIZE) {
		asm volatile (".set mips32\n\t"
				" cache %0, 0(%1)\n\t"
				".set mips32\n\t"
				:
				: "I" (Index_Store_Tag_I), "r"(addr));
	}
	/* invalidate BTB */
	asm volatile (  ".set mips32\n\t"
			" mfc0 $26, $16, 7\n\t"
			" nop\n\t"
			" ori $26, 2\n\t"
			" mtc0 $26, $16, 7\n\t"
			" nop\n\t"
			"nop\n\t"
			".set mips32\n\t"
		    );
}

#endif	/*  __CACHE_H__ */
