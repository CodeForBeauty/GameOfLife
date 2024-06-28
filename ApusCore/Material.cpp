#include <iostream>

#include "Material.h"


void ApusCore::Material::_Compile() {
	program = glCreateProgram();
	glAttachShader(program, vs.id);
	glAttachShader(program, fs.id);
	glLinkProgram(program);
	glValidateProgram(program);
	glUseProgram(program);
}

void ApusCore::Material::Bind() {
	tex.Bind();
	glUseProgram(program);

}

void ApusCore::Material::Destroy() {
	vs.Destroy();
	fs.Destroy();
	tex.Clear();
	glDeleteProgram(program);
}

void ApusCore::Material::LoadTexture(const char* path) {
	tex.LoadTexture(path);
}
