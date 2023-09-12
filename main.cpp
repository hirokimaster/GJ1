#include "Enemy.h"
#include <Novice.h>

const char kWindowTitle[] = "GJ1";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	enum Scene { TITLE, GAME, GAMEOVER, EXPLANATION };

	// 最初のシーン
	Scene scene = TITLE;

	int title = Novice::LoadTexture("bombseparation.png");
	int game = Novice::LoadTexture("BG.png");
	int gameOver = Novice::LoadTexture("GAMEOVER.png");

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

		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == false && scene == GAMEOVER) {
			enemy->Initialize();
			scene = TITLE;
		}

		switch (scene) {

			// ゲーム
		case GAME:
			enemy->Update();
			if (enemy->Life_ <= 0) {
				scene = GAMEOVER;
			}
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
			Novice::DrawSprite(0, 0, game, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(40,70, title, 1.0f, 1.0f, 0.0f, WHITE);
			break;

			// 説明画面
		case EXPLANATION:

			break;

			// ゲーム
		case GAME:
			enemy->Draw();
			enemy->DrawUI();
			break;

			break;

			// ゲームオーバー
		case GAMEOVER:
			Novice::DrawBox(0, 0, 1280, 720, 0.0f, RED, kFillModeSolid);
			Novice::DrawSprite(280,100, gameOver, 2.0f, 2.0f, 0.0f, WHITE);
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