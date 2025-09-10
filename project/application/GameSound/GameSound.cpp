#include "GameSound.h"
#include <filesystem>

void GameSound::Initialize()
{
	// Soundフォルダ内全てのデータを読む
	std::filesystem::path dir("resources/Sound/");
	if (std::filesystem::exists(dir)) {
		for (const auto& entry : std::filesystem::directory_iterator(dir)) {
			if (entry.is_regular_file() && entry.path().extension() == ".wav") {
				std::string name = entry.path().stem().string();
				// 読み込み、記録
				auto it = GameSound::GetInstance()->handleMap_.find(name);
				if (it != GameSound::GetInstance()->handleMap_.end()) {
					// 既にロードされていたらスキップ
					continue;
				}
				else {
					// 新しくロード
					std::string fullpath = entry.path().string();
					GameSound::GetInstance()->handleMap_[name] = GameSound::GetInstance()->audio_->SoundLoadWave(fullpath.c_str());
				}
			}
		}
	}
}

void GameSound::SoundPlayBGM(const std::string& name)
{
	// ループ再生
	GameSound::GetInstance()->audio_->SoundPlayLoop(GetHandle(name));
}

void GameSound::SoundPlaySE(const std::string& name)
{
	// 一度再生
	GameSound::GetInstance()->audio_->SoundPlayWave(GetHandle(name));
}

void GameSound::SoundStop(const std::string& name)
{
	// 止める
	GameSound::GetInstance()->audio_->SoundPlayStop(GetHandle(name));
}
