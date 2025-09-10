#include "SelectScene.h"

#include "application/GameObject/SharedGameData/SharedGameData.h"
#include "application/GameSound/GameSound.h"
SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
}

void SelectScene::Initialize()
{
	camera_.Initialize();
	// ポストエフェクト初期化
	postEffect_ = std::make_unique<PostProcess>();
	postEffect_->Initialize();
	postEffect_->SetEffect(PostEffectType::Bloom);

	LoadTextureFile(); // texture読み込み

	selectSprite_ = std::make_unique<SelectSprite>();
	selectSprite_->Initialize();

	const std::filesystem::path folderPath = "Resources/stage/json"; // ← ここを自分のパスに
	for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
		if (entry.is_regular_file() && entry.path().extension() == ".json") {
			maxStageNum_++;
		}
	}

	// 選択ステージのスプライトの初期化
	for (int i = 0; i < maxStageNum_; i++) {
		std::unique_ptr<SelectStage> selectStage_ = std::make_unique<SelectStage>();
		selectStage_->Initialize(i);
		selectStages_.push_back(std::move(selectStage_));

	}

	// スカイドーム
	skydome_ = std::make_unique<Skydome>();
	skydome_->Init();

	// シーン遷移用
	transition_ = std::make_unique<FadeOut>();
	transition_->Initialize();
	GameManager::GetInstance()->SetSceneTransition(transition_.get());
	isTransition_ = false;

	// particle
	particleManager_ = ParticleManager::GetInstance();
	particleManager_->Initialize();

	// エフェクト
	sceneEffect_ = std::make_unique<SceneEffect>();
	sceneEffect_->Initialize();

	
}

void SelectScene::Update()
{
	camera_.UpdateMatrix();

	// SPACEボタンが押されたらシーン遷移処理を開始する
	if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A) || Input::GetInstance()->PressedKey(DIK_SPACE)) {
		if (!isTransition_) {// シーン遷移がまだ始まっていない場合のみ
			isTransition_ = true;
			transition_ = std::make_unique<FadeIn>();
			transition_->Initialize();
			SharedGameData::GetInstance()->LoadFromJson("Resources/stage/json/stage" + std::to_string(selectedStageNum_ + 1) + ".json");
			GameManager::GetInstance()->SetSceneTransition(transition_.get());
			GameManager::GetInstance()->ChangeScene("GAME");
			GameSound::SoundStop("tittle");
			GameSound::SoundPlayBGM(SharedGameData::GetInstance()->GetBGMFile());
		}
	}
	// RETURNボタンが押されたらシーン遷移処理を開始する
	else if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_B) || Input::GetInstance()->PressedKey(DIK_RETURN)) {
		if (!isTransition_) {// シーン遷移がまだ始まっていない場合のみ
			isTransition_ = true;
			transition_ = std::make_unique<FadeIn>();
			transition_->Initialize();
			GameManager::GetInstance()->SetSceneTransition(transition_.get());
			GameManager::GetInstance()->ChangeScene("TITLE");
			GameSound::SoundStop("tittle");
		}
	}

	StageSelect();
	selectSprite_->Update();
	for (auto& selectStage : selectStages_) {
		selectStage->Update(selectedStageNum_);
	}

	skydome_->Update();
	ObjectManager::GetInstance()->Update();

	sceneEffect_->Update();
	particleManager_->Update();
}

void SelectScene::Draw()
{

	postEffect_->Draw();
	particleManager_->Draw(camera_);
}

void SelectScene::PostProcessDraw()
{
	postEffect_->PreDraw();
	ObjectManager::GetInstance()->Draw(camera_);
	for (auto& selectStage : selectStages_) {
		selectStage->Draw();
	}
	
#ifdef _DEBUG
	ParticleEditor::GetInstance()->Draw(camera_);
#endif // _DEBUG
	selectSprite_->Draw();

	postEffect_->PostDraw();
}

void SelectScene::LoadTextureFile()
{
	TextureManager::Load("resources/TempTexture/white.png");
	TextureManager::Load("resources/UI/select.png");
	TextureManager::Load("resources/UI/selectUI.png");
}

void SelectScene::StageSelect()
{
	inputWaitTime_ += 0.016f; // フレームごとに入力待機時間を増加
	if (inputWaitTime_ >= maxInputWaitTime_) {
		inputWaitTime_ = maxInputWaitTime_; // 入力待機時間の上限を設定
	}
	if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_DPAD_RIGHT) || Input::GetInstance()->PressedKey(DIK_RIGHT) && inputWaitTime_ >= maxInputWaitTime_) {
		inputWaitTime_ = 0.0f; // 入力待機時間をリセット
		selectedStageNum_++; // ステージ番号をインクリメント
		// ステージ番号の上限をチェック
		if (selectedStageNum_ == maxStageNum_) {
			selectedStageNum_--; // ステージ番号が最大値を超えないようにする
		}
	}
	else if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_DPAD_LEFT) || Input::GetInstance()->PressedKey(DIK_LEFT) && inputWaitTime_ >= maxInputWaitTime_) {
		inputWaitTime_ = 0.0f; // 入力待機時間をリセット
		selectedStageNum_--; // ステージ番号をデクリメント
		// ステージ番号の下限をチェック
		if (selectedStageNum_ < 0) {
			selectedStageNum_ = 0; // ステージ番号が負にならないようにする
		}
	}
}