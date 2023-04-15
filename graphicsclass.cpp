#include "graphicsclass.h"

bool result;
int vertexCount, textureCount, normalCount, faceCount;

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_specLightShader = 0;
	m_GroundModel = 0;
	m_WallModel = 0;
	m_BathModel = 0;
	m_WaterModel = 0;

	m_RefractionTexture = 0;
	m_ReflectionTexture = 0;
	m_RefractionShader = 0;
	m_WaterShader = 0;

	m_FireModel = 0;
	m_FireShader = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{

}


GraphicsClass::~GraphicsClass()
{

}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	m_hwnd = hwnd;
		m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

		result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	m_D3D->GetWorldMatrix(baseWorld);

		m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

		m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

		m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

		/*result = m_Model->Initialize(m_D3D->GetDevice(), "cube.txt", L"seafloor.dds", isSolid);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}*/

		m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

		result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	m_specLightShader = new SpecLightShaderClass;

	result = m_specLightShader ->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the speclight shader object.", L"Error", MB_OK);
		return false;
	}


		m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

		m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, -1.0f, 0.5f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	m_GroundModel = new ModelClass;
	result = m_GroundModel->Initialize(m_D3D->GetDevice(), "ground.txt", L"ground01.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Ground object.", L"Error", MB_OK);
		return false;
	}

	m_WallModel = new ModelClass;
	result = m_WallModel->Initialize(m_D3D->GetDevice(), "wall.txt", L"wall01.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the wall object.", L"Error", MB_OK);
		return false;
	}

	m_BathModel = new ModelClass;
	result = m_BathModel->Initialize(m_D3D->GetDevice(), "bath.txt", L"marble01.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Bath object.", L"Error", MB_OK);
		return false;
	}

	m_WaterModel = new ModelClass;
	
	result = m_WaterModel->Initialize(m_D3D->GetDevice(), "water.txt", L"water01.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the water model object.", L"Error", MB_OK);
		return false;
	}

	m_RefractionTexture = new RenderTextureClass;
	if (!m_RefractionTexture)
	{
		return false;
	}

	result = m_RefractionTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the refraction render to texture object.", L"Error", MB_OK);
		return false;
	}

	m_ReflectionTexture = new RenderTextureClass;
	if (!m_ReflectionTexture)
	{
		return false;
	}

		result = m_ReflectionTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the reflection render to texture object.", L"Error", MB_OK);
		return false;
	}

	m_RefractionShader = new RefractionShaderClass;
	if (!m_RefractionShader)
	{
		return false;
	}

		result = m_RefractionShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the refraction shader object.", L"Error", MB_OK);
		return false;
	}

		m_WaterShader = new WaterShaderClass;
	if (!m_WaterShader)
	{
		return false;
	}

		result = m_WaterShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the water shader object.", L"Error", MB_OK);
		return false;
	}

	m_waterHeight = 2.75f;

	m_waterTranslation = 0.0f;

	m_FireModel = new FireModelClass;

	result = m_FireModel->Initialize(m_D3D->GetDevice(), L"square.txt", L"fire01.dds",L"noise01.dds",L"alpha01.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fire model object.", L"Error", MB_OK);
		return false;
	}

	m_FireShader = new FireShaderClass;
	if (!m_FireShader)
	{
		return false;
	}

	result = m_FireShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fire shader object.", L"Error", MB_OK);
		return false;
	}
	return true;
}


void GraphicsClass::Shutdown()
{
		if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

		if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

		if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

		if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

		if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;
	static float rotation = 0.0f;

	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
    m_Camera->SetRotation(0.0f, 0.0f, 0.0f);
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f); 
		rotation += (float)D3DX_PI * 0.002f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

		result = Render(rotation);
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::FrameWater(string objpath, string texpath)
{
	static float rotation1 = 0.0f;
	m_waterTranslation += 0.001f;
	if (m_waterTranslation > 1.0f)
	{
		m_waterTranslation -= 1.0f;
	}
	m_Camera->SetPosition(-10.0f, 6.0f, -10.0f);
	m_Camera->SetRotation(0.0f, 45.0f, 0.0f);
	m_Light->SetDirection(0.0f, -1.0f, 0.5f);
	float ang = 0.0f,light_ang = 0.0f;
	ang = (float)D3DX_PI * 100 * cam_angle  / 99;
	light_ang = (float)D3DX_PI *  light_angle / 99 * 0.4;
	if (ang > 360.0f) {
		ang -= 360.0f;
	}

	m_Camera->SetRotation(0.0f, 45.0f + ang, 0.0f);
	m_Light->SetDirection(light_ang, -1.0f, 0.5f);
	rotation1 += (float)D3DX_PI * 0.002f;
	if (rotation1 > 360.0f)
	{
		rotation1 -= 360.0f;
	}

	RenderRefraction();

	RenderReflection();

	RenderScene(objpath,texpath,rotation1);

	return true;
}

