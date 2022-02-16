//=============================================================================
// モデル処理 [model.cpp]
// Aouthor : 草刈 翔
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "model.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CModel::CModel()
{
	// 変数のクリア
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_nNumMat = 0;
	memset(&m_pTexture, NULL, sizeof(m_pTexture));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pParent = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CModel::~CModel()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModelLoad::MODEL_TYPE type)
{
	// 頂点の最大値・最小値は後で再計算するため極端な数字にしておく
	m_vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
	m_vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);

	// 変数の初期化
	m_rot = rot;
	m_pos = pos;

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// Xファイルの情報読み込み
	m_pBuffMat = CManager::GetModelLoad()->GetBuffMat(type);
	m_nNumMat = CManager::GetModelLoad()->GetNumMat(type);
	m_pMesh = CManager::GetModelLoad()->GetMesh(type);

	// マテリアルへのポインタ
	D3DXMATERIAL *pMat;

	// マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL *)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_pTexture[nCntMat]);
		}
	}

	// 頂点情報の取得
	int nNumVtx;		// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点バッファへのポインタ

						// 頂点数を取得
	nNumVtx = m_pMesh->GetNumVertices();

	// 頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	// 頂点バッファをロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		// 頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		// 全ての頂点を比較して最大値と最小値を出す
		// 最大値
		if (vtx.x >= m_vtxMax.x)
		{
			m_vtxMax.x = vtx.x;
		}
		if (vtx.y >= m_vtxMax.y)
		{
			m_vtxMax.y = vtx.y;
		}
		if (vtx.z >= m_vtxMax.z)
		{
			m_vtxMax.z = vtx.z;
		}
		// 最小値
		if (vtx.x <= m_vtxMin.x)
		{
			m_vtxMin.x = vtx.x;
		}
		if (vtx.y <= m_vtxMin.y)
		{
			m_vtxMin.y = vtx.y;
		}
		if (vtx.z <= m_vtxMin.z)
		{
			m_vtxMin.z = vtx.z;
		}

		// モデルのサイズ
		m_size.x = m_vtxMax.x - m_vtxMin.x;
		m_size.y = m_vtxMax.y - m_vtxMin.y;
		m_size.z = m_vtxMax.z - m_vtxMin.z;

		// 頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	// 頂点の最大値と最小値から8頂点の位置を求める
	m_vtxPos[0].x = m_vtxMin.x;
	m_vtxPos[0].z = m_vtxMax.z;
	m_vtxPos[0].y = m_vtxMax.y;
	m_vtxPos[1].x = m_vtxMax.x;
	m_vtxPos[1].z = m_vtxMax.z;
	m_vtxPos[1].y = m_vtxMax.y;
	m_vtxPos[2].x = m_vtxMin.x;
	m_vtxPos[2].z = m_vtxMax.z;
	m_vtxPos[2].y = m_vtxMin.y;
	m_vtxPos[3].x = m_vtxMax.x;
	m_vtxPos[3].z = m_vtxMax.z;
	m_vtxPos[3].y = m_vtxMin.y;
	m_vtxPos[4].x = m_vtxMin.x;
	m_vtxPos[4].z = m_vtxMin.z;
	m_vtxPos[4].y = m_vtxMax.y;
	m_vtxPos[5].x = m_vtxMax.x;
	m_vtxPos[5].z = m_vtxMin.z;
	m_vtxPos[5].y = m_vtxMax.y;
	m_vtxPos[6].x = m_vtxMin.x;
	m_vtxPos[6].z = m_vtxMin.z;
	m_vtxPos[6].y = m_vtxMin.y;
	m_vtxPos[7].x = m_vtxMax.x;
	m_vtxPos[7].z = m_vtxMin.z;
	m_vtxPos[7].y = m_vtxMin.y;

	// 頂点バッファをアンロック
	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CModel::Uninit(void)
{
	// メッシュの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// マテリアルの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < MAX_MODEL_TEXTURE; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CModel::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CModel::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ
	D3DXMATRIX mtxParent;						// 親のマトリックス

												// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// 親のモデルのマトリックスの設定
	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->GetMtx();
	}
	// 親のモデルが無い場合
	else
	{
		// ワールドマトリックスを取得
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// 算出したパーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// それぞれのパーツにマテリアル・テクスチャを設定して描画
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture[nCntMat]);

		//モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 生成処理
