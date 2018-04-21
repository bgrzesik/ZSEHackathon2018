#include "WAVHelper.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>

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

void WAVHelper::Load(WAVFile &file, std::string filename)
{
  FILE* f = fopen(filename.c_str(), "r");
  fread(&file.header, sizeof(WAVHeader), 1, f);
  file.size = file.header.Subchunk2Size;
  file.data = new char[file.size];
  fread(file.data, 1, file.size, f);
  fclose(f);
}

void WAVHelper::Append(WAVFile &wav)
{
  file_.data = (char*) realloc(file_.data, file_.size + wav.size);
  memcpy(file_.data + file_.size, wav.data, wav.size);
  file_.size += wav.size;
  file_.header.ChunkSize += wav.size;
  file_.header.Subchunk2Size += wav.size;

}

void WAVHelper::Append(WAVFile &wav, float length)
{
  int offset = file_.size;
  int num_bytes = length * wav.header.ByteRate;
  file_.data = (char*) realloc(file_.data, file_.size + num_bytes);
  int times = num_bytes / wav.header.Subchunk2Size;
  int rest = num_bytes % wav.header.Subchunk2Size;
  for(int i = times; i > 0; i--) {
    memcpy(file_.data + offset, wav.data, wav.header.Subchunk2Size);
    offset += wav.header.Subchunk2Size;
  }
  memcpy(file_.data + offset, wav.data, rest);
  file_.size += num_bytes;
  file_.header.ChunkSize += num_bytes;
  file_.header.Subchunk2Size += num_bytes;
}

void WAVHelper::AddAt(WAVFile &wav, float offset)
{
  int offset_bytes = offset * wav.header.ByteRate;
  if(wav.size + offset_bytes > file_.size) {
    int n_size = wav.size + offset_bytes;
    file_.data = (char *) realloc(file_.data, n_size);
    file_.header.ChunkSize = 36 + n_size;
    file_.header.Subchunk2Size = n_size;
    file_.size = n_size;
  }
  for(int i = 0; i < wav.size; i++) {
    file_.data[i+offset_bytes] += wav.data[i % wav.header.Subchunk2Size];
  } 
}

void WAVHelper::AddAt(WAVFile &wav, float offset, float length)
{
  int length_bytes = length * wav.header.ByteRate;
  int offset_bytes = offset * wav.header.ByteRate;
  if(length_bytes + offset_bytes > file_.size) {
    file_.data = (char*) realloc(file_.data, length_bytes+offset_bytes);
    file_.header.ChunkSize = 36 + length_bytes;
    file_.header.Subchunk2Size = length_bytes;
    file_.size = length_bytes;
  }
  for(int i = 0; i < length_bytes; i++) {
    file_.data[i+offset_bytes] += wav.data[i % wav.header.Subchunk2Size];
  } 
}

void WAVHelper::Render(std::string output)
{
  FILE* f = fopen(output.c_str(), "w");
  fwrite(&file_.header, sizeof(WAVHeader), 1, f);
  fwrite(file_.data, file_.size, 1, f);
  fclose(f);
}
