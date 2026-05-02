#include"DXGI.h"
#include"Device.h"
#include"CommandQueue.h"
#include"Fence.h"

#include"RendererCore.h"
#include"../../Debug/Debug.h"

#define CHECK(expr) \
    if (!(expr)) { \
        LOG_ERROR(LOG_CONTEXT(), LOG_HEADER(Message,#expr)); \
        return false; \
    }

namespace {
    const D3D12_COMMAND_LIST_TYPE command_type = D3D12_COMMAND_LIST_TYPE_DIRECT;
}

RendererCore::RendererCore() = default;
RendererCore::~RendererCore() = default;

//---------------------------------------------------------------------------------------------------

[[nodiscard]] bool RendererCore::initalize() {

    dxgi_ = std::make_unique<DXGI>();
    CHECK(dxgi_->initialize_DXGI());

    device_ = std::make_unique<Device>();
    CHECK(device_->create_device(dxgi_->get_adapter()));

    queue_ = std::make_unique<CommandQueue>();
    CHECK(queue_->create_queue(device_->get_device(), command_type));

    fence_ = std::make_unique<Fence>();
    CHECK(fence_->create_fence(device_->get_device()));

    LOG_INFO(LOG_HEADER(Message,"RendererCore SUCSSESD"));
    return true;
}

//---------------------------------------------------------------------------------------------------

[[nodiscard]] DXGI* RendererCore::get_DXGI()const noexcept {
    ASSERT(dxgi_);
    return dxgi_.get();
}

[[nodiscard]] Device* RendererCore::get_Device()const noexcept {
    ASSERT(device_);
    return device_.get();
}

[[nodiscard]] CommandQueue* RendererCore::get_CommandQueue()const noexcept {
    ASSERT(queue_);
    return queue_.get();
}

[[nodiscard]] Fence* RendererCore::get_fence()const noexcept {
    ASSERT(fence_);
    return fence_.get();
}