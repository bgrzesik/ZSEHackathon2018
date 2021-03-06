#ifndef WAVHELPER
#define WAVHELPER

#include <cstdint>
#include <string>

typedef struct WAVHeader_ {
  int32_t ChunkID;
  int32_t ChunkSize;
  int32_t Format;
  int32_t Subchunk1ID;
  int32_t Subchunk1Size;
  int16_t AudioFormat;
  int16_t NumChannels;
  int32_t SampleRate;
  int32_t ByteRate;
  int16_t BlockAlign;
  int16_t BitsPerSample;
  int32_t Subchunk2ID;
  int32_t Subchunk2Size;
} WAVHeader;

class WAVFile
{
  public:
    WAVFile();
    void SetTone(int diff);
    void SetSpeed(int multiplier);
    WAVHeader header;
    int32_t size;
    char* data;
};

class WAVHelper
{
  public:
    WAVHelper();
    void Load(WAVFile &file, std::string filename);
    void Append(WAVFile &wav);
    void Append(WAVFile &wav, float length);
    void AddAt(WAVFile &wav, float offset);
    void AddAt(WAVFile &wav, float offset, float length);
    void Render(std::string output);
  private:
    WAVFile file_;
};

#endif
