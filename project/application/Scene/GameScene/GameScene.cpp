/**
* @file GameScene.cpp
* @brief ゲームシーン
* @author 仁平 琉乃
*/

#include "GameScene.h"
#include "engine/3d/ObjectManager/ObjectManager.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	// ユニット登録
	UnitFactory::Register("warrior", [] { return std::make_unique<Warrior>("warrior"); });
	UnitFactory::Register("archer", [] { return std::make_unique<Archer>("archer"); });

	gameCamera_ = std::make_unique<GameCamera>();
	gameCamera_->Init();

	// ポストエフェクト初期化
	postEffect_ = std::make_unique<PostProcess>();
	postEffect_->Initialize();

	LoadTextureFile(); // texture読み込み

	gameSprite_ = std::make_unique<GameSprite>();
	gameSprite_->Initialize();

	isGameOver = false;
	isGameClear = false;
  
	// プール
	projectilePool_ = std::make_unique<ProjectilePool>();
	projectilePool_->Initialize();

	tileMap_ = std::make_unique<TileMap>();
	tileMap_->LoadTile();

	player_ = std::make_unique<Player>();
	player_->Init();
	player_->SetTileMap(tileMap_.get());
	player_->SetProjectilePool(projectilePool_.get());
	gameCamera_->SetTileMap(tileMap_.get());
	// スカイドーム
	skydome_ = std::make_unique<Skydome>();
	skydome_->Init();

	enemy_ = std::make_unique<Enemy>();
	enemy_->SetTileMap(tileMap_.get());
	enemy_->SetProjectilePool(projectilePool_.get());
	enemy_->Init();

}

void GameScene::Update()
{
	gameCamera_->Update();

	if (tileMap_->IsEnemyAtFrontLine()) {
		isGameOver = true;
	}
	if (tileMap_->IsAllBlue()) {
		isGameClear = true;
	}

	if (isGameOver) {
		if (Input::GetInstance()->PressedKey(DIK_S)) {
			GameManager::GetInstance()->ChangeScene("SELECT");
		}
	}
	else if (isGameClear) {
		if (Input::GetInstance()->PressedKey(DIK_S)) {
			GameManager::GetInstance()->ChangeScene("SELECT");
		}
	}

	tileMap_->Update();

	player_->Update();
	enemy_->Update();
	// プール
	projectilePool_->Update();

	skydome_->Update();
  
	ObjectManager::GetInstance()->Update();
}

void GameScene::Draw()
{
	ObjectManager::GetInstance()->Draw(gameCamera_->GetCamera());

	if (isGameClear) {
		gameSprite_->ClearDraw();
	}
	else if (isGameOver) {
		gameSprite_->GameOverDraw();
	}
	else if (!isGameClear && !isGameOver) {
		gameSprite_->Draw();
	}

	//postEffect_->Draw();
}

void GameScene::PostProcessDraw()
{
	/*postEffect_->PreDraw();
	postEffect_->PostDraw();*/
}

void GameScene::Collision()
{
}

void GameScene::LoadTextureFile()
{
	TextureManager::Load("resources/TempTexture/white.png");
	TextureManager::Load("resources/UI/ui.png");
	TextureManager::Load("resources/UI/s.png");
}

