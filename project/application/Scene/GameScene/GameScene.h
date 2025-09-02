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
#include "engine/3d/ObjectManager/ObjectManager.h"

#include "application/GameObject/GameCamera/GameCamera.h"

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
};
