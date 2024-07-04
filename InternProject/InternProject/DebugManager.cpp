#include "DebugManager.h"
#include "Game.h"

DebugManager::DebugManager(float _size)
{
	for (auto& pASCII : mDebugASCII)
	{
		//初期化
		pASCII = new CanvasUI();
		mSize = _size;		
		//モデル作成
		pASCII->InitCanvas({ mSize,mSize }, { 12,8 }, Game::Get()->GetModelManager()->debugFont,Anime::SINGLE_PATTERN, ModelSet::MIDDLE);

	}
}

DebugManager::~DebugManager()
{
	for (auto& pASCII : mDebugASCII) {
		delete pASCII;
	}
}

void DebugManager::UpdateChar(char* outputChar, Debug::TEXT_ALIGN _align)
{
	switch(_align)
	{
		case Debug::TEXT_ALIGN::CENTER:
			{
				int totalCharacters = (int)strlen(outputChar);
				float totalWidth = totalCharacters * mSize;

				for (int i = 0; i < totalCharacters; i++)
				{
					// 文字の横番目を取得 SPACE ASCII->32
					int frameX = ((int)outputChar[i] - 32) % 12;
					// オブジェクトにセットする
					mDebugASCII[i]->mSprite->GetAnimation()->SetFrameX(frameX);

					//文字の縦番目を取得
					int frameY = ((int)outputChar[i] - 32) / 12;
					mDebugASCII[i]->mSprite->GetAnimation()->SetFrameY(frameY);

					// 文字の位置を設定する（中央に調整）
					float posX = msPosX - totalWidth / 2 + (int)i * mSize + mInterval;

					mDebugASCII[i]->mSprite->SetPos(posX, msPosY, 0.1f);

					// UVOFFSET更新
					mDebugASCII[i]->mSprite->GetAnimation()->Update();

					// 描画
					mDebugASCII[i]->Draw();
					
				}
			}
			break;
		case Debug::TEXT_ALIGN::LEFT:
			{
				int totalCharacters = (int)strlen(outputChar);
				float totalWidth = totalCharacters * mSize;
				for (int i = 0; i < strlen(outputChar); i++)
				{
					//文字の横番目を取得 SPACE ASCII->32
					int frameX = ((int)outputChar[i] - 32) % 12;
					mDebugASCII[i]->mSprite->GetAnimation()->SetFrameX(frameX);

					//文字の縦番目を取得
					int frameY = ((int)outputChar[i] - 32) / 12;
					mDebugASCII[i]->mSprite->GetAnimation()->SetFrameY(frameY);

					//文字の位置を設定する
					float posX = mSize * i;
					mDebugASCII[i]->mSprite->SetPos(msPosX + posX, msPosY, 0.1f);

					//UVOFFSET更新
					mDebugASCII[i]->mSprite->GetAnimation()->Update();

					//描画
					mDebugASCII[i]->Draw();
				}
			}
			break;
		case Debug::TEXT_ALIGN::RIGHT:
			{

			for (int i = 0; i < strlen(outputChar); i++)
			{
				//文字の横番目を取得 SPACE ASCII->32
				int frameX = ((int)outputChar[i] - 32) % 12;

				//オブジェクトにセットする
				mDebugASCII[i]->mSprite->GetAnimation()->SetFrameX(frameX);

				//文字の縦番目を取得
				int frameY = ((int)outputChar[i] - 32) / 12;
				mDebugASCII[i]->mSprite->GetAnimation()->SetFrameY(frameY);

				//文字の位置を設定する
				float posX = msPosX - mSize * (strlen(outputChar) - i);
				mDebugASCII[i]->mSprite->SetPos(posX, msPosY, 0.1f);

				//UVOFFSET更新
				mDebugASCII[i]->mSprite->GetAnimation()->Update();

				//描画
				mDebugASCII[i]->Draw();
			}
		}
		break;

	}
	
}

void DebugManager::SetPosition(float posX, float posY){
	msPosX = posX;
	msPosY = posY;
}

void DebugManager::PrintDebugLog(float _posX, float _posY, const char* word, Debug::TEXT_ALIGN _align)
{
	//文字列に転換
	char str[256];
	snprintf(str, 255, "%s", word);
	//スタート位置を設定
	SetPosition(_posX, _posY);
	//更新と描画
	UpdateChar(str, _align);
}

void DebugManager::PrintDebugLog(float _posX, float _posY, const float _num, Debug::TEXT_ALIGN _align)
{
	//文字列に転換
	char str[32];
	snprintf(str, 32, "%f", _num);
	//スタート位置を設定
	SetPosition(_posX, _posY);
	//更新と描画
	UpdateChar(str,_align);
}

void DebugManager::PrintDebugLog(float _posX, float _posY, const int _num, Debug::TEXT_ALIGN _align)
{
	//文字列に転換
	char str[32];
	snprintf(str, 31, "%d", _num);
	//スタート位置を設定
	SetPosition(_posX, _posY);
	//更新と描画
	UpdateChar(str, _align);
}
