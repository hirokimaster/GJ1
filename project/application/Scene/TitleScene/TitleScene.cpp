/**
* @file TitleScene.cpp
* @brief タイトルシーン
* @author 仁平 琉乃
*/

#include "TitleScene.h"
#include "engine/3d/ObjectManager/ObjectManager.h"
TitleScene::TitleScene()
{

	
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	// particle
	particleManager_ = ParticleManager::GetInstance();
	particleManager_->Initialize();
	ModelManager::LoadObjModel("TempModel/board.obj");

	gameCamera_ = std::make_unique<GameCamera>();
	gameCamera_->Init();

	// ポストエフェクト初期化
	postEffect_ = std::make_unique<PostProcess>();
	postEffect_->Initialize();
	postEffect_->SetEffect(PostEffectType::Bloom); // ブルーム有効

	LoadTextureFile(); // texture読み込み

	titleSprite_ = std::make_unique<TitleSprite>();
	titleSprite_->Initialize();
	
	// シーン遷移用
	transition_ = std::make_unique<FadeOut>();
	transition_->Initialize();
	GameManager::GetInstance()->SetSceneTransition(transition_.get());
	isTransition_ = false;


	// エフェクト
	sceneEffect_ = std::make_unique<SceneEffect>();
	sceneEffect_->Initialize();

	// スカイドーム
	skydome_ = std::make_unique<Skydome>();
	skydome_->Init();
}

void TitleScene::Update()
{
	// Aボタンが押されたらシーン遷移処理を開始する
	if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A) || Input::GetInstance()->PressedKey(DIK_SPACE)) {
		if (!isTransition_) {// シーン遷移がまだ始まっていない場合のみ
			isTransition_ = true;
			transition_ = std::make_unique<FadeIn>();
			transition_->Initialize();
			GameManager::GetInstance()->SetSceneTransition(transition_.get());
			GameManager::GetInstance()->ChangeScene("SELECT");
		}
	}
	skydome_->Update();
	ObjectManager::GetInstance()->Update();
	sceneEffect_->Update();
	particleManager_->Update();
	
}

void TitleScene::Draw()
{
	postEffect_->Draw();
}

void TitleScene::PostProcessDraw()
{
	postEffect_->PreDraw();
	ObjectManager::GetInstance()->Draw(gameCamera_->GetCamera());
	particleManager_->Draw(gameCamera_->GetCamera());
	titleSprite_->Draw();
#ifdef _DEBUG
	ParticleEditor::GetInstance()->Draw(gameCamera_->GetCamera());
#endif // _DEBUG
	

	postEffect_->PostDraw();
}

void TitleScene::LoadTextureFile()
{
	TextureManager::Load("resources/TempTexture/white.png");
	TextureManager::Load("resources/TempTexture/white2.png");
	TextureManager::Load("resources/UI/space.png");
	TextureManager::Load("resources/UI/title2.png");
}
