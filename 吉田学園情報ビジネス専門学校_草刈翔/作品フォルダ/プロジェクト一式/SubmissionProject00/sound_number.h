//=============================================================================
// サウンドナンバー処理 [sound_number.h]
// Authore : 草刈 翔
//=============================================================================
#ifndef _SOUND_NUMBER_H_
#define _SOUND_NUMBER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_SOUND_NUMBER_DIGIT (3)	// 曲の最大桁数

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CNumber;

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSoundNumber : public CScene
{
public:
	CSoundNumber(int nPriority = PRIORITY_UI);			// コンストラクタ
	~CSoundNumber();									// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理
	static CSoundNumber *Create(D3DXVECTOR3 pos,
		D3DXVECTOR3 size, D3DXCOLOR col);				// 生成処理
	void SetNumber(int nNumber);						// ナンバー設定処理

private:
	void PlaySound(int nNum);							// サウンド再生処理

	CNumber *m_apNumber[MAX_SOUND_NUMBER_DIGIT];		// ナンバーのポインタ
	int m_nSoundNumber;									// 現在の数
	D3DXVECTOR3 m_pos;									// 位置
	D3DXVECTOR3 m_size;									// サイズ
	D3DXCOLOR m_col;									// カラー
};

#endif	//_SOUND_NUMBER_H_