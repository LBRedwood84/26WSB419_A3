#ifndef ESP_H
#define ESP_H

#include "common.hpp"

typedef struct esp_t
{
    int active;
    int numpins;
    pin_t pins[];
} esp_t;

#endif
