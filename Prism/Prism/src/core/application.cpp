#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/application.h>

namespace Prism {

	GLenum ShaderDataTypeToOpenGLBaseType(BufferLayoutType type) {
		switch (type) {
			case Prism::BufferLayoutType::Float1:    return GL_FLOAT;
			case Prism::BufferLayoutType::Float2:   return GL_FLOAT;
			case Prism::BufferLayoutType::Float3:   return GL_FLOAT;
			case Prism::BufferLayoutType::Float4:   return GL_FLOAT;
			case Prism::BufferLayoutType::Mat3:     return GL_FLOAT;
			case Prism::BufferLayoutType::Mat4:     return GL_FLOAT;
			case Prism::BufferLayoutType::Int1:      return GL_INT;
			case Prism::BufferLayoutType::Int2:     return GL_INT;
			case Prism::BufferLayoutType::Int3:     return GL_INT;
			case Prism::BufferLayoutType::Int4:     return GL_INT;
			case Prism::BufferLayoutType::Bool:     return GL_BOOL;
		}

		PRISM_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Application* Application::_singletonInstance = nullptr;

	Application::Application(uint32_t width, uint32_t height, std::string windowTitle) {
		if (_singletonInstance == nullptr) _singletonInstance = this;
		else throw "Only one instance of Application is allowed.";

		_window = Window::Create(width, height, windowTitle);
		_window->Attach(this);

		Input::_singletonInstance = new Input(); // glfw init before input can be init'd

		_layerStack = std::make_unique<LayerStack>();
		_imguiLayer = std::make_unique<ImGUILayer>();
		_layerStack->PushOverlayUnmanaged(_imguiLayer.get());

		float v[]{
			-0.5, -0.5f, 0.0f, 0.8, 0.3, 0.2, 1.0,
			 0.5, -0.5f, 0.0f, 0.2, 0.8, 0.3, 1.0,
			 0.0,  0.5f, 0.0f, 0.3, 0.2, 0.8, 1.0
		};

		uint32_t i[]{
			0, 1, 2
		};

		glCreateVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		_vertexBuffer.reset(VertexBuffer::Create(v, sizeof(v)));

		{
			BufferLayout basicLayout = {
				{ "VertexBuffer", BufferLayoutType::Float3, false },
				{ "ColorBuffer", BufferLayoutType::Float4, false }
			};
			_vertexBuffer->SetLayout(basicLayout);
		}

		uint32_t index = 0;
		const auto& layout = _vertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.count,
				ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.offset);
			index++;
		}

		_indexBuffer.reset(IndexBuffer::Create(i, sizeof(i)));

		_basicShader.reset(Shader::Create());
		std::string vertexShader = R"(
			#version 450
			layout(location = 0) in vec3 _pos;
			layout(location = 1) in vec4 _col;
			out vec4 _color;
			void main() {
				gl_Position = vec4(_pos, 1.0);
				_color = _col;
			}
		)";

		std::string fragmentShader = R"(
			#version 450
			in vec4 _color;
			out vec4 color;
			void main() {
				color = _color;
			}
		)";

		_basicShader->AddShaderSource(vertexShader, ShaderType::Vertex);
		_basicShader->AddShaderSource(fragmentShader, ShaderType::Pixel);
		_basicShader->Compile();

	};

	Application::~Application() {
		CORE_INFO("Prism is shutting down.");
		delete Input::_singletonInstance;
	};

	void Application::PopLayer(Layer* layer) {
		_layerStack->Pop(layer); // fwd
	}

    void Application::PopOverlay(Layer* layer) {
		_layerStack->PopOverlay(layer); // fwd
	}

	void Application::Run() {

		while (_running) {
			glClearColor(0.11, 0.11, 0.11, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			_basicShader->Bind();
			_vertexBuffer->Bind();
			_indexBuffer->Bind();
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (auto layer : *_layerStack)
				layer->Update();

			_imguiLayer->Begin();
			for (auto layer : *_layerStack)
				layer->ImGuiRender();
			_imguiLayer->End();

			_window->Update();
		}

	}

	void Application::OnEvent(IEvent* e) {

		IDispatcher dispatcher(e);
		dispatcher.Forward<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		dispatcher.Forward<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));

		for (auto layer : *_layerStack) {
			if (!e->IsHandled()) layer->OnEvent(e); // fwd to layers
		}

	}

	bool Application::OnWindowClose(WindowCloseEvent* e) {
		_running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent* e) {
		_window->SetHeight(e->GetHeight());
		_window->SetWidth(e->GetWidth());
		return false;
	}

}