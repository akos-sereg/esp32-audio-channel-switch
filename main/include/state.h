#ifndef __state_h_included__
#define __state_h_included__

#include "nvs.h"

struct app_state {
    int relay_in_comp;
    int relay_in_guitar;
    int relay_in_vinyl;
    int relay_out_headphones;
    int relay_out_speaker;
    int relay_out_amplifier;
    int is_muted;
    int child_lock;
} app_state;

/**
 * in_channel:
 *  - 0: computer
 *  - 1: guitar
 *  - 2: vinyl
 */
extern void state_set_input(int32_t in_channel);

/**
 * out_channel:
 *  - 0: headphones
 *  - 1: speaker
 *  - 2: amplifier
 */
extern void state_set_output(int32_t out_channel);

extern void state_set_muted(int32_t is_muted);

extern void state_print();

#endif