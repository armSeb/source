/*
 * Arch specific code for Lantiq based boards
 *
 * Copyright (C) 2013 John Crispin <blogic@openwrt.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 */

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include "config.h"


#define READREG(r)		*(volatile unsigned int *)(r)
#define READREG32(r)		*(volatile uint32_t *)(r)
#define WRITEREG(r,v)		*(volatile unsigned int *)(r) = v
#define WRITEREG32(r,v)		*(volatile uint32_t *)(r) = v

#define UART_BASE		0xbe100c00
#define ASC_TBUF		(UART_BASE | 0x20)
#define ASC_FSTAT		(UART_BASE | 0x48)

// Watchdog

#define LTQ_WDT_MEMBASE_CR	0xbf8803f0 // Membase + control register

#define LTQ_WDT_PW1             0x00BE0000
#define LTQ_WDT_PW2             0x00DC0000

#define LTQ_WDT_SR_EN           (0x1 << 31)     /* enable bit */
#define LTQ_WDT_SR_PWD          (0x3 << 26)     /* turn on power */
#define LTQ_WDT_SR_CLKDIV       (0x3 << 24)     /* turn on clock and set */
                                                /* divider to 0x40000 */
#define LTQ_WDT_DIVIDER         0x40000
#define LTQ_MAX_TIMEOUT         ((1 << 16) - 1) /* the reload field is 16 bit */

#define RCU_MEMBASE			0xBF203000
/* reboot bit */
#define RCU_RD_GPHY0_XRX200     (1<<31)
#define RCU_RD_SRST             (1<<30)
#define RCU_RD_GPHY1_XRX200     (1<<29)
#define RCU_RST_REQ             0x0010

#define CGU_BASE_ADDR		0xBF103000

#define PMU_BASE		0xBF102000
#define BSP_PMU_PWDCR		0x001C
#define PMU_PWDCR 		0xBF10201C
#define PMU_SR			0xBF102020

#define TXMASK          0x3F00
#define TXOFFSET        8

void board_putc(char c)
{
	while ((READREG(ASC_FSTAT) & TXMASK) >> TXOFFSET);

	WRITEREG(ASC_TBUF, c);
}

void board_init(void)
{

	// WDT reset timer
	WRITEREG(LTQ_WDT_MEMBASE_CR, LTQ_WDT_PW1); // First magic word
	WRITEREG(LTQ_WDT_MEMBASE_CR, LTQ_WDT_SR_EN | LTQ_WDT_SR_PWD | LTQ_WDT_SR_CLKDIV | LTQ_WDT_PW2 | LTQ_MAX_TIMEOUT);


 printf("%08X\n", READREG32(0xBF10201C));
// printf("%08X %08X\n", READREG32(0xBE109138), READREG32(0xBE10913C));
// printf("%08X %08X\n", READREG32(0xBE10B308), READREG32(0xBE10B1DC));
// printf("%08X %08X\n", READREG32(0xBE10B1E4), READREG32(0xBE10B204));

//	WRITEREG(CGU_BASE_ADDR+0x44, 0x1FE00000);
//	WRITEREG(0xBF103020, 0x01);
//	WRITEREG(RCU_RST_REQ+RCU_MEMBASE, RCU_RD_GPHY0_XRX200 | RCU_RD_GPHY0_XRX200);
/*	uint32_t lu = READREG32(0xBF10201C);
	WRITEREG32(0xBF10201C, 0x02);
	printf("%08X\n", READREG32(0xBF10201C));
	WRITEREG32(PMU_PWDCR, 0x0e1592cf);
	printf("%08X\n", READREG32(0xBF10201C));
	lu = READREG32(0xBF203010);
	printf("%08X\n", lu);
	WRITEREG32(0xBF203010,lu | 0x200300);
	lu = READREG32(0xBF203010);
	printf("%08X\n", lu);
	WRITEREG32(0xBF203010, lu & 0xFFDFFCFF);
	printf("%08X\n", READREG(0xBF203010));
*/
//	WRITEREG(0xBF203010, 0x40000008);

/*	uint32_t n=0;
	while (n<999999999) n++;
	WRITEREG(0xBF203010, 0x20);*/
//	WRITEREG(0xBF401070, 0x1010100);



	uint32_t val = READREG32(RCU_MEMBASE);
	uint32_t gpio = READREG32(0xBE100B10);
	printf("Reset status: %08X, gpio: %08X\n", val, gpio);

	// WDT reset timer
        WRITEREG(LTQ_WDT_MEMBASE_CR, LTQ_WDT_PW1); // First magic word
        WRITEREG(LTQ_WDT_MEMBASE_CR, LTQ_WDT_SR_EN | LTQ_WDT_SR_PWD | LTQ_WDT_SR_CLKDIV | LTQ_WDT_PW2 | LTQ_MAX_TIMEOUT);

//	WRITEREG(0xbe105360, 0x000111A7);
}
