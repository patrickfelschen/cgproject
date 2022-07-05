#include "Renderer.hpp"

const float Renderer::FOV = 70;
const float Renderer::NEAR_PLANE = 0.1f;
const float Renderer::FAR_PLANE = 1000;

Renderer::Renderer(float width, float height, StaticShader shader)
{
	this->width = width;
	this->height = height;
	createProjectionMatrix();
	shader.start();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.stop();
}

Renderer::~Renderer()
{
}

void Renderer::prepare()
{
	glEnable(GL_DEPTH_TEST); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 0, 0, 1);
}

void Renderer::render(Entity entity, StaticShader shader) {
	TexturedModel* texturedModel = entity.getModel();
	RawModel rawModel = texturedModel->getRawModel();
	glBindVertexArray(rawModel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	Matrix transformationMatrix = Maths::createTransformationMatrix(entity.getPosition(), entity.getRotX(), entity.getRotY(), entity.getRotZ(), entity.getScale());
	shader.loadTransformationMatrix(transformationMatrix);
	glActiveTexture(GL_TEXTURE0);
	glDrawElements(GL_TRIANGLES, (GLsizei)rawModel.getVertexCount(), GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, texturedModel->getTexture().getID());	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}

void Renderer::createProjectionMatrix() {
	float aspectRatio = width / height;

	projectionMatrix.perspective(FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);
}
