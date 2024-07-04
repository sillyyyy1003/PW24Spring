#pragma once
#include "DirectX3D.h"
#include "WaveFrontReader.h"
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

//Pictrue&Model 
class ModelManager
{
public:
    //2D
    //ID3D11ShaderResourceView* test;

    //Tool
    ID3D11ShaderResourceView* debugFont;
    ComPtr<ID3D11ShaderResourceView> fade;

    //GameObject
    //Background
    ComPtr<ID3D11ShaderResourceView> stageBg[3];

    ComPtr<ID3D11ShaderResourceView> coconut[2];
    ComPtr<ID3D11ShaderResourceView> lamp[2];
    ComPtr<ID3D11ShaderResourceView> housePlate[2];

    ComPtr<ID3D11ShaderResourceView> lamp1_2[2];
    ComPtr<ID3D11ShaderResourceView> triangleBlock[2];
    ComPtr<ID3D11ShaderResourceView> iphone[2];

    ComPtr<ID3D11ShaderResourceView> sandwich[2];
    ComPtr<ID3D11ShaderResourceView> newspaper[2];
    ComPtr<ID3D11ShaderResourceView> bucket[2];
    ComPtr<ID3D11ShaderResourceView> picnicBasket[2];
    
    ComPtr<ID3D11ShaderResourceView> stepNum;
    //Result用
    ComPtr<ID3D11ShaderResourceView> resultNum;//手数表示
    ComPtr<ID3D11ShaderResourceView> resultTitle;
    ComPtr<ID3D11ShaderResourceView> resultBg;
    ComPtr<ID3D11ShaderResourceView> resultScoreTitle;//星獲得タイトル
    ComPtr<ID3D11ShaderResourceView> resultStepTitle;//手数タイトル
    ComPtr<ID3D11ShaderResourceView> resultButton[3];
    ID3D11ShaderResourceView* resultStar;
    ID3D11ShaderResourceView* resultStarShadow;

    //Result Comics
    ComPtr<ID3D11ShaderResourceView> ResultComic[3][3];
    ComPtr<ID3D11ShaderResourceView> SkipButton;

    //Effect
	ComPtr<ID3D11ShaderResourceView> cursor;

    //Ui
    ComPtr<ID3D11ShaderResourceView> uiTitle;

    //tutorial
    ComPtr<ID3D11ShaderResourceView> uiTutorialAnimation[8];//switch
    ComPtr<ID3D11ShaderResourceView> uiTutorial[8];//loop

    ComPtr<ID3D11ShaderResourceView> uiSelectBg;

    ComPtr<ID3D11ShaderResourceView> uiSelectCursor;
    ComPtr<ID3D11ShaderResourceView> uiSelectStage[3];
    ComPtr<ID3D11ShaderResourceView> uiSelectChapter[3];
    ComPtr<ID3D11ShaderResourceView> selectMask;
    ComPtr<ID3D11ShaderResourceView> chapterMask;

    ID3D11ShaderResourceView* uiClear;//NeedCopy

    ComPtr<ID3D11ShaderResourceView> stageMask;
    ComPtr<ID3D11ShaderResourceView> resultMask;
    ComPtr<ID3D11ShaderResourceView> controlPanel;



    ComPtr<ID3D11ShaderResourceView> uiPauseBg;
    ComPtr<ID3D11ShaderResourceView> uiPauseButton[4];


    //サウンド画面用
    ComPtr<ID3D11ShaderResourceView> uiSoundBg;//サウンド背景
    ComPtr<ID3D11ShaderResourceView> uiSoundOp_SE;//サウンド調節
    ComPtr<ID3D11ShaderResourceView> uiSoundCursor;
    ID3D11ShaderResourceView* uiSoundOp;//サウンド調節

    ComPtr<ID3D11ShaderResourceView> stageTutorial[3];

    ComPtr<ID3D11ShaderResourceView> stageHint[3];
    ComPtr<ID3D11ShaderResourceView> stageShapeHint[3];

    ComPtr<ID3D11ShaderResourceView> hintBg;//ヒント出された時の描画
    ComPtr<ID3D11ShaderResourceView> PauseBg;//ヒント出された時の描画

    ComPtr<ID3D11ShaderResourceView> uiArrow;
public:

    ModelManager();

    ~ModelManager();

};

