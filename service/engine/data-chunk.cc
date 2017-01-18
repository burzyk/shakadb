//
// Created by Pawel Burzynski on 17/01/2017.
//

#include <cmath>
#include <utils/common.h>
#include "data-chunk.h"

namespace apollo {

DataChunk *DataChunk::Create(std::string series_name, StoragePage *page) {
  data_chunk_info_t info;
  memset(&info, 0, sizeof(data_chunk_info_t));
  strcpy(info.series_name, series_name.c_str());
  page->Write(0, &info, sizeof(data_chunk_info_t));

  return new DataChunk(series_name, page);
}

DataChunk *DataChunk::Load(StoragePage *page) {
  data_chunk_info_t info;
  memcpy(&info, page->Read(0, sizeof(data_chunk_info_t)), sizeof(data_chunk_info_t));

  if (strlen(info.series_name) == 0) {
    return NULL;
  }

  DataChunk *chunk = new DataChunk(std::string(info.series_name), page);
  data_point_t *points = chunk->Read(0, chunk->GetMaxNumberOfPoints());

  for (int i = 0; i < chunk->GetMaxNumberOfPoints() && points[i].time != 0; i++) {
    chunk->begin = MIN(chunk->begin, points[i].time);
    chunk->end = MAX(chunk->end, points[i].time);
    chunk->number_of_points++;
  }

  return chunk;
}

data_point_t *DataChunk::Read(int offset, int count) {
  return (data_point_t *)this->page->Read(sizeof(data_chunk_info_t) + sizeof(data_point_t) * offset,
                                           sizeof(data_point_t) * count);
}

void DataChunk::Write(int offset, data_point_t *points, int count) {
  this->page->Write(sizeof(data_chunk_info_t) + sizeof(data_point_t) * offset,
                     points,
                     sizeof(data_point_t) * count);

  this->begin = MIN(this->begin, points[0].time);
  this->end = MAX(this->end, points[count - 1].time);
  this->number_of_points += count;
}

std::string DataChunk::GetSeriesName() {
  return this->series_name;
}

timestamp_t DataChunk::GetBegin() {
  return this->begin;
}

timestamp_t DataChunk::GetEnd() {
  return this->end;
}

int DataChunk::GetNumberOfPoints() {
  return this->number_of_points;
}

void DataChunk::PrintMetadata() {
  printf(
      "begin: %llu, end: %llu, points: %d\n",
      this->begin,
      this->end,
      this->number_of_points);
}

int DataChunk::GetMaxNumberOfPoints() {
  return (this->page->GetPageSize() - sizeof(data_chunk_info_t)) / sizeof(data_point_t);
}

DataChunk::DataChunk(std::string series_name, StoragePage *page) {
  this->page = page;
  this->series_name = series_name;
  this->begin = A_MAX_TIMESTAMP;
  this->end = A_MIN_TIMESTAMP;
  this->number_of_points = 0;
}

}

