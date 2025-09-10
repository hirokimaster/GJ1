#pragma once
#include <engine/Audio/Audio.h>

class GameSound {
public:
	/// <summary>
	/// シングルトン
	/// </summary>
	/// <returns></returns>
	static GameSound* GetInstance() {
		static GameSound instance;
		return &instance;
	}

	/// <summary>
	/// 初期化
	/// </summary>
	static void Initialize();

	/// <summary>
	/// bgm再生
	/// </summary>
	/// <param name="name"></param>
	static void SoundPlayBGM(const std::string& name);

	/// <summary>
	/// se再生
	/// </summary>
	/// <param name="name"></param>
	static void SoundPlaySE(const std::string& name);

	/// <summary>
	/// 消す
	/// </summary>
	/// <param name="name"></param>
	static void SoundStop(const std::string& name);

private:


#pragma region getter

	static uint32_t GetHandle(const std::string& name) {
		std::string path = name;
		auto it = GameSound::GetInstance()->handleMap_.find(path);
		if (it == GameSound::GetInstance()->handleMap_.end()) {
			// ファイル名が存在しない場合
			assert(0);
		}
		return it->second;
	}

#pragma endregion

private:
	GameSound() = default;
	~GameSound() = default;
	GameSound(const GameSound&) = delete;
	GameSound& operator=(const GameSound&) = delete;

private:
	Audio* audio_ = Audio::GetInstance(); // audioのポインタ借りる
	std::unordered_map<std::string, uint32_t> handleMap_; // soundHandle管理
};
