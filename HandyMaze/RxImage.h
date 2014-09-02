#pragma once

#include	<stdio.h>
#include	<jpeglib.h>
#include	<stdint.h>
#include	<inttypes.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<string.h>
#include	<vector>

struct		RxColor
{
  uint8_t	red;
  uint8_t	green;
  uint8_t	blue;

RxColor(uint8_t r, uint8_t g, uint8_t b) :
  red(r), green(g), blue(b) { }

};

class		RxImage
{
 private:
  uint8_t*		p_rawdata;
  uint64_t		p_raw_size;
  uint64_t		p_width;
  uint64_t		p_height;

 public:
  RxImage();
  ~RxImage();

 public:
  bool		Create(uint64_t, uint64_t);
  bool		SetPixel(uint64_t, uint64_t, uint8_t, uint8_t, uint8_t);
  bool		SaveToJpeg(const char*);
};
