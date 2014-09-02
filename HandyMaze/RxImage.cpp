#include	"RxImage.h"

RxImage::RxImage() :
  p_rawdata(0), p_raw_size(0), p_width(0), p_height(0)
{
}

RxImage::~RxImage()
{
}

bool		RxImage::Create(uint64_t w, uint64_t h)
{
  if (w && h)
    {
      if (this->p_rawdata)
	delete (this->p_rawdata);
      this->p_raw_size = w * h * 4;
      this->p_width = w;
      this->p_height = h;
      this->p_rawdata = new uint8_t[this->p_raw_size]();
      memset(this->p_rawdata, 0, this->p_raw_size);
      return (true);
    }
  return (false);
}

bool		RxImage::SetPixel(uint64_t x, uint64_t y, uint8_t r, uint8_t g, uint8_t b)
{
  uint8_t*	tmp;

  tmp = &(this->p_rawdata[(x + y * this->p_width) * 4]);
  *tmp++ = r;
  *tmp++ = g;
  *tmp++ = b;
  *tmp++ = 255;	// Try a 255 si ca marche pas ..
  return (true);
}

bool		RxImage::SaveToJpeg(const char* filename)
{
  FILE*			f = fopen(filename, "wb");
  jpeg_compress_struct	compressInfos;
  jpeg_error_mgr	errorManager;

  if (!f) return (false);
  compressInfos.err = jpeg_std_error(&errorManager);

  jpeg_create_compress(&compressInfos);
  compressInfos.image_width = this->p_width;
  compressInfos.image_height = this->p_height;
  compressInfos.input_components = 3;
  compressInfos.in_color_space = JCS_RGB;
  jpeg_stdio_dest(&compressInfos, f);
  jpeg_set_defaults(&compressInfos);
  jpeg_set_quality(&compressInfos, 90, FALSE);

  uint64_t	len = this->p_width * this->p_height;
  uint8_t*	buffer = new uint8_t[len * 3];

  for (uint64_t i = 0; i < len; ++i)
    {
      buffer[i * 3 + 0] = this->p_rawdata[i * 4 + 0];
      buffer[i * 3 + 1] = this->p_rawdata[i * 4 + 1];
      buffer[i * 3 + 2] = this->p_rawdata[i * 4 + 2];
    }
  uint8_t*	ptr;

  ptr = &(buffer[0]);
  jpeg_start_compress(&compressInfos, TRUE);

  while (compressInfos.next_scanline < compressInfos.image_height)
    {
      JSAMPROW rawpointer = ptr + (compressInfos.next_scanline * this->p_width * 3);
      jpeg_write_scanlines(&compressInfos, &rawpointer, 1);
    }

  jpeg_finish_compress(&compressInfos);
  jpeg_destroy_compress(&compressInfos);

  fclose(f);
  return (true);
}
