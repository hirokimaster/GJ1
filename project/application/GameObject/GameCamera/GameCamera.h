#pragma once
#include "engine/Graphics/Camera/Camera.h"
#include "application/GameObject/TileMap/TileMap.h"
class GameCamera
{
public:
		void Init();
		void Update();
		Camera GetCamera() { return camera_; }

		void DebugCamera();
public:
	void SetTileMap(TileMap* tileMap) { tileMap_ = tileMap; }
private:
	Camera camera_;
	TileMap* tileMap_ = nullptr;
};

