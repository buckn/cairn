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

//sin wave synthesis function
float snd_wav_sin(int t, float hz, float amp, int sample_rate) {
    float value = sinf(hz * M_PI * 2.0f * t * (1.0f / sample_rate)) * amp;
    snd_debug_graph(value, 10);
    return value;
}

//sound callback provided to sokol_audio.h
void snd_clbk(float* buffer, int num_frames, int num_channels) {
    for (int i = 0; i < num_frames; i++) {
    	if (cli.keys_down[SAPP_KEYCODE_SPACE]) {
    		buffer[num_channels * i] = snd_wav_sin(cli.snd_sin_wav, 110.0, .5, 44100);  // left channel
            cli.snd_sin_wav++;
    	} else {
    		buffer[num_channels * i] = 0;  // left channel
            snd_debug_graph(0, 10);
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