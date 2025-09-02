#include "TeamTile.h"
#include "engine/Graphics/TextureManager/TextureManager.h" 
#include "engine/3d/Model/ModelManager.h" 
void TeamTile::Initialize()
{
	TextureManager::Load("Stage/block.png");
	ModelManager::LoadObjModel("Stage/wall.obj");
	// object共通の初期化
	BaseInstancingObject::Initialize("Stage/wall.obj", "Stage/block.png", ColliderType::AABB);
	
	// colliderの属性
	collider_->SetCollosionAttribute(kCollisionAttributeEnemyBullet);
	collider_->SetCollisionMask(kCollisionAttributePlayer); // 当たる対象
}

void TeamTile::Update()
{
	BaseInstancingObject::Update(); // object共通の更新処理
	collider_->SetWorldPosition(GetWorldPosition());
	collider_->SetScale(object_.lock()->worldTransform.scale);
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
