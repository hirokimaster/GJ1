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

	// モデル、テクスチャのロード
	ModelManager::LoadObjModel("Unit/sword/blue_ken.obj");
	TextureManager::Load("resources/Unit/sword/ken.png");
	ModelManager::LoadObjModel("Unit/Archer/yumi.obj");
	TextureManager::Load("resources/Unit/Archer/ken.png");

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

	// シーン遷移
	transition_ = std::make_unique<FadeOut>();
	transition_->Initialize();
	GameManager::GetInstance()->SetSceneTransition(transition_.get());


}

void GameScene::Update()
{
	gameCamera_->Update();

	if (tileMap_->IsEnemyAtFrontLine() || Input::GetInstance()->PressedKey(DIK_G)) {
		isGameOver = true;
	}
	if (tileMap_->IsAllBlue() || Input::GetInstance()->PressedKey(DIK_C)) {
		isGameClear = true;
	}

	if (Input::GetInstance()->PressedKey(DIK_S) && isGameOver && (!isTransitionClear_)) {
		isTransitionClear_ = true;
		transition_ = std::make_unique<FadeIn>();
		transition_->Initialize();
		GameManager::GetInstance()->SetSceneTransition(transition_.get());
		GameManager::GetInstance()->ChangeScene("SELECT");
	}
	else if (Input::GetInstance()->PressedKey(DIK_S) &&isGameClear && (!isTransitionClear_)) {
		isTransitionClear_ = true;
		transition_ = std::make_unique<FadeIn>();
		transition_->Initialize();
		GameManager::GetInstance()->SetSceneTransition(transition_.get());
		GameManager::GetInstance()->ChangeScene("SELECT");
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
	postEffect_->Draw();
}

void GameScene::PostProcessDraw()
{
	postEffect_->PreDraw();
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

	player_->DrawUI(gameCamera_->GetCamera());
	postEffect_->PostDraw();
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

