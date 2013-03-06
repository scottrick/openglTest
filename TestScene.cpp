#include "TestScene.h"

#include "opengl/glm/glm.hpp"
#include "opengl/glm/gtc/matrix_transform.hpp"
#include "opengl/glm/gtc/type_ptr.hpp"
#include <GL/glew.h>

#include "opengl/GLContext.h"
#include "opengl/GLShader.h"
#include "opengl/GLTexture.h"
#include "opengl/GLTextureFactory.h"

#include <iostream>
#include <ctime>
using namespace std;

TestScene::TestScene(void) {
	create();
}

TestScene::~TestScene(void) {
	destroy();
}

void TestScene::create() {
	pFragShader = new GLShader("shaders/basic.frag");
	pVertShader = new GLShader("shaders/basic.vert");

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, pFragShader->getShader());
	glAttachShader(shaderProgram, pVertShader->getShader());
	
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// this setup is needed for EACH VertexArrayObject I want to use
	////////////////////////////////////////////////////////////////////////////////////////////////////
	float vertices[] = {
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

		-1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	};

	//setup the vertex buffer
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

	GLint colorAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));

	GLint textureAttrib = glGetAttribLocation(shaderProgram, "texture");
	glEnableVertexAttribArray(textureAttrib);
	glVertexAttribPointer(textureAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////

	pTextureOne = GLTextureFactory::createTextureForImage("hobbes.png");
	pTextureTwo = GLTextureFactory::createTextureForImage("test_texture.png");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, pTextureOne->getTexture());
	glUniform1i(glGetUniformLocation(shaderProgram, "textureOne"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, pTextureTwo->getTexture());
	glUniform1i(glGetUniformLocation(shaderProgram, "textureTwo"), 1);

	timeUniform = glGetUniformLocation(shaderProgram, "time");
	overrideColorUniform = glGetUniformLocation(shaderProgram, "overrideColor");
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////
	modelTransformUniform = glGetUniformLocation(shaderProgram, "model");
	viewTransformUniform = glGetUniformLocation(shaderProgram, "view");
	projTransformUniform = glGetUniformLocation(shaderProgram, "proj");

	glm::mat4 proj = glm::perspective( 45.0f, (float)GLContext::contextWidth() / (float)GLContext::contextHeight(), 1.0f, 10.0f );
	glUniformMatrix4fv(projTransformUniform, 1, GL_FALSE, glm::value_ptr(proj));

	glm::mat4 view = glm::lookAt(
		glm::vec3(4.0f, 0.0f, 1.5f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	);
	glUniformMatrix4fv(viewTransformUniform, 1, GL_FALSE, glm::value_ptr(view));
}

void TestScene::destroy() {
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &vbo);

    pVertShader->Release();
    pFragShader->Release();

    pTextureOne->Release();
    pTextureTwo->Release();
}

void TestScene::prepareRender() {

}

void TestScene::render() {
	GLfloat time = ((float)clock() / (float)CLOCKS_PER_SEC);
	glUniform1f(timeUniform, time);

	glm::mat4 modelTransform;
	modelTransform = glm::rotate(modelTransform, time * 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(modelTransformUniform, 1, GL_FALSE, glm::value_ptr(modelTransform));
	glUniform3f(overrideColorUniform, 1.0f, 1.0f, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////
	glEnable( GL_STENCIL_TEST );

	// Draw floor
	glStencilFunc( GL_ALWAYS, 1, 0xFF );
	glStencilOp( GL_KEEP, GL_KEEP, GL_REPLACE );
	glStencilMask( 0xFF );

	glDepthMask( GL_FALSE );
	glClear(GL_STENCIL_BUFFER_BIT);
	glDrawArrays( GL_TRIANGLES, 36, 6 );

	//// Draw cube reflection
	glStencilFunc( GL_EQUAL, 1, 0xFF );
	glStencilMask( 0x00 );
	glDepthMask( GL_TRUE );

	modelTransform = glm::scale( glm::translate( modelTransform, glm::vec3( 0, 0, -1 ) ), glm::vec3( 1, 1, -1 ) );
	glUniformMatrix4fv( modelTransformUniform, 1, GL_FALSE, glm::value_ptr( modelTransform ) );

	glUniform3f(overrideColorUniform, 0.3f, 0.3f, 0.3f);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisable( GL_STENCIL_TEST );
	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////
}

const char *TestScene::GetClassName() const {
    return "TestScene";
}