﻿#include <windows.h>
#include "DxLib.h"
#include "共通.h"
#include "サービス・レンダリング.h"

/// 設定情報 
#define ルートパス L""

namespace エンジン
{

	/// 静的データ
	TCHAR* リソース_ローダー::画像パス_[画像_枚数] = {
		ルートパス"img/mat04-01.png",
		ルートパス"img/mat04-02.png",
		ルートパス"img/mat04-03.png",
		ルートパス"img/mat04-04.png",
		ルートパス"img/mat04-05.png",
	};

	UVテーブル リソース_ローダー::uvテーブル_[RID_個数] = {// エラーチェックのため要素数を明示的に指定
		 ///  RID_IMG_MAT04_01
		 // RID_MY_SHIP: 自機
		{IMG_MAT04_01, 0 + 32 * 0, 0, 32,32},
		{IMG_MAT04_01, 0 + 32 * 1, 0, 32,32},
		{IMG_MAT04_01, 0 + 32 * 2, 0, 32,32},// まっすぐ
		{IMG_MAT04_01, 0 + 32 * 3, 0, 32,32},
		{IMG_MAT04_01, 0 + 32 * 4, 0, 32,32},
		// RID_INJECTION: 噴射
		{IMG_MAT04_01, 72,32, 16,16},
		{IMG_MAT04_01, 72,48, 16,16},
		{IMG_MAT04_01, 04,32, 16,16},
		{IMG_MAT04_01, 104,48, 16,16},
		// RID_SHOT: 自機の弾
		{IMG_MAT04_01,  0,48, 16,16},

		// RID_BULLET: 大きめの弾
		{IMG_MAT04_01, 32,32, 32,32},

		// RID_FORMING: 16方向弾(下)
		{IMG_MAT04_01, 192 + 16 * 0, 0,16,16},
		{IMG_MAT04_01, 192 + 16 * 1, 0,16,16},
		{IMG_MAT04_01, 192 + 16 * 2, 0,16,16},
		{IMG_MAT04_01, 192 + 16 * 3, 0,16,16},
		{IMG_MAT04_01, 192 + 16 * 4, 0,16,16},// 右
		{IMG_MAT04_01, 192 + 16 * 5, 0,16,16},
		{IMG_MAT04_01, 192 + 16 * 6, 0,16,16},
		{IMG_MAT04_01, 192 + 16 * 7, 0,16,16},
		{IMG_MAT04_01, 192 + 16 * 0,16,16,16},// 上
		{IMG_MAT04_01, 192 + 16 * 1,16,16,16},
		{IMG_MAT04_01, 192 + 16 * 2,16,16,16},
		{IMG_MAT04_01, 192 + 16 * 3,16,16,16},
		{IMG_MAT04_01, 192 + 16 * 4,16,16,16},// 左
		{IMG_MAT04_01, 192 + 16 * 5,16,16,16},
		{IMG_MAT04_01, 192 + 16 * 6,16,16,16},
		{IMG_MAT04_01, 192 + 16 * 7,16,16,16},

		// RID_BULLET_ANIM: アニメ弾
		{IMG_MAT04_01, 256 + 8 * 0, 32, 8,8},
		{IMG_MAT04_01, 256 + 8 * 1, 32, 8,8},
		{IMG_MAT04_01, 256 + 8 * 2, 32, 8,8},
		{IMG_MAT04_01, 256 + 8 * 3, 32, 8,8},
		{IMG_MAT04_01, 256 + 8 * 4, 32, 8,8},
		{IMG_MAT04_01, 256 + 8 * 5, 32, 8,8},
		{IMG_MAT04_01, 256 + 8 * 6, 32, 8,8},
		{IMG_MAT04_01, 256 + 8 * 7, 32, 8,8},

		// RID_EXPLOSION_L: 爆発(大)
		{IMG_MAT04_01, 0 + 28 * 0, 64, 48,48},
		{IMG_MAT04_01, 0 + 28 * 1, 64, 48,48},
		{IMG_MAT04_01, 0 + 28 * 2, 64, 48,48},
		{IMG_MAT04_01, 0 + 28 * 3, 64, 48,48},
		{IMG_MAT04_01, 0 + 28 * 4, 64, 48,48},
		{IMG_MAT04_01, 0 + 28 * 5, 64, 48,48},

		// RID_EXPLOSION_M: 爆発(中)
		{IMG_MAT04_01, 0 + 32 * 0,160, 32,32},
		{IMG_MAT04_01, 0 + 32 * 1,160, 32,32},
		{IMG_MAT04_01, 0 + 32 * 2,160, 32,32},
		{IMG_MAT04_01, 0 + 32 * 3,160, 32,32},
		{IMG_MAT04_01, 0 + 32 * 4,160, 32,32},
		{IMG_MAT04_01, 0 + 32 * 5,160, 32,32},

		// RID_EXPLOSION_SR: 爆発(小・赤)
		{IMG_MAT04_01, 0 + 24 * 0,112, 24,24},
		{IMG_MAT04_01, 0 + 24 * 1,112, 24,24},
		{IMG_MAT04_01, 0 + 24 * 2,112, 24,24},
		{IMG_MAT04_01, 0 + 24 * 3,112, 24,24},
		{IMG_MAT04_01, 0 + 24 * 4,112, 24,24},
		{IMG_MAT04_01, 0 + 24 * 5,112, 24,24},

		// RID_EXPLOSION_SB: 爆発(小・青)
		{IMG_MAT04_01, 0 + 24 * 0,136, 24,24},
		{IMG_MAT04_01, 0 + 24 * 1,136, 24,24},
		{IMG_MAT04_01, 0 + 24 * 2,136, 24,24},
		{IMG_MAT04_01, 0 + 24 * 3,136, 24,24},
		{IMG_MAT04_01, 0 + 24 * 4,136, 24,24},
		{IMG_MAT04_01, 0 + 24 * 5,136, 24,24},

		///  RID_IMG_MAT04_02

		///  RID_IMG_MAT04_03
		// RID_ENEMY_S0: 敵(小・その0)
		{IMG_MAT04_03, 0 + 32 * 0, 0, 32,32},
		{IMG_MAT04_03, 0 + 32 * 1, 0, 32,32},
		// RID_ENEMY_S1: 敵(小・その2)
		{IMG_MAT04_03, 0 + 32 * 2, 0, 32,32},
		{IMG_MAT04_03, 0 + 32 * 3, 0, 32,32},
		// RID_ENEMY_S2: 敵(小・その3)
		{IMG_MAT04_03, 0 + 32 * 4, 0, 32,32},
		{IMG_MAT04_03, 0 + 32 * 5, 0, 32,32},
		// RID_ENEMY_S3: 敵(小・その4)
		{IMG_MAT04_03, 0 + 32 * 6, 0, 32,32},
		{IMG_MAT04_03, 0 + 32 * 7, 0, 32,32},
		// RID_ENEMY_S4: 敵(小・その5)
		{IMG_MAT04_03, 0 + 32 * 8, 0, 32,32},
		{IMG_MAT04_03, 0 + 32 * 9, 0, 32,32},

		// RID_ENEMY_M0: 敵(中・その0)
		{IMG_MAT04_03, 0 + 64 * 0, 32, 64,48},
		{IMG_MAT04_03, 0 + 64 * 1, 32, 64,48},
		// RID_ENEMY_M1: 敵(中・その1)
		{ IMG_MAT04_03, 0 + 64 * 2, 32, 64,48},
		{ IMG_MAT04_03, 0 + 64 * 3, 32, 64,48},

		// RID_ENEMY_L0: 敵(中・その0)
		{ IMG_MAT04_03, 0 + 48 * 0, 80, 48,80},
		{ IMG_MAT04_03, 0 + 48 * 2, 80, 48,80},
		// RID_ENEMY_L1: 敵(中・その1)
		{ IMG_MAT04_03, 96 + 64 * 0, 80, 64,80},
		{ IMG_MAT04_03, 96 + 64 * 1, 80, 64,80},

		// RID_ENEMY_BOSS: 敵(ボス)
		{ IMG_MAT04_03, 0 + 128 * 0, 160, 128,64},
		{ IMG_MAT04_03, 0 + 128 * 1, 160, 128,64},

		// RID_MISSILE: 16方向ミサイル
		{ IMG_MAT04_03, 0 + 16 * 0, 224, 16,16},
		{ IMG_MAT04_03, 0 + 16 * 1, 224, 16,16},
		{ IMG_MAT04_03, 0 + 16 * 2, 224, 16,16},
		{ IMG_MAT04_03, 0 + 16 * 3, 224, 16,16},
		{ IMG_MAT04_03, 0 + 16 * 4, 224, 16,16},
		{ IMG_MAT04_03, 0 + 16 * 5, 224, 16,16},
		{ IMG_MAT04_03, 0 + 16 * 6, 224, 16,16},
		{ IMG_MAT04_03, 0 + 16 * 7, 224, 16,16},
		{ IMG_MAT04_03, 0 + 16 * 8, 224, 16,16},
		{ IMG_MAT04_03, 0 + 16 * 9, 224, 16,16},
		{ IMG_MAT04_03, 0 + 16 * 10, 224, 16,16},
		{ IMG_MAT04_03, 0 + 16 * 11, 224, 16,16},
		{ IMG_MAT04_03, 0 + 16 * 12, 224, 16,16},
		{ IMG_MAT04_03, 0 + 16 * 13, 224, 16,16},
		{ IMG_MAT04_03, 0 + 16 * 14, 224, 16,16},
		{ IMG_MAT04_03, 0 + 16 * 15, 224, 16,16},
		// RID_MISSILE_BREAK: ミサイル破壊
		{ IMG_MAT04_03, 0 + 16 * 16, 224, 16,16},

		///  RID_IMG_MAT04_05
		{ IMG_MAT04_03, 0, 0, 960,960 },
	};


