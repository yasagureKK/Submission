//=============================================================================
// ゲーム中の背景オブジェクト生成処理 [game_object.h]
// Author : 草刈 翔
//=============================================================================
#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAME_MAX_BACK_OBJECT	(20)	// 背景オブジェクトの最大数

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CModelSingle;
class CBillboard;

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CGameObject : public CScene
{
public:
	CGameObject();											// コンストラクタ
	~CGameObject();											// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理
	static CGameObject *Create(D3DXVECTOR3 pos, 
		D3DXVECTOR3 size, int nNumPlayer);					// 生成処理

private:
	void DeleteObject();									// オブジェクトの消去処理
	D3DXVECTOR3 m_pos;										// 位置
	D3DXVECTOR3 m_size;										// サイズ
	CModelSingle *m_apModelSingle[GAME_MAX_BACK_OBJECT];	// モデル(単体)のポインタ
	CBillboard *m_apBilboard[GAME_MAX_BACK_OBJECT];			// ビルボードのポインタ
	int m_nNumPlayer;										// どのプレイヤーに対するものか
};

#endif	// _GAME_OBJECT_H_