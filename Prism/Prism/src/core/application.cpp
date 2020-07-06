#include <glad/glad.h>
#include <core/application.h>

namespace Prism {

	Application* Application::_singletonInstance = nullptr;

	Application::Application(uint32_t width, uint32_t height, std::string windowTitle) {
		if (_singletonInstance == nullptr) _singletonInstance = this;
		else throw "Only one instance of Application is allowed.";

		CORE_INFO("Creating window W{} H{} titled: {}", width, height, windowTitle);
		_window = Window::Create(WindowProperties{width, height, windowTitle});
		_window->Attach(this);

		Input::_singletonInstance = new Input(); // glfw init before input can be init'd

		_layerStack = std::make_unique<LayerStack>();
		_imguiLayer = std::make_unique<ImGUILayer>();
		_layerStack->PushOverlayUnmanaged(_imguiLayer.get());

		std::string vshader = R"(
			#version 450
			layout(location = 0) in vec3 _pos;
			void main() {
				gl_Position = vec4(_pos, 1.0);
			}
		)";

		std::string fshader = R"(
			#version 450
			layout(location = 0) out vec4 _color;
			void main() {
				_color = vec4(0.2, 0.3, 0.85, 1.0);
			}
		)";

		_basicShader = std::make_unique<Shader>(vshader, fshader);

		float vpos[9]{
			-0.5, -0.5f, 0.0f,
			 0.5, -0.5f, 0.0f,
			 0.0,  0.5f, 0.0f
		};

		uint32_t ind[3]{
			0,1,2
		};

		glCreateVertexArrays(1, &vao);
		glBindVertexArray(vao);

		//glCreateBuffers(1, &vbo);
		//glBindBuffer(GL_ARRAY_BUFFER, vbo);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vpos), vpos, GL_STATIC_DRAW);
		_vertexBuffer.reset(VertexBuffer::Create(sizeof(vpos),vpos));
		_vertexBuffer->Bind();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, 0, sizeof(float) * 3, nullptr);
		_vertexBuffer->Unbind();

		//glCreateBuffers(1, &vio);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vio);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);
		_indexBuffer.reset(IndexBuffer::Create(sizeof(ind), ind));

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

			glClearColor(0.125f, 0.125f, 0.125f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			_basicShader->Bind();
			_vertexBuffer->Bind();
			_indexBuffer->Bind();
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
			_basicShader->Unbind();

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
		if (e->GetEventType() != EventType::MouseMoveEvent) CORE_INFO("Event received: {}", e->GetEventName());

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