#include "World.h"

World world;
int height = 200;
int width = 200;

void draw()
{
	world.render_scene();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	world.build(width, height);
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}