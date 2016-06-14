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
  
  if (Image.SetSize(l->w, l->h) == false)
    { return (false); }
  
  Image.SetBitDepth(8);
    
  for (int i = 0; i < l->h; ++i)
    {
      for (int j = 0; j < l->w; ++j)
	{
	  if (l->shebangs[i * l->h + j] == WALL)
	    {
	      Image(j, i)->Red = 0;
	      Image(j, i)->Green = 0;
	      Image(j, i)->Blue = 0;
	    }
	  else if (l->shebangs[i * l->h + j] == WAY)
	    {
	      Image(j, i)->Red = 255;
	      Image(j, i)->Green = 255;
	      Image(j, i)->Blue = 255;
	    }
	  else if (l->shebangs[i * l->h + j] == PATH)
	    {
	      Image(j, i)->Red = 255;
	      Image(j, i)->Green = 0;
	      Image(j, i)->Blue = 255;
	    }
	  Image(j, i)->Alpha = 0;
	}
    }
  Image.WriteToFile(fname);
  return (true);
}
