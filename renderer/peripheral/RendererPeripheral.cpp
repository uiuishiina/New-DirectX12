#include"CommandAllocator.h"
#include"CommandList.h"
#include"SwapChain.h"
#include"RenderTarget.h"

#include"../base/DescriptorHeap.h"

#include"../core/DXGI.h"
#include"../core/Device.h"
#include"../core/CommandQueue.h"
#include"../core/Fence.h"

#include"../../window/window.h"

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

	[[nodiscard]] D3D12_RESOURCE_BARRIER resource_Barrier(ID3D12Resource* resource, D3D12_RESOURCE_STATES from, D3D12_RESOURCE_STATES to) noexcept {
		D3D12_RESOURCE_BARRIER barrier{};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = resource;
		barrier.Transition.StateBefore = from;
		barrier.Transition.StateAfter = to;
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

		return barrier;
	}
}

RendererPeripheral::RendererPeripheral() = default;
RendererPeripheral::~RendererPeripheral() {
	LOG_INFO(LOG_HEADER(Message, "~RendererPeripheral()"),LOG_VALUE(frameFenceValue_[0]));
}

//---------------------------------------------------------------------------------------------------

[[nodiscard]] bool RendererPeripheral::initalize(RendererCore* core, windowBase* window, const int& buffercount) {

    renderer_core = core;

    auto device = renderer_core->get_Device()->get_device();
	const auto [w, h] = window->get_size();
	const auto hwnd = window->get_hwnd();

    allocator_ = std::make_unique<CommandAllocator>();
    CHECK(allocator_->create_command_allocator(device, buffercount, command_type));


    list_ = std::make_unique<CommandList>();
    CHECK(list_->create_command_list(device, allocator_->get_command_allocator(0), command_type));


    swapchain_ = std::make_unique<SwapChain>();
    CHECK(swapchain_->create_swapchain(renderer_core->get_DXGI()->get_factory(), renderer_core->get_CommandQueue()->get_queue(),
		hwnd, w, h, buffercount));

    rtv_heap_ = std::make_unique<DescriptorHeap>();
    CHECK(rtv_heap_->create_heap(device, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 3, false));

    render_target_ = std::make_unique<RenderTarget>();
    CHECK(render_target_->create_render_target(device, swapchain_->get_swapchain(),
        rtv_heap_->get_heap(), buffercount));

	frameFenceValue_.resize(buffercount, 0);

    LOG_INFO(LOG_HEADER(Message, "RendererPeripheral SUCSSECED"));
    return true;
}

//---------------------------------------------------------------------------------------------------

void RendererPeripheral::update() {
	const auto backBufferIndex = swapchain_->get_swapchain()->GetCurrentBackBufferIndex();

	if (frameFenceValue_[backBufferIndex] != 0) {
		renderer_core->get_fence()->wait_event(frameFenceValue_[backBufferIndex]);
	}

	allocator_->reset_command_allocator(backBufferIndex);

	list_->reset_command_list(allocator_->get_command_allocator(backBufferIndex));

	auto pToRT = resource_Barrier(render_target_->get_render_target(backBufferIndex), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	list_->get_command_list()->ResourceBarrier(1, &pToRT);

	D3D12_CPU_DESCRIPTOR_HANDLE handles[] = { render_target_->get_rtv_handle(backBufferIndex) };
	list_->get_command_list()->OMSetRenderTargets(1, handles, false, nullptr);

	const float clearColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };  // 黒でクリア
	list_->get_command_list()->ClearRenderTargetView(handles[0], clearColor, 0, nullptr);

	
	// ビューポート設定
	D3D12_VIEWPORT viewport{};
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = 1280.0f;
	viewport.Height = 720.0f;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	list_->get_command_list()->RSSetViewports(1, &viewport);

	// シザー矩形設定
	D3D12_RECT scissorRect{};
	scissorRect.left = 0;
	scissorRect.top = 0;
	scissorRect.right = 1280;
	scissorRect.bottom = 720;
	list_->get_command_list()->RSSetScissorRects(1, &scissorRect);

	// リソースバリアでレンダーターゲットを RenderTarget から Present へ変更
	auto rtToP = resource_Barrier(render_target_->get_render_target(backBufferIndex), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	list_->get_command_list()->ResourceBarrier(1, &rtToP);

	// コマンドリストをクローズ
	list_->get_command_list()->Close();

	// コマンドキューにコマンドリストを送信
	ID3D12CommandList* ppCommandLists[] = { list_->get_command_list() };
	renderer_core->get_CommandQueue()->get_queue()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	// プレゼント
	swapchain_->get_swapchain()->Present(1, 0);

	const auto nextFenceValue = renderer_core->get_fence()->signal(renderer_core->get_CommandQueue()->get_queue());
	frameFenceValue_[backBufferIndex] = nextFenceValue;
}

void RendererPeripheral::end() {
	for (auto& fenceValue : frameFenceValue_) {
		if (fenceValue != 0) {
			renderer_core->get_fence()->wait_event(fenceValue);
		}
	}
	LOG_INFO(LOG_HEADER(Message, "Renderer cleanup completed. All GPU tasks have finished."));
	LOG_INFO(LOG_VALUE(renderer_core->get_fence()->get_completed_value()));
}