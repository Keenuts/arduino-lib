#pragma once

struct multiplexer_t {
    uint8_t en;
    uint8_t z;
    uint8_t addr[4];
};

void multi_set_pin(struct multiplexer_t *ctx, uint8_t pin, uint8_t value);
uint8_t multi_get_pin(struct multiplexer_t *ctx, uint8_t pin);
