#include "renderer/vertexarray.h"
#include "platform/opengl/ogl_vertexarray.h"

namespace Prism {

	VertexArray* VertexArray::Create() {
		return new OpenGLVertexArray();
	}

}