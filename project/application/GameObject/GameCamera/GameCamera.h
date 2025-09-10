#pragma once
#include "engine/Graphics/Camera/Camera.h"
#include "application/GameObject/TileMap/TileMap.h"

enum class CameraMode {
	FRONT,
	HIGH,
	SIDE
};

class GameCamera
{
public:
		void Init();
		void Update();
  
		/// <summary>
		/// カメラモードによって取ってくるカメラを変える
		/// </summary>
		/// <returns></returns>
		Camera& GetCamera() { 
			switch (mode_) {
			case CameraMode::FRONT: return frontCamera_;
			case CameraMode::HIGH:  return highCamera_;
			case CameraMode::SIDE:  return sideCamera_;
			}
			return frontCamera_;
		}

		Camera& GetFrontCamera() {
			return frontCamera_;
		}

		const CameraMode& GetCameraMode()const { return mode_; }

		void DebugCamera();
public:
	void SetTileMap(TileMap* tileMap) { tileMap_ = tileMap; }
	void SetCameraMode(CameraMode mode) { mode_ = mode; }
private:
	Camera frontCamera_; // 正面
	Camera highCamera_;	 // 真上
	Camera sideCamera_;	 // 横
	TileMap* tileMap_ = nullptr;
	CameraMode mode_ = CameraMode::FRONT; // 初期は正面
};

