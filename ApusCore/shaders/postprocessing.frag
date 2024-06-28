#version 440 core

in vec2 uv;

uniform sampler2D tex;

out vec4 fragColor;


void main() 
{
    //fragColor =  vec4(uv.x, uv.y, 0.0f, 1.0f);
    fragColor = texture(tex, uv);
}