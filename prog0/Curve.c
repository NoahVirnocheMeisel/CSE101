#include <cairo.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define ANGLE M_PI / 4.0
#define OPTIONS "i:"
// main command line control for program. Can specifiy an input file with -i(or
// <)
int main(int argc, char *argv[]) {
  int opt = 0;
  FILE *infile = stdin;
  while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
    switch (opt) {
    case 'i':
      if (infile != stdin) {
        fclose(infile);
      }
      infile = fopen(optarg, "r");
      break;
    }
  }
  // main variables for math calculations and for reading and outputting our
  // files.
  double x_start;
  double y_start;
  double x_end;
  double y_end;
  int n;
  int height;
  int width;
  char out[4096];
  char line[4096];
  fgets(line, 4096, infile);
  // reads the line of input into the different variables.
  sscanf(line, "%s %d %d %d %lf %lf %lf %lf", out, &height, &width, &n,
         &x_start, &y_start, &x_end, &y_end);
  strcat(out, ".png");

  // creates a cairo surface to produce the .png file
  cairo_surface_t *surface =
      cairo_image_surface_create(CAIRO_FORMAT_ARGB32, height, width);
  cairo_t *cr = cairo_create(surface);
  // sets the background to be white.
  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_rectangle(cr, 0, 0, width, height);
  cairo_fill(cr);

  cairo_set_source_rgb(cr, 250, 0, 0);
  int curve_draw(int sn, double sx, double sy, double ex, double ey,
                 cairo_t *surf);

  cairo_set_line_width(cr, 1);
  // call to our C curve function.
  curve_draw(n, x_start, -y_start, x_end, -y_end, cr);
  cairo_stroke(cr);

  // closes our surface and file
  cairo_destroy(cr);
  cairo_surface_write_to_png(surface, out);
  cairo_surface_destroy(surface);
  fclose(infile);

  return 0;
}

// if the recursive depth >0, translate our ending point by subtracting the
// starting point and dividing by sqrt(2).  Then, use the rotation matrix to
// rotate the point which we then translate back by readding the starting point.
// We then call our function again twice with n-1, and the first call taking our
// starting point -> translated point, and the  second call taking our
// translated point -> original end point.

// if n is 0 or less, we draw a line from our starting point to our end point.
int curve_draw(int sn, double sx, double sy, double ex, double ey,
               cairo_t *surf) {
  int n = sn;
  if (n > 0) {
    float tx = (ex - sx) / sqrt(2.0);
    float ty = (ey - sy) / sqrt(2.0);
    float e_tx = tx;
    tx = tx * cos(ANGLE) - ty * sin(ANGLE) + sx;
    ty = e_tx * sin(ANGLE) + ty * cos(ANGLE) + sy;
    curve_draw(n - 1, sx, sy, tx, ty, surf);
    curve_draw(n - 1, tx, ty, ex, ey, surf);
  } else {
    cairo_move_to(surf, sx, -sy);
    cairo_line_to(surf, ex, -ey);
  }
}
