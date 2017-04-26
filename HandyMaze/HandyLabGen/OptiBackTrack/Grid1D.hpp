#ifndef		__GRID_H__
#define		__GRID_H__

template<typename T>
class		Grid1D
{
private:
  unsigned int	p_width;
  unsigned int	p_height;
  unsigned int	p_size;
  T*		p_grid;
  
private:
  Grid1D() { }
  Grid1D(const Grid1D&);
  
public:
  Grid1D(unsigned int w, unsigned int h);
  ~Grid1D();
  
public:
  unsigned int	GetWidth() const;
  unsigned int	GetHeight() const;
  unsigned int	GetSize() const;
  
public:
  T*		GetElement(unsigned int x, unsigned int y);
  
};

template<typename T>
Grid1D<T>::Grid1D(unsigned int w, unsigned int h) :
  p_width(w), p_height(h), p_size(w * h)
{
  this->p_grid = new T[this->p_size]();
}

template<typename T>
Grid1D<T>::~Grid1D()
{
}

template<typename T>
unsigned int	Grid1D<T>::GetWidth() const
{
  return (this->p_width);
}

template<typename T>
unsigned int	Grid1D<T>::GetHeight() const
{
  return (this->p_height);
}

template<typename T>
unsigned int	Grid1D<T>::GetSize() const
{
  return (this->p_size);
}

template<typename T>
T*		Grid1D<T>::GetElement(unsigned int x, unsigned int y)
{
  return (&this->p_grid[y * this->p_width + x]);
}


#endif		// __GRID_H__
