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
    QWidget::setAttribute(Qt::WA_PaintOnScreen);//����DX��Ⱦ
    QWidget::setAttribute(Qt::WA_NativeWindow, true);
    setFocusPolicy(Qt::WheelFocus);//������ʱ��
    setMouseTracking(true);//��������ƶ�

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

//��ȡÿ֡���ʱ��
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
    
    //���³�������Ⱦ����
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
    
    
    //��֤�˺�����ÿһ֡������
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
    HRESULT hr;//�������Ϊ�����ַ���ֵ��bool��������������������������ֵ���ص���ʮ�����Ƶ�0x0000,�������������ʮ�����Ʊ�ʶ����Ӧ�������Ͽ����ѵ�

    DXGI_MODE_DESC bufferDesc;//Dx�������� ��̨������ �Ľṹ��

    ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));//��������������Dx�����ṹ�壬����ı���ȫ������0

    bufferDesc.Width = width();         //QT�Դ��Ļ�ȡ���ڿ�ȵķ���// ��̨���������
    bufferDesc.Height = height();       //QT�Դ��Ļ�ȡ���ڸ߶ȵķ���// ��̨�������߶�
    bufferDesc.RefreshRate.Numerator = 60;              //��ע��1��  ��ʾ����ˢ����  ˢ���������  60pfs/ÿ1��
    bufferDesc.RefreshRate.Denominator = 1;             //��ע��1��  ��ʾ���ˢ����
    bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;                     // ��̨���������ظ�ʽ
    bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //ScanlineOrdering:��������ɨ���߻���ģʽ��ö�١���������Ϊ0
    bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;                 //��������������ʽ��ö�����ͣ�Ĭ��ʹ��DXGI_MODE_SCALING_UNSPECIFIED��


    DXGI_SWAP_CHAIN_DESC swapChainDesc;//Dx�������������������Ľṹ��

    ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));  //�����н�����

    swapChainDesc.BufferDesc = bufferDesc;                          //���ز�����������������
    swapChainDesc.SampleDesc.Count = 1;                             //��ע��2�����ز����Ľṹ������
    swapChainDesc.SampleDesc.Quality = 0;                           //��ע��2�����ز����Ľṹ������
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    //��Ϊ DXGI_USAGE_RENDER_TARGET_OUTPUT����Ϊ����Ҫ�� ������Ⱦ����̨������
    swapChainDesc.BufferCount = 1;                                  //�������еĺ�̨����������������һ��ֻ��һ����̨��������ʵ��˫ ���档��Ȼ����Ҳ����ʹ��������̨��������ʵ�������档
    swapChainDesc.OutputWindow = (HWND)winId();                     //����ǳ���Ҫ��winId()��Qt��QWidget��ȡ��������ĺ����������ʾ���ǰѵ�ǰQWidget�Ŀ���Ȩ������DX����DXȥ����������
    swapChainDesc.Windowed = TRUE;                                  //����Ϊ true ʱ�������Դ���ģʽ���У�����Ϊ false ʱ��������ȫ��ģʽ����
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;            //��Ϊ DXGI_SWAP_EFFECT_DISCARD�����Կ���������ѡ�����Ч ����ʾģʽ
    


    //��ע��3������һ�����µķ���������ͬʱ�����豸���豸�����ĺͽ�����������ǳ�����
    hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
        D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, NULL, &m_deviceContex);

    //����������ͼƬ�����Լ����Ϊ����һ��ǰ̨�����ͼƬ������Dx�ں�̨�����������һ��ͼƬ֮����Ҫͨ��Swap������ǰ̨�����൱�ڽ���̨��ͼƬ�ڴ�������ʾ�˳������������ʾ��������ʵ���ʾ���һ��ͼƬ
    ID3D11Texture2D* backBuffer;
    //�������������ȡ��̨��������ָ�룬�ѵ�һ����̨�������������������������
    hr = m_swapChain->GetBuffer(0,      //��̨���������ֵ��һ����0.֮�������������Ϊ��̨��������кܶ��
        __uuidof(ID3D11Texture2D),//���ǲ����ӿڵ�����
        (void**)&backBuffer);       //Ŀ����Ⱦ��ͼ��ͼƬ


//���������Ĵ�����Ŀ����Ⱦ��ͼ������ƽʱ������������������ʾ���Ǹ�����viewport���Ѻ�̨������
    hr = m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);

    SafeDel(backBuffer)       //��ע��4������ǳ���Ҫ��������Ϊ�˰�ȫ�ͷ�COM�Զ����
            //ÿ����һ��GetBuffer ��������̨�������� COM ���ü����ͻ� ���ϵ���һ�Σ�����������ڴ���Ƭ�εĽ�β���ͷ�����ԭ��
            //������ͷ���ᷢ�ֻ��Ʋ���shader������ȴ����clear��Ļ��ɫŶ


    //������Ǵ������ģ�建����,�������̺�Ŀ����Ⱦ��ͼ����һ����������Բ�һ���Ĳ�������ע��
        D3D11_TEXTURE2D_DESC depthStencilDesc;

    depthStencilDesc.Width = (uint)width();
    depthStencilDesc.Height = (uint)height();
    depthStencilDesc.MipLevels = 1;     //mipLevelsҪ���ɼ�����1��ʾ���������0��ʾ������һ���׵�mipMap�����ﲻ��Ҫmip����д1
    depthStencilDesc.ArraySize = 1;     //���������е�����������������������ͼ�������棬��߾Ϳ�������Ϊ6������6�ı���
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;        //�����ʽ
    depthStencilDesc.SampleDesc.Count = 1;
    depthStencilDesc.SampleDesc.Quality = 0;
    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;   //�󶨱�ʶ�������������һ�����ģ�建��ͼƬ����ʵ����ṹ����Ǹ���ͨ��2D���������Ľṹ��
    depthStencilDesc.CPUAccessFlags = 0;            //���û�и㶮������Ū���˲���������°ɣ��д���֪���Ļ�ӭ������������лл�����������CPU���ʵ�
    depthStencilDesc.MiscFlags = 0;                 //����ǿ��������Ǹ�CPU���ʵ�

    //��GPU�ϸ��������Ǹ���������һ��������������ڴ�Buffer
    hr = m_device->CreateTexture2D(&depthStencilDesc, NULL, &m_depthStencilBuffer);
    //�����buffer�󶨸��ӿ�
    hr = m_device->CreateDepthStencilView(m_depthStencilBuffer, NULL, &m_depthStencilView);


    //��Ŀ����Ⱦ�ӿں����ģ���������
    m_deviceContex->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);


    //���Ĳ��������ӿڴ�С��D3D11Ĭ�ϲ��������ӿڣ��˲�������ֶ�����
    viewport.TopLeftX = 0;          //�ӿ����Ͻǵĺ�����
    viewport.TopLeftY = 0;          //�ӿ����Ͻǵ�������
    viewport.Width = width();         //��
    viewport.Height = height();       //��
    viewport.MinDepth = 0.0f;       //��Ȼ�����Сֵ0��dx�����ֵ��0��1��Χ�ڵģ���������ֵ��0
    viewport.MaxDepth = 1.0f;       //���ֵ���ֵ1��

    //ˢ��������viewport
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
