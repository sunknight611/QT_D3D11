#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

#define SafeDel(obj)    \
    obj->Release();         \
    obj=0;                  \

#include<iostream>
#include <fstream>
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightclass.h"
#include "lightshaderclass.h"
#include"specLightshaderclass.h"
#include "refractionshaderclass.h"
#include "watershaderclass.h"
#include"rendertextureclass.h"
#include"Fireshaderclass.h"
#include"Fireclass.h"

typedef struct
{
	float x, y, z;
}VertexType;

typedef struct
{
	int vIndex1, vIndex2, vIndex3;
	int tIndex1, tIndex2, tIndex3;
	int nIndex1, nIndex2, nIndex3;
}FaceType;



bool ReadFileCounts(const char* filename, int& vertexCount, int& textureCount, int& normalCount, int& faceCount);
bool LoadDataStructures(const char*, int, int, int, int);

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
	bool Render(float);
	bool FrameWater(string,string);
	bool RenderScene(string,string,float);
	bool FrameFire(string,string);
	bool RenderFire(string, string, float);
	bool RenderRefraction();
	bool RenderReflection();
	bool RenderBack();
	//void GraphicsClass::setColor(float red, float green, float blue, float alpha);
	void GraphicsClass::Resize(int width, int height);
	void setLightColor(float, float, float, float);
	void setRasterizerState(int state);
	void setSpec(bool isSpecular);
	bool setModel(string path);
	bool setTex(string path);
	D3DXMATRIX baseWorld;
	void setCamarePos(int angle);

	int cam_angle = 0;
	int light_angle = 0;
private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	FireModelClass* m_FireModel;
	LightClass* m_Light;
	LightShaderClass* m_LightShader;
	SpecLightShaderClass* m_specLightShader;
	LPCWSTR modelPath,texPath;
	bool isSolid = true;
	bool isSpec = false;
	HWND m_hwnd;
	//float lightColor[4] = { 1.0f,1.0f,1.0f,1.0f };
	ModelClass* m_GroundModel, * m_WallModel, * m_BathModel, * m_WaterModel;
	RenderTextureClass* m_RefractionTexture, * m_ReflectionTexture;
	RefractionShaderClass* m_RefractionShader;
	WaterShaderClass* m_WaterShader;
	FireShaderClass* m_FireShader;

	float m_waterHeight, m_waterTranslation;
	//int cam_angle = 0;
}; 

#endif
