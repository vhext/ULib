/**
 * @file test_uconfig_if.h
 * @author vhex (visual86n@outlook.com)
 * @brief This file is uconfig user interface header file.
 * @version 0.1
 * @date 2024-01-04
 *
 * Copyright 2023 vhex. visual86n@outlook.com
 *
 */

#ifndef __TEST_UCONFIG_IF_H
#define __TEST_UCONFIG_IF_H

#include <stdint.h>
#include <stdbool.h>

#include "ULib.h"

enum uconfig_if_ret {
    UCONFIG_IF_SUCCESS = 0,
};

uint32_t uconfig_if_init(void);

uint32_t uconfig_if_read(const uint32_t field, uint8_t *data, const uint32_t size);

uint32_t uconfig_if_write(const uint32_t field, const uint8_t *data, const uint32_t size);

#endif
