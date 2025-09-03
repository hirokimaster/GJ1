#pragma once
#include "engine/3d/BaseObject/BaseInstancingObject.h"


class TeamTile : public BaseInstancingObject
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector2 mapPos, int tileMode, int rowNum);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();


	void ColorChange();

#pragma region getter

	bool GetIsHit()const { return isHit_; }

	Vector3 GetWorldPosition()const;

	Collider* GetCollider() { return BaseInstancingObject::GetCollider(); }

	int GetTileMode()const { return tileMode_; }

#pragma endregion

#pragma region setter

	void SetPosition(const Vector3& position) { BaseInstancingObject::SetPosition(position); }

	void SetScale(const Vector3& scale) { BaseInstancingObject::SetScale(scale); }

	void SetTileMode(int mode) { tileMode_ = mode; }

#pragma endregion


private:
	bool isHit_ = false;
	int tileMode_ = 0; // 0:通常 1:味方 2:敵
	// 何行目か
	int32_t rowNum_ = 0;
};