//=============================================================================
CModel* CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModelLoad::MODEL_TYPE type)
{
	// インスタンスの生成
	CModel *pModel = NULL;

	// ヌルチェック
	if (pModel == NULL)
	{
		// クラスの生成
		pModel = new CModel;
		if (pModel != NULL)
		{
			// 初期化処理
			pModel->Init(pos, rot, type);
		}
	}

	return pModel;
}


////=============================================================================
////当たり判定処理
////=============================================================================
//void CModel::Collision(void)
//{
//	//オブジェクト情報を入れるポインタ
//	CScene *pObject = NULL;
//	//オブジェクト情報を保存するポインタ変数
//	CScene *pSaveObject = NULL;
//
//	//先頭のポインタを代入
//	pObject = pObject->GetTopObj(CScene::PRIORITY_MODEL);
//
//	while (pObject != NULL)
//	{
//		//現在のオブジェクトのポインタを保存
//		pSaveObject = pObject;
//
//		if (pObject->GetObjType() == CScene::OBJTYPE_PLAYER)
//		{
//			//横からの当たり判定に使う
//			CPlayer *pPlayer = NULL;									//プレイヤーのポインタ
//			D3DXVECTOR3 posPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//対象の位置
//			D3DXVECTOR3 sizePlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//対象のサイズ
//			D3DXVECTOR3 posOldPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//対象の1フレーム前の位置
//			D3DXVECTOR3 nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//法線ベクトル
//			D3DXVECTOR3 moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//対象のムーブベクトル
//			D3DXVECTOR3 norInVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//法線ベクトルの方向に対象と法線ベクトルの内積分伸ばしたベクトル
//			D3DXVECTOR3 posPlayerVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//対象を押し出す位置までのベクトル
//			D3DXVECTOR3 posFinPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//対象を押し出す位置
//			D3DXVECTOR3 vecVtx[4];										//対象とのベクトル算出のために使う頂点までのベクトル
//			D3DXVECTOR3 vecObj[4];										//対象とのベクトル算出のために使う対象までのベクトル
//			D3DXVECTOR3 vecObjOld[4];									//1フレーム前の対象とのベクトル算出のために使う対象までのベクトル
//			D3DXVECTOR3 vecNorVtx[2];									//面の法線ベクトルを求めるための頂点ベクトル
//			float fVecNorObj[4];										//対象と頂点の法線ベクトルの長さ
//			float fVecNorObjOld[4];										//1フレーム前の対象と頂点の法線ベクトルの長さ
//			float fInVec = 0.0f;										//対象と法線ベクトルの内積
//
//																		//上からの当たり判定に使う
//			D3DXVECTOR3 topVtxVec[4];									//対象とのベクトル算出のために使う頂点までのベクトル
//			D3DXVECTOR3 topVecObj[4];									//対象とのベクトル算出のために使う対象までのベクトル
//			D3DXVECTOR3 topVecObjOld[4];								//1フレーム前の対象とのベクトル算出のために使う対象までのベクトル
//			float fTopVecNorObj[4];										//対象と頂点の法線ベクトルの長さ
//			float fTopVecNorObjOld[4];									//1フレーム前の対象と頂点の法線ベクトルの長さ
//
//																		//初期化処理
//			for (int nCnt = 0; nCnt < 4; nCnt++)
//			{
//				vecVtx[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//				vecObj[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//				vecObjOld[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//				fVecNorObj[nCnt] = 0.0f;
//				fVecNorObjOld[nCnt] = 0.0f;
//			}
//
//			for (int nCnt1 = 0; nCnt1 < 2; nCnt1++)
//			{
//				vecNorVtx[nCnt1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			}
//
//			//プレイヤーのポインタにキャスト
//			pPlayer = (CPlayer*)pObject;
//
//			//プレイヤーの位置取得
//			posPlayer = pPlayer->GetPos();
//			posOldPlayer = pPlayer->GetPosOld();
//
//			//プレイヤーのサイズ取得
//			sizePlayer = pPlayer->GetSize();
//
//			//対象の幅の分大きくする
//			m_vtxPos[0].x -= sizePlayer.x / 2.0f;
//			m_vtxPos[1].x += sizePlayer.x / 2.0f;
//			m_vtxPos[2].x -= sizePlayer.x / 2.0f;
//			m_vtxPos[3].x += sizePlayer.x / 2.0f;
//			m_vtxPos[4].x -= sizePlayer.x / 2.0f;
//			m_vtxPos[5].x += sizePlayer.x / 2.0f;
//			m_vtxPos[6].x -= sizePlayer.x / 2.0f;
//			m_vtxPos[7].x += sizePlayer.x / 2.0f;
//			m_vtxPos[0].z += sizePlayer.x / 2.0f;
//			m_vtxPos[1].z += sizePlayer.x / 2.0f;
//			m_vtxPos[2].z += sizePlayer.x / 2.0f;
//			m_vtxPos[3].z += sizePlayer.x / 2.0f;
//			m_vtxPos[4].z -= sizePlayer.x / 2.0f;
//			m_vtxPos[5].z -= sizePlayer.x / 2.0f;
//			m_vtxPos[6].z -= sizePlayer.x / 2.0f;
//			m_vtxPos[7].z -= sizePlayer.x / 2.0f;
//
//			//デバイスのポインタ
//			LPDIRECT3DDEVICE9 pDevice;
//			//デバイスの取得
//			pDevice = CManager::GetRenderer()->GetDevice();
//
//			D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
//			D3DXMATRIX mtxParent;						//親のマトリックス
//
//														//8頂点の設定
//			for (int nCntVtx = 0; nCntVtx < MODEL_VTX; nCntVtx++)
//			{
//				D3DXMatrixIdentity(&m_vtxMtxWorld[nCntVtx]);		//ワールドマトリックスの初期化
//
//																	//向きを反映
//				D3DXMatrixRotationYawPitchRoll(&mtxRot, m_vtxRot[nCntVtx].y, m_vtxRot[nCntVtx].x, m_vtxRot[nCntVtx].z);
//				D3DXMatrixMultiply(&m_vtxMtxWorld[nCntVtx], &m_vtxMtxWorld[nCntVtx], &mtxRot);
//
//				//位置を反映
//				D3DXMatrixTranslation(&mtxTrans, m_vtxPos[nCntVtx].x, m_vtxPos[nCntVtx].y, m_vtxPos[nCntVtx].z);
//				D3DXMatrixMultiply(&m_vtxMtxWorld[nCntVtx], &m_vtxMtxWorld[nCntVtx], &mtxTrans);
//
//				D3DXMATRIX mtxParent;		//親のマトリックス
//				mtxParent = m_mtxWorld;
//
//				//算出した各パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
//				D3DXMatrixMultiply(&m_vtxMtxWorld[nCntVtx], &m_vtxMtxWorld[nCntVtx], &mtxParent);
//
//				//ワールドマトリックスの設定
//				pDevice->SetTransform(D3DTS_WORLD, &m_vtxMtxWorld[nCntVtx]);
//			}
//
//			//頂点のベクトルを出す
//			vecVtx[0] = D3DXVECTOR3(m_vtxMtxWorld[3]._41 - m_vtxMtxWorld[2]._41, 0.0f, m_vtxMtxWorld[3]._43 - m_vtxMtxWorld[2]._43);
//			vecVtx[1] = D3DXVECTOR3(m_vtxMtxWorld[7]._41 - m_vtxMtxWorld[3]._41, 0.0f, m_vtxMtxWorld[7]._43 - m_vtxMtxWorld[3]._43);
//			vecVtx[2] = D3DXVECTOR3(m_vtxMtxWorld[6]._41 - m_vtxMtxWorld[7]._41, 0.0f, m_vtxMtxWorld[6]._43 - m_vtxMtxWorld[7]._43);
//			vecVtx[3] = D3DXVECTOR3(m_vtxMtxWorld[2]._41 - m_vtxMtxWorld[6]._41, 0.0f, m_vtxMtxWorld[2]._43 - m_vtxMtxWorld[6]._43);
//
//			//上からの当たり判定用頂点のベクトルを出す
//			topVtxVec[0] = D3DXVECTOR3(m_vtxMtxWorld[1]._41 - m_vtxMtxWorld[0]._41, 0.0f, m_vtxMtxWorld[1]._43 - m_vtxMtxWorld[0]._43);
//			topVtxVec[1] = D3DXVECTOR3(m_vtxMtxWorld[3]._41 - m_vtxMtxWorld[1]._41, 0.0f, m_vtxMtxWorld[3]._43 - m_vtxMtxWorld[1]._43);
//			topVtxVec[2] = D3DXVECTOR3(m_vtxMtxWorld[2]._41 - m_vtxMtxWorld[3]._41, 0.0f, m_vtxMtxWorld[2]._43 - m_vtxMtxWorld[3]._43);
//			topVtxVec[3] = D3DXVECTOR3(m_vtxMtxWorld[0]._41 - m_vtxMtxWorld[2]._41, 0.0f, m_vtxMtxWorld[0]._43 - m_vtxMtxWorld[2]._43);
//
//			//対象とのベクトルを出す
//			vecObj[0] = D3DXVECTOR3(posPlayer.x - m_vtxMtxWorld[2]._41, 0.0f, posPlayer.z - m_vtxMtxWorld[2]._43);
//			vecObj[1] = D3DXVECTOR3(posPlayer.x - m_vtxMtxWorld[3]._41, 0.0f, posPlayer.z - m_vtxMtxWorld[3]._43);
//			vecObj[2] = D3DXVECTOR3(posPlayer.x - m_vtxMtxWorld[7]._41, 0.0f, posPlayer.z - m_vtxMtxWorld[7]._43);
//			vecObj[3] = D3DXVECTOR3(posPlayer.x - m_vtxMtxWorld[6]._41, 0.0f, posPlayer.z - m_vtxMtxWorld[6]._43);
//
//			//上からの当たり判定用対象とのベクトルを出す
//			topVecObj[0] = D3DXVECTOR3(posPlayer.x - m_vtxMtxWorld[0]._41, 0.0f, posPlayer.z - m_vtxMtxWorld[0]._43);
//			topVecObj[1] = D3DXVECTOR3(posPlayer.x - m_vtxMtxWorld[1]._41, 0.0f, posPlayer.z - m_vtxMtxWorld[1]._43);
//			topVecObj[2] = D3DXVECTOR3(posPlayer.x - m_vtxMtxWorld[3]._41, 0.0f, posPlayer.z - m_vtxMtxWorld[3]._43);
//			topVecObj[3] = D3DXVECTOR3(posPlayer.x - m_vtxMtxWorld[2]._41, 0.0f, posPlayer.z - m_vtxMtxWorld[2]._43);
//
//			//対象の1フレーム前のベクトルを出す
//			vecObjOld[0] = D3DXVECTOR3(posOldPlayer.x - m_vtxMtxWorld[2]._41, 0.0f, posOldPlayer.z - m_vtxMtxWorld[2]._43);
//			vecObjOld[1] = D3DXVECTOR3(posOldPlayer.x - m_vtxMtxWorld[3]._41, 0.0f, posOldPlayer.z - m_vtxMtxWorld[3]._43);
//			vecObjOld[2] = D3DXVECTOR3(posOldPlayer.x - m_vtxMtxWorld[7]._41, 0.0f, posOldPlayer.z - m_vtxMtxWorld[7]._43);
//			vecObjOld[3] = D3DXVECTOR3(posOldPlayer.x - m_vtxMtxWorld[6]._41, 0.0f, posOldPlayer.z - m_vtxMtxWorld[6]._43);
//
//			//上からの当たり判定用対象の1フレーム前のベクトルを出す
//			topVecObjOld[0] = D3DXVECTOR3(posOldPlayer.x - m_vtxMtxWorld[0]._41, 0.0f, posOldPlayer.z - m_vtxMtxWorld[0]._43);
//			topVecObjOld[1] = D3DXVECTOR3(posOldPlayer.x - m_vtxMtxWorld[1]._41, 0.0f, posOldPlayer.z - m_vtxMtxWorld[1]._43);
//			topVecObjOld[2] = D3DXVECTOR3(posOldPlayer.x - m_vtxMtxWorld[3]._41, 0.0f, posOldPlayer.z - m_vtxMtxWorld[3]._43);
//			topVecObjOld[3] = D3DXVECTOR3(posOldPlayer.x - m_vtxMtxWorld[2]._41, 0.0f, posOldPlayer.z - m_vtxMtxWorld[2]._43);
//
//			//外積の計算
//			fVecNorObj[0] = (vecVtx[0].x * vecObj[0].z) - (vecObj[0].x * vecVtx[0].z);
//			fVecNorObj[1] = (vecVtx[1].x * vecObj[1].z) - (vecObj[1].x * vecVtx[1].z);
//			fVecNorObj[2] = (vecVtx[2].x * vecObj[2].z) - (vecObj[2].x * vecVtx[2].z);
//			fVecNorObj[3] = (vecVtx[3].x * vecObj[3].z) - (vecObj[3].x * vecVtx[3].z);
//
//			//上からの当たり判定用外積の計算
//			fTopVecNorObj[0] = (topVtxVec[0].x * topVecObj[0].z) - (topVecObj[0].x * topVtxVec[0].z);
//			fTopVecNorObj[1] = (topVtxVec[1].x * topVecObj[1].z) - (topVecObj[1].x * topVtxVec[1].z);
//			fTopVecNorObj[2] = (topVtxVec[2].x * topVecObj[2].z) - (topVecObj[2].x * topVtxVec[2].z);
//			fTopVecNorObj[3] = (topVtxVec[3].x * topVecObj[3].z) - (topVecObj[3].x * topVtxVec[3].z);
//
//			//1フレーム前の外積の計算
//			fVecNorObjOld[0] = (vecVtx[0].x * vecObjOld[0].z) - (vecObjOld[0].x * vecVtx[0].z);
//			fVecNorObjOld[1] = (vecVtx[1].x * vecObjOld[1].z) - (vecObjOld[1].x * vecVtx[1].z);
//			fVecNorObjOld[2] = (vecVtx[2].x * vecObjOld[2].z) - (vecObjOld[2].x * vecVtx[2].z);
//			fVecNorObjOld[3] = (vecVtx[3].x * vecObjOld[3].z) - (vecObjOld[3].x * vecVtx[3].z);
//
//			//上からの当たり判定用1フレーム前の外積の計算
//			fTopVecNorObjOld[0] = (topVtxVec[0].x * topVecObjOld[0].z) - (topVecObjOld[0].x * topVtxVec[0].z);
//			fTopVecNorObjOld[1] = (topVtxVec[1].x * topVecObjOld[1].z) - (topVecObjOld[1].x * topVtxVec[1].z);
//			fTopVecNorObjOld[2] = (topVtxVec[2].x * topVecObjOld[2].z) - (topVecObjOld[2].x * topVtxVec[2].z);
//			fTopVecNorObjOld[3] = (topVtxVec[3].x * topVecObjOld[3].z) - (topVecObjOld[3].x * topVtxVec[3].z);
//
//			//どの壁にぶつかっているか
//			if (fVecNorObjOld[0] >= 0.0f && fVecNorObj[0] < 0.0f)
//			{
//				//面ベクトルを求めるための頂点ベクトルの算出
//				vecNorVtx[0] = D3DXVECTOR3(m_vtxMtxWorld[1]._41 - m_vtxMtxWorld[3]._41,
//					m_vtxMtxWorld[1]._42 - m_vtxMtxWorld[3]._42,
//					m_vtxMtxWorld[1]._43 - m_vtxMtxWorld[3]._43);
//				vecNorVtx[1] = D3DXVECTOR3(m_vtxMtxWorld[2]._41 - m_vtxMtxWorld[3]._41,
//					m_vtxMtxWorld[2]._42 - m_vtxMtxWorld[3]._42,
//					m_vtxMtxWorld[2]._43 - m_vtxMtxWorld[3]._43);
//			}
//			else if (fVecNorObjOld[1] >= 0.0f && fVecNorObj[1] < 0.0f)
//			{
//				//面ベクトルを求めるための頂点ベクトルの算出
//				vecNorVtx[0] = D3DXVECTOR3(m_vtxMtxWorld[5]._41 - m_vtxMtxWorld[7]._41,
//					m_vtxMtxWorld[5]._42 - m_vtxMtxWorld[7]._42,
//					m_vtxMtxWorld[5]._43 - m_vtxMtxWorld[7]._43);
//				vecNorVtx[1] = D3DXVECTOR3(m_vtxMtxWorld[3]._41 - m_vtxMtxWorld[7]._41,
//					m_vtxMtxWorld[3]._42 - m_vtxMtxWorld[7]._42,
//					m_vtxMtxWorld[3]._43 - m_vtxMtxWorld[7]._43);
//			}
//			else if (fVecNorObjOld[2] >= 0.0f && fVecNorObj[2] < 0.0f)
//			{
//				//面ベクトルを求めるための頂点ベクトルの算出
//				vecNorVtx[0] = D3DXVECTOR3(m_vtxMtxWorld[4]._41 - m_vtxMtxWorld[6]._41,
//					m_vtxMtxWorld[4]._42 - m_vtxMtxWorld[6]._42,
//					m_vtxMtxWorld[4]._43 - m_vtxMtxWorld[6]._43);
//				vecNorVtx[1] = D3DXVECTOR3(m_vtxMtxWorld[7]._41 - m_vtxMtxWorld[6]._41,
//					m_vtxMtxWorld[7]._42 - m_vtxMtxWorld[6]._42,
//					m_vtxMtxWorld[7]._43 - m_vtxMtxWorld[6]._43);
//			}
//			else if (fVecNorObjOld[3] >= 0.0f && fVecNorObj[3] < 0.0f)
//			{
//				//面ベクトルを求めるための頂点ベクトルの算出
//				vecNorVtx[0] = D3DXVECTOR3(m_vtxMtxWorld[0]._41 - m_vtxMtxWorld[2]._41,
//					m_vtxMtxWorld[0]._42 - m_vtxMtxWorld[2]._42,
//					m_vtxMtxWorld[0]._43 - m_vtxMtxWorld[2]._43);
//				vecNorVtx[1] = D3DXVECTOR3(m_vtxMtxWorld[6]._41 - m_vtxMtxWorld[2]._41,
//					m_vtxMtxWorld[6]._42 - m_vtxMtxWorld[2]._42,
//					m_vtxMtxWorld[6]._43 - m_vtxMtxWorld[2]._43);
//			}
//
//
//			//元の大きさに戻す
//			m_vtxPos[0].z -= sizePlayer.x / 2.0f;
//			m_vtxPos[1].z -= sizePlayer.x / 2.0f;
//			m_vtxPos[2].z -= sizePlayer.x / 2.0f;
//			m_vtxPos[3].z -= sizePlayer.x / 2.0f;
//			m_vtxPos[4].z += sizePlayer.x / 2.0f;
//			m_vtxPos[5].z += sizePlayer.x / 2.0f;
//			m_vtxPos[6].z += sizePlayer.x / 2.0f;
//			m_vtxPos[7].z += sizePlayer.x / 2.0f;
//			m_vtxPos[0].x += sizePlayer.x / 2.0f;
//			m_vtxPos[1].x -= sizePlayer.x / 2.0f;
//			m_vtxPos[2].x += sizePlayer.x / 2.0f;
//			m_vtxPos[3].x -= sizePlayer.x / 2.0f;
//			m_vtxPos[4].x += sizePlayer.x / 2.0f;
//			m_vtxPos[5].x -= sizePlayer.x / 2.0f;
//			m_vtxPos[6].x += sizePlayer.x / 2.0f;
//			m_vtxPos[7].x -= sizePlayer.x / 2.0f;
//
//			//法線ベクトルを求める
//			D3DXVec3Cross(&nor, &vecNorVtx[0], &vecNorVtx[1]);
//			D3DXVec3Normalize(&nor, &nor);			//正規化する(ベクトルの大きさを1にする)
//
//													//ムーブベクトルを求める
//			moveVec = D3DXVECTOR3(posPlayer.x - posOldPlayer.x, posPlayer.y - posOldPlayer.y, posPlayer.z - posOldPlayer.z);
//
//			//ムーブベクトルと法線の内積を求める
//			fInVec = (-moveVec.x * nor.x) + (-moveVec.y * nor.y) + (-moveVec.z * nor.z);
//
//			//法線の方向に内積分伸ばしたベクトルを求める
//			norInVec = D3DXVECTOR3(nor.x * fInVec, nor.y * fInVec, nor.z * fInVec);
//
//			//対象を押し戻す位置のベクトルを求める
//			posPlayerVec = D3DXVECTOR3(nor.x * sizePlayer.x / 2.0f, nor.y * sizePlayer.x / 2.0f, nor.z * sizePlayer.x / 2.0f);
//
//			//当たり判定
//			if (((fVecNorObj[0] < 0.0f && fVecNorObj[1] < 0.0f && fVecNorObj[2] < 0.0f && fVecNorObj[3] < 0.0f) &&
//				(fVecNorObjOld[0] >= 0.0f || fVecNorObjOld[1] >= 0.0f || fVecNorObjOld[2] >= 0.0f || fVecNorObjOld[3] >= 0.0f)))
//			{
//				//対象の押出先を求める
//				posFinPlayer.x = (moveVec.x + norInVec.x);
//				posFinPlayer.y = (moveVec.y + norInVec.y);
//				posFinPlayer.z = (moveVec.z + norInVec.z);
//
//				//当たってる
//				posPlayer.x = posOldPlayer.x;
//				posPlayer.z = posOldPlayer.z;
//				posPlayer.x += posFinPlayer.x;
//				posPlayer.z += posFinPlayer.z;
//
//				//位置を設定
//				pPlayer->SetPos(posPlayer);
//			}
//		}
//		pObject = pSaveObject->GetObjNext(pSaveObject);
//	}
//}

//=============================================================================
// 親モデル設定処理
//=============================================================================
void CModel::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}

//=============================================================================
// ワールドマトリックス取得処理
//=============================================================================
D3DXMATRIX CModel::GetMtx(void)
{
	return m_mtxWorld;
}

//================================================
// 位置設定処理
//================================================
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//================================================
// 位置取得処理
//================================================
D3DXVECTOR3 CModel::GetPos(void)
{
	return m_pos;
}

//================================================
// 向き設定処理
//================================================
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//================================================
// 向き取得処理
//================================================
D3DXVECTOR3 CModel::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// サイズ取得処理
//=============================================================================
D3DXVECTOR3 CModel::GetSize(void)
{
	return m_size;
}