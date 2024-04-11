#include "Object.h"
#include "Game.h"
#include "Camera.h"

Object::Object()
{
	
}

Object::~Object()
{
	
}

void Object::SetModel(const ModelData& _model)
{
	mModel. model = _model;
}

void Object::SetPos(float _x, float _y, float _z)
{
	mPos.x = _x;
	mPos.y = _y;
	mPos.z = _z;
}


void Object::SetRotate(float _x, float _y, float _z)
{
	mRotation.x = _x;
	mRotation.y = _y;
	mRotation.z = _z;
}

void Object::SetScale(float _x, float _y, float _z)
{
	mScale.x = _x;
	mScale.y = _y;
	mScale.z = _z;
}

void Object::SetSpeed(float _x, float _y, float _z)
{
	mSpeed.x = _x;
	mSpeed.y = _y;
	mSpeed.z = _z;
}

void Object::Update()
{
	//回転の結果を移動方向に実装
	mForward = GenerateRotate();

	//移動量
	mPos.x += mForward.x * mSpeed.x;
	mPos.y += mForward.y * mSpeed.y;
	mPos.z += mForward.z * mSpeed.z;

}

void Object::Draw()
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
	DirectX3D::Get()->GetD3D_Context()->IASetIndexBuffer(mModel.model.indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	DirectX3D::Get()->GetD3D_Context()->PSSetShaderResources(0, 1, &mModel.model.texture);

	//Draw
	DirectX3D::Get()->GetD3D_Context()->DrawIndexed(mModel.model.indexNum, 0, 0);

}


DirectX::XMFLOAT3 Object::GenerateRotate()
{
	XMFLOAT3 forward = {};
	//初期
	XMVECTOR initForward = DirectX::XMVectorSet(0.f, 0.f, 1.f, 0.f );

	//Get Rotate Matrix
	XMMATRIX matrixRotateX = XMMatrixRotationX(XMConvertToRadians(mRotation.x));
	XMMATRIX matrixRotateY = XMMatrixRotationY(XMConvertToRadians(mRotation.y));
	XMMATRIX matrixRotateZ = XMMatrixRotationZ(XMConvertToRadians(mRotation.z));
	XMMATRIX matrixRotate = matrixRotateX * matrixRotateY * matrixRotateZ;
	
	XMVECTOR compForward = XMVector3TransformCoord(initForward, matrixRotate);

	//Set Vector to forward
	forward.x = XMVectorGetX(compForward);
	forward.y = XMVectorGetY(compForward);
	forward.z = XMVectorGetZ(compForward);

	return forward;
}

void Object::GenerateMatrix(ConstBuffer& cb)
{
	//カメラの行列を単位行列
	XMMATRIX matrixView = Game::Get()->GetCamera3D()->GetMatrixView();
	//透視投影行列を作成
	XMMATRIX matrixProj = Game::Get()->GetCamera3D()->GetMatrixProj();

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
	XMMATRIX matrixTex = XMMatrixIdentity();

	cb.matrixWorld = XMMatrixTranspose(matrixWorld);
	cb.matrixNormal = XMMatrixTranspose(matrixRotate);
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
