#ifndef _DXWINDOW_H_
#define _DXWINDOW_H_
#include <QWidget>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")


#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include<d3dcompiler.h>
#include<string>

#include"graphicsclass.h"
#include"inputclass.h"

#define SafeDel(obj)    \
    obj->Release();     \
    obj=0;              \


class DxWindow : public QWidget
{
	Q_OBJECT

public:
	DxWindow(QWidget* parent = nullptr);
	~DxWindow();

	QPaintEngine* paintEngine()const {
		return nullptr;
	}

	void paintEvent(QPaintEvent* event);
	void resize(QResizeEvent* event);

	void Init3D();
	void ResizeD3D();
	void RenderInit();
	void RenderUpdate();

	void setLightColor(float, float, float, float);
	void setRaster(int);
	void setSpec(bool);

	float bgcolor[4] = { 1,0.5,0.5,1 };           //我自定义清空背景颜色的颜色值
	ID3D11Device* m_device;             //创建D3D主要接口
	ID3D11DeviceContext* m_deviceContex;  //创建D3D绘制上下文
	IDXGISwapChain* m_swapChain;           //交换链
	ID3D11Texture2D* m_depthStencilBuffer; //深度和模板缓冲区的Buffer缓存，可以理解为一张窗口图片
	ID3D11DepthStencilView* m_depthStencilView;    //深度模板缓冲区窗口描述
	ID3D11RenderTargetView* m_renderTargetView;    //绘制窗口描述
	ID3D11RasterizerState* m_rasterizeState;       //状态

	D3D11_VIEWPORT viewport;       //我们所看到的视口
    bool isback = true;
	//bool isTex = false;
	string filepath;
	string texpath;
	bool isFirstOpen = true;
	int renderMode = 1;
	bool isModify = false;
	int angle = 0;
	int lightangle = 0;
private:
	HWND m_hwnd;
	int m_height, m_width;
	InputClass* m_Input;
	GraphicsClass* m_Graphics;
	float lightColor[4] = { 1.0f,1.0f,1.0f,1.0f };
	int RasterizerState = 0;
	bool isSpec = false;
	
};

#endif