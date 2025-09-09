#pragma once
#include "engine/Graphics/Effects/Particle/ParticleManager.h"

class SceneEffect {
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="playerRotate"></param>
	/// <param name="playerPosition"></param>
	void Update();

#pragma region setter

	void SetLifeTime(float time) { lifeTime_ = time; }

	void SetIsActive(bool flag) {
		sceneEffectRed_->SetIsActive(flag);
		sceneEffectBlue_->SetIsActive(flag);
	}

#pragma endregion

private:

	ParticleManager* particleManager_ = nullptr;
	GPUParticle* sceneEffectRed_ = nullptr;
	GPUParticle* sceneEffectBlue_ = nullptr;
	float lifeTime_ = 0.0f;
};

