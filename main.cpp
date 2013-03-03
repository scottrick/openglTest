#include "opengl/GLContext.h"

#include "TestScene.h"

int main(int numArgs, char **args) {
	GLContext::create(numArgs, args, 0, 800, 600);
	GLContext::setScene(new TestScene());
	GLContext::go();
	return 0;
}