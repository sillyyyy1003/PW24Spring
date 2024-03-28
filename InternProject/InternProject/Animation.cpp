#include "Animation.h"

Animation::Animation()
{

}

Animation::~Animation()
{
	mAnimeTable.clear();
}

void Animation::InitAnime(DirectX::XMINT2 _split)
{
	//SetSplit
	mSplit = _split;

	//SetAnimeTable
	int frameNum = _split.x;
	for (int i = 0; i < _split.x; i++) {
		mAnimeTable.push_back(i);
	}

	//SetEndFrame
	mAnimeTable.push_back(-1);

}

void Animation::Update()
{
	if (!isPlaying) {
		UpdateUV();//In case if need to Change UV
		return;
	}

	UpdateIsPlaying();
	UpdateUV();
}

void Animation::UpdateIsPlaying()
{
	int animeId = 0;

	if (mAnimeTable.size() == 0) {
		//Output DebugLog
		//メッセージボックスで表示
		MessageBoxA(NULL, "AnimeTable is null", "エラー", MB_OK | MB_ICONERROR);
		return;
	}

	animeId = mAnimeTable[(int)mAnimeCounter];
	mAnimeCounter += mAnimeSpeed;
	
	if (isLoop) {

		if (mAnimeTable[(int)mAnimeCounter] == -1) {
			mAnimeCounter = 0.0f;
		}
	}
	else {
		if (mAnimeTable[(int)mAnimeCounter] == -1) {
			mAnimeCounter = 0.0f;
			isPlaying = false;
		}
	}

	//表示させるコマのUVを計算
	mFrame.x = animeId % mSplit.x;
	//if there is only one pattern and the picture is not in line
	//mFrame.y = animeId / mSplit.x;

}

void Animation::UpdateUV()
{
	mOffsetUV.x = 1.0f / mSplit.x * mFrame.x;
	mOffsetUV.y = 1.0f / mSplit.y * mFrame.y;
}

void Animation::SetFrameX(int _frameX)
{
	mFrame.x = _frameX;
}

void Animation::SetFrameY(int _frameY)
{
	mFrame.y = _frameY;
}
