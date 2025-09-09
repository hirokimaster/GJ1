#pragma once
#include "application/Scene/IScene/IScene.h"
#include "engine/Input/Input.h"
#include "engine/3d/Object3dPlacer/Object3dPlacer.h"
#include "application/SceneTransition/FadeIn/FadeIn.h"
#include "application/SceneTransition/FadeOut/FadeOut.h"
#include "application/GameManager/GameManager.h"
#include "engine/Graphics/Camera/Camera.h"
#include <application/SceneSprite/SelectSprite.h>

#include "application/GameObject/Skydome/Skydome.h"
#include "SelectStage/SelectStage.h"

class SelectScene : public IScene {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SelectScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SelectScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

	/// <summary>
	/// postProcess描画
	/// </summary>
	void PostProcessDraw()override;

private:
	/// <summary>
	/// textureはここに書く
	/// </summary>
	void LoadTextureFile();

	void StageSelect();
private:
	std::unique_ptr<PostProcess> postEffect_ = nullptr;
	std::unique_ptr<SelectSprite> selectSprite_ = nullptr;

	std::list<std::unique_ptr<SelectStage>> selectStages_;

	Camera camera_; // ゲームカメラ
	// スカイドーム
	std::unique_ptr<Skydome> skydome_;

	int32_t selectedStageNum_ = 0; // 選択されたステージ番号
	// ステージの最大数
	int32_t maxStageNum_ = 0; // 最大ステージ数

	// padの入力待機時間
	float inputWaitTime_ = 0.0f; // 入力待機時間
	// padの入力待機時間の最大値
	const float maxInputWaitTime_ = 0.1f; // 入力待機時間の最大値
	// シーン遷移用
	bool isTransition_ = false;
	std::unique_ptr<ISceneTransition> transition_ = nullptr;
};
