#include"Fireclass.h"

FireModelClass::FireModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture1 = 0;
	m_Texture2 = 0;
	m_Texture3 = 0;
	m_model = 0;
}


FireModelClass::FireModelClass(const FireModelClass& other)
{
}


FireModelClass::~FireModelClass()
{
}


bool FireModelClass::Initialize(ID3D11Device* device, const WCHAR* modelFilename,const WCHAR* textureFilename1,const WCHAR* textureFilename2,
	const WCHAR* textureFilename3)
{
	bool result;


		result = LoadModel(modelFilename);
	if (!result)
	{
		return false;
	}

		result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

		result = LoadTextures(device, textureFilename1, textureFilename2, textureFilename3);
	if (!result)
	{
		return false;
	}

	return true;
}


void FireModelClass::Shutdown()
{
		ReleaseTextures();

		ShutdownBuffers();

		ReleaseModel();

	return;
}


void FireModelClass::Render(ID3D11DeviceContext* deviceContext)
{
		RenderBuffers(deviceContext);

	return;
}


int FireModelClass::GetIndexCount()
{
	return m_indexCount;
}


bool FireModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;


		vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

		indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

		for (i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = D3DXVECTOR3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = D3DXVECTOR2(m_model[i].tu, m_model[i].tv);
		indices[i] = i;
	}

		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

		vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

		result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

		indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

		result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

		delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}


void FireModelClass::ShutdownBuffers()
{
		if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

		if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void FireModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


		stride = sizeof(VertexType);
	offset = 0;

		deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

		deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}


bool FireModelClass::LoadTextures(ID3D11Device* device, const WCHAR* textureFilename1,const WCHAR* textureFilename2,const WCHAR* textureFilename3)
{
	bool result;


		m_Texture1 = new TextureClass;
	if (!m_Texture1)
	{
		return false;
	}

		result = m_Texture1->Initialize(device, textureFilename1);
	if (!result)
	{
		return false;
	}

		m_Texture2 = new TextureClass;
	if (!m_Texture2)
	{
		return false;
	}

		result = m_Texture2->Initialize(device, textureFilename2);
	if (!result)
	{
		return false;
	}

		m_Texture3 = new TextureClass;
	if (!m_Texture3)
	{
		return false;
	}

		result = m_Texture3->Initialize(device, textureFilename3);
	if (!result)
	{
		return false;
	}

	return true;
}


void FireModelClass::ReleaseTextures()
{
		if (m_Texture1)
	{
		m_Texture1->Shutdown();
		delete m_Texture1;
		m_Texture1 = 0;
	}

	if (m_Texture2)
	{
		m_Texture2->Shutdown();
		delete m_Texture2;
		m_Texture2 = 0;
	}

	if (m_Texture3)
	{
		m_Texture3->Shutdown();
		delete m_Texture3;
		m_Texture3 = 0;
	}

	return;
}


ID3D11ShaderResourceView* FireModelClass::GetTexture1()
{
	return m_Texture1->GetTexture();
}


ID3D11ShaderResourceView* FireModelClass::GetTexture2()
{
	return m_Texture2->GetTexture();
}


ID3D11ShaderResourceView* FireModelClass::GetTexture3()
{
	return m_Texture3->GetTexture();
}


bool FireModelClass::LoadModel(const WCHAR* filename)
{
	ifstream fin;
	char input;
	int i;


	fin.open(filename);
	if (fin.fail())
	{
		return false;
	}

	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	fin >> m_vertexCount;

	
	m_indexCount = m_vertexCount;


	m_model = new ModelType[m_vertexCount];
	if (!m_model)
	{
		return false;
	}

	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

		for (i = 0; i < m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

		fin.close();

	return true;
}


void FireModelClass::ReleaseModel()
{
	if (m_model)
	{
		delete[] m_model;
		m_model = 0;
	}

	return;
}