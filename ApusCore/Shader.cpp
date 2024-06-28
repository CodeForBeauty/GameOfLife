#include <fstream>
#include <iostream>

#include "Shader.h"


void ApusCore::Shader::Destroy() {
	glDeleteShader(id);
}

void ApusCore::Shader::LoadFromFile(std::string filepath) {
	std::string content, line;

	std::ifstream file(filepath);

	while (std::getline(file, line))
		content += line + "\n";

	file.close();
	SetShader(content);
}

std::string ApusCore::Shader::GetShader() {
	return text;
}

void ApusCore::Shader::SetShader(std::string shader) {
	text = shader;
}

void ApusCore::Shader::RecompileShader()
{
	id = glCreateShader(type);
	const char* src = text.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);
	
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* msg = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, msg);
		std::cout << "Error: " << msg;
	}
}
