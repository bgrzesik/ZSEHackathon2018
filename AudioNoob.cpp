#include "AudioNoob.hpp"
#include <iostream>

AudioNoob::AudioNoob()
{
}

void AudioNoob::Play(std::string file)
{
	ALuint buffer, source;
	ALint state;
	alutInit(0, NULL);
	alGetError();
	buffer = alutCreateBufferFromFile(file.c_str());
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);
	alSourcePlay(source);
	do {
			alGetSourcei(source, AL_SOURCE_STATE, &state);
	} while (state == AL_PLAYING);
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
	alutExit();
}