	/// リソース_ローダー

	リソース_ローダー::リソース_ローダー()
	{
		ハンドル初期化();
	}

	リソース_ローダー::~リソース_ローダー()
	{
	}

	void リソース_ローダー::ハンドル初期化()
	{
		for (int i = 0; i < 画像_枚数; i++) {
			ハンドル配列_[i] = -1;
		}
	}

	int リソース_ローダー::初期化()
	{
		for (int i = 0; i < 画像_枚数; i++) {
			ハンドル配列_[i] = LoadGraph(画像パス_[i]);
			if (ハンドル配列_[i] == -1) return -1;
		}

		//DrawGraph(0, 0, ハンドル配列_[4], true);

		return 0;
	}

	int リソース_ローダー::片付け()
	{
		// この後描画を呼ばれても変なメモリを使われないようにする
		ハンドル初期化();

		// 読みこんだグラフィックデータをすべて削除
		int ret = InitGraph();

		return ret;
	}


	/// レンダリングサービス

	レンダリングサービス::レンダリングサービス()
	{
		ローダー = new リソース_ローダー();
	}

	レンダリングサービス::~レンダリングサービス()
	{
		安全DELETE(ローダー);
	}

	int レンダリングサービス::初期化()
	{
		int 返り値 = 0;

		返り値 = ローダー->初期化();
		if (返り値 != 0) return 返り値;

		// 情報の取得
		RECT 矩形;
		GetClientRect(GetMainWindowHandle(), &矩形);
		情報_.画面サイズ[0] = 矩形.right;
		情報_.画面サイズ[1] = 矩形.bottom;

		return 返り値;
	}

	int レンダリングサービス::片付け()
	{
		int 返り値 = 0;

		返り値 = ローダー->片付け();
		if (返り値 != 0) return 返り値;

		return 0;
	}

	int レンダリングサービス::サイズ取得(unsigned int リソースID, int(&出力先)[2]) const
	{
		if (RID_個数 <= リソースID) return -1; // 範囲外確認
		
		const UVテーブル& uv = ローダー->UVテーブル(リソースID);
		出力先[0] = uv.w;
		出力先[1] = uv.h;

		return 0;
	}


	void レンダリングサービス::描画_左上(unsigned int リソースID, int x, int y)
	{
		
		const UVテーブル& uv = リソース_ローダー::UVテーブル(リソースID);

		//描画(x,y, u,v, w,h, handle,半透明,反転)
		DrawRectGraph(x, y, uv.u, uv.v, uv.w, uv.h,
			ローダー->ハンドル所得(uv.画像), TRUE, FALSE);
	}

	void レンダリングサービス::描画(unsigned int リソースID, int x, int y)
	{
		const UVテーブル& uv = リソース_ローダー::UVテーブル(リソースID);

		//描画(x,y, u,v, w,h, handle,半透明,反転)
		DrawRectGraph(x - uv.w / 2, y - uv.h / 2, uv.u, uv.v, uv.w, uv.h,
			ローダー->ハンドル所得(uv.画像), TRUE, FALSE);
	}

	void BG()
	{
		
	}
}
