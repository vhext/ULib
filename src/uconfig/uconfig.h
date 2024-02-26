/**
 * @file uconfig.h
 * @author vhex (visual86n@outlook.com)
 * @brief This is util config header file.
 * @version 0.1
 * @date 2023-12-30
 *
 * Copyright 2023 Neutron Star Inc. visual86n@outlook.com
 *
 */

#ifndef __UCONFIG_H
#define __UCONFIG_H

#include <stdint.h>
#include <stdbool.h>

#define UCONFIG_DEBUG 0

#if UCONFIG_DEBUG == 1
/* Enable debug */
#define UCONFIG_PARAM_ASSERT(exp) \
    if (!(exp)) {                 \
        while (1)                 \
            ;                     \
    }
#define UCONFIG_LOG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define UCONFIG_FIELD_PRINT(field, val, sz)         \
    do {                                            \
        printf("Field [%d]: ", field);              \
        for (unsigned int idx = 0; idx < sz; idx++) \
            printf("0x%02X ", *((val) + idx));      \
        printf("\n");                               \
    } while (0)

#else
/* Disable debug */
#define UCONFIG_PARAM_ASSERT(exp)
#define UCONFIG_LOG(fmt, ...)
#define UCONFIG_FIELD_PRINT(field, val, sz)
#endif

enum uconfig_ret {
    UCONFIG_SUCCESS = 0,
    UCONFIG_ERROR_INVALID_FIELD,
    UCONFIG_ERROR_SIZE_MISMATCH,
};

uint32_t uconfig_read(const uint32_t field, uint8_t *data, const uint32_t size);

uint32_t uconfig_write(const uint32_t field, const uint8_t *data, const uint32_t size);

uint32_t uconfig_restore(void);

uint32_t uconfig_init(void);

#endif
