#ifndef DRAWING_H
#define DRAWING_H
#include "drawbase.h"
// forward reference
class GraphicsContext;
class drawing : public DrawingBase
{
public:
drawing();
// we will override just these
virtual void paint(GraphicsContext
*
gc);
virtual void mouseButtonDown(GraphicsContext
*
gc, unsigned int button,
int x, int y);
virtual void mouseButtonUp(GraphicsContext
*
gc, unsigned int button,
int x, int y);
virtual void mouseMove(GraphicsContext
*
gc, int x, int y);
private:
// We will only support one "remembered" line
// In an actual implementation, we would also have one of our "image"
// objects here to store all of our drawn shapes.
int x0;
int y0;
int x1;
int y1;
bool dragging; // flag to know if we are dragging
};
#endif
