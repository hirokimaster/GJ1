#include "TeamTile.h"
#include "engine/Graphics/TextureManager/TextureManager.h" 
#include "engine/3d/Model/ModelManager.h" 
void TeamTile::Initialize(Vector2 mapPos, int tileMode, int rowNum)
{
	TextureManager::Load("resources/TempTexture/white2.png");
	ModelManager::LoadObjModel("TempModel/cube.obj");
	// object共通の初期化
	BaseInstancingObject::Initialize("TempModel/cube.obj", "TempTexture/white2.png", ColliderType::AABB);
	
	BaseInstancingObject::SetPosition({ mapPos.x, 0.0f,mapPos.y});

	// タイルモード
	tileMode_ = tileMode;
	// 何行目か
	rowNum_ = rowNum;
	ColorChange();

	// colliderの属性
	collider_->SetCollosionAttribute(kCollisionAttributeEnemyBullet);
	collider_->SetCollisionMask(kCollisionAttributePlayer); // 当たる対象
}

void TeamTile::Update()
{

	ColorChange();
	BaseInstancingObject::Update(); // object共通の更新処理
	collider_->SetWorldPosition(GetWorldPosition());
	collider_->SetScale(object_.lock()->worldTransform.scale);
}

void TeamTile::ColorChange()
{
	switch (tileMode_)
	{
		case 0: // 通常
			object_.lock()->color = { 1.0f,1.0f,1.0f,1.0f };
		break;
		case 1: // 味方
			object_.lock()->color = { 0.0f,0.0f,1.0f,1.0f };
		break;
		case 2: // 敵
			object_.lock()->color = { 1.0f,0.0f,0.0f,1.0f };
		break;
		case 3: // 敵のアーチャータイル
			object_.lock()->color = { 1.0f,0.0f,0.0f,1.0f };
			
		break;
	}
}

Vector3 TeamTile::GetWorldPosition() const
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = object_.lock()->worldTransform.matWorld.m[3][0];
	worldPos.y = object_.lock()->worldTransform.matWorld.m[3][1];
	worldPos.z = object_.lock()->worldTransform.matWorld.m[3][2];

	return worldPos;
}
