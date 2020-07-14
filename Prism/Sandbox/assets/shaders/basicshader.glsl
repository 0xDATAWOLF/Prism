#shader vertex
#version 410 core
layout(location = 0) in vec3 _aPosition;
layout(location = 1) in vec2 _aTexCoord;

uniform mat4 _uViewProjection;
uniform mat4 _uTransform;

out vec2 _texCoord;

void main() {
    gl_Position = _uViewProjection * _uTransform * vec4(_aPosition, 1.0);
    _texCoord = _aTexCoord;
}

#shader fragment
#version 410 core
in vec2 _texCoord;

uniform sampler2D _uTexture;

out vec4 color;

void main() {
    color = texture(_uTexture, _texCoord);
}