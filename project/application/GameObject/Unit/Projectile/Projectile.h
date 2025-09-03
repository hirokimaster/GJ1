#pragma once
//#include <application/GameObject/Unit/BaseUnit.h>
#include <engine/3d/BaseObject/BaseInstancingObject.h>

class Projectile : public BaseInstancingObject{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="name"></param>
	Projectile(const std::string name)
		:name_(name){}

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Projectile(){}

	/// <summary>
	/// object生成
	/// </summary>
	/// <param name="modelName"></param>
	/// <param name="textureName"></param>
	void CreateObject(const std::string& modelName, const std::string& textureName);

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 攻撃が当たった時の処理
	/// </summary>
	/// <param name="target"></param>
	//virtual void OnHit(BaseUnit* target) = 0;

#pragma region getter
	/// <summary>
	/// アクティブかどうか
	/// </summary>
	/// <returns></returns>
	bool GetIsActive() const{ return active_; }

	const std::string GetName()const { return name_; }

#pragma endregion

	/// <summary>
	/// アクティブ化
	/// </summary>
	void Activate() { active_ = true; }

	/// <summary>
	/// アクティブ解除
	/// </summary>
	void Deactivate() { active_ = false; };

protected:
	std::string name_;
	bool active_ = false;
};
