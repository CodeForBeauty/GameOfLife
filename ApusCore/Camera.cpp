#include "Camera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void ApusCore::Camera::UpdateMatrix() {
	lm::mat4 rot = lm::rotation2d(rotation);
	rot.w.z = 1;
	rot.w.w = 1;
	
	matrix = rot * lm::position3d(-position);
}

ApusCore::Camera::Camera(lm::vec2 position, float rotation) : position(position), rotation(rotation), 
						vs("shaders/postprocessing.vert", GL_VERTEX_SHADER), fs("shaders/postprocessing.frag", GL_FRAGMENT_SHADER) {
	gladLoadGL();
	glGenFramebuffers(1, &posFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, posFBO);
	
	GenerateTexture(800, 650);

	program = glCreateProgram();
	glAttachShader(program, vs.id);
	glAttachShader(program, fs.id);
	glLinkProgram(program);
	glValidateProgram(program);
	glUseProgram(program);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, rect, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	UpdateMatrix();
}

ApusCore::Camera::~Camera() {
	glDeleteTextures(1, &posTex);
	vs.Destroy();
	fs.Destroy();
	glDeleteProgram(program);
}

void ApusCore::Camera::SetPosition(lm::vec2 newPosition) {
	position = newPosition;
	UpdateMatrix();
}

void ApusCore::Camera::SetRotation(float newRotation) {
	rotation = newRotation;
	UpdateMatrix();
}

void ApusCore::Camera::Move(lm::vec2 offset) {
	position += offset;
	UpdateMatrix();
}

void ApusCore::Camera::Rotate(float offset) {
	rotation += offset;
	UpdateMatrix();
}

void ApusCore::Camera::GenerateTexture(float width, float height) {
	if (lastWidth == width && lastHeight == height)
		return;
	if (posTex)
		glDeleteTextures(1, &posTex);
	glGenTextures(1, &posTex);
	glBindTexture(GL_TEXTURE_2D, posTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, posFBO, 0);

	lastWidth = width;
	lastHeight = height;
}

void ApusCore::Camera::BindFBO(float width, float height) {
	glBindFramebuffer(GL_FRAMEBUFFER, posFBO);
	GenerateTexture(width, height);
}

void ApusCore::Camera::Render(float width, float height) {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glViewport(0, 0, width, height);
	glUseProgram(program);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, posTex);

	glUniform1i(glGetUniformLocation(program, "tex"), 1);


	glDrawArrays(GL_TRIANGLES, 0, 8);
}
