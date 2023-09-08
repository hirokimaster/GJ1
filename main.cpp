#include <Novice.h>
#include "Enemy.h"

const char kWindowTitle[] = "GJ1";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	enum Scene {
		TITLE,
		GAME,
		GAMEOVER,
		GAMECLEAR,
		EXPLANATION
	};

	// 最初のシーン
	Scene scene = TITLE;
	
	// クリアフラグ
	//int success = false;
	// ゲームオーバーフラグ
	//int failure = false;

	// 初期化
	Enemy* enemy = new Enemy();
	enemy->Initialize();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		// タイトルからゲーム
		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == false && scene == TITLE) {
			scene = GAME;

		}
		
		switch (scene) {

		// ゲーム
		case GAME:
			enemy->Update();
			break;
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		switch (scene) {

		// タイトル
		case TITLE:
			Novice::DrawBox(0, 0, 1280, 720, 0.0f, WHITE, kFillModeSolid);
			break;

		// 説明画面
		case EXPLANATION:

			break;

		// ゲーム
		case GAME:
			enemy->Draw();
			break;

		// ゲームクリア
		case GAMECLEAR:

			break;

		// ゲームオーバー
		case GAMEOVER:

			break;
		}
		

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
