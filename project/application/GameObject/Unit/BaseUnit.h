#pragma once
#include "engine/3d/BaseObject/BaseInstancingObject.h"
#include <string>

class BaseUnit : public BaseInstancingObject {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="name"></param>
	/// <param name="hp"></param>
	/// <param name="attack"></param>
	BaseUnit(const std::string& name, uint32_t hp, uint32_t attack)
		: name_(name), hp_(hp), attack_(attack){}

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BaseUnit() {};

	/// <summary>
	/// object生成
	/// </summary>
	/// <param name="modelName"></param>
	/// <param name="textureName"></param>
	void CreateObject(const std::string& modelName, const std::string& textureName);

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 攻撃
	/// </summary>
	virtual void Attack() = 0;

	/// <summary>
	/// ダメージ食らった
	/// </summary>
	/// <param name="damage"></param>
	void TakeDamage(uint32_t damage) {
		hp_ = hp_ - damage;
	}

#pragma region getter
	
	bool GetIsAlive() const { return hp_ > 0; }

	const std::string GetName() const { return name_; }

#pragma endregion

protected:
	std::string name_; // 役職の名前
	uint32_t hp_; // ライフ
	uint32_t attack_; // 攻撃力
};
