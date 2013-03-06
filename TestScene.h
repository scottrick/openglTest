#pragma once

#include "opengl\GLScene.h"
#include <GL/glew.h>

class GLShader;
class GLTexture;

class TestScene : public GLScene
{
public:
	TestScene();

	//creation and deletion of this scene
	void create();
	void destroy();

	//rendering
	void prepareRender();
	void render();

    //unknown
    const char *GetClassName() const;

protected:
	~TestScene();

private:
	GLShader *pFragShader;
	GLShader *pVertShader;

	GLuint timeUniform;
	GLuint overrideColorUniform;
	GLuint modelTransformUniform;
	GLuint viewTransformUniform;
	GLuint projTransformUniform;

	GLTexture *pTextureOne;
	GLTexture *pTextureTwo;

	GLuint shaderProgram;
	GLuint vbo;
};

