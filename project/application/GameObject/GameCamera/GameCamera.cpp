#include "GameCamera.h"
#include "engine/Utility/ImGuiManager/ImGuiManager.h"
void GameCamera::Init()
{
	// 正面
	frontCamera_.Initialize();
	frontCamera_.translate = {0.0f,6.4f,-11.3f};
	frontCamera_.rotate = { 0.3f,0.0f,0.0f };

	// 真上
	highCamera_.Initialize();
	highCamera_.translate = { 0.0f, 20.0f, 0.0f };
	highCamera_.rotate = { std::numbers::pi_v<float> /2.0f, 0.0f, 0.0f };

	// 横
	sideCamera_.Initialize();
	sideCamera_.translate = { 20.0f, 5.0f, 0.0f };
	sideCamera_.rotate = { 0.3f, std::numbers::pi_v<float> /2.0f, 0.0f };
}

void GameCamera::Update()
{
	// デバッグカメラ

	DebugCamera();

	float centerPosX = tileMap_->GetMaxCol() * 2.0f / 2.0f - 1.0f;

	// マップサイズ
	float tileWidth = 2.0f; // タイル1枚の幅
	float mapWidth = tileMap_->GetMaxCol() * tileWidth;
	float mapDepth = tileMap_->GetMaxRow() * tileWidth;
	float centerX = mapWidth / 2.0f - tileWidth / 2.0f;
	float centerZ = mapDepth / 2.0f - tileWidth / 2.0f;
	float maxSize = max(mapWidth, mapDepth);

	float fov = 23.0f * (std::numbers::pi_v<float> / 180.0f);
	float cameraHeight = maxSize / (2.0f * tan(fov / 2.0f));

	
	// モードによって変える
	switch (mode_)
	{
	case CameraMode::FRONT:
		frontCamera_.translate.x = centerPosX;
		frontCamera_.UpdateMatrix();
		break;
	case CameraMode::HIGH:
		highCamera_.translate = { centerX, cameraHeight, centerZ }; // 真上
		highCamera_.UpdateMatrix();
		break;
									    
	case CameraMode::SIDE:
		sideCamera_.translate = { -mapWidth - 15.0f, mapWidth + 2.2f, centerZ }; // X負側に離す、Y少し高め
		sideCamera_.UpdateMatrix();
		break;

	default:
		break;
	}
}

void GameCamera::DebugCamera()
{
#ifdef _DEBUG
	ImGui::Begin("DebugCamera");
	const char* modes[] = { "Front", "High", "Side" };
	int modeIndex = static_cast<int>(mode_);
	if (ImGui::Combo("Camera Mode", &modeIndex, modes, IM_ARRAYSIZE(modes))) {
		mode_ = static_cast<CameraMode>(modeIndex);
	}

	Camera& active = GetCamera();
	ImGui::DragFloat3("CameraPos", &active.translate.x, 0.1f);
	ImGui::DragFloat3("CameraRot", &active.rotate.x, 0.1f);
	ImGui::End();
#endif // _DEBUG
}
