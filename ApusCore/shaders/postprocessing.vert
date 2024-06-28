#version 440 core

layout(location = 0) in vec4 _position;
layout(location = 1) in vec2 _uv;

out vec2 uv;

void main()
{
    uv = _uv;
    gl_Position = _position;
}