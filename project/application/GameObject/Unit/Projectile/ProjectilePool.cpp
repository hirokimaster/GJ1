#include "ProjectilePool.h"

void ProjectilePool::Initialize() {
	// 初期化時にあらかじめ作っておく
	for (uint32_t i = 0; i < kPoolSize-100; ++i) {
		Create("arrow");
	}
	for (uint32_t i = 0+100; i < kPoolSize ; ++i) {
		Create("sword");
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
				projectile->SetPosition({ -10.0f, -10.0f, -10.0f });
				PushPool("arrow", projectile.get());
			}
			else if (projectile->GetName() == "sword") {
				projectile->SetPosition({ -10.0f, -10.0f, -10.0f });
				PushPool("sword", projectile.get());
			}
		}
	}
}