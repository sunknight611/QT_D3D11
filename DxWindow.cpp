#include "DxWindow.h"

double countsPerSecond = 0.0;
__int64 CounterStart = 0;

int frameCount = 0;
int fps = 0;

__int64 frameTimeOld = 0;
double frameTime;

DxWindow::DxWindow(QWidget* parent)
    : QWidget(parent)
{
    QWidget::setAttribute(Qt::WA_PaintOnScreen);//允许DX渲染
    QWidget::setAttribute(Qt::WA_NativeWindow, true);
    setFocusPolicy(Qt::WheelFocus);//允许按键时间
    setMouseTracking(true);//允许鼠标移动

   // Init3D();
   //RenderInit();
    m_hwnd = (HWND)winId();
    m_Graphics = new GraphicsClass;
    
    m_Input = new InputClass;

    m_Graphics->Initialize(width() * 20, height() * 20, m_hwnd);

    /*wchar_t char1[10];
    _itow_s(width(), char1, 10, 10);

    MessageBox(m_hwnd, char1, NULL, MB_OK);*/
}

DxWindow::~DxWindow()
{
    m_Graphics->Shutdown();
}

void startFPStimer()
{
    LARGE_INTEGER frequencyCount;
    QueryPerformanceFrequency(&frequencyCount);

    countsPerSecond = double(frequencyCount.QuadPart);

    QueryPerformanceCounter(&frequencyCount);
    CounterStart = frequencyCount.QuadPart;
}

double getTime()
{
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);
    return double(currentTime.QuadPart - CounterStart) / countsPerSecond;
}

//获取每帧间隔时间
double getFrameTime()
{
    LARGE_INTEGER currentTime;
    __int64 tickCount;
    QueryPerformanceCounter(&currentTime);

    tickCount = currentTime.QuadPart - frameTimeOld;
    frameTimeOld = currentTime.QuadPart;

    if (tickCount < 0.0f)
        tickCount = 0.0f;

    return float(tickCount) / countsPerSecond;
}


void DxWindow::paintEvent(QPaintEvent* event)
{
    if (isModify) {
        m_Graphics->setModel(filepath);
        isModify = false;
    }
    
    if (renderMode == 1) {
      m_Graphics->cam_angle = angle;
      m_Graphics->setLightColor(lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
      m_Graphics->setRasterizerState(RasterizerState);
      if (RasterizerState == 1) {
          m_Graphics->setTex(texpath);
       }
       m_Graphics->setSpec(isSpec);
    
    //更新场景和渲染场景
      if (isback) 
        m_Graphics->RenderBack();
      else {
        if (isFirstOpen) {
           m_Graphics->setModel(filepath);
           isFirstOpen = false;
        }     
        m_Graphics->Frame();
       }
    }else if (renderMode == 2) {
        if (RasterizerState == 1) {
          m_Graphics->cam_angle = angle;
          m_Graphics->light_angle = lightangle;
          m_Graphics->setModel(filepath);
          m_Graphics->setTex(texpath);
          m_Graphics->setLightColor(lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
          m_Graphics->setRasterizerState(RasterizerState);
          m_Graphics->setSpec(isSpec);
          m_Graphics->FrameWater(filepath,texpath);
        }      
    }
    else if (renderMode == 3) {
        if (RasterizerState == 1) {
            m_Graphics->setModel(filepath);
            m_Graphics->setTex(texpath);
            m_Graphics->setLightColor(lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
            m_Graphics->setRasterizerState(RasterizerState);
            m_Graphics->setSpec(isSpec);
            m_Graphics->FrameFire(filepath, texpath);
        }
    }
    
    
    //保证此函数体每一帧都调用
     //MessageBox(m_hwnd, L"1", NULL, MB_OK);
     update();
}


void DxWindow::resize(QResizeEvent* event)
{
    //ResizeD3D();
    m_Graphics->Resize(width(), height());
}

void DxWindow::Init3D()
{
    HRESULT hr;//可以理解为带各种返回值的bool变量，如果函数运行正常，这个值返回的是十六进制的0x0000,其余错误代码均是十六进制标识，对应错误网上可以搜到

    DXGI_MODE_DESC bufferDesc;//Dx用来描述 后台缓冲区 的结构体

    ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));//这个宏就是用来把Dx描述结构体，里面的变量全部给个0

    bufferDesc.Width = width();         //QT自带的获取窗口宽度的方法// 后台缓冲区宽度
    bufferDesc.Height = height();       //QT自带的获取窗口高度的方法// 后台缓冲区高度
    bufferDesc.RefreshRate.Numerator = 60;              //（注释1）  显示最大的刷新率  刷新率如果是  60pfs/每1秒
    bufferDesc.RefreshRate.Denominator = 1;             //（注释1）  显示最大刷新率
    bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;                     // 后台缓冲区像素格式
    bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //ScanlineOrdering:用于描述扫描线绘制模式的枚举。可以设置为0
    bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;                 //用于描述缩放形式的枚举类型，默认使用DXGI_MODE_SCALING_UNSPECIFIED。


    DXGI_SWAP_CHAIN_DESC swapChainDesc;//Dx用来描述交换缓冲区的结构体

    ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));  //上面有解释啦

    swapChainDesc.BufferDesc = bufferDesc;                          //多重采样数量和质量级别
    swapChainDesc.SampleDesc.Count = 1;                             //（注释2）多重采样的结构体描述
    swapChainDesc.SampleDesc.Quality = 0;                           //（注释2）多重采样的结构体描述
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    //设为 DXGI_USAGE_RENDER_TARGET_OUTPUT，因为我们要将 场景渲染到后台缓冲区
    swapChainDesc.BufferCount = 1;                                  //交换链中的后台缓冲区数量；我们一般只用一个后台缓冲区来实现双 缓存。当然，你也可以使用两个后台缓冲区来实现三缓存。
    swapChainDesc.OutputWindow = (HWND)winId();                     //这个非常重要，winId()是Qt中QWidget获取操作句柄的函数，这里表示我们把当前QWidget的控制权交给了DX，让DX去管理这个句柄
    swapChainDesc.Windowed = TRUE;                                  //当设为 true 时，程序以窗口模式运行；当设为 false 时，程序以全屏模式运行
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;            //设为 DXGI_SWAP_EFFECT_DISCARD，让显卡驱动程序选择最高效 的显示模式
    


    //（注释3）这是一个最新的方法，用来同时创建设备、设备上下文和交换链，这个非常方便
    hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
        D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, NULL, &m_deviceContex);

    //创建缓冲区图片，可以简单理解为就是一张前台缓冲的图片，我们Dx在后台缓冲区算出来一张图片之后，需要通过Swap交换到前台来，相当于将后台的图片在窗口中显示了出来，而这个显示出来的其实本质就是一张图片
    ID3D11Texture2D* backBuffer;
    //这个方法用来获取后台缓冲区的指针，把第一个后台缓冲区和这个缓冲区连接起来
    hr = m_swapChain->GetBuffer(0,      //后台缓冲的索引值，一般是0.之所以有这个是因为后台缓冲可以有很多个
        __uuidof(ID3D11Texture2D),//这是参数接口的类型
        (void**)&backBuffer);       //目标渲染视图的图片


