#include "WAVHelper.hpp"
#include <cstdlib>
#include <cstring>

WAVFile::WAVFile()
{
  size = 0;
  data = 0;
  header = {};
  header.ChunkID = 0x46464952;
  header.ChunkSize = 36;
  header.Format = 0x45564157;
  header.Subchunk1ID = 0x20746d66;
  header.Subchunk1Size = 16;
  header.AudioFormat = 1;
  header.NumChannels = 2;
  header.SampleRate = 44100;
  header.ByteRate = 44100 * 2 * 16 / 8;
  header.BlockAlign = 2 * 16 / 8;
  header.BitsPerSample = 16;
  header.Subchunk2ID = 0x61746164;
  header.Subchunk2Size = 0;
}

WAVHelper::WAVHelper() {
  file_ = WAVFile();
}

WAVFile WAVHelper::load(std::string file)
{
  WAVFile wav;
  FILE* f = fopen(file.c_str(), "r");
  fread(&wav.header, sizeof(WAVHeader), 1, f);
  wav.size = wav.header.Subchunk2Size;
  wav.data = (char*) calloc(wav.size, 1);
  fread(wav.data, 1, wav.size, f);

  return wav;
}

void WAVHelper::append(WAVFile wav) 
{
  file_.data = (char*) realloc(file_.data, file_.size + wav.size);
  memcpy(file_.data + file_.size, wav.data, wav.size);
  file_.size += wav.size;
  file_.header.ChunkSize += wav.size;
  file_.header.Subchunk2Size += wav.size;
}

void WAVHelper::append(WAVFile wav, float length)
{
  int num_bytes = length * wav.header.ByteRate;
  file_.data = (char*) realloc(file_.data, file_.size + num_bytes);
  memcpy(file_.data + file_.size, wav.data, num_bytes);
  file_.size += num_bytes;
  file_.header.ChunkSize += num_bytes;
  file_.header.Subchunk2Size += num_bytes;
}

void WAVHelper::render(std::string output)
{
  FILE* f = fopen(output.c_str(), "w");
  fwrite(&file_.header, sizeof(WAVHeader), 1, f);
  fwrite(file_.data, file_.size, 1, f);
}
