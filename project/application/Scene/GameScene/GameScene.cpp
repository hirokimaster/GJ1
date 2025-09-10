/**
* @file GameScene.cpp
* @brief ゲームシーン
* @author 仁平 琉乃
*/

#include "GameScene.h"
#include "engine/3d/ObjectManager/ObjectManager.h"
#include "application/GameObject/SharedGameData/SharedGameData.h"
#include "application/GameSound/GameSound.h"
GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	// モデル、テクスチャのロード
	ModelManager::LoadObjModel("Unit/sword/blue_ken.obj");
	TextureManager::Load("resources/Unit/sword/ken.png");
	ModelManager::LoadObjModel("Unit/Archer/yumi_move2.obj");
	ModelManager::LoadObjModel("Unit/Archer/yumi.obj");
	TextureManager::Load("resources/Unit/Archer/ken.png");
	ModelManager::LoadObjModel("Unit/gardian/tate.obj");
	// 人だけのモデル
	ModelManager::LoadObjModel("Unit/gardian/hito.obj");
	ModelManager::LoadObjModel("Unit/sword/hito.obj");
	// ウェポンのモデル
	ModelManager::LoadObjModel("Unit/gardian/tatedake.obj");
	ModelManager::LoadObjModel("Unit/sword/kendake.obj");
	// ユニット登録
	UnitFactory::Register("warrior", [] { return std::make_unique<Warrior>("warrior"); });
	UnitFactory::Register("archer", [] { return std::make_unique<Archer>("archer"); });
	UnitFactory::Register("swordsman", [] { return std::make_unique<Swordsman>("swordsman"); });
	gameCamera_ = std::make_unique<GameCamera>();
	gameCamera_->Init();

	// ポストエフェクト初期化
	postEffect_ = std::make_unique<PostProcess>();
	postEffect_->Initialize();
	postEffect_->SetEffect(PostEffectType::Bloom);

	LoadTextureFile(); // texture読み込み

	gameSprite_ = std::make_unique<GameSprite>();
	gameSprite_->Initialize();

	isGameOver = false;
	isGameClear = false;

	// プール
	projectilePool_ = std::make_unique<ProjectilePool>();
	projectilePool_->Initialize();

	tileMap_ = std::make_unique<TileMap>();
	tileMap_->LoadTile(SharedGameData::GetInstance()->GetStageId());

	player_ = std::make_unique<Player>();
	player_->Init();
	player_->SetTileMap(tileMap_.get());
	player_->SetCamera(&gameCamera_->GetCamera());
	player_->SetProjectilePool(projectilePool_.get());
	player_->SetSelectTile({ 0,static_cast<float>(tileMap_->GetMaxRow()) - 1 });
	player_->SetMaxUnitCount(SharedGameData::GetInstance()->GetMaxUnitCount());
	gameCamera_->SetTileMap(tileMap_.get());
	// スカイドーム
	skydome_ = std::make_unique<Skydome>();
	skydome_->Init();

	enemy_ = std::make_unique<Enemy>();
	enemy_->SetTileMap(tileMap_.get());
	enemy_->SetProjectilePool(projectilePool_.get());
	enemy_->Init();

	// シーン遷移
	transition_ = std::make_unique<FadeOut>();
	transition_->Initialize();
	GameManager::GetInstance()->SetSceneTransition(transition_.get());

	// particle
	particleManager_ = ParticleManager::GetInstance();
	particleManager_->Initialize();

	// エフェクト
	sceneEffect_ = std::make_unique<SceneEffect>();
	sceneEffect_->Initialize();

	
}

void GameScene::Update()
{
	// カメラの切り替え
	if (Input::GetInstance()->PressedKey(DIK_RETURN) || Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_START)) {

		switch (gameCamera_->GetCameraMode())
		{
		case CameraMode::FRONT:
			gameCamera_->SetCameraMode(CameraMode::HIGH);
			break;
		case CameraMode::HIGH:
			gameCamera_->SetCameraMode(CameraMode::SIDE);
			break;
		case CameraMode::SIDE:
			gameCamera_->SetCameraMode(CameraMode::FRONT);
			break;
		}
	}

	gameCamera_->Update();
#ifdef _DEBUG
	if (tileMap_->IsEnemyAtFrontLine() || Input::GetInstance()->PressedKey(DIK_G)) {
		isGameOver = true;
	}
	if (tileMap_->IsAllBlue() || Input::GetInstance()->PressedKey(DIK_C)) {
		isGameClear = true;
	}
#endif // _DEBUG

	if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_X) || Input::GetInstance()->PressedKey(DIK_S) && isGameOver && (!isTransitionClear_)) {
		isTransitionClear_ = true;
		transition_ = std::make_unique<FadeIn>();
		transition_->Initialize();
		GameManager::GetInstance()->SetSceneTransition(transition_.get());
		GameSound::SoundStop(SharedGameData::GetInstance()->GetBGMFile());
		GameSound::SoundPlayBGM("tittle");
		GameManager::GetInstance()->ChangeScene("SELECT");
	}
	else if (isGameClear && (!isTransitionClear_)) {
		if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_Y) || Input::GetInstance()->PressedKey(DIK_B)) {
			isTransitionClear_ = true;
			transition_ = std::make_unique<FadeIn>();
			transition_->Initialize();
			GameManager::GetInstance()->SetSceneTransition(transition_.get());
			// 次のステージへいく前にBGM止める
			GameSound::SoundStop(SharedGameData::GetInstance()->GetBGMFile());
			int nextStage = SharedGameData::GetInstance()->GetStageId() + 1;
			SharedGameData::GetInstance()->LoadFromJson(
				"Resources/stage/json/stage" + std::to_string(nextStage) + ".json"
			);
			SharedGameData::GetInstance()->SetStageId(nextStage); // 管理用に更新
			GameManager::GetInstance()->ChangeScene("GAME");
		}
		else if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_X) || Input::GetInstance()->PressedKey(DIK_S)) {
			// Bキーでセレクトに戻る (あとで変えて)
			isTransitionClear_ = true;
			transition_ = std::make_unique<FadeIn>();
			transition_->Initialize();
			GameManager::GetInstance()->SetSceneTransition(transition_.get());
			GameManager::GetInstance()->ChangeScene("SELECT");
			GameSound::SoundStop(SharedGameData::GetInstance()->GetBGMFile());
		}

	}

	if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_B) || Input::GetInstance()->PressedKey(DIK_R)) {
		transition_ = std::make_unique<FadeIn>();
		transition_->Initialize();
		GameManager::GetInstance()->SetSceneTransition(transition_.get());
		GameManager::GetInstance()->ChangeScene("GAME");
		return;
	}

	tileMap_->Update();

	player_->Update();
	gameSprite_->SetNumber(player_->GetMaxUnitCount());

	enemy_->Update();
	// プール
	projectilePool_->Update();

	skydome_->Update();

	ObjectManager::GetInstance()->Update();

	sceneEffect_->Update();
	particleManager_->Update();

}

void GameScene::Draw()
{
	postEffect_->Draw();
	particleManager_->Draw(gameCamera_->GetCamera());
}

void GameScene::PostProcessDraw()
{
	postEffect_->PreDraw();
	ObjectManager::GetInstance()->Draw(gameCamera_->GetCamera());
	
#ifdef _DEBUG
	ParticleEditor::GetInstance()->Draw(gameCamera_->GetCamera());
#endif // _DEBUG
	if (isGameClear) {
		gameSprite_->ClearDraw();
	}
	else if (isGameOver) {
		gameSprite_->GameOverDraw();
	}
	else if (!isGameClear && !isGameOver) {
		gameSprite_->Draw();
	}

	player_->DrawUI(gameCamera_->GetFrontCamera());
	postEffect_->PostDraw();
}

void GameScene::Collision()
{
}

void GameScene::LoadTextureFile()
{
	TextureManager::Load("resources/TempTexture/white.png");
	TextureManager::Load("resources/UI/haiti.png");
	TextureManager::Load("resources/UI/s.png");
	TextureManager::Load("resources/UI/num.png");
	TextureManager::Load("resources/UI/yazirusi.png");
	TextureManager::Load("resources/UI/retry.png");
	TextureManager::Load("resources/UI/next.png");
	TextureManager::Load("resources/UI/backSelect.png");
}

