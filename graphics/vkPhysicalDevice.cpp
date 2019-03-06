#include "vkPhysicalDevice.h"

#include "vkInstance.h"


#include <vulkan/vulkan_core.h>

#include <cassert>
#include <vector>

namespace Graphics
{
	vkPhysicalDevice::~vkPhysicalDevice()
	{
		
	}

	void vkPhysicalDevice::Init(vkInstance* instance)
	{
		uint32 device_count = 0;
		VkResult result = vkEnumeratePhysicalDevices(instance->get(), &device_count, nullptr);
		assert(result == VK_SUCCESS && "Failed to enumerate device!");

		std::vector<VkPhysicalDevice> devices{ device_count };
		result = vkEnumeratePhysicalDevices(instance->get(), &device_count, devices.data());
		assert(result == VK_SUCCESS && "Failed to enumerate device!");

		for (auto device : devices)
		{
			uint32 property_count = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(device, &property_count, nullptr);

			std::vector<VkQueueFamilyProperties> queue_properties{ property_count };
			vkGetPhysicalDeviceQueueFamilyProperties(device, &property_count, queue_properties.data());

			for (size_t i = 0; i < queue_properties.size(); ++i)
			{
				const VkQueueFamilyProperties& property = queue_properties[i];
				if (property.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				{
					if (!m_PhysicalDevice)
						m_PhysicalDevice = device;

					
					m_QueueFamilyIndex = (uint32)i;

					break;
				}
			}
		}
				
		assert(m_PhysicalDevice);

	}

}; //namespace Graphics