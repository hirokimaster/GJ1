#include "SelectScene.h"

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

	const std::filesystem::path folderPath = "Resources/stage/"; // ← ここを自分のパスに
	for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
		if (entry.is_regular_file() && entry.path().extension() == ".csv") {
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
}

void SelectScene::Update()
{
	camera_.UpdateMatrix();
	if (Input::GetInstance()->PressedKey(DIK_SPACE)) {
		GameManager::GetInstance()->ChangeScene("GAME");
	}

	if (Input::GetInstance()->PressedKey(DIK_RETURN)) {
		GameManager::GetInstance()->ChangeScene("TITLE");
	}

	StageSelect();
	selectSprite_->Update();
	for (auto& selectStage : selectStages_) {
		selectStage->Update(selectedStageNum_);
	}
	
	skydome_->Update();
	ObjectManager::GetInstance()->Update();
}

void SelectScene::Draw()
{
	
	postEffect_->Draw();
}

void SelectScene::PostProcessDraw()
{
	postEffect_->PreDraw();
	for (auto& selectStage : selectStages_) {
		selectStage->Draw();
	}
	selectSprite_->Draw();
	ObjectManager::GetInstance()->Draw(camera_);
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
	if (Input::GetInstance()->PressedKey(DIK_RIGHT) && inputWaitTime_ >= maxInputWaitTime_) {
		inputWaitTime_ = 0.0f; // 入力待機時間をリセット
		selectedStageNum_++; // ステージ番号をインクリメント
		// ステージ番号の上限をチェック
		if (selectedStageNum_ == maxStageNum_) {
			selectedStageNum_--; // ステージ番号が最大値を超えないようにする
		}
	}
	else if (Input::GetInstance()->PressedKey(DIK_LEFT) && inputWaitTime_ >= maxInputWaitTime_) {
		inputWaitTime_ = 0.0f; // 入力待機時間をリセット
		selectedStageNum_--; // ステージ番号をデクリメント
		// ステージ番号の下限をチェック
		if (selectedStageNum_ < 0) {
			selectedStageNum_ = 0; // ステージ番号が負にならないようにする
		}
	}
}