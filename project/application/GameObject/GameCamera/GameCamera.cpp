#include "GameCamera.h"
#include "engine/Utility/ImGuiManager/ImGuiManager.h"
void GameCamera::Init()
{
	camera_.Initialize();
	camera_.translate = {0.0f,6.4f,-11.3f};
	camera_.rotate = { 0.3f,0.0f,0.0f };
}

void GameCamera::Update()
{
	// デバッグカメラ

	DebugCamera();


	camera_.UpdateMatrix();
}

void GameCamera::DebugCamera()
{
#ifdef _DEBUG
	ImGui::Begin("DebugCamera");
	ImGui::DragFloat3("CameraPos", &camera_.translate.x, 0.1f);
	ImGui::DragFloat3("CameraRot", &camera_.rotate.x, 0.1f);

	ImGui::End();
#endif // _DEBUG
}