bool GraphicsClass::RenderScene(string objpath,string texpath, float rotation)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, reflectionMatrix;
	bool result;

	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	m_Camera->Render();


	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	D3DXMatrixTranslation(&worldMatrix, 0.0f, 1.0f, 0.0f);


	m_GroundModel->Render(m_D3D->GetDeviceContext());

	
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_GroundModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_GroundModel->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	
	m_D3D->GetWorldMatrix(worldMatrix);

	D3DXMatrixTranslation(&worldMatrix, 0.0f, 6.0f, 8.0f);

	m_WallModel->Render(m_D3D->GetDeviceContext());

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_WallModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_WallModel->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

	if (!result)
	{
		return false;
	}

	m_D3D->GetWorldMatrix(worldMatrix);

	D3DXMatrixTranslation(&worldMatrix, 0.0f, 2.0f, 0.0f);

	
	m_BathModel->Render(m_D3D->GetDeviceContext());


	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_BathModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_BathModel->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	reflectionMatrix = m_Camera->GetReflectionViewMatrix();

	D3DXMatrixTranslation(&worldMatrix, 0.0f, m_waterHeight, 0.0f);

	m_WaterModel->Render(m_D3D->GetDeviceContext());

	result = m_WaterShader->Render(m_D3D->GetDeviceContext(), m_WaterModel->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, reflectionMatrix, m_ReflectionTexture->GetShaderResourceView(),
		m_RefractionTexture->GetShaderResourceView(), m_WaterModel->GetTexture(),
		m_waterTranslation, 0.01f);
	if (!result)
	{
		return false;
	}


	m_D3D->GetWorldMatrix(worldMatrix);

	D3DXMatrixTranslation(&worldMatrix, 0.0f, 6.0f, 0.0f);
	//D3DXMatrixRotationY(&worldMatrix, rotation);
	
	m_Model->Render(m_D3D->GetDeviceContext());

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	m_D3D->EndScene();
	return true;
}

bool GraphicsClass::FrameFire(string filename, string texname)
{
	bool result;
	static float rotation1 = 0.0f;

	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Camera->SetRotation(0.0f, 0.0f, 0.0f);
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
		rotation1 += (float)D3DX_PI * 0.002f;
	if (rotation1 > 360.0f)
	{
		rotation1 -= 360.0f;
	}

		result = RenderFire(filename,texname,rotation1);
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::RenderFire(string filename, string texname, float rotation)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, reflectionMatrix;
	bool result;
	D3DXVECTOR3 scrollSpeeds, scales;
	D3DXVECTOR2 distortion1, distortion2, distortion3;
	float distortionScale, distortionBias;
	static float frameTime = 0.0f;

	frameTime += 0.01f;
	if (frameTime > 1000.0f)
	{
		frameTime = 0.0f;
	}

	scrollSpeeds = D3DXVECTOR3(1.3f, 2.1f, 2.3f);

	scales = D3DXVECTOR3(1.0f, 2.0f, 3.0f);

	distortion1 = D3DXVECTOR2(0.1f, 0.2f);
	distortion2 = D3DXVECTOR2(0.1f, 0.3f);
	distortion3 = D3DXVECTOR2(0.1f, 0.1f);

	distortionScale = 0.8f;
	distortionBias = 0.5f;

	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	m_Camera->Render();

	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	D3DXMatrixTranslation(&worldMatrix, 0.0f, -2.0f, 0.0f);

	m_D3D->TurnOnAlphaBlending();

	m_FireModel->Render(m_D3D->GetDeviceContext());

	result = m_FireShader->Render(m_D3D->GetDeviceContext(), m_FireModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_FireModel->GetTexture1(), m_FireModel->GetTexture2(), m_FireModel->GetTexture3(), frameTime, scrollSpeeds,
		scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);

	m_D3D->TurnOffAlphaBlending();

	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixRotationY(&worldMatrix, rotation);
	//D3DXMatrixTranslation(&worldMatrix, 0.0f, 0.0f, 0.0f);
	m_Model->Render(m_D3D->GetDeviceContext());

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	m_D3D->EndScene();
	return true;
}

bool GraphicsClass::RenderRefraction()
{
	D3DXVECTOR4 clipPlane;
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	
	clipPlane = D3DXVECTOR4(0.0f, -1.0f, 0.0f, m_waterHeight + 0.1f);

	m_RefractionTexture->SetRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView());


	m_RefractionTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView(), 0.0f, 0.0f, 0.0f, 1.0f);

	
	m_Camera->Render();

	
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	
	D3DXMatrixTranslation(&worldMatrix, 0.0f, 2.0f, 0.0f);

	
	m_BathModel->Render(m_D3D->GetDeviceContext());

	
	result = m_RefractionShader->Render(m_D3D->GetDeviceContext(), m_BathModel->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_BathModel->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), clipPlane);
	if (!result)
	{
		return false;
	}

	m_D3D->SetBackBufferRenderTarget();

	return true;
}

bool GraphicsClass::RenderReflection()
{
	D3DXMATRIX reflectionViewMatrix, worldMatrix, projectionMatrix;
	bool result;

	m_ReflectionTexture->SetRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView());

	m_ReflectionTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView(), 0.0f, 0.0f, 0.0f, 1.0f);

	m_Camera->RenderReflection(m_waterHeight);

	reflectionViewMatrix = m_Camera->GetReflectionViewMatrix();

	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	D3DXMatrixTranslation(&worldMatrix, 0.0f, 6.0f, 8.0f);
	
	m_WallModel->Render(m_D3D->GetDeviceContext());
	
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_WallModel->GetIndexCount(), worldMatrix, reflectionViewMatrix,
		projectionMatrix, m_WallModel->GetTexture(), m_Light->GetDirection(),m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}
	m_D3D->SetBackBufferRenderTarget();

	return true;
}


bool GraphicsClass::Render(float rotation)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix,worldTranslation;
	bool result;

	float ang = 0.0f;
	ang = (float)D3DX_PI * 100 * cam_angle / 99;

	if (ang > 360.0f) {
		ang -= 360.0f;
	}

	m_Camera->SetRotation(0.0f, ang, 0.0f);

	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	m_Camera->Render();

	m_Camera->GetViewMatrix(viewMatrix);
	
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	D3DXMatrixRotationY(&worldMatrix, rotation);
	D3DXMatrixTranslation(&worldTranslation, 0.0f, -2.0f, 0.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &worldTranslation);

	m_Model->Render(m_D3D->GetDeviceContext());

    if (isSpec == false) { 
	    result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	}
	else {
		result = m_specLightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	}
	
	if (!result)
	{
		return false;
	}

	m_D3D->EndScene();

	return true;
}

bool GraphicsClass::RenderBack()
{
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	m_D3D->EndScene();
	return true;
}

void GraphicsClass::Resize(int width, int height)
{
	m_D3D->ResizeD3D(width, height);
}

void GraphicsClass::setLightColor(float red, float green, float blue, float alpha)
{
	m_Light->SetDiffuseColor(red, green, blue, alpha);
}

void GraphicsClass::setRasterizerState(int state)
{
	m_D3D->setRasterizerState(state);
}

void GraphicsClass::setSpec(bool isSpecular)
{
	isSpec = isSpecular;
}

bool GraphicsClass::setTex(string path) {
	const size_t len = strlen(path.c_str()) + 1;
	wchar_t* wch = new wchar_t[len];
	mbstowcs(wch, path.c_str(), len);
	
	result = m_Model->InitializeTex(m_D3D->GetDevice(), wch);
	if (!result)
	{
				return false;
	}
}

void GraphicsClass::setCamarePos(int angle)
{

}

bool GraphicsClass::setModel(string path)
{
	HRESULT result;

	
	if (path.compare("sphere.txt") == -1) {
       ReadFileCounts(path.c_str(), vertexCount, textureCount, normalCount, faceCount);
	   LoadDataStructures(path.c_str(), vertexCount, textureCount, normalCount, faceCount);
	   result = m_Model->Initialize(m_D3D->GetDevice(), "model.txt", L"seafloor.dds");
	}else
	   result = m_Model->Initialize(m_D3D->GetDevice(), "sphere.txt", L"seafloor.dds");

	if (!result)
	{
				return false;
	}
}

