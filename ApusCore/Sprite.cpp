#include "Sprite.h"


ApusCore::Mesh::Mesh(size_t vertCount) {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertCount, nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, col));


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ApusCore::Mesh::LoadTexture(const char* path) {
	material.LoadTexture(path);
}

void ApusCore::Mesh::Destroy() {
	material.Destroy();
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void ApusCore::Mesh::Draw(lm::mat4 proj, lm::mat4 cam) {
	BeforeDraw();

	material.Bind();

	glUniformMatrix4fv(5, 1, GL_FALSE, proj);
	glUniformMatrix4fv(6, 1, GL_FALSE, cam);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * vertices.size(), vertices.data());

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

Vertex* ApusCore::Mesh::GetData() {
	return &vertices[0];
}

ApusCore::Sprite::Sprite(lm::vec4 tint, lm::vec2 scale, lm::vec2 position, float rotation, lm::vec2 tiling, const char* texPath) : 
	Mesh(6), tintColor(tint), scale(scale), position(position), rotation(rotation), tiling(tiling), z(0) {
	vertices.push_back({ {-0.5f,  0.5f, 0.0f}, {0, 1}, {1, 1, 1, 1} });
	vertices.push_back({ { 0.5f,  0.5f, 0.0f}, {1, 1}, {1, 1, 1, 1} });
	vertices.push_back({ { 0.5f, -0.5f, 0.0f}, {1, 0}, {0, 0, 0, 1} });

	vertices.push_back({ { 0.5f, -0.5f, 0.0f}, {1, 0}, {0, 0, 0, 1} });
	vertices.push_back({ {-0.5f, -0.5f, 0.0f}, {0, 0}, {0, 0, 0, 1} });
	vertices.push_back({ {-0.5f,  0.5f, 0.0f}, {0, 1}, {1, 1, 1, 1} });
	
	for (int i = 0; i < vertices.size(); i++) {
		vertices.at(i).pos *= scale;
		vertices[i].uv *= tiling;
		vertices[i].pos += position;
		vertices[i].col *= tint;
	}

	material.LoadTexture(texPath);
}

void ApusCore::Sprite::SetPosition(lm::vec2 newPos) {
	lm::vec2 offset = newPos - position;
	position = newPos;
	for (int i = 0; i < vertices.size(); i++)
		vertices[i].pos += offset;
}

void ApusCore::Sprite::SetRotation(float newRot) {
	float offset = newRot - rotation;
	rotation = newRot;
	lm::mat2 mat = lm::rotation2d(offset);
	for (int i = 0; i < vertices.size(); i++)
		vertices[i].pos = mat * (vertices[i].pos - position) + position;
}

void ApusCore::Sprite::SetScale(lm::vec2 newScale) {
	lm::vec2 offset = newScale / scale;
	scale = newScale;
	for (int i = 0; i < vertices.size(); i++)
		vertices[i].pos = (vertices[i].pos - position) * offset + position;
}

lm::vec2 ApusCore::Sprite::GetPosition() {
	return position;
}

float ApusCore::Sprite::GetRotation() {
	return rotation;
}

lm::vec2 ApusCore::Sprite::GetScale() {
	return scale;
}

lm::vec2 ApusCore::Sprite::Move(lm::vec2 offset) {
	position += offset;
	for (int i = 0; i < vertices.size(); i++)
		vertices[i].pos += offset;
	return position;
}

float ApusCore::Sprite::Rotate(float offset) {
	rotation += offset;
	lm::mat2 mat = lm::rotation2d(offset);
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].pos = mat * (vertices[i].pos - position) + position;
	}
	return rotation;
}

lm::vec2 ApusCore::Sprite::Scale(lm::vec2 offset) {
	scale += offset;
	for (int i = 0; i < vertices.size(); i++)
		vertices[i].pos = (vertices[i].pos - position) * offset + position;
	return scale;
}

void ApusCore::Sprite::SetZ(float zValue) {
	z = zValue;
	for (int i = 0; i < 6; i++) {
		vertices[i].pos.z = zValue;
	}
}

float ApusCore::Sprite::GetZ() {
	return z;
}


void ApusCore::Sprite::GenerateTexture(std::function<Color (lm::vec2 pos, lm::vec2 uv)> func, int width, int height, bool hasAlpha) {
	material.tex.width = width;
	material.tex.height = height;
	material.tex.Generate(func, hasAlpha);
}

void ApusCore::Sprite::RegenerateTexture(std::function<Color(lm::vec2 pos, lm::vec2 uv, Color previous)> func) {
	material.tex.Regenerate(func);
}

ApusCore::ScreenOverlay::ScreenOverlay(Window* window) : Mesh(6), window(window) {
	vertices.push_back({ {-1.0f,  1.0f, 0.0f}, {0, 1}, {1, 1, 1, 1} });
	vertices.push_back({ { 1.0f,  1.0f, 0.0f}, {1, 1}, {1, 1, 1, 1} });
	vertices.push_back({ { 1.0f, -1.0f, 0.0f}, {1, 0}, {0, 0, 0, 1} });

	vertices.push_back({ { 1.0f, -1.0f, 0.0f}, {1, 0}, {0, 0, 0, 1} });
	vertices.push_back({ {-1.0f, -1.0f, 0.0f}, {0, 0}, {0, 0, 0, 1} });
	vertices.push_back({ {-1.0f,  1.0f, 0.0f}, {0, 1}, {1, 1, 1, 1} });

	lastHeight = 1;
	lastWidth = 1;

	material = Material("shaders/vertexNoScaling.vert");
}

void ApusCore::ScreenOverlay::GenerateTexture(std::function<Color(lm::vec2 pos, lm::vec2 uv)> func, bool hasAlpha) {
	material.tex.width = window->viewportWidth;
	material.tex.height = window->viewportHeight;
	material.tex.Generate(func, hasAlpha);
}

void ApusCore::ScreenOverlay::GenerateTexture(std::function<Color(lm::vec2 pos, lm::vec2 uv)> func, int width, int height, bool hasAlpha) {
	material.tex.width = width;
	material.tex.height = height;
	material.tex.Generate(func, hasAlpha);
}

void ApusCore::ScreenOverlay::RegenerateTexture(std::function<Color(lm::vec2 pos, lm::vec2 uv, Color previous)> func) {
	material.tex.Regenerate(func);
}

