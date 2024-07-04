#include "ResultProcess.h"

#include "Game.h"

ResultProcess::ResultProcess()
{
	for(auto& stepnum : mStepNum)
	{
		stepnum = new CanvasUI();

	}
}

ResultProcess::~ResultProcess()
{
	for (auto& stepnum : mStepNum)
	{
		delete stepnum;

	}
}

void ResultProcess::SetPosition(float posX, float posY)
{
	msPosX = posX;
	msPosY = posY;
}

void ResultProcess::Init(float posX, float posY, float size, float interval)
{
	//文字の大きさ
	SetSize(size);

	mInterval = interval;

	for (auto& stepNum : mStepNum)
	{
		stepNum->InitCanvas({ 52.3f * mSize,110.f * mSize }, { 10,1 }, Game::Get()->GetModelManager()->resultNum.Get(), Anime::SINGLE_PATTERN, ModelSet::MIDDLE);

		stepNum->mSprite->GetAnimation()->SetPlaying(false);
		stepNum->mSprite->mPos.z = mPosz;
	}
	SetPosition(posX, posY);

	mInterval = 52.3f * mSize * SCREEN_PARA;

}

void ResultProcess::Print(float _posX, float _posY, const char* word, Debug::TEXT_ALIGN _align)
{
	//文字列に転換
	char str[256];
	snprintf(str, 255, "%s", word);
	//スタート位置を設定
	SetPosition(_posX, _posY);
	//更新と描画
	UpdateChar(str, _align);
}

void ResultProcess::Print(float _posX, float _posY, const float _num, Debug::TEXT_ALIGN _align)
{
	//文字列に転換
	char str[32];
	snprintf(str, 32, "%f", _num);
	//スタート位置を設定
	SetPosition(_posX, _posY);
	//更新と描画
	UpdateChar(str, _align);
}

void ResultProcess::Print(float _posX, float _posY, const int _num, Debug::TEXT_ALIGN _align)
{
	//文字列に転換
	char str[32];
	snprintf(str, 31, "%d", _num);
	//スタート位置を設定
	SetPosition(_posX, _posY);
	//更新と描画
	UpdateChar(str, _align);
}

void ResultProcess::UpdateChar(char* outputChar, Debug::TEXT_ALIGN _align)
{
	switch (_align)
	{
	case Debug::TEXT_ALIGN::CENTER:
	{
		int totalCharacters = (int)strlen(outputChar);
		float totalWidth = totalCharacters * mSize;

		for (int i = 0; i < totalCharacters; i++)
		{
			// 文字の横番目を取得 SPACE ASCII->32
			int frameX = ((int)outputChar[i] - 32) % 16;
			// オブジェクトにセットする
			mStepNum[i]->mSprite->GetAnimation()->SetFrameX(frameX);


			// 文字の位置を設定する（中央に調整）
			//float posX = msPosX - totalWidth / 2 + (int)i * mSize + mInterval;
			float posX = msPosX - totalWidth / 2 + mInterval * i;

			mStepNum[i]->mSprite->SetPos(posX, msPosY, mPosz);

			// UVOFFSET更新
			mStepNum[i]->Update();

			// 描画
			mStepNum[i]->Draw();

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
			int frameX = ((int)outputChar[i] - 32) % 16;
			mStepNum[i]->mSprite->GetAnimation()->SetFrameX(frameX);

			//文字の位置を設定する
			float posX = mSize * i;
			mStepNum[i]->mSprite->SetPos(msPosX + posX, msPosY, mPosz);

			//UVOFFSET更新
			mStepNum[i]->Update();

			//描画
			mStepNum[i]->Draw();
		}
	}
	break;
	case Debug::TEXT_ALIGN::RIGHT:
	{

		for (int i = 0; i < strlen(outputChar); i++)
		{
			//文字の横番目を取得 SPACE ASCII->32
			int frameX = ((int)outputChar[i] - 32) % 16;

			//オブジェクトにセットする
			mStepNum[i]->mSprite->GetAnimation()->SetFrameX(frameX);

			//文字の位置を設定する
			float posX = msPosX - mSize * (strlen(outputChar) - i);
			mStepNum[i]->mSprite->SetPos(posX, msPosY, mPosz);

			//UVOFFSET更新
			mStepNum[i]->Update();

			//描画
			mStepNum[i]->Draw();
		}
	}
	break;

	}
}
