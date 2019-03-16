#ifndef JN_CIRCLE_H
#define JN_CIRCLE_H

#include <GL/glew.h>
#include <string>

#include "JN_Texture.h"

class JN_Circle
{
public:
	JN_Circle();
	~JN_Circle();

	float radius;

	void Init(float radius, float offsetX, float offsetY);
	void Render();

	GLuint GetShaderProgram() { return shaderProgram; }

private:
	static JN_Texture texture;

	GLuint shaderProgram;
	GLuint VBO, VAO, EBO;
	GLfloat vertices[240];
	GLuint indices[87] = {
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5,
		0, 5, 6,
		0, 6, 7,
		0, 7, 8,
		0, 8, 9,
		0, 9, 10,
		0, 10, 11,
		0, 11, 12,
		0, 12, 13,
		0, 13, 14,
		0, 14, 15,
		0, 15, 16,
		0, 16, 17,
		0, 17, 18,
		0, 18, 19,
		0, 19, 20,
		0, 20, 21,
		0, 21, 22,
		0, 22, 23,
		0, 23, 24,
		0, 24, 25,
		0, 25, 26,
		0, 26, 27,
		0, 27, 28,
		0, 28, 29
	};

	void SetBuffers();
};

#endif // !JN_CIRCLE_H