//这里真正的创建了目标渲染试图，就是平时我们肉眼所看到的显示的那个界面viewport，把后台缓冲区
    hr = m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);

    SafeDel(backBuffer)       //（注释4）这个非常重要，宏是我为了安全释放COM自定义的
            //每调用一次GetBuffer 方法，后台缓冲区的 COM 引用计数就会 向上递增一次，这便是我们在代码片段的结尾处释放它的原因
            //这个不释放你会发现绘制不了shader，但是却可以clear屏幕颜色哦


    //下面就是创建深度模板缓冲区,创建过程和目标渲染视图基本一样，这里仅对不一样的参数做下注解
        D3D11_TEXTURE2D_DESC depthStencilDesc;

    depthStencilDesc.Width = (uint)width();
    depthStencilDesc.Height = (uint)height();
    depthStencilDesc.MipLevels = 1;     //mipLevels要生成几级，1表示多采样纹理，0表示会生成一整套的mipMap，这里不需要mip所以写1
    depthStencilDesc.ArraySize = 1;     //纹理数组中的纹理数量，比如立方体贴图由六个面，这边就可以设置为6，或者6的倍数
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;        //纹理格式
    depthStencilDesc.SampleDesc.Count = 1;
    depthStencilDesc.SampleDesc.Quality = 0;
    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;   //绑定标识符，描述这个是一个深度模板缓冲图片，其实这个结构体就是个普通的2D纹理声明的结构体
    depthStencilDesc.CPUAccessFlags = 0;            //这个没有搞懂，后续弄懂了补充更新文章吧，有大佬知道的欢迎评论区补充下谢谢，大概是允许CPU访问的
    depthStencilDesc.MiscFlags = 0;                 //这个是控制上面那个CPU访问的

    //在GPU上根据上面那个描述创建一块用于纹理储存的内存Buffer
    hr = m_device->CreateTexture2D(&depthStencilDesc, NULL, &m_depthStencilBuffer);
    //把这个buffer绑定给视口
    hr = m_device->CreateDepthStencilView(m_depthStencilBuffer, NULL, &m_depthStencilView);


    //把目标渲染视口和深度模板关联起来
    m_deviceContex->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);


    //第四步，设置视口大小，D3D11默认不会设置视口，此步骤必须手动设置
    viewport.TopLeftX = 0;          //视口左上角的横坐标
    viewport.TopLeftY = 0;          //视口左上角的总坐标
    viewport.Width = width();         //宽
    viewport.Height = height();       //高
    viewport.MinDepth = 0.0f;       //深度缓存最小值0，dx里深度值是0到1范围内的，所以下限值是0
    viewport.MaxDepth = 1.0f;       //深度值最大值1，

    //刷新重置下viewport
    m_deviceContex->RSSetViewports(1, &viewport);
}

void DxWindow::ResizeD3D()
{
    SafeDel(m_renderTargetView)
    SafeDel(m_depthStencilView)
    SafeDel(m_depthStencilBuffer)

        HRESULT hr;
    hr = m_swapChain->ResizeBuffers(1, width(), height(), DXGI_FORMAT_R8G8B8A8_UNORM, 0);
    //Create our BackBuffer
    ID3D11Texture2D* backBuffer;
    hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

    //Create our Render Target
    hr = m_device->CreateRenderTargetView(backBuffer, NULL, &m_renderTargetView);
    SafeDel(backBuffer)

    D3D11_TEXTURE2D_DESC depthStencilDesc;

    depthStencilDesc.Width = (uint)width();
    depthStencilDesc.Height = (uint)height();
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.ArraySize = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilDesc.SampleDesc.Count = 1;
    depthStencilDesc.SampleDesc.Quality = 0;
    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilDesc.CPUAccessFlags = 0;
    depthStencilDesc.MiscFlags = 0;

    hr = m_device->CreateTexture2D(&depthStencilDesc, NULL, &m_depthStencilBuffer);
    hr = m_device->CreateDepthStencilView(m_depthStencilBuffer, NULL, &m_depthStencilView);

    m_deviceContex->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = width();
    viewport.Height = height();
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    m_deviceContex->RSSetViewports(1, &viewport);
}

void DxWindow::RenderInit()
{

}

void DxWindow::RenderUpdate()
{
    m_deviceContex->ClearRenderTargetView(m_renderTargetView, bgcolor);
}

void DxWindow::setLightColor(float red, float green, float blue, float alpha)
{
    lightColor[0] = red;
    lightColor[1] = green;
    lightColor[2] = blue;
    lightColor[3] = alpha;
}

void DxWindow::setRaster(int state)
{
    RasterizerState = state;
}

void DxWindow::setSpec(bool isSpec)
{
    this->isSpec = isSpec;
}
