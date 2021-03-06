#include "common.h"
#include "gpio.h"
void set_gpio_func(int gpio, int type) {
	int i;
	int port = gpio >> 5;
	int pin = gpio & 0x1f;
	int addr = GPIO_BASE + PXINT + port * 0x100;
	int b;
	for(i = 0;i < 4;i++){
		b = REG32(addr + 0x10 * i);
		b &= ~(1 << pin);
		b |= (((type >> (3 - i)) & 1) << pin);
		REG32(addr + 0x10 * i) = b;
	}
}

int get_gpio_func(int gpio) {
	int i;
	int ret = 0;
	int port = gpio >> 5;
	int pin = gpio & 0x1f;
	int addr = GPIO_BASE + PXINT + port * 0x100;
	for(i = 0;i < 4;i++){
		ret |= ((REG32(addr + 0x10 * i) >> pin) & 1)  << (3 - i);
	}
	return ret;
}


#if 0
#define readl(addr)      ({*(volatile unsigned int *)(addr);})

#define writel(v,addr)   do{*(volatile unsigned int *)(addr) = (v);}while(0)


int gpio_get_value(unsigned int gpio)
{
	unsigned int port = gpio / 32;
	unsigned int pin = gpio % 32;
	unsigned int base = GPIO_BASE + 0x100 * port;
	return !!(readl(base + PXPIN) & (1 << pin));
}
void gpio_direction_output(unsigned int gpio, int value)
{
	unsigned int port = gpio / 32;
	unsigned int pin = gpio % 32;
	unsigned int base = GPIO_BASE + 0x100 * port;
	writel(1 << pin, base + PXINTC);
	writel(1 << pin, base + PXMSKS);
	writel(1 << pin, base + PXPAT1C);
	if (value)
		writel(1 << pin, base + PXPAT0S);
	else
		writel(1 << pin, base + PXPAT0C);

}
void gpio_direction_input(unsigned int gpio)
{
	unsigned int port = gpio / 32;
	unsigned int pin = gpio % 32;
	unsigned int base = GPIO_BASE + 0x100 * port;

	writel(1 << pin, base + PXINTC);
	writel(1 << pin, base + PXMSKS);
	writel(1 << pin, base + PXPAT1S);
}
#endif
