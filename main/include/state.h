#ifndef __state_h_included__
#define __state_h_included__

struct app_state {
    int relay_in_comp;
    int relay_in_guitar;
    int relay_in_vinyl;
    int relay_out_headphones;
    int relay_out_speaker;
    int relay_out_amplifier;
    int mute;
    int child_lock;
} app_state;

#endif