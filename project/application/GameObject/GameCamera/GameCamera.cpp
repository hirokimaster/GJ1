#include "GameCamera.h"

void GameCamera::Init()
{
	camera_.Initialize();
}

void GameCamera::Update()
{
	camera_.UpdateMatrix();
}
