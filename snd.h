void snd_clbk(float* buffer, int num_frames, int num_channels) {
	assert(2 == num_channels);
    for (int i = 0; i < num_frames; i++) {
    	if (cli.keys_down[SAPP_KEYCODE_SPACE]) {
    		buffer[2*i + 0] = (i % 168 == 0);  // left channel
        	buffer[2*i + 1] = (i % 168 == 0);  // right channel
    	} else {
    		buffer[2*i + 0] = 0;  // left channel
        	buffer[2*i + 1] = 1;  // right channel
    	}
    }
}

void snd_init() {
	saudio_setup(&(saudio_desc){
        .stream_cb = snd_clbk,
    });
}

void snd_shutdown() {
	saudio_shutdown();
}