#include "Object3D.h"
#include "Game.h"
#include "Camera.h"

Object3D::Object3D()
{
	
}

Object3D::~Object3D()
{
	
}

void Object3D::SetModel(const ModelData& _model)
{
	mModel. model = _model;
}

void Object3D::SetPos(float _x, float _y, float _z)
{
	mPos.x = _x;
	mPos.y = _y;
	mPos.z = _z;
}


void Object3D::SetRotate(float _x, float _y, float _z)
{
	mRotation.x = _x;
	mRotation.y = _y;
	mRotation.z = _z;
}

void Object3D::SetScale(float _x, float _y, float _z)
{
	mScale.x = _x;
	mScale.y = _y;
	mScale.z = _z;
}

void Object3D::SetSpeed(float _x, float _y, float _z)
{
	mSpeed.x = _x;
	mSpeed.y = _y;
	mSpeed.z = _z;
}

void Object3D::Update()
{
	//回転の結果を移動方向に実装
	mForward = GenerateRotate();

	//移動量
	mPos.x += mForward.x * mSpeed.x;
	mPos.y += mForward.y * mSpeed.y;
	mPos.z += mForward.z * mSpeed.z;

}

void Object3D::Draw()
{
	UINT strides = sizeof(Vertex3D);
	UINT offsets = 0;

	ConstBuffer cb;
	GenerateMatrix(cb);

	//Set Data to Constant Buffer
	DirectX3D::Get()->GetD3D_Context()->UpdateSubresource(DirectX3D::Get()->GetConstantBuffer(), 0, NULL,
		&cb, 0, 0);

	//Set data to ShaderFile
	DirectX3D::Get()->GetD3D_Context()->IASetVertexBuffers(0, 1, &mModel.model.vertexBuffer,
		&strides, &offsets);
	DirectX3D::Get()->GetD3D_Context()->IASetIndexBuffer(mModel.model.indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	DirectX3D::Get()->GetD3D_Context()->PSSetShaderResources(0, 1, &mModel.model.texture);

	//Draw
	DirectX3D::Get()->GetD3D_Context()->DrawIndexed(mModel.model.indexNum, 0, 0);

}


DirectX::XMFLOAT3 Object3D::GenerateRotate()
{
	DirectX::XMFLOAT3 forward = {};
	//初期
	DirectX::XMVECTOR initForward = DirectX::XMVectorSet(0.f, 0.f, 1.f, 0.f );

	//Get Rotate Matrix
	DirectX::XMMATRIX matrixRotateX = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(mRotation.x));
	DirectX::XMMATRIX matrixRotateY = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(mRotation.y));
	DirectX::XMMATRIX matrixRotateZ = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(mRotation.z));
	DirectX::XMMATRIX matrixRotate = matrixRotateX * matrixRotateY * matrixRotateZ;

	DirectX::XMVECTOR compForward = DirectX::XMVector3TransformCoord(initForward, matrixRotate);

	//Set Vector to forward
	forward.x = DirectX::XMVectorGetX(compForward);
	forward.y = DirectX::XMVectorGetY(compForward);
	forward.z = DirectX::XMVectorGetZ(compForward);

	return forward;
}

void Object3D::GenerateMatrix(ConstBuffer& cb)
{
	//カメラの行列を単位行列
	DirectX::XMMATRIX matrixView = Game::Get()->GetCamera3D()->GetMatrixView();
	//透視投影行列を作成
	DirectX::XMMATRIX matrixProj = Game::Get()->GetCamera3D()->GetMatrixProj();

	matrixProj = matrixView * matrixProj;


	//ワールド変換行列の作成
	//移動行列
	DirectX::XMMATRIX matrixMove = DirectX::XMMatrixTranslation(mPos.x, mPos.y, mPos.z);
	//拡大縮小行列
	DirectX::XMMATRIX matrixScale = DirectX::XMMatrixScaling(mScale.x, mScale.y, mScale.z);

	//回転行列
	DirectX::XMMATRIX matrixRotateX = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(mRotation.x));
	DirectX::XMMATRIX matrixRotateY = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(mRotation.y));
	DirectX::XMMATRIX matrixRotateZ = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(mRotation.z));
	DirectX::XMMATRIX matrixRotate = matrixRotateX * matrixRotateY * matrixRotateZ;
	DirectX::XMMATRIX matrixWorld = matrixScale * matrixRotate * matrixMove;
	matrixWorld = matrixWorld * matrixProj;

	//UVアニメーション行列作成
	DirectX::XMMATRIX matrixTex = DirectX::XMMatrixIdentity();

	cb.matrixWorld = DirectX::XMMatrixTranspose(matrixWorld);
	cb.matrixNormal = DirectX::XMMatrixTranspose(matrixRotate);
	cb.matrixUV = matrixTex;
	cb.matrixUV = XMMatrixTranspose(cb.matrixUV);
	cb.materialDiffuse = this->mMaterialDiffuse;

	//to Do
	cb.isLight = isLight;
	//cb.lightDir = {};
	//cb.ambientLight = {};
	//cb.lightDir = { 0, -1, 0 };
	//cb.ambientLight = mAmbientLight;


}
