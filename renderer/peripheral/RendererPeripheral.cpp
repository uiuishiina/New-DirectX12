#include"CommandAllocator.h"
#include"CommandList.h"
#include"SwapChain.h"
#include"RenderTarget.h"

#include"../core/DXGI.h"
#include"../core/Device.h"
#include"../core/CommandQueue.h"
#include"../core/Fence.h"

#include"../core/RendererCore.h"
#include"RendererPeripheral.h"
#include"../../Debug/Debug.h"

#define CHECK(expr) \
    if (!(expr)) { \
        LOG_ERROR(LOG_CONTEXT(), LOG_HEADER(Message,#expr)); \
        return false; \
    }

namespace {
    const D3D12_COMMAND_LIST_TYPE command_type = D3D12_COMMAND_LIST_TYPE_DIRECT;
}

RendererPeripheral::RendererPeripheral() = default;
RendererPeripheral::~RendererPeripheral() = default;

//---------------------------------------------------------------------------------------------------

[[nodiscard]] bool RendererPeripheral::initalize(RendererCore* core, const windowContext& context, const int& buffercount) {

    renderer_core = core;

    allocator_ = std::make_unique<CommandAllocator>();
    CHECK(allocator_->create_command_allocator(renderer_core->get_Device()->get_device(), buffercount, command_type));


    list_ = std::make_unique<CommandList>();
    CHECK(list_->create_command_list(renderer_core->get_Device()->get_device(), 
        allocator_->get_command_allocator(0), command_type));


    swapchain_ = std::make_unique<SwapChain>();
    const auto [w, h] = context.size;
    CHECK(swapchain_->create_swapchain(renderer_core->get_DXGI()->get_factory(), renderer_core->get_CommandQueue()->get_queue(),
        context.hwnd, w, h, buffercount));

    render_target_ = std::make_unique<RenderTarget>();


    LOG_INFO(LOG_HEADER(Message, "RendererPeripheral SUCSSECED"));
    return true;
}

//---------------------------------------------------------------------------------------------------