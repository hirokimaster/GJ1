#include "SceneEffect.h"

void SceneEffect::Initialize()
{
	// texture
	TextureManager::Load("resources/TempTexture/circle.png");
	particleManager_ = ParticleManager::GetInstance();
	// particleManagerから取ってくる
	sceneEffectRed_ = particleManager_->GetParticle("sceneEffectParticle", "TempTexture/circle.png");
	sceneEffectBlue_ = particleManager_->GetParticle("sceneEffectParticleBlue","TempTexture/circle.png");
	// 生存時間設定
	lifeTime_ = 60000.0f;
	sceneEffectRed_->SetLifeTime(lifeTime_);
	//sceneEffectRed_->SetModel("TempModel/board.obj");
	//sceneEffectBlue_->SetModel("TempModel/board.obj");
	sceneEffectBlue_->SetLifeTime(lifeTime_);
}

void SceneEffect::Update()
{
	// パーティクルのパラメーターを設定
	sceneEffectRed_->SetParticleParam(particleManager_->GetParam("sceneEffectParticle"));
	sceneEffectBlue_->SetParticleParam(particleManager_->GetParam("sceneEffectParticleBlue"));
	// アクティブにする
	sceneEffectRed_->SetIsActive(true);
	sceneEffectRed_->SetIsActive(true);

}