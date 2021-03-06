//=============================================================================
// メッシュ(半球)処理 [mesh_sphere.h]
// Authore : 草刈 翔
//=============================================================================
#ifndef _MESH_SPHERE_H_
#define _MESH_SPHERE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
//クラスの定義
//*****************************************************************************
class CMeshSphere : public CScene
{
public:
	CMeshSphere(int nPriority = PRIORITY_NONE);						// コンストラクタ
	~CMeshSphere();													// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
	static CMeshSphere *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
		D3DXVECTOR3 rot, int nVertical, int nSide);					// 生成処理
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);					// テクスチャ割当処理

private:
	LPDIRECT3DTEXTURE9 m_pTexture;									// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;								// 頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;								// インデックスバッファへのポインタ
	D3DXVECTOR3 m_pos;												// 位置
	D3DXVECTOR3	m_size;												// サイズ
	D3DXVECTOR3 m_rot;												// 向き
	D3DXMATRIX m_mtxWorld;											// ワールドマトリックス
	int m_nVertical;												// 縦の分割数
	int m_nSide;													// 横の分割数
};

#endif // _MESH_SPHERE_H_