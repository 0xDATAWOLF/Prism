#shader vertex
#version 410 core
layout(location = 0) in vec3 _aPosition;

uniform mat4 _uViewProjection;
uniform mat4 _uTransform;

void main() {
    gl_Position = _uViewProjection * _uTransform * vec4(_aPosition, 1.0);
}

#shader fragment
#version 410 core

uniform vec4 _uColor;
out vec4 color;

void main() {
    color = _uColor;
}