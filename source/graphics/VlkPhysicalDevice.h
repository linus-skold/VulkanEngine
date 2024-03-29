#pragma once
#include <Core/Defines.h>
#include <Core/Types.h>
#include <Core/containers/GrowingArray.h>

#include "IGfxObject.h"

#include <vulkan/vulkan_core.h>

DEFINE_HANDLE(VkPhysicalDevice);
DEFINE_HANDLE(VkDevice);

struct VkDeviceCreateInfo;
namespace Graphics
{
	class VlkInstance;
	class VlkSurface;

	struct QueueProperties
	{
		int32 queueIndex = -1;
		int32 familyIndex = -1;
	};

	class VlkPhysicalDevice
	{
	public:
		VlkPhysicalDevice();
		~VlkPhysicalDevice();

		void Init(VlkInstance* instance);

		uint32 GetQueueFamilyIndex() const { return m_QueueFamilyIndex; }

		VkDevice CreateDevice(const VkDeviceCreateInfo& createInfo) const;

		void GetSurfaceInfo(VkSurfaceKHR pSurface, bool* canPresent, Core::GrowingArray<VkSurfaceFormatKHR>& formats,
							Core::GrowingArray<VkPresentModeKHR>& presentModes, VkSurfaceCapabilitiesKHR* capabilities);

		QueueProperties FindFamilyIndices(VlkSurface* pSurface);
		VkPhysicalDevice GetDevice() { return m_PhysicalDevice; }

		uint32 FindMemoryType(uint32 typeFilter, VkMemoryPropertyFlags flags);

		VkFormat FindSupportedFormat(const Core::GrowingArray<VkFormat>& formats, VkImageTiling tilingOption,
									 VkFormatFeatureFlags features);

		VkFormat FindDepthFormat();

	private:
		bool SurfaceCanPresent(VkSurfaceKHR pSurface) const;
		uint32 GetSurfacePresentModeCount(VkSurfaceKHR pSurface) const;
		void GetSurfacePresentModes(VkSurfaceKHR pSurface, uint32 presentModeCount,
									VkPresentModeKHR* presentModes) const;
		void GetSurfaceFormats(VkSurfaceKHR pSurface, uint32 formatCount, VkSurfaceFormatKHR* formats) const;
		uint32 GetSurfaceFormatCount(VkSurfaceKHR pSurface) const;
		VkSurfaceCapabilitiesKHR GetSurfaceCapabilities(VkSurfaceKHR pSurface) const;

		VkPhysicalDevice m_PhysicalDevice = nullptr;
		uint32 m_QueueFamilyIndex = 0;
		uint32 m_PresentFamily = 0;

		Core::GrowingArray<VkQueueFamilyProperties> m_QueueProperties;
	};

}; // namespace Graphics
