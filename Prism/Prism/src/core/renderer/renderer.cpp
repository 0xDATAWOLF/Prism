#include <core/renderer/renderer.h>
#include <platform/opengl/ogl_renderapi.h>
#include <platform/opengl/ogl_shader.h>

namespace Prism {

	// -------------------------------------------------------
	// --- Renderer ------------------------------------------
	// -------------------------------------------------------

	glm::mat4 Renderer::_viewProjectionMatrix = glm::mat4(1.0);

	void Renderer::BeginScene(std::shared_ptr<Camera>& camera) {
		_viewProjectionMatrix = camera->GetViewProjectionMatrix();
	}

	void Renderer::Submit(std::shared_ptr<Shader>& shader, std::shared_ptr<VertexArray>& vertexArray, glm::mat4 transform) {
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->DefineUniformMat4("_uViewProjection", _viewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->DefineUniformMat4("_uTransform", transform);
		vertexArray->Bind();
		RendererCommand::DrawIndexed(vertexArray);
	};

	// -------------------------------------------------------
	// --- RendererCommand -----------------------------------
	// -------------------------------------------------------

	BaseRendererInterface* RendererCommand::_api = new OpenGLRendererAPI();

}