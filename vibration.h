#ifndef VIBRATION_H
#define VIBRATION_H

#include <stdbool.h>
#include <stdint.h>

void vibration_init(void);

void vibration_vibrate(uint32_t pattern, uint16_t timeout); 

void vibration_stop(void);

#endif /* VIBRATION_H */
