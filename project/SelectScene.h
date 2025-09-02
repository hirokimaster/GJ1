#pragma once
#include "application/Scene/IScene/IScene.h"
#include "engine/Input/Input.h"
#include "engine/3d/Object3dPlacer/Object3dPlacer.h"
#include "application/SceneTransition/FadeIn/FadeIn.h"
#include "application/SceneTransition/FadeOut/FadeOut.h"
#include "application/GameManager/GameManager.h"

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
};
