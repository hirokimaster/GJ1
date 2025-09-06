/**
* @file GameScene.h
* @brief ゲームシーン
* @author 仁平 琉乃
*/

#pragma once
#include "application/Scene/IScene/IScene.h"
#include "engine/Utility/CollisionManager/CollisionManager.h"
#include "application/Loader/Loader.h"
#include "application/SceneTransition/FadeOut/FadeOut.h"
#include "application/SceneTransition/FadeIn/FadeIn.h"
#include "application/SceneSprite/GameSprite.h"
#include "engine/Graphics/Effects/Particle/ParticleManager.h"

#include "application/GameObject/GameCamera/GameCamera.h"
#include "application/GameObject/TeamTile/TeamTile.h"
#include <application/GameObject/Unit/Projectile/ProjectilePool.h>
#include <application/GameObject/Unit/Archer/Archer.h>
#include "application/GameObject/TileMap/TileMap.h"
#include "application/GameObject/Skydome/Skydome.h"
#include "application/GameObject/player/Player.h"
#include "application/GameObject/Enemy/Enemy.h"
#include <application/GameObject/Unit/UnitFactory.h>
#include <application/GameObject/Unit/Warrior/Warrior.h>
#include <application/GameObject/Unit/Swordsman/Swordsman.h>


class GameScene : public IScene {
public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

	/// <summary>
	/// ポストエフェクト描画
	/// </summary>
	void PostProcessDraw()override;

private:

	/// <summary>
	/// collision書くとこ
	/// </summary>
	void Collision();

	/// <summary>
	/// テクスチャ読み込む場所
	/// </summary>
	void LoadTextureFile();

private:

	std::unique_ptr<GameCamera> gameCamera_; // ゲームカメラ

	std::unique_ptr<PostProcess> postEffect_ = nullptr;

	std::unique_ptr<GameSprite> gameSprite_ = nullptr;

	bool isGameOver;
	bool isGameClear;
  
	// タイルマップ管理クラス
	std::unique_ptr<TileMap> tileMap_;

	// プレイヤー（ユニット操作）
	std::unique_ptr<Player> player_;

	std::unique_ptr<Enemy> enemy_;
  
	std::unique_ptr<ProjectilePool> projectilePool_;
	// スカイドーム
	std::unique_ptr<Skydome> skydome_;

};
