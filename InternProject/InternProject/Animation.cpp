#include "Animation.h"
#include <string>

#include "DebugLog.h"

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
	case NULL_PATTERN:
		//DebugLog
		DebugLog::Log("AnimePattern is null");
		return;
		break;
	case SINGLE_PATTERN:
	{
		int num = mSplit.x * mSplit.y;
		for (int i = 0; i < num; i++)
		{
			mAnimeTable.push_back(i);
		}
	}
		break;

	case MULTI_PATTERN:
		for(int i=0;i<mSplit.x;i++)
		{
			mAnimeTable.push_back(i);
		}
		break;
	}
	

	//SetEndFrame
	mAnimeTable.push_back(-1);

}

void Anime::Animation::Update()
{
	if (!isPlaying) {
		UpdateUV();//In case if only need to Change UV
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
		DebugLog::Log("AnimeTable is null");
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
	case NULL:
		DebugLog::Log("AnimePattern is null!");
		return;
		break;
	case SINGLE_PATTERN:
		mFrame.x = animeId % mSplit.x;
		mFrame.y = animeId / mSplit.x;
		break;
	case MULTI_PATTERN:
		//y
		mFrame.x = animeId % mSplit.x;
		break;
	}

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
