#shader vertex
#version 410 core
layout(location = 0) in vec3 _aPosition;
layout(location = 1) in vec4 _aColor;
layout(location = 2) in vec2 _aTexCoord;
layout(location = 3) in float _aTextureIndex;

uniform mat4 _uViewProjection;

out vec4 _color;
out vec2 _texCoord;
out float _textureIndex;

void main() {
	_color = _aColor;
	_texCoord = _aTexCoord;
	_textureIndex = _aTextureIndex;

	gl_Position = _uViewProjection * vec4(_aPosition, 1.0);
}

#shader fragment
#version 410 core

in vec4 _color;
in vec2 _texCoord;
in float _textureIndex;

uniform sampler2D _uTextures[32];

out vec4 color;

void main() {
	color = texture(_uTextures[int(_textureIndex)], _texCoord) * _color;
}