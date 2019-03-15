#include "VlkSwapchain.h"

#include "VlkDevice.h"
#include "VlkInstance.h"
#include "VlkSurface.h"
#include "VlkPhysicalDevice.h"
#include "Window.h"

#include "GraphicsEngine.h"
#include "vkGraphicsDevice.h"

#include <vulkan/vulkan_core.h>
#include <windows.h>
#include <vulkan/vulkan_win32.h>

#include <cassert>

namespace Graphics
{
	void VlkSwapchain::Release()
	{
		VlkDevice& device = GraphicsEngine::GetDevice().GetVlkDevice();
		device.DestroySwapchain( m_Swapchain );
	}

	VlkSwapchain::~VlkSwapchain()
	{
		Release();
	}

	void VlkSwapchain::Init( const VlkInstance& instance, const VlkDevice& device, const VlkPhysicalDevice& physicalDevice, const Window& window )
	{
		VkWin32SurfaceCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		createInfo.hwnd = window.GetHandle();
		createInfo.hinstance = GetModuleHandle( nullptr );

		m_Surface = std::make_unique<VlkSurface>();
		m_Surface->Init( instance.CreateSurface( createInfo ), physicalDevice );

		if( !m_Surface->CanPresent() )
		{
			assert( !"Surface cannot present!" );
			return;
		}

		const uint32 presentModeCount = physicalDevice.GetSurfacePresentModeCount( *m_Surface );
		std::vector<VkPresentModeKHR> presentModes{ presentModeCount };
		physicalDevice.GetSurfacePresentModes( *m_Surface, presentModeCount, presentModes.data() );

		VkSurfaceCapabilitiesKHR surfaceCapabilities = m_Surface->GetCapabilities( physicalDevice );

		uint32 swapchain_image_count = 2; //backbuffer count, atleast 2;
		assert( swapchain_image_count < surfaceCapabilities.maxImageCount );

		VkExtent2D extent = surfaceCapabilities.currentExtent;

		

		VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
		swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		swapchainCreateInfo.surface = m_Surface->m_Surface;
		swapchainCreateInfo.minImageCount = surfaceCapabilities.minImageCount;
		swapchainCreateInfo.imageFormat = VK_FORMAT_R8G8B8_UNORM;
		swapchainCreateInfo.imageColorSpace = REPLACE_ME;
		swapchainCreateInfo.imageExtent = extent;
		swapchainCreateInfo.imageArrayLayers = 1;

		if( m_Surface->CanPresent() )
		{
			uint32_t queueIndices[] = { physicalDevice.GetQueueFamilyIndex(), physicalDevice.GetQueueFamilyIndex() };
			swapchainCreateInfo.queueFamilyIndexCount = physicalDevice.GetQueueFamilyIndex();
			swapchainCreateInfo.pQueueFamilyIndices = queueIndices;
			swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		}
		else
		{
			swapchainCreateInfo.queueFamilyIndexCount = 0;
			swapchainCreateInfo.pQueueFamilyIndices = nullptr;
			swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}

		VkSurfaceTransformFlagBitsKHR transformFlags = surfaceCapabilities.currentTransform;
		if( surfaceCapabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR )
			transformFlags = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;

		swapchainCreateInfo.preTransform = transformFlags;

		swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		swapchainCreateInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
		swapchainCreateInfo.clipped = VK_TRUE;

		m_Swapchain = device.CreateSwapchain( swapchainCreateInfo );
	}

	void VlkSwapchain::GetSurfaceCapabilities( VkSurfaceKHR surface, const VlkPhysicalDevice& physicalDevice, VkSurfaceCapabilitiesKHR* pCapabilities )
	{

		//VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR( surface, 0, pCapabilities );
	}

}; //namespace Graphics