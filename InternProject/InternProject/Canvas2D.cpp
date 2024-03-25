#include "Canvas2D.h"
using namespace DirectX;

void Canvas2D::GenerateMatrix(ConstBuffer& cb)
{
	XMMATRIX matrixView;
	XMMATRIX matrixProj;


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

	//UVアニメーション行列作成
	XMMATRIX matrixTex = XMMatrixTranslation(m_anime->GetUVOffset().x, m_anime->GetUVOffset().y, 0.0f);

	cb.matrixWorld = matrixWorld * matrixView * matrixProj;

	cb.matrixUV = XMMatrixTranspose(matrixTex);
	cb.matrixWorld = XMMatrixTranspose(matrixWorld);
	cb.matrixNormal = XMMatrixTranspose(matrixRotate);

	//マテリアル色を定数バッファデータに代入
	cb.materialDiffuse = mMaterialDiffuse;


}

Canvas2D::Canvas2D()
{
}

Canvas2D::~Canvas2D()
{

}

void Canvas2D::InitCanvas()
{
	
}
