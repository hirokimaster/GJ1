/**
* @file GameScene.cpp
* @brief ゲームシーン
* @author 仁平 琉乃
*/

#include "GameScene.h"
#include "engine/3d/ObjectManager/ObjectManager.h"
#include "application/GameObject/TileMap/TileMap.h"
GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	gameCamera_ = std::make_unique<GameCamera>();
	gameCamera_->Init();

	TileMap::LoadTile(teamTiles_);
}

void GameScene::Update()
{
	gameCamera_->Update();
	for (auto& tile : teamTiles_) {
		tile->Update();
	}
	ObjectManager::GetInstance()->Update();
}

void GameScene::Draw()
{
	ObjectManager::GetInstance()->Draw(gameCamera_->GetCamera());
}

void GameScene::PostProcessDraw()
{
}

void GameScene::Collision()
{
}

void GameScene::LoadTextureFile()
{
}

