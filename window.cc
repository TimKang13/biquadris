#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height, int background_color) : width{width}, height{height} {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Define colors
  const char* color_vals[] = {
      "white", "black", "red", "green", "blue",
      "#2888b8", "#ff9932", "#ffcc00", "#99cc33", 
      "#986699", "#e61c34", "#33cb98", "#895129"
  };

  Colormap cmap = DefaultColormap(d, DefaultScreen(d));
  XColor xcolour;
  
  for(int i = 0; i < NUM_COLORS; ++i) {
      if(XParseColor(d, cmap, color_vals[i], &xcolour) && 
          XAllocColor(d, cmap, &xcolour)) {
          colours[i] = xcolour.pixel;
      }
  }

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);
  fillRectangle(0, 0, width, height, background_color);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

int Xwindow::getWidth() const { return width; }
int Xwindow::getHeight() const { return height; }

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawRectangleWithStroke(int x, int y, int width, int height,
                                     int fill_colour, int stroke_colour, int stroke_width) {
  // Draw the outer stroke
  XSetForeground(d, gc, colours[stroke_colour]);
  XFillRectangle(d, w, gc, 
                  x - stroke_width,           // Left edge of stroke
                  y - stroke_width,           // Top edge of stroke
                  width + (2 * stroke_width), // Full width including stroke
                  height + (2 * stroke_width) // Full height including stroke
  );
  // Draw the inner filled rectangle
  XSetForeground(d, gc, colours[fill_colour]);
  XFillRectangle(d, w, gc,
                  x,      // Inner rectangle x
                  y,      // Inner rectangle y
                  width,  // Inner rectangle width
                  height  // Inner rectangle height
  );
  
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg, int colour) {
  XSetForeground(d, gc, colours[colour]);
  const int TEXT_HEIGHT = 9;
  XDrawString(d, w, gc, x, y + TEXT_HEIGHT, msg.c_str(), msg.length());
  XSetForeground(d, gc, colours[Black]);
}

