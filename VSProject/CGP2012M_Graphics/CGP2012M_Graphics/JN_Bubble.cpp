#include "JN_Bubble.h"

#include <iostream>



JN_Bubble::JN_Bubble()
{
}


JN_Bubble::~JN_Bubble()
{
}


void JN_Bubble::Init(float radius, float offsetX, float offsetY, JN_ScreenBoundaries boundaries)
{
	this->offset = glm::vec2(offsetX, offsetY);
	this->speed = -0.001f;
	this->boundaries = boundaries;

	circle.Init(radius, offsetX, offsetY);

	float angle = glm::radians((float)(rand() % 360));

	transform.SetDirection((float)cos(angle), (float)sin(angle), 0.0f);

	transform.Translate(glm::vec3(boundaries.cX, boundaries.cY, 0.0f));
	transform.Scale(glm::vec3(1, 1, 0));


	// Hacky solution to random bubble position
	for (int i = 0; i < rand() % 4096; i++)
		Update();
}


void JN_Bubble::Render(JN_Texture texture)
{
	circle.Render(texture);
}


void JN_Bubble::Update()
{
	if (damaged)
		destroyTimer--;

	auto pos = transform.GetPosition();

	bool hitRight = pos.x > (5.1f - 0.35f  - this->offset.x);
	bool hitLeft = pos.x < (boundaries.l + (circle.radius) + 0.35f);
	bool hitTop = pos.y > (boundaries.t - (circle.radius) - 0.25f);
	bool hitBottom = pos.y < (boundaries.b + (circle.radius) + 0.25f);


	if (hitLeft || hitRight)
		transform.MultiplyDirection(-1, 1);

	else if (hitTop || hitBottom)
		transform.MultiplyDirection(1, -1);

	transform.Translate(transform.GetDirection() * 0.010f);
}


void JN_Bubble::SetUniforms(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	auto shaderProgram = circle.GetShaderProgram();

	glUseProgram(shaderProgram);

	auto projectionLocation = glGetUniformLocation(shaderProgram, "uProjection");
	auto modelLocation = glGetUniformLocation(shaderProgram, "uModel");
	auto viewLocation = glGetUniformLocation(shaderProgram, "uView");

	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(transform.Multiply()));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}
