#pragma once
#include <memory>
#include <engine/2d/Sprite/Sprite.h>

class SelectStage {
public:
	void Initialize(int num);
	void Update(int num);
	void Draw();
private:

	std::unique_ptr<Sprite> stageSprite_;
	Vector2 spriteStagePosition_{};

	int myNum_ = 0;
	float timer_ = 0.0f;
};