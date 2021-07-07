//waveform printing function to debug audio
void snd_debug_graph(float sample, int detail) {
    for (int i = 0; i < (int)((sample + 1.0) * detail); i++) {
        printf(" ");
    }
    printf("|");

    for (int i = 0; i < detail * 2 - (int)((sample + 1.0) * detail); i++) {
        printf(" ");
    }

    printf("value: %f", sample);
    printf(" t: %d\n", cli.snd_sin_wav);
    printf("sample rate: %d", saudio_sample_rate()); 
}

/*
    Synthesis Fns
*/

//sin wave synthesis function
float snd_sin(int t, float hz, float amp, int sample_rate) {
    float value = sinf(hz * M_PI * 2.0f * t * (1.0f / sample_rate)) * amp;
    //snd_debug_graph(value, 10);
    return value;
}

/*
    Basic Processing Fns
*/

void snd_amp2(float samples[2], float amp) {
    samples[0] = samples[0] * amp;
    samples[1] = samples[1] * amp;
}

//add sound samples together with a fader between the two
float snd_add(float samples[2], float fader) {
    return lerp(samples[0], samples[1], fader);
}

//subtract the first sound sample from the second with a fader between the two
float snd_sub(float samples[2], float fader) {
    return (samples[0] * (1.0 - fader)) - (samples[1] * fader);
}

/*
    Audio Filter Fns
*/

//ADSR filter function
void snd_adsr(int t, float samples[2], int sample_rate, float adsr_t[4], float adsr_amp[4]) {
    //if attacking
    if (t * (1.0f / sample_rate) < adsr_t[0]) {
        snd_amp2(samples, (t * (1.0f / sample_rate)) / (adsr_t[0] * adsr_amp[0]));
    } /* if decaying */ else if (t * (1.0f / sample_rate) < adsr_t[0] + adsr_t[1]) {
        snd_amp2(samples, (t * (1.0f / sample_rate)) - adsr_t[0] / (adsr_t[1] * adsr_amp[1]));
    } /* if sustaining */ else if (t * (1.0f / sample_rate) < adsr_t[0] + adsr_t[1] + adsr_t[2]) {
        snd_amp2(samples, (t * (1.0f / sample_rate)) - adsr_t[0] - adsr_t[1] / (adsr_t[2] * adsr_amp[2]));
    } /* if releasing */ else if ((t * (1.0f / sample_rate) < adsr_t[0] + adsr_t[1] + adsr_t[2] + adsr_t[3]) && !(t * (1.0f / sample_rate) > adsr_t[0] + adsr_t[1] + adsr_t[2] + adsr_t[3])) {
        snd_amp2(samples, (t * (1.0f / sample_rate)) - adsr_t[0] - adsr_t[1] - adsr_t[2] / (adsr_t[3] * adsr_amp[3]));
    } /* if adsr filter done */ else {
        snd_amp2(samples, 0.0f);
    }
}

//sound callback provided to sokol_audio.h
void snd_clbk(float* buffer, int num_frames, int num_channels) {
    for (int i = 0; i < num_frames; i++) {
        if (cli.keys_down[SAPP_KEYCODE_SPACE]) {
            /*float frame_a[2] = {snd_sin(cli.snd_sin_wav, 440.0f, 1.0f, 44100), snd_sin(cli.snd_sin_wav + 55, 110.0f, 1.0f, 44100)};
            float frame_b[2] = {snd_sin(cli.snd_sin_wav, 880.0f, 1.0f, 44100), snd_sin(cli.snd_sin_wav + 55, 220.0f, 1.0f, 44100)};
            float frame_c[2] = {snd_add(frame_a, 0.5f), snd_add(frame_b, 0.5f)};*/
            float frame_d[2] = {snd_sin(cli.snd_sin_wav, 440.0f, 0.9f, 44100), snd_sin(cli.snd_sin_wav + 55, 110.0f, 0.9f, 44100)};
            float adsr_times[4] = {3.0f, 1.5f, 4.0f, 5.0f};
            float adsr_amplitudes[4] = {0.9f, 0.7f, 0.67f, 0.1f};
            snd_adsr(cli.snd_sin_wav, frame_d, 44100, adsr_times, adsr_amplitudes);
            buffer[num_channels * i] = snd_add(frame_d, 0.5f);  // mono channel
            cli.snd_sin_wav++;
        } else {
            buffer[num_channels * i] = snd_sin(cli.snd_sin_wav, 1.0f, 0.0f, 44100);  // left channel
            cli.snd_sin_wav = 0;
        }
    }
}

//initalization fn for sokol_audio.h
void snd_init() {
    saudio_setup(&(saudio_desc) {
        .stream_cb = snd_clbk,
        .num_channels = 1,
        //.sample_rate = 44100,
        //.buffer_frames = 2048
    });
}

//shutdown fn for sokol_audio.h
void snd_shutdown() {
    saudio_shutdown();
}