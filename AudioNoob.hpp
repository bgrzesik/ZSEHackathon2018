#ifndef AUDIONOOB
#define AUDIONOOB

#ifndef __APPLE__
  #include <AL/al.h>
  #include <AL/alc.h>
  #include <AL/alut.h>
#else
  #include <OpenAL/al.h>
  #include <OpenAL/alc.h>
#endif

class Audio
{
};

class AudioNoob
{
  public:
    AudioNoob();
		~AudioNoob();
    void Play();

  private:
    Audio data_;
};

#endif
