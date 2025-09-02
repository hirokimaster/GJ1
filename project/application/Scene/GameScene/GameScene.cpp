/**
* @file GameScene.cpp
* @brief ゲームシーン
* @author 仁平 琉乃
*/

#include "GameScene.h"

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
}

void GameScene::Update()
{
	gameCamera_->Update();
}

void GameScene::Draw()
{
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

