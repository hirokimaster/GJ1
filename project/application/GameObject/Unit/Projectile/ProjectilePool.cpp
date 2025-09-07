#include "ProjectilePool.h"

void ProjectilePool::Initialize() {
	// 初期化時にあらかじめ作っておく
	for (uint32_t i = 0; i < kPoolSize-200; ++i) {
		Create("arrow");
	}
	for (uint32_t i = kPoolSize - 200; i < kPoolSize -100 ; ++i) {
		Create("sword");
	}
	for (uint32_t i = kPoolSize - 100; i < kPoolSize; ++i) {
		Create("shield");
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
			else if (projectile->GetName() == "shield") {
				projectile->SetPosition({ -10.0f, -10.0f, -10.0f });
				PushPool("shield", projectile.get());
			}
		}
	}
}