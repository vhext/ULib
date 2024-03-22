/**
 * @file uprotocol.c
 * @author vhex (visual86n@outlook.com)
 * @brief This file is uprotocol source file.
 * @version 0.1
 * @date 2024-01-04
 *
 * Copyright 2023 vhex. visual86n@outlook.com
 *
 */

#include "stdio.h"
#include "string.h"

#include "uprotocol.h"
#include "uprotocol_if.h"

// ------------------------------------------------------------------------
//                          External Variables
// ------------------------------------------------------------------------
extern struct uptl_cmd_handler __ext_cmd_hdl_list[];
extern uint32_t __ext_cmd_hdl_list_len;

// ------------------------------------------------------------------------
//                          Private Variables
// ------------------------------------------------------------------------
static uint8_t __uptl_static_buf[UPROTOCOL_STATIC_BUF_SIZE];

// ------------------------------------------------------------------------
//                             Private Macro
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
//                           Private Functions
// ------------------------------------------------------------------------

static uint32_t __uptl_cmd_hdl_match(const struct uptl_frame *frame, const uint32_t payload_len)
{
    for (uint32_t i = 0; i < __ext_cmd_hdl_list_len; i++) {
        // match cmd code
        if (__ext_cmd_hdl_list[i].cmd != frame->cmd) {
            continue;
        }
        // check type
        if (__ext_cmd_hdl_list[i].type != frame->type) {
            continue;
        }
        // check segment
        if (__ext_cmd_hdl_list[i].can_segment != 1) {
            if (frame->is_segment == 1) {
                return UPTL_ERROR_CMD_HDL_SEGMENT;
            }
        }

        UPROTOCOL_LOG("UPTL[%u], cmd: %d, type: %d, len: %d\n",
                      i, __ext_cmd_hdl_list[i].cmd, __ext_cmd_hdl_list[i].type, payload_len);
        // all prerequisite match
        return __ext_cmd_hdl_list[i].handler(frame->payload, payload_len);
    }

    return UPTL_ERROR_CMD_HDL_NOT_FOUND;
}

// ------------------------------------------------------------------------
//                           Public Functions
// ------------------------------------------------------------------------

/**
 * @brief Sends an UPTL protocol frame.
 *
 * This function sends an UPTL protocol frame with the given frame type, command,
 * and data. The length of the data determines the size of the payload.
 *
 * @param type The frame type.
 * @param cmd The command for the frame.
 * @param data The data to be sent.
 * @param len The length of the data.
 *
 * @return uint32_t uprotocol error code.
 *
 * @retval UPTL_SUCCESS: Send success
 */
uint32_t uptl_send(const enum uptl_frame_type type, const uint8_t cmd, const uint8_t *data, uint32_t len)
{
    struct uptl_frame *frame        = (struct uptl_frame *)__uptl_static_buf;
    uint32_t frame_size             = sizeof(struct uptl_frame);
    const uint32_t payload_size_max = UPROTOCOL_STATIC_BUF_SIZE - sizeof(struct uptl_frame);

    frame->cmd  = cmd;
    frame->type = type;
    while (len > payload_size_max) {
        frame->cmd  = cmd;
        frame->type = type;

        if (len > payload_size_max) {
            frame->is_segment = 1;
            frame_size        = payload_size_max;
        } else {
            frame->is_segment = 0;
            frame_size        = len;
        }

        frame->is_segment = 1;
        memcpy(frame->payload, data, frame_size);
        frame_size += sizeof(struct uptl_frame); // add header size
        const uint32_t ret = uptl_if_send(__uptl_static_buf, frame_size);
        if (ret != UPTL_SUCCESS) {
            return ret;
        }
        len -= frame_size;
    }

    return UPTL_SUCCESS;
}

/**
 * @brief Process the UPTL frame
 *
 * This function processes the UPTL (uprotocol) frame received.
 * It performs various checks and operations based on the contents of the frame.
 *
 * @param data Pointer to the UPTL frame data
 * @param len Length of the UPTL frame data
 * @return uint32_t The return value depends on the processing result
 *
 * @retval UPTL_SUCCESS if the frame is processed successfully
 * @retval UPTL_ERROR_FRAME_LEN if the frame length is invalid
 * @retval UPTL_ERROR_FRAME_SEQ if the frame sequence is invalid
 */
uint32_t uptl_process(const uint8_t *data, uint32_t len)
{
    if (len < sizeof(struct uptl_frame)) {
        return UPTL_ERROR_FRAME_LEN;
    }

    const struct uptl_frame *frame = (const struct uptl_frame *)data;
    const uint32_t payload_len     = len - sizeof(struct uptl_frame);

    return __uptl_cmd_hdl_match(frame, payload_len);
}
