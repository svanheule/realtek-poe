/* SPDX-License-Identifier: GPL-2.0+ */

#ifndef TEK_POE_H
#define TEK_POE_H

#include <stddef.h>
#include <stdint.h>
#include <libubox/utils.h>

#define ULOG_DBG(fmt, ...) ulog(LOG_DEBUG, fmt, ## __VA_ARGS__)

#define GET_STR(a, b)	((a) < ARRAY_SIZE(b) ? (b)[a] : NULL)
#define MAX(a, b)	(((a) > (b)) ? (a) : (b))
#define MAX_PORT	48

struct port_state {
	const char *status;
	float watt;
	const char *poe_mode;
};

struct port_config {
	char name[16];
	unsigned int valid : 1;
	unsigned int enable : 1;
	uint8_t priority;
	uint8_t power_up_mode;
	uint8_t power_budget;
};

struct config {
	float budget;
	float budget_guard;

	unsigned int port_count;
	uint8_t pse_id_set_budget_mask;
	struct port_config ports[MAX_PORT];
};

static inline uint16_t read16_be(uint8_t *raw)
{
	return (uint16_t)raw[0] << 8 | raw[1];
}

static inline void write16_be(uint8_t *raw, uint16_t value)
{
	raw[0] = value >> 8;
	raw[1] =  value & 0xff;
}

#endif /* TEK_POE_H */
