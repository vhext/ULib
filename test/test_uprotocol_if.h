/**
 * @file uprotocol_if.h
 * @author vhex (visual86n@outlook.com)
 * @brief This file is uprotocol user interface header file.
 * @version 0.1
 * @date 2024-01-08
 * 
 * Copyright 2023 vhex. visual86n@outlook.com
 * 
 */

#ifndef __UPROTOCOL_IF_H
#define __UPROTOCOL_IF_H

#include <stdint.h>
#include <stdbool.h>

uint32_t uptl_if_send(const uint8_t *data, const uint32_t len);

#endif
