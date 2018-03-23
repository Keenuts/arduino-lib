#include <time.h>
#include <util/delay.h>
#include <stdio.h>

#include "digital.h"
#include "multiplexer.h"

#define LOCK() digital_write(ctx->en, 1)
#define UNLOCK() digital_write(ctx->en, 0)

static void select_pin(struct multiplexer_t *ctx, uint8_t pin)
{
	for (uint8_t i = 0; i < 4; i++)
		digital_write(ctx->addr[i], (pin >> i) & 1);
}

void multi_set_pin(struct multiplexer_t *ctx, uint8_t pin, uint8_t value)
{
	LOCK();

	select_pin(ctx, pin);
	digital_write(ctx->z, value);

	UNLOCK();
}

uint8_t multi_get_pin(struct multiplexer_t *ctx, uint8_t pin)
{
	select_pin(ctx, pin);

	uint8_t value = digital_read(ctx->z);
	digital_write(ctx->en, 1);

	return value;
}
