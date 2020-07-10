#include <core/application.h>
#include <core/renderer/renderer.h>
#include <core/renderer/buffer.h>

namespace Prism {

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

		float vb[]{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.3f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.3f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.3f, 0.2f, 0.8f, 1.0f
		};

		float vb2[]{
			-0.8, -0.8, 0.0, 0.5f, 0.1f, 0.4f, 1.0f,
			0.8, -0.8, 0.0, 0.3f, 0.5f, 0.9f, 1.0f,
			0.8, 0.8, 0.0, 0.2f, 0.8f, 0.3f, 1.0f,
			-0.8, 0.8, 0.0, 0.9f, 0.2f, 0.5f, 1.0f
		};

		uint32_t ib[]{ 0, 1, 2 };

		uint32_t ib2[]{ 0, 1, 2, 0, 2, 3 };

		_vertexArray.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(sizeof(vb), vb));
		vertexBuffer->SetLayout({
			{ "VertexBuffer", BufferElementType::Float3 },
			{ "ColorBuffer", BufferElementType::Float4 }
		});

		_vertexArray2.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBuffer2;
		vertexBuffer2.reset(VertexBuffer::Create(sizeof(vb2), vb2));
		vertexBuffer2->SetLayout({
			{ "VertexBuffer", BufferElementType::Float3 },
			{ "ColorBuffer", BufferElementType::Float4 }
		});

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(sizeof(ib), ib));

		std::shared_ptr<IndexBuffer> indexBuffer2;
		indexBuffer2.reset(IndexBuffer::Create(sizeof(ib2), ib2));

		_vertexArray->AddVertexBuffer(vertexBuffer);
		_vertexArray->SetIndexBuffer(indexBuffer);

		_vertexArray2->AddVertexBuffer(vertexBuffer2);
		_vertexArray2->SetIndexBuffer(indexBuffer2);

		_basicShader.reset(Shader::Create());
		std::string vertexShader = R"(
		#version 450 core
		layout(location = 0) in vec3 _aPosition;
		layout(location = 1) in vec4 _aColor;
		uniform mat4 _uViewProjection;
		out vec4 _color;
		void main() {
			gl_Position = _uViewProjection * vec4(_aPosition, 1.0);
			_color = _aColor;
		}
		)";
		std::string fragmentShader = R"(
		#version 450 core
		in vec4 _color;
		out vec4 color;
		void main() {
			color = _color;
		}
		)";
		_basicShader->AddShaderSource(vertexShader, ShaderType::Vertex);
		_basicShader->AddShaderSource(fragmentShader, ShaderType::Pixel);
		_basicShader->CompileShaders();

		_camera.reset(new OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f));
		_camera->SetPosition(glm::vec3(0.5f, 0.5f, 0.0f)); // Camera position


	};

	Application::~Application() {
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
			RendererCommand::SetClearColor({ 0.12f, 0.12f, 0.12f, 1.0f });
			RendererCommand::Clear();
			Renderer::BeginScene();
			_basicShader->Bind();
			_basicShader->DefineUniformMat4("_uViewProjection", _camera->GetViewProjectionMatrix());
			Renderer::Submit(_vertexArray2);
			Renderer::Submit(_vertexArray);
			Renderer::EndScene();

			for (auto& layer : *_layerStack)
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