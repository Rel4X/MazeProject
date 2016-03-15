#include	"LabzDrawer.h"
#include	"AStarLabzSolver.h"

LabzDrawer::LabzDrawer(void)
{
}

LabzDrawer::~LabzDrawer(void)
{
}

bool			LabzDrawer::DrawToFile(const Labz* l, const char* fname, bool color)
{
	BMP			Image;

	if (l == 0 || fname == 0)
	{ return (false); }

	if (strlen(fname) < 1)
	{ return (false); }

	if (Image.SetSize(l->w, l->h) == false)
	{ return (false); }

	if (color == false)
		Image.SetBitDepth(1);
	else
		Image.SetBitDepth(8);

	for (int i = 0; i < l->w; ++i)
	{
		for (int j = 0; j < l->h; ++j)
		{
			if (l->lab[i][j] == WALL)
			{
				Image(i, j)->Red = 0;
				Image(i, j)->Green = 0;
				Image(i, j)->Blue = 0;
			}
			else if (l->lab[i][j] == IN_PATH)
			{
				Image(i, j)->Red = 255;
				Image(i, j)->Green = 0;
				Image(i, j)->Blue = 255;
			}
			else if (l->lab[i][j] == IN_CLOSED)
			{
				Image(i, j)->Red = 0;
				Image(i, j)->Green = 0;
				Image(i, j)->Blue = 255;
			}
			else
			{
				Image(i, j)->Red = 255;
				Image(i, j)->Green = 255;
				Image(i, j)->Blue = 255;
			}
			Image(i, j)->Alpha = 0;
		}
	}
	Image.WriteToFile(fname);

	return (true);
}
