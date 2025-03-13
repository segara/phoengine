#include "Graphic/GraphicEngine.h"

#include <stdexcept>

GraphicEngine::GraphicEngine(void* hwnd)
{
    // Metal 디바이스 생성 = opengl HGLRC
      device = MTLCreateSystemDefaultDevice();
      if (!device) {
          throw std::runtime_error("Failed to create Metal device");
      }

    // CAMetalLayer 생성 및 설정 = opengl HDC
    // 현재 프레임 버퍼
    // Attach CAMetalLayer to the NSView
     NSView* view = static_cast<NSView*>(hwnd);
     metalLayer = [CAMetalLayer layer];
     metalLayer.device = device;
     metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
     metalLayer.framebufferOnly = YES; //해당 CAMetalLayer이 GPU 렌더링의 결과물을 저장하기 위한 용도
     metalLayer.frame = view.bounds; //해당 레이어가 화면상의 view 전체
    metalLayer.drawableSize = view.bounds.size;
     view.layer = metalLayer;
     view.wantsLayer = YES;

        //Metal 명령 큐 생성
  
        commandQueue = [device newCommandQueue];
       if (!commandQueue) {
           throw std::runtime_error("Failed to create Metal command queue");
       }

    m_deviceContext = new DeviceContext();
    m_deviceContext->m_mtlDevice = device;
}
GraphicEngine::~GraphicEngine()
{

}
void GraphicEngine::present()
{
   
    
    [renderEncoder endEncoding]; //endEncoding 커맨드 인코딩을 완료합니다.
    
   
    // Commit and present
    [commandBuffer presentDrawable:drawable];
   //이 호출은 현재 프레임의 렌더링 결과를 화면에 표시하도록 Metal에게 요청합니다.
//    presentDrawable은 프레임을 표시하기 위해 Drawable 객체(프레임 버퍼)를 화면 표시 큐에 추가합니다.
//    하지만 실제 실행은 커맨드 버퍼가 GPU에 제출될 때 이루어집니다
    [commandBuffer commit];//커맨드 버퍼를 GPU에 제출하여 실행되도록 합니다.
    [commandBuffer waitUntilCompleted];
}
void GraphicEngine::clear(const simd::float4& color)
{
     // Metal 렌더 패스 설정
     drawable = [metalLayer nextDrawable];
     if (!drawable) return;

     // Create a render pass descriptor
    //렌더링 패스를 정의
    //GPU가 데이터를 받아 화면을 렌더링하는 과정을 하나의 패스로 관리

//    렌더 패스 디스크립터 (MTLRenderPassDescriptor)
//    렌더링 패스에 필요한 입출력 상태를 정의하는 객체입니다.
//    색상 어태치먼트 (colorAttachments)
//    렌더링 결과를 출력할 텍스처입니다.
//    깊이/스텐실 어태치먼트 (depth/stencilAttachments)
//    깊이(depth) 및 스텐실(stencil) 버퍼 설정입니다.
//    로드 액션 (MTLLoadAction)
//    렌더링 시작 시 버퍼의 초기화 상태를 설정합니다.
//    MTLLoadActionClear: 버퍼를 특정 색으로 초기화
//    MTLLoadActionLoad: 버퍼의 기존 내용을 유지
//    MTLLoadActionDontCare: 초기 상태를 신경 쓰지 않음
//    스토어 액션 (MTLStoreAction)
//    렌더링이 끝난 후 버퍼를 어떻게 처리할지를 설정합니다.
//    MTLStoreActionStore: 결과를 저장
//    MTLStoreActionDontCare: 결과를 무시
     MTLRenderPassDescriptor* passDescriptor = [MTLRenderPassDescriptor renderPassDescriptor];
     passDescriptor.colorAttachments[0].texture = drawable.texture;
     passDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
     passDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(color.x, color.y, color.z, color.w);
     passDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;

     // Create a command buffer
     commandBuffer = [commandQueue commandBuffer];

     // Create a render command encoder
     renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:passDescriptor];
    
    m_deviceContext->m_renderEncoder = renderEncoder;

}
