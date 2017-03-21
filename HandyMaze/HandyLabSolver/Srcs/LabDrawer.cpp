#include	"LabDrawer.h"

LabDrawer::LabDrawer()
{
}

LabDrawer::~LabDrawer()
{
}

bool		LabDrawer::DrawToBMP(const Labz* l, const char* fname)
{
  BMP	Image;
  
  if (l == 0 || fname == 0)
    { return (false); }
  
  if (strlen(fname) < 1)
    { return (false); }
  
  if (Image.SetSize(l->w + 2, l->h + 2) == false)
    { return (false); }
  
  Image.SetBitDepth(8);

  unsigned int ki = 0;
  unsigned int kj = 0;
  for (int i = 0; i < l->h + 2; ++i)
    {
      for (int j = 0; j < l->w + 2; ++j)
	{
	  Image(j, i)->Red = 0;
	  Image(j, i)->Green = 0;
	  Image(j, i)->Blue = 0;
	}
    }
  for (int i = 0; i < l->h; ++i)
    {
      for (int j = 0; j < l->w; ++j)
	{
	  ki = i + 1;
	  kj = j + 1;
	  if (l->shebangs[i * l->h + j] == WALL)
	    {
	      Image(kj, ki)->Red = 0;
	      Image(kj, ki)->Green = 0;
	      Image(kj, ki)->Blue = 0;
	    }
	  else if (l->shebangs[i * l->h + j] == WAY)
	    {
	      Image(kj, ki)->Red = 255;
	      Image(kj, ki)->Green = 255;
	      Image(kj, ki)->Blue = 255;
	    }
	  else if (l->shebangs[i * l->h + j] == VISIT)
	    {
	      Image(kj, ki)->Red = 0;
	      Image(kj, ki)->Green = 0;
	      Image(kj, ki)->Blue = 255;
	    }
	  else if (l->shebangs[i * l->h + j] == PATH)
	    {
	      Image(kj, ki)->Red = 255;
	      Image(kj, ki)->Green = 0;
	      Image(kj, ki)->Blue = 255;
	    }
	  Image(kj, ki)->Alpha = 0;
	}
    }
  Image.WriteToFile(fname);
  return (true);
}
