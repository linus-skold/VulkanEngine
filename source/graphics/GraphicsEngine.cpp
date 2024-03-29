#include "GraphicsEngine.h"
#include "Window.h"

#include <cassert>

#ifdef _WIN32
#include <d3d11.h>
#include <Windows.h>
#endif

#include "vkGraphicsDevice.h"

#include "imgui/imgui.h"

constexpr float BLACK[4] = { 0.f, 0.f, 0.f, 0.f };

namespace Graphics
{
	void CreateImGuiContext()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
	}

	std::unique_ptr<GraphicsEngine> GraphicsEngine::m_Instance = nullptr;

	GraphicsEngine::GraphicsEngine() {}

	void GraphicsEngine::Create() { m_Instance = std::make_unique<GraphicsEngine>(); }

	GraphicsEngine& GraphicsEngine::Get() { return *m_Instance; }

	bool GraphicsEngine::Init( const Window& window )
	{
		m_Device = std::make_unique<vkGraphicsDevice>();

		if( !m_Device->Init( window ) )
		{
			return false;
		}

		return true;
	}

	void GraphicsEngine::Present( float dt ) { m_Device->DrawFrame( dt ); }

	Camera* GraphicsEngine::GetCamera() { return m_Device->GetCamera(); }

	void GraphicsEngine::BeginFrame() {}

	GraphicsEngine::~GraphicsEngine() {}

}; // namespace Graphics
