#pragma once
#include <application/GameObject/Unit/BaseUnit.h>

class Swordsman : public BaseUnit {
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="name"></param>
	Swordsman(const std::string& name)
		: BaseUnit(name, 100, 1) {
	}

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector2 pos);

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack()override;

	bool CanAttackInFront()override;

	bool IsInActionRange(const GridPosition& targetPosition) const override;

public:

	bool CanAttackInBack();

	void Move();

	void CheckAttackHit();

private:
	int32_t attackTimer_ = 0;

};