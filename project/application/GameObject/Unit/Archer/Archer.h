#pragma once
#include <application/GameObject/Unit/BaseUnit.h>
#include <engine/Input/Input.h>

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
	void Initialize(Vector2 pos);

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack()override;

	/// <summary>
	/// アクション範囲
	/// </summary>
	/// <param name="targetPosition"></param>
	/// <returns></returns>
	bool IsInActionRange(const GridPosition& targetPosition)const;

#pragma region setter


#pragma endregion
	bool CanAttackInFront();

	bool CanAttackInBack();

	void Move();

	void CheckAttackHit();

private:
	int32_t minRange_;
	int32_t maxRange_;

	int shotTimer_ = 0;
};

