#include "include/state.h"
#include "include/relays.h"

void state_set_input(int32_t in_channel) {

    app_state.relay_in_comp = 0;
    app_state.relay_in_guitar = 0;
    app_state.relay_in_vinyl = 0;

    switch (in_channel) {
        case 0: app_state.relay_in_comp = 1; break;
        case 1: app_state.relay_in_guitar = 1; break;
        case 2: app_state.relay_in_vinyl = 1; break;

        default:
        case -1:
            app_state.relay_in_comp = 1;
            break;
    }
}

void state_set_output(int32_t out_channel) {
    app_state.relay_out_headphones = 0;
    app_state.relay_out_speaker = 0;
    app_state.relay_out_amplifier = 0;

    switch (out_channel) {
        case 0: app_state.relay_out_headphones = 1; break;
        case 1: app_state.relay_out_speaker = 1; break;
        case 2: app_state.relay_out_amplifier = 1; break;

        default:
        case -1:
            app_state.relay_out_speaker = 1;
            break;
    }
}

void state_set_muted(int32_t is_muted) {
    if (is_muted == -1) {
        app_state.is_muted = 0;
        return;
    }

    app_state.is_muted = is_muted;
}

void state_set_child_lock(int32_t child_lock) {
    if (child_lock == -1) {
        app_state.child_lock = 0;
        return;
    }

    app_state.child_lock = child_lock;
}

void state_print() {
    printf("[state] Input - Computer: %d\n", app_state.relay_in_comp);
    printf("[state] Input - Guitar: %d\n", app_state.relay_in_guitar);
    printf("[state] Input - Vinyl: %d\n", app_state.relay_in_vinyl);

    printf("[state] Output - Headphones: %d\n", app_state.relay_out_headphones);
    printf("[state] Output - Speaker: %d\n", app_state.relay_out_speaker);
    printf("[state] Output - Amplifier: %d\n", app_state.relay_out_amplifier);

    printf("[state] Is Muted: %d\n", app_state.is_muted);
    printf("[state] Child Lock: %d\n", app_state.child_lock);
    printf("\n");
}