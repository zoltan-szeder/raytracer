
#define WIDTH 600
#define HEIGHT 600

struct Screen
{
public:
  int x;
  int y;

  Color canvas[WIDTH * HEIGHT];

  Screen(  )
  {
    x = WIDTH;
    y = HEIGHT;
  }

  void draw()
  {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels( x, y, GL_RGB, GL_FLOAT, canvas );
    glutSwapBuffers();
  }
};

