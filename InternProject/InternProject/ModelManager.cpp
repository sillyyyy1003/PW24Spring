#include "ModelManager.h"
#include "GameObject2D.h"
#include "WaveFrontReader.h"
#include "WICTextureLoader.h"
#include "Model.h"
#include "ResultManager.h"
#include "Scene.h"
#include "UiManager.h"

ModelManager::ModelManager()
{ 
    /*
    プラスα：もっとやりやすい読み込み方法をかんがえよう
    */
   //test = Model::LoadTexture(L"Assets/Img/ASCIILib.png");
    debugFont = Model::LoadTexture(L"Assets/Img/System/ASCIILib.png");
    fade = Model::LoadTexture(L"Assets/Img/System/Fade.png");

    //背景
    stageBg[scene::StageInfo::STAGE1_1]= Model::LoadTexture(L"Assets/Img/Stage1/1_1_bg.png");
	stageBg[scene::StageInfo::STAGE1_2] = Model::LoadTexture(L"Assets/Img/Stage1/1_2_bg.png");
	stageBg[scene::StageInfo::STAGE1_3] = Model::LoadTexture(L"Assets/Img/Stage1/1_3_bg.png");

    //オブジェクト
    coconut[GameObject::object] = Model::LoadTexture(L"Assets/Img/Stage1/1_1_coconut.png");
    coconut[GameObject::shadow] = Model::LoadTexture(L"Assets/Img/Stage1/1_1_coconut_s.png");
    lamp[GameObject::object] = Model::LoadTexture(L"Assets/Img/Stage1/1_1_lamp.png");
    lamp[GameObject::shadow] = Model::LoadTexture(L"Assets/Img/Stage1/1_1_lamp_s.png");
    housePlate[GameObject::object] = Model::LoadTexture(L"Assets/Img/Stage1/1_1_housePlate.png");
    housePlate[GameObject::shadow] = Model::LoadTexture(L"Assets/Img/Stage1/1_1_housePlate_s.png");

    lamp1_2[GameObject::object] = Model::LoadTexture(L"Assets/Img/Stage1/1_2_lamp.png");
    lamp1_2[GameObject::shadow] = Model::LoadTexture(L"Assets/Img/Stage1/1_2_lamp_s.png");
    triangleBlock[GameObject::object] = Model::LoadTexture(L"Assets/Img/Stage1/1_2_bulidingblock.png");
    triangleBlock[GameObject::shadow] = Model::LoadTexture(L"Assets/Img/Stage1/1_2_buldingblock_shadow.png");
    iphone[GameObject::object] = Model::LoadTexture(L"Assets/Img/Stage1/1_2_iphone.png");
    iphone[GameObject::shadow] = Model::LoadTexture(L"Assets/Img/Stage1/1_2_iphone_s.png");

    sandwich[GameObject::object] = Model::LoadTexture(L"Assets/Img/Stage1/1_3_sandwich.png");
    sandwich[GameObject::shadow] = Model::LoadTexture(L"Assets/Img/Stage1/1_3_sandwich_s.png");
    newspaper[GameObject::object] = Model::LoadTexture(L"Assets/Img/Stage1/1_3_newspaper.png");
    newspaper[GameObject::shadow] = Model::LoadTexture(L"Assets/Img/Stage1/1_3_newspaper_s.png");
    bucket[GameObject::object] = Model::LoadTexture(L"Assets/Img/Stage1/1_3_bucket.png");
    bucket[GameObject::shadow] = Model::LoadTexture(L"Assets/Img/Stage1/1_3_bucket_s.png");
    picnicBasket[GameObject::object] = Model::LoadTexture(L"Assets/Img/Stage1/1_3_picnicbasket.png");
    picnicBasket[GameObject::shadow] = Model::LoadTexture(L"Assets/Img/Stage1/1_3_picnicbasket_s.png");

    //Result
    stepNum = Model::LoadTexture(L"Assets/Img/Result/resultNum.png");
    resultNum = Model::LoadTexture(L"Assets/Img/Result/resultNum.png");
	resultTitle = Model::LoadTexture(L"Assets/Img/Result/resultTitle.png");
	resultBg = Model::LoadTexture(L"Assets/Img/Result/resultBG.png");
    resultScoreTitle = Model::LoadTexture(L"Assets/Img/Result/result_score.png");
    resultStepTitle = Model::LoadTexture(L"Assets/Img/Result/result_stepcount.png");

	resultButton[Result::AGAIN] = Model::LoadTexture(L"Assets/Img/Result/result_button_again.png");
    resultButton[Result::RETURN] = Model::LoadTexture(L"Assets/Img/Result/result_button_return.png");
    resultButton[Result::NEXT] = Model::LoadTexture(L"Assets/Img/Result/result_button_next.png");
    resultStar = Model::LoadTexture(L"Assets/Img/Result/Star.png");
    resultStarShadow= Model::LoadTexture(L"Assets/Img/Result/Star_s.png");

    cursor = Model::LoadTexture(L"Assets/Img/Effect/cursor.png");


	uiTitle= Model::LoadTexture(L"Assets/Img/title/00_title.png");

	//tutorial
    //switch
   uiTutorialAnimation[INTRODUCE] = Model::LoadTexture(L"Assets/Img/tutorial/01_switch.png");
   uiTutorialAnimation[MOVE1] = Model::LoadTexture(L"Assets/Img/tutorial/03_switch.png");
   uiTutorialAnimation[MOVE2] = Model::LoadTexture(L"Assets/Img/tutorial/05_switch.png");
   uiTutorialAnimation[MOVE3] = Model::LoadTexture(L"Assets/Img/tutorial/07_switch.png");
   uiTutorialAnimation[MOVE4] = Model::LoadTexture(L"Assets/Img/tutorial/09_switch.png");
   uiTutorialAnimation[SIZECHANGE] = Model::LoadTexture(L"Assets/Img/tutorial/11_switch.png");
   uiTutorialAnimation[COMBINITION] = Model::LoadTexture(L"Assets/Img/tutorial/13_switch.png");
   uiTutorialAnimation[END] = Model::LoadTexture(L"Assets/Img/tutorial/15_switch.png");

	//loopAnimation
   uiTutorial[INTRODUCE]= Model::LoadTexture(L"Assets/Img/tutorial/02_forward.png");
   uiTutorial[MOVE1] = Model::LoadTexture(L"Assets/Img/tutorial/04_skill1.png");
   uiTutorial[MOVE2] = Model::LoadTexture(L"Assets/Img/tutorial/06_skill2.png");
   uiTutorial[MOVE3] = Model::LoadTexture(L"Assets/Img/tutorial/08_skill3.png");
   uiTutorial[MOVE4] = Model::LoadTexture(L"Assets/Img/tutorial/10_skill4.png");
   uiTutorial[SIZECHANGE] = Model::LoadTexture(L"Assets/Img/tutorial/12_skill5.png");
   uiTutorial[COMBINITION] = Model::LoadTexture(L"Assets/Img/tutorial/14_skill6.png");
   uiTutorial[END] = Model::LoadTexture(L"Assets/Img/tutorial/16_start.png");

   uiSelectBg= Model::LoadTexture(L"Assets/Img/System/ui/select/Select_bg.png");
   uiSelectCursor= Model::LoadTexture(L"Assets/Img/System/ui/select/hane.png");
   uiSelectStage[scene::STAGE1_1]= Model::LoadTexture(L"Assets/Img/System/ui/select/stage1.png");
   uiSelectStage[scene::STAGE1_2] = Model::LoadTexture(L"Assets/Img/System/ui/select/stage2.png");
   uiSelectStage[scene::STAGE1_3] = Model::LoadTexture(L"Assets/Img/System/ui/select/stage3.png");
   uiSelectChapter[0] = Model::LoadTexture(L"Assets/Img/System/ui/select/chapter1.png");
   uiSelectChapter[1] = Model::LoadTexture(L"Assets/Img/System/ui/select/chapter2.png");
   uiSelectChapter[2]= Model::LoadTexture(L"Assets/Img/System/ui/select/chapter3.png");

   selectMask = Model::LoadTexture(L"Assets/Img/System/ui/select/stage_select_left_mask.png");
   chapterMask = Model::LoadTexture(L"Assets/Img/System/ui/select/stage_select_right_mask.png");

   uiClear = Model::LoadTexture(L"Assets/Img/System/ui/select/clear.png");//NeedCopy

   stageMask= Model::LoadTexture(L"Assets/Img/System/bg_mask.png");
   resultMask = Model::LoadTexture(L"Assets/Img/System/result_mask.png");
   controlPanel= Model::LoadTexture(L"Assets/Img/System/controlPanel.png");


   //Pause
   uiPauseBg= Model::LoadTexture(L"Assets/Img/System/ui/Pause/pauseBg.png");
   uiPauseButton[0] = Model::LoadTexture(L"Assets/Img/System/ui/Pause/resume.png");
   uiPauseButton[1] = Model::LoadTexture(L"Assets/Img/System/ui/Pause/restart.png");
   uiPauseButton[2] = Model::LoadTexture(L"Assets/Img/System/ui/Pause/select.png");
   uiPauseButton[3] = Model::LoadTexture(L"Assets/Img/System/ui/Pause/sound.png");

    //サウンド画面用
   uiSoundBg= Model::LoadTexture(L"Assets/Img/System/ui/Pause/soundBg.png");//サウンド背景
   uiSoundOp= Model::LoadTexture(L"Assets/Img/System/ui/Pause/pause_note.png");//サウンド調節
   uiSoundCursor= Model::LoadTexture(L"Assets/Img/System/ui/Pause/pause_select.png");

    stageTutorial[0] = Model::LoadTexture(L"Assets/Img/Stage1/hint_direction_animation.png");
    stageTutorial[1] = Model::LoadTexture(L"Assets/Img/Stage1/hint_space_animation.png");
    stageTutorial[2] = Model::LoadTexture(L"Assets/Img/Stage1/hint_h_animation.png");

    stageHint[0] = Model::LoadTexture(L"Assets/Img/Stage1/1_1_hint.png");
    stageHint[1] = Model::LoadTexture(L"Assets/Img/Stage1/1_2_hint.png");
    stageHint[2] = Model::LoadTexture(L"Assets/Img/Stage1/1_3_hint.png");

    stageShapeHint[0]=  Model::LoadTexture(L"Assets/Img/Stage1/1_1_ingame_hint.png");
    stageShapeHint[1] = Model::LoadTexture(L"Assets/Img/Stage1/1_2_ingame_hint.png");
    stageShapeHint[2] = Model::LoadTexture(L"Assets/Img/Stage1/1_3_ingame_hint.png");

    hintBg= Model::LoadTexture(L"Assets/Img/System/bg_shadow.png");
    PauseBg = Model::LoadTexture(L"Assets/Img/System/bg_shadow.png");


    ResultComic[scene::STAGE1_1][0]= Model::LoadTexture(L"Assets/Img/Stage1/Clear/1_1_1.png");
    ResultComic[scene::STAGE1_1][1] = Model::LoadTexture(L"Assets/Img/Stage1/Clear/1_1_2.png");
    ResultComic[scene::STAGE1_1][2] = Model::LoadTexture(L"Assets/Img/Stage1/Clear/1_1_3.png");

    ResultComic[scene::STAGE1_2][0] = Model::LoadTexture(L"Assets/Img/Stage1/Clear/1_2_1.png");
    ResultComic[scene::STAGE1_2][1] = Model::LoadTexture(L"Assets/Img/Stage1/Clear/1_2_2.png");
    ResultComic[scene::STAGE1_2][2] = Model::LoadTexture(L"Assets/Img/Stage1/Clear/1_2_3.png");

    ResultComic[scene::STAGE1_3][0] = Model::LoadTexture(L"Assets/Img/Stage1/Clear/1_3_1.png");
    ResultComic[scene::STAGE1_3][1] = Model::LoadTexture(L"Assets/Img/Stage1/Clear/1_3_2.png");
    ResultComic[scene::STAGE1_3][2] = Model::LoadTexture(L"Assets/Img/Stage1/Clear/1_1_3.png");

    SkipButton = Model::LoadTexture(L"Assets/Img/Result/result_skip_botton.png");
    uiArrow = Model::LoadTexture(L"Assets/Img/System/direction_animation.png");

}

ModelManager::~ModelManager()
{
    SAFE_RELEASE(debugFont);
    SAFE_RELEASE(resultStar);
    SAFE_RELEASE(resultStarShadow);
    SAFE_RELEASE(uiClear);
    SAFE_RELEASE(uiSoundOp);
}

