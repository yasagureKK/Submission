//=============================================================================
// チュートリアルでのポーズ処理 [tutorial_pause.h]
// Author : 草刈 翔
//=============================================================================
#ifndef _TUTORIAL_PAUSE_H_
#define _TUTORIAL_PAUSE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CTutorialPause : public CScene
{
public:
	CTutorialPause(int nPriority = PRIORITY_PAUSE);						// コンストラクタ
	~CTutorialPause();													// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);					// 初期化処理
	void Uninit(void);													// 終了処理
	void Update(void);													// 更新処理
	void Draw(void);													// 描画処理
	static CTutorialPause *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
		int nTimer);													// 生成処理
	static void SetPause(bool bPause);									// ポーズ設定処理
	static bool GetPause(void);											// ポーズ取得処理

private:
	static bool m_bPause;												// ポーズしてるかどうか
	int m_nTimer;														// 何秒止めるか
};

#endif	// _TUTORIAL_PAUSE_H_