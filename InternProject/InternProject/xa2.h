//=============================================================================
//
// サウンド処理 [xa2.h]
//
//=============================================================================
#ifndef _XAUDIO2_H_
#define _XAUDIO2_H_

#include <xaudio2.h>

// サウンドファイル
typedef enum
{
	BGM_Stage1 = 0,		// BGM
	BGM_Stage2,			// BGM
	BGM_Stage3,			// BGM
	BGM_SelectStage,	// BGM
	BGM_TITLE,			// BGM
	

	SE_TITLE,			// SE
	SE_Select,			// SE
	SE_SelectDecide,	// SE
	SE_Present,			// SE
	SE_Combine,			// SE
	SE_Result,
	SE_Press,
	SE_Plant,		
	SE_Interval1,
	SE_Interval2,
	SE_Interval3,
	SE_Limitation,
	SE_MOVE,
	


	SOUND_LABEL_LAST,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

// ゲームループ開始前に呼び出すサウンドの初期化処理
HRESULT XA_Initialize(void);

// ゲームループ終了後に呼び出すサウンドの解放処理
void XA_Release(void);

// 引数で指定したサウンドを再生する
void XA_Play(SOUND_LABEL label);

// 引数で指定したサウンドを停止する
void XA_Stop(SOUND_LABEL label);

// 引数で指定したサウンドの再生を再開する
void XA_Resume(SOUND_LABEL label);

// 引数で指定したサウンドの音量を数値で設定する
void XA_SetVolume(SOUND_LABEL label, float volume);






#endif
