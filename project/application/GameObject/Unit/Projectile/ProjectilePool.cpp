#include "ProjectilePool.h"

void ProjectilePool::Initialize() {
	// 初期化時にあらかじめ作っておく
	for (uint32_t i = 0; i < kPoolSize; ++i) {
		Create("arrow");
	}
}

void ProjectilePool::Update() {
	// 更新
	for (auto& projectile : projectiles_) {
		// アクティブのものだけ
		if (projectile->GetIsActive()) {
			projectile->Update();
		}

		// アクティブじゃなかったら戻す
		if (!projectile->GetIsActive()) {
			if (projectile->GetName() == "arrow") {
				PushPool("arrow", projectile.get());
			}
		}
	}
}