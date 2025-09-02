#pragma once
#include <application/GameObject/Unit/BaseUnit.h>

class Archer : public BaseUnit {
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="name"></param>
	Archer(const std::string& name)
		: BaseUnit(name, 1, 1) {
	}

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack()override;

private:

};

