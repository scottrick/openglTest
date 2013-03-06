#include "opengl/GLContext.h"

#include "TestScene.h"

int main(int numArgs, char **args) {
	GLContext::create(numArgs, args, 0, 800, 600);
    TestScene *scene = new TestScene();
	GLContext::setScene(scene);
	GLContext::go();

    scene->Release();

	return 0;
}