#version 440 core

layout(location = 0) in vec4 _position;

layout(location = 1) in vec2 _uv;
layout(location = 2) in vec4 _color;

layout(location = 5) uniform mat4 u_Proj;
layout(location = 6) uniform mat4 u_Cam;

out vec2 uv;
out vec4 color;

void main()
{
    uv = _uv;
    color = _color;
    gl_Position = _position;
}