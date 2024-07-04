#include "Sprite2D.h"
#include "Game.h"
#include "Camera.h"


using namespace DirectX;


void Sprite2D::GenerateMatrix(ConstBuffer& cb)
{
	//カメラの行列を単位行列
	XMMATRIX matrixView = Game::Get()->GetCamera2D()->GetMatrixView();
	//平行投影行列を作成
	XMMATRIX matrixProj = Game::Get()->GetCamera2D()->GetMatrixProj();

	matrixProj = matrixView * matrixProj;


	//ワールド変換行列の作成
	//移動行列
	XMMATRIX matrixMove = XMMatrixTranslation(mPos.x, mPos.y, mPos.z);
	//拡大縮小行列
	XMMATRIX matrixScale = XMMatrixScaling(mScale.x, mScale.y, mScale.z);

	//回転行列
	XMMATRIX matrixRotateX = XMMatrixRotationX(XMConvertToRadians(mRotation.x));
	XMMATRIX matrixRotateY = XMMatrixRotationY(XMConvertToRadians(mRotation.y));
	XMMATRIX matrixRotateZ = XMMatrixRotationZ(XMConvertToRadians(mRotation.z));
	XMMATRIX matrixRotate = matrixRotateX * matrixRotateY * matrixRotateZ;
	XMMATRIX matrixWorld = matrixScale * matrixRotate * matrixMove;
	matrixWorld = matrixWorld * matrixProj;

	//UVアニメーション行列作成
	XMMATRIX matrixTex = XMMatrixTranslation(pAnimation->GetOffsetUV().x, pAnimation->GetOffsetUV().y, 0.0f);

	cb.matrixWorld = XMMatrixTranspose(matrixWorld);
	cb.matrixNormal=XMMatrixTranspose(matrixRotate);
	cb.matrixUV = matrixTex;
	cb.matrixUV = XMMatrixTranspose(cb.matrixUV);
	cb.materialDiffuse = this->mMaterialDiffuse;

	cb.isLight = isLight;
}

Sprite2D::Sprite2D()
{
	pModel = std::make_unique<Model>();
	pAnimation = std::make_unique<Anime::Animation>();
}

Sprite2D::~Sprite2D()= default;

void Sprite2D::SetPos(float x, float y, float z)
{
	mPos.x = x;
	mPos.y = y;
	mPos.z = z;
}

void Sprite2D::SetRotate(float x, float y, float z)
{
	mRotation.x = x;
	mRotation.y = y;
	mRotation.z = z;
}


void Sprite2D::InitSprite(DirectX::XMFLOAT2 _size, DirectX::XMINT2 _split, ID3D11ShaderResourceView* _assets,Anime::AnimePattern _pattern, ModelSet::VerticalAlign _align)
{
	//Create Model
	pModel->model = Model::Create2DModel(_size, _split, _align);
	pModel->SetTexture(_assets);
	

	//SetAnimation
	pAnimation->InitAnime(_split, _pattern);
	
}

void Sprite2D::Update()
{
	pAnimation->Update();
	
}

void Sprite2D::Draw()
{
	UINT strides = sizeof(Vertex3D);
	UINT offsets = 0;

	ConstBuffer cb;
	GenerateMatrix(cb);

	//Set Data to Constant Buffer
	DirectX3D::Get()->GetD3D_Context()->UpdateSubresource(DirectX3D::Get()->GetConstantBuffer(), 0, NULL,
		&cb, 0, 0);

	//Set data to ShaderFile
	if(pModel!=nullptr)
	{
		DirectX3D::Get()->GetD3D_Context()->IASetVertexBuffers(0, 1, pModel->model.vertexBuffer.GetAddressOf(),
			&strides, &offsets);
		DirectX3D::Get()->GetD3D_Context()->IASetIndexBuffer(pModel->model.indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
		DirectX3D::Get()->GetD3D_Context()->PSSetShaderResources(0, 1, pModel->model.texture.GetAddressOf());

		//Draw
		DirectX3D::Get()->GetD3D_Context()->DrawIndexed(pModel->model.indexNum, 0, 0);
	}
}
	

void Sprite2D::SetMaterialDiffuse(Color sRGB)
{
	mMaterialDiffuse.x = sRGB.r;
	mMaterialDiffuse.y = sRGB.g;
	mMaterialDiffuse.z = sRGB.b;
	mMaterialDiffuse.w = sRGB.a;
}
