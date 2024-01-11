/**
 * @file uprotocol_if.c
 * @author vhex (visual86n@outlook.com)
 * @brief This file is uprotocol user interface source file.
 * @version 0.1
 * @date 2024-01-08
 *
 * Copyright 2023 vhex. visual86n@outlook.com
 *
 */

#include "uprotocol_if.h"
#include "ULib.h"

struct uptl_cmd_handler __ext_cmd_hdl_list[] = {
    // example implement
    {
        .cmd         = 0x00,
        .type        = UPTL_FRAME_REQUEST,
        .can_segment = 1,
        .handler     = NULL,
    },
    // ------CMD Handler List------
    // -------User Implement-------

    // ----------------------------
};
uint32_t __ext_cmd_hdl_list_len = sizeof(__ext_cmd_hdl_list);

const uint32_t uptl_if_send(const uint8_t *data, const uint32_t len)
{
    // ------UPTL Send Interface------
    // --------User Implement---------

    // -------------------------------
    return UPTL_SUCCESS;
}
