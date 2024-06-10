#include "Animation.h"

Anime::Animation::Animation()
{

}

Anime::Animation::~Animation()
{
	mAnimeTable.clear();
}

void Anime::Animation::InitAnime(DirectX::XMINT2 _split, AnimePattern _pattern)
{
	//Set split
	mSplit = _split;
	//Set anime pattern
	mPattern = _pattern;

	//Create Anime Table
	int frameNum = _split.x;
	switch(mPattern)
	{
	case Null:
		MessageBoxA(NULL, "AnimePattern is null", "Error", MB_OK | MB_ICONERROR);
		return;
		break;
	}
	for (int i = 0; i < _split.x; i++) {
		mAnimeTable.push_back(i);
	}

	//SetEndFrame
	mAnimeTable.push_back(-1);

}

void Anime::Animation::Update()
{
	if (!isPlaying) {
		UpdateUV();//In case if need to Change UV
		return;
	}

	UpdateIsPlaying();

	UpdateUV();
}

void Anime::Animation::UpdateIsPlaying()
{
	int animeId = 0;

	if (mAnimeTable.size() == 0) {
		//DebugLog
		MessageBoxA(NULL, "AnimeTable is null", "Error", MB_OK | MB_ICONERROR);
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
	switch (mPattern)
	{
	case Null:
		//DebugLog:
		MessageBoxA(NULL, "AnimePattern is null", "Error", MB_OK | MB_ICONERROR);
		return;
		break;
	case SinglePattern:
		mFrame.x = animeId % mSplit.x;
		mFrame.y = animeId / mSplit.y;
		break;
	case MultiPattern:
		//y
		mFrame.x = animeId % mSplit.x;
		break;
	}

	//mFrame.x = animeId % mSplit.x;


}

void Anime::Animation::UpdateUV()
{
	mOffsetUV.x = 1.0f / mSplit.x * mFrame.x;
	mOffsetUV.y = 1.0f / mSplit.y * mFrame.y;
}

void Anime::Animation::SetFrameX(int _frameX)
{
	mFrame.x = _frameX;
}

void Anime::Animation::SetFrameY(int _frameY)
{
	mFrame.y = _frameY;
}
