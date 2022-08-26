#pragma once

#include <core/DeviceProp.h>

#include <utils/DPCPP.h>
#include <utils/Macros.h>

namespace xpu {
namespace dpcpp {

using DeviceId = at::DeviceIndex;

int dpcppGetDeviceCount(int* deviceCount);

int dpcppGetDevice(DeviceId* pDI);

int dpcppSetDevice(DeviceId device_id);

int dpcppGetDeviceIdFromPtr(DeviceId* device_id, void* ptr);

sycl::device dpcppGetRawDevice(DeviceId device_id);

DeviceProp* dpcppGetCurrentDeviceProperties();

DeviceProp* dpcppGetDeviceProperties(DeviceId device_id = -1);

sycl::context dpcppGetDeviceContext(DeviceId device_id = -1);

std::vector<int>& dpcppGetDeviceIdListForCard(int card_id = -1);
} // namespace dpcpp
} // namespace xpu