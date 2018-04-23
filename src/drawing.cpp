#include "drawing.h"
#include "gcontext.h"

#include <iostream>
#include <fstream>
// Constructor
drawing::drawing()
{
	dragging = false;

	dot = true;
	seg = false;
	tri = false;

	tVert = 0;
	xOrg = xVert2 = yVert2 = xVert3 = yVert3 = 0;
	yOrg = 0;

	x0 = x1 = y0 = y1 = 0;
	RED = GREEN = BLUE = 0;
	decodeColor(GraphicsContext::GREEN);
	return;
}

//TODO: mod this
void drawing::paint(GraphicsContext*gc)
{
	gc->clear();
	picture.draw(gc);
	return;
}


void drawing::keyDown(GraphicsContext* gc, unsigned int keycode){
	if(!dragging){
		//point
		if(keycode == 112){
			dot = true;
			seg = false;
			tri = false;
			tVert = 0;
		}
		//line
		else if(keycode == 108){
			dot = false;
			seg = true;
			tri = false;
			tVert = 0;
		}
		//triangle
		else if(keycode == 116){
			dot = false;
			seg = false;
			tri = true;
			tVert = 0;
		}

		else if(keycode == 49){
			gc->setColor(GraphicsContext::RED);
			decodeColor(GraphicsContext::RED);
		}
		else if(keycode == 50){
			gc->setColor(GraphicsContext::YELLOW);
			decodeColor(GraphicsContext::YELLOW);
		}
		else if(keycode == 51){
			gc->setColor(GraphicsContext::GREEN);
			decodeColor(GraphicsContext::GREEN);
		}
		else if(keycode == 52){
			gc->setColor(GraphicsContext::BLUE);
			decodeColor(GraphicsContext::BLUE);
		}
		else if(keycode == 53){
			gc->setColor(GraphicsContext::MAGENTA);
			decodeColor(GraphicsContext::MAGENTA);
		}
		else if(keycode == 54){
			gc->setColor(GraphicsContext::CYAN);
			decodeColor(GraphicsContext::CYAN);
		}
		else if(keycode == 55){
			gc->setColor(GraphicsContext::GRAY);
			decodeColor(GraphicsContext::GRAY);
		}
		else if(keycode == 56){
			gc->setColor(GraphicsContext::WHITE);
			decodeColor(GraphicsContext::WHITE);
		}
		//save an image
		else if(keycode == 115){
			std::ofstream output;
			output.open("PictureOutput.txt");
			output << "PICTURE OUTPUT" << std::endl;
			output << picture << std:: endl;
			output.close();
		}
		//open an image
		else if(keycode == 111){
			picture.erase();
			std::ifstream input;
			input.open("PictureOutput.txt");
			while(input){
				picture.in(input);
			}
			input.close();
			gc->clear();
			picture.draw(gc);
		}
	}
}

void drawing::mouseButtonDown(GraphicsContext* gc, unsigned int button, int x, int y)
{
	if(seg){
		// mouse button pushed down
		// - clear context
		// - set origin of new line
		// - set XOR mode for rubber-banding
		// - draw new line in XOR mode.  Note, at this point, the line is
		//   degenerate (0 length), but need to do it for consistency
		x0 = x1 = x;
		y0 = y1 = y;
		gc->setMode(GraphicsContext::MODE_XOR);
		gc->drawLine(x0,y0,x1,y1);
		dragging = true;
	}

	else if(tri){
		if(tVert == 0){
			xOrg = x0 = x1 = x;
			yOrg = y0 = y1 = y;
			gc->setMode(GraphicsContext::MODE_XOR);
			gc->drawLine(x0, y0, x1, y1);
			dragging = true;
			tVert++;
		}
		else if(tVert == 1){
			// undraw old line
			gc->drawLine(x0,y0,x1,y1);
			// just in x and y here do not match x and y of last mouse move
			xVert2 = x1 = x;
			yVert2 = y1 = y;
			// go back to COPY mode
			gc->setMode(GraphicsContext::MODE_NORMAL);
			// new line drawn in copy mode
			gc->drawLine(x0,y0,x1,y1);
			x0 = x1 = x;
			y0 = y1 = y;
			gc->setMode(GraphicsContext::MODE_XOR);
			gc->drawLine(x0, y0, x1, y1);
			tVert++;
		}
		else if(tVert == 2){
			// undraw old line
			gc->drawLine(x0,y0,x1,y1);
			// just in x and y here do not match x and y of last mouse move
			xVert3 = x1 = x;
			yVert3 = y1 = y;
			// go back to COPY mode
			gc->setMode(GraphicsContext::MODE_NORMAL);
			// new line drawn in copy mode
			gc->drawLine(x0,y0,x1,y1);
			gc->drawLine(x1, y1, xOrg, yOrg);
			tVert = 0;
			dragging = false;
			triangle t1(xOrg, yOrg, RED, GREEN, BLUE, xVert2, yVert2, xVert3, yVert3);
			picture.add(&t1);
		}
	}
	else{
		gc->setPixel(x, y);
		point p1(0,0,0,0,0);
		picture.add(&p1);
	}
	return;
}

void drawing::mouseButtonUp(GraphicsContext* gc, unsigned int button, int x, int y)
{
	if(dragging)
	{
		if(seg){
			// undraw old line
			gc->drawLine(x0,y0,x1,y1);
			// just in x and y here do not match x and y of last mouse move
			x1 = x;
			y1 = y;
			// go back to COPY mode
			gc->setMode(GraphicsContext::MODE_NORMAL);
			// new line drawn in copy mode
			gc->drawLine(x0,y0,x1,y1);
			// clear flag
			dragging = false;
			line l1(x0, y0, RED, GREEN, BLUE, x1, y1);
		}
	}
return;
}

void drawing::mouseMove(GraphicsContext* gc, int x, int y)
{
	if(dragging)
	{
		if(seg){
			// mouse moved - "undraw" old line, then re-draw in new position
			// will already be in XOR mode if dragging
			// old line undrawn
			gc->drawLine(x0,y0,x1,y1);
			// update
			x1 = x;
			y1 = y;
			// new line drawn
			gc->drawLine(x0,y0,x1,y1);
		}
		else if(tri){
				gc->drawLine(x0, y0, x1, y1);
				x1 = x;
				y1 = y;
				gc->drawLine(x0, y0, x1, y1);
		}
	}
return;
}

void drawing::decodeColor(unsigned int color){
	RED = (color >> 16) & 0xFF;
	GREEN = (color >> 8) & 0xFF;
	BLUE = color & 0xFF;
}