bool ReadFileCounts(const char* filename, int& vertexCount, int& textureCount, int& normalCount, int& faceCount)
{
	ifstream fin;
	char input;


	vertexCount = 0;
	textureCount = 0;
	normalCount = 0;
	faceCount = 0;

		fin.open(filename);

		if (fin.fail() == true)
	{
		return false;
	}

		fin.get(input);
	while (!fin.eof())
	{
		if (input == 'v')
		{
			fin.get(input);
			if (input == ' ') { vertexCount++; }
			if (input == 't') { textureCount++; }
			if (input == 'n') { normalCount++; }
		}

				if (input == 'f')
		{
			fin.get(input);
			if (input == ' ') { faceCount++; }
		}

				while (input != '\n')
		{
			fin.get(input);
		}

				fin.get(input);
	}

		fin.close();

	return true;
}

bool LoadDataStructures(const char* filename, int vertexCount, int textureCount, int normalCount, int faceCount)
{
	VertexType* vertices, * texcoords, * normals;
	FaceType* faces;
	ifstream fin;
	int vertexIndex, texcoordIndex, normalIndex, faceIndex, vIndex, tIndex, nIndex;
	char input, input2;
	ofstream fout;


		vertices = new VertexType[vertexCount];
	if (!vertices)
	{
		return false;
	}

	texcoords = new VertexType[textureCount];
	if (!texcoords)
	{
		return false;
	}

	normals = new VertexType[normalCount];
	if (!normals)
	{
		return false;
	}

	faces = new FaceType[faceCount];
	if (!faces)
	{
		return false;
	}

	vertexIndex = 0;
	texcoordIndex = 0;
	normalIndex = 0;
	faceIndex = 0;

	fin.open(filename);

	if (fin.fail() == true)
	{
		return false;
	}

	fin.get(input);
	while (!fin.eof())
	{
		if (input == 'v')
		{
			fin.get(input);

						if (input == ' ')
			{
				fin >> vertices[vertexIndex].x >> vertices[vertexIndex].y >> vertices[vertexIndex].z;

								vertices[vertexIndex].z = vertices[vertexIndex].z * -1.0f;
				vertexIndex++;
			}

						if (input == 't')
			{
				fin >> texcoords[texcoordIndex].x >> texcoords[texcoordIndex].y;

								texcoords[texcoordIndex].y = 1.0f - texcoords[texcoordIndex].y;
				texcoordIndex++;
			}

						if (input == 'n')
			{
				fin >> normals[normalIndex].x >> normals[normalIndex].y >> normals[normalIndex].z;

								normals[normalIndex].z = normals[normalIndex].z * -1.0f;
				normalIndex++;
			}
		}

				if (input == 'f')
		{
			fin.get(input);
			if (input == ' ')
			{
								fin >> faces[faceIndex].vIndex3 >> input2 >> faces[faceIndex].tIndex3 >> input2 >> faces[faceIndex].nIndex3
					>> faces[faceIndex].vIndex2 >> input2 >> faces[faceIndex].tIndex2 >> input2 >> faces[faceIndex].nIndex2
					>> faces[faceIndex].vIndex1 >> input2 >> faces[faceIndex].tIndex1 >> input2 >> faces[faceIndex].nIndex1;
				faceIndex++;
			}
		}

		while (input != '\n')
		{
			fin.get(input);
		}

		fin.get(input);
	}

		fin.close();

		fout.open("model.txt");

		fout << "Vertex Count: " << (faceCount * 3) << endl;
	fout << endl;
	fout << "Data:" << endl;
	fout << endl;

		for (int i = 0; i < faceIndex; i++)
	{
		vIndex = faces[i].vIndex1 - 1;
		tIndex = faces[i].tIndex1 - 1;
		nIndex = faces[i].nIndex1 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;

		vIndex = faces[i].vIndex2 - 1;
		tIndex = faces[i].tIndex2 - 1;
		nIndex = faces[i].nIndex2 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;

		vIndex = faces[i].vIndex3 - 1;
		tIndex = faces[i].tIndex3 - 1;
		nIndex = faces[i].nIndex3 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;
	}

		fout.close();

		if (vertices)
	{
		delete[] vertices;
		vertices = 0;
	}
	if (texcoords)
	{
		delete[] texcoords;
		texcoords = 0;
	}
	if (normals)
	{
		delete[] normals;
		normals = 0;
	}
	if (faces)
	{
		delete[] faces;
		faces = 0;
	}

	return true;
}
