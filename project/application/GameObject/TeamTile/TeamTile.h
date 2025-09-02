#pragma once
#include "engine/3d/BaseObject/BaseInstancingObject.h"
class TeamTile : public BaseInstancingObject
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

#pragma region getter

	bool GetIsHit()const { return isHit_; }

	Vector3 GetWorldPosition()const;

	Collider* GetCollider() { return BaseInstancingObject::GetCollider(); }

#pragma endregion

#pragma region setter

	void SetPosition(const Vector3& position) { BaseInstancingObject::SetPosition(position); }

	void SetScale(const Vector3& scale) { BaseInstancingObject::SetScale(scale); }

#pragma endregion


private:
	bool isHit_ = false;
};

