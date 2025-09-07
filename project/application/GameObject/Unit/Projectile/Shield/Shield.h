#pragma once
#include <application/GameObject/Unit/Projectile/Projectile.h>


class Shield : public Projectile {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="name"></param>
	Shield(const std::string& name)
		:Projectile(name) {
	}

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 当てたときの挙動
	/// </summary>
	//void OnHit(BaseUnit* target)override;

};
