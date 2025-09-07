#pragma once
#include <application/GameObject/Unit/Projectile/Projectile.h>
#include <application/GameObject/Unit/Projectile/Arrow/Arrow.h>
#include <application/GameObject/Unit/Projectile/Sword/Sword.h>
#include <map>
#include <queue>

class ProjectilePool {
public:	

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 生成
	/// </summary>
	/// <param name="name"></param>
	void Create(const std::string& name) {
		std::unique_ptr<Projectile> projectile;
		if (name == "arrow") {
			projectile = std::make_unique<Arrow>("arrow");
			projectile->Initialize();
		}
		else if (name == "sword") {
			projectile = std::make_unique<Sword>("sword");
			projectile->Initialize();
		}

		Projectile* ptr = projectile.get();
		projectiles_.push_back(std::move(projectile));
		pool_[name].push(ptr);
	}

	/// <summary>
	/// poolから取り出す
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	Projectile* Get(const std::string& name) {
		// 空だったら新しく作る
		if (pool_[name].empty()) {
			// 最大数を越えてたら
			if (projectiles_.size() > kPoolSize) {
				return nullptr;
			}
			Create(name);
		}
		
		// キューから取り出す
		Projectile* projectile = pool_[name].front();
		pool_[name].pop();

		return projectile;
	}

	/// <summary>
	/// poolに入れる
	/// </summary>
	/// <param name="name"></param>
	/// <param name="ptr"></param>
	void PushPool(const std::string& name, Projectile* ptr) {
		 // nullだったらここで止める
		if (!ptr) return;

		// アクティブ解除
		ptr->Deactivate();
		// poolに戻す
		pool_[name].push(ptr);
	}

public: //Getter
	/// <summary>
	/// poolのサイズ
	/// </summary>
	/// <returns></returns>
	// コピーではなく参照を返す
	const std::vector<std::unique_ptr<Projectile>>& GetProjectiles() const {
		return projectiles_;
	}

private:
	static const uint32_t kPoolSize = 600; // poolのサイズ
	std::vector<std::unique_ptr<Projectile>> projectiles_;
	std::map<std::string, std::queue<Projectile*>> pool_;
};
