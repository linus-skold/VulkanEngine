#pragma once

#include "Core/Defines.h"
#include <memory>
LPE_DEFINE_HANDLE( VkSwapchainKHR );
LPE_DEFINE_HANDLE( VkSurfaceKHR );
struct VkSurfaceCapabilitiesKHR;
struct VkSurfaceFormatKHR;

class Window;
namespace Graphics
{
	class VlkDevice;
	class VlkPhysicalDevice;
	class VlkInstance;
	class VlkSurface;

	class VlkSwapchain 
	{
	public:
		VlkSwapchain();
		~VlkSwapchain();
		void Release();

		void Init( VlkInstance* instance, VlkDevice* device, VlkPhysicalDevice* physicalDevice, const Window& window );

	private:

		std::unique_ptr<VlkSurface> m_Surface;
		VkSwapchainKHR m_Swapchain;
	};

}; //namespace Graphics