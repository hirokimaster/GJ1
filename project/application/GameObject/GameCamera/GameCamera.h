#pragma once
#include "engine/Graphics/Camera/Camera.h"
class GameCamera
{
public:
		void Init();
		void Update();
		Camera GetCamera() { return camera_; }

		void DebugCamera();
private:
	Camera camera_;
};

