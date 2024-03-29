#pragma once
#include "Core/Defines.h"
#include "GraphicsDecl.h"
#include <vector>
DEFINE_HANDLE( VkInstance );
DEFINE_HANDLE(VkSurfaceKHR);
DEFINE_HANDLE(VkPhysicalDevice)
struct VkWin32SurfaceCreateInfoKHR;
namespace Graphics
{
	class VlkInstance
	{
	public:
		VlkInstance() = default;
		~VlkInstance();

		void Init();
		void Release();

		VkSurfaceKHR CreateSurface( const VkWin32SurfaceCreateInfoKHR& createInfo ) const;
		upVlkSurface CreateSurface( const VkWin32SurfaceCreateInfoKHR& createInfo, VlkPhysicalDevice* physicalDevice ) const;
		void DestroySurface( VkSurfaceKHR pSurface );


		void GetPhysicalDevices(std::vector<VkPhysicalDevice>& deviceList);

		VkInstance GetVKInstance() { return m_Instance; }

	private:
		VkInstance m_Instance = nullptr;

	};

}; //namespace Graphics