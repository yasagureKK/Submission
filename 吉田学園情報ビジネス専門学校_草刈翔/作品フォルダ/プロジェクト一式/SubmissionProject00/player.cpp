//=============================================================================
// プレイヤー処理 [player.cpp]
// Authore : 草刈 翔
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "input_keyboard.h"
#include "model.h"
#include "model_load.h"
#include "model_single.h"
#include "mesh_field.h"
#include "camera.h"
#include "motion_player.h"
#include "control_player.h"
#include "game.h"
#include "tutorial.h"
#include "shadow.h"
#include "particle_circle.h"
#include "sound.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority) :CScene(nPriority)
{
	// 変数のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{
		m_apModel[nCntModel] = NULL;
	}
	m_pParent = NULL;
	m_pControl = NULL;
	m_pShadow = NULL;
	m_pMotionPlayer = NULL;
	m_pParticle = NULL;
	m_bLand = false;
	m_bJumpOld = false;
	m_bLandFinish = false;
	m_bStop = true;
	m_nNum = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 変数の初期化
	m_pos = pos;
	m_posOld = pos;
	m_move = m_pControl->GetMove();
	m_bLand = false;
	m_bJump = true;
	m_bJumpOld = true;
	m_bLandFinish = false;
	m_bStop = true;

	// モデルの生成
	switch (m_nNum)
	{
	case 0:
		m_apModel[0] = CModel::Create(D3DXVECTOR3(0.0f, 2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_BODY);
		m_apModel[1] = CModel::Create(D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_HEAD);
		m_apModel[2] = CModel::Create(D3DXVECTOR3(-7.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_EAR_RIGHT_0);
		m_apModel[3] = CModel::Create(D3DXVECTOR3(-7.5f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_EAR_RIGHT_1);
		m_apModel[4] = CModel::Create(D3DXVECTOR3(7.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_EAR_LEFT_0);
		m_apModel[5] = CModel::Create(D3DXVECTOR3(7.5f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_EAR_LEFT_1);
		m_apModel[6] = CModel::Create(D3DXVECTOR3(-1.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_HAND_RIGHT);
		m_apModel[7] = CModel::Create(D3DXVECTOR3(1.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_HAND_LEFT);
		m_apModel[8] = CModel::Create(D3DXVECTOR3(-4.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_LEG_RIGHT);
		m_apModel[9] = CModel::Create(D3DXVECTOR3(0.0f, -5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_FOOT_RIGHT);
		m_apModel[10] = CModel::Create(D3DXVECTOR3(4.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_LEG_LEFT);
		m_apModel[11] = CModel::Create(D3DXVECTOR3(0.0f, -5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_FOOT_LEFT);
		break;

	case 1:
		m_apModel[0] = CModel::Create(D3DXVECTOR3(0.0f, 2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_2_BODY);
		m_apModel[1] = CModel::Create(D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_2_HEAD);
		m_apModel[2] = CModel::Create(D3DXVECTOR3(-7.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_2_EAR_RIGHT_0);
		m_apModel[3] = CModel::Create(D3DXVECTOR3(-7.5f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_2_EAR_RIGHT_1);
		m_apModel[4] = CModel::Create(D3DXVECTOR3(7.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_2_EAR_LEFT_0);
		m_apModel[5] = CModel::Create(D3DXVECTOR3(7.5f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_2_EAR_LEFT_1);
		m_apModel[6] = CModel::Create(D3DXVECTOR3(-1.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_2_HAND_RIGHT);
		m_apModel[7] = CModel::Create(D3DXVECTOR3(1.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_2_HAND_LEFT);
		m_apModel[8] = CModel::Create(D3DXVECTOR3(-4.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_2_LEG_RIGHT);
		m_apModel[9] = CModel::Create(D3DXVECTOR3(0.0f, -5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_2_FOOT_RIGHT);
		m_apModel[10] = CModel::Create(D3DXVECTOR3(4.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_2_LEG_LEFT);
		m_apModel[11] = CModel::Create(D3DXVECTOR3(0.0f, -5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_RABBIT_2_FOOT_LEFT);
		break;

	default:
		break;
	}
	
	// 親の設定
	m_apModel[0]->SetParent(NULL);			// 体	(親なし)
	m_apModel[1]->SetParent(m_apModel[0]);	// 頭	(親:体)
	m_apModel[2]->SetParent(m_apModel[1]);	// 右耳0(親:頭)
	m_apModel[3]->SetParent(m_apModel[2]);	// 右耳1(親:右耳0)
	m_apModel[4]->SetParent(m_apModel[1]);	// 左耳0(親:頭)
	m_apModel[5]->SetParent(m_apModel[4]);	// 左耳0(親:左耳0)
	m_apModel[6]->SetParent(m_apModel[0]);	// 右手 (親:体)
	m_apModel[7]->SetParent(m_apModel[0]);	// 左手 (親:体)
	m_apModel[8]->SetParent(m_apModel[0]);	// 右腿 (親:体)
	m_apModel[9]->SetParent(m_apModel[8]);	// 右足 (親:右腿)
	m_apModel[10]->SetParent(m_apModel[0]);	// 左腿 (親:体)
	m_apModel[11]->SetParent(m_apModel[10]);// 左足 (親:左腿)

	// 位置の設定
	SetPos(m_pos);
	SetPosOld(m_posOld);

	// オブジェクトの種類の設定
	SetObjType(CScene::OBJECT_TYPE_PLAYER);

	// サイズを取得
	m_size = m_apModel[0]->GetSize();

	// サイズの設定
	SetSize(m_size);

	// モーションの生成
	m_pMotionPlayer = CMotionPlayer::Create(this);

	// カメラのポインタ配列1番目のアドレス取得
	CCamera **pCameraAddress = CManager::GetCamera();

	// カメラの最大数ぶん、ポインタ配列を進める
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++, pCameraAddress++)
	{
		// カメラの取得
		CCamera *pCamera = &**pCameraAddress;
		if (pCamera != NULL)
		{
			// プレイヤーの番号とカメラの番号が同じだったら
			if (m_nNum == pCamera->GetNum())
			{
				if (CManager::GetMode() == CManager::MODE_RESULT)
				{
					// カメラの向きをプレイヤーの向きと等しくなるよう設定
					pCamera->SetRotV(m_rot);
					// カメラの注視点をプレイヤーの位置になるよう設定
					pCamera->SetPosR(m_pos);
					// カメラの視点がプレイヤーの後ろになるよう設定
					pCamera->SetPosV(D3DXVECTOR3(m_pos.x + sinf(m_rot.y) * CAMERA_DISTANCE,
						CAMERA_HEIGHT,
						m_pos.z + cosf(m_rot.y) * CAMERA_DISTANCE));
				}
				else
				{
					// カメラの向きをプレイヤーの向きと等しくなるよう設定
					pCamera->SetRotV(m_rot);
					// カメラの注視点をプレイヤーの位置になるよう設定
					pCamera->SetPosR(m_pos);
					// カメラの視点がプレイヤーの後ろになるよう設定
					pCamera->SetPosV(D3DXVECTOR3(m_pos.x + sinf(m_rot.y) * CAMERA_DISTANCE,
						CAMERA_HEIGHT,
						m_pos.z + cosf(m_rot.y) * CAMERA_DISTANCE));
				}
			}
		}
	}

	// チュートリアル画面で、説明をする場合
	if (CManager::GetMode() == CManager::MODE_TUTORIAL && CTutorial::GetExplanation() == true)
	{
		// プレイヤーの方を向かせる
		m_rot.y = 0.0f;
	}
	// リザルト画面なら
	else if (CManager::GetMode() == CManager::MODE_RESULT)
	{
		// プレイヤーの方を向かせる
		m_rot.y = 0.0f;
	}
	else
	{
		// プレイヤーから見て右に向かせる
		m_rot.y = -D3DX_PI / 2;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	//影を消す
	m_pShadow->Uninit();

	// オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	if (this != NULL)
	{
		// 位置の取得
		D3DXVECTOR3 pos = GetPos();
		m_pos = pos;
		m_posOld = pos;

		// 1フレーム前の位置設定
		SetPosOld(m_posOld);

		// 前のフレームにジャンプしているかどうかの情報を代入
		m_bJumpOld = m_bJump;

		// 移動処理
		Move();

		// 移動量反映
		m_pos += m_move;

		// 位置反映
		SetPos(m_pos);

		// 着地しているときは移動量を0にする
		m_bLand = CModelSingle::SimpleCollision(this);

		// 一番下に足場判定をつける
		if (m_pos.y <= 0)
		{
			m_pos.y = 0.0f;

			// キャラが埋まってしまうため位置を反映
			SetPos(m_pos);

			m_bLand = true;
		}
			
		if (m_bLand == true)
		{
			if (m_bJumpOld == true)
			{
				// ジャンプ関連モーションの時なら
				if (m_pMotionPlayer->GetMotion() == CMotionPlayer::MOTION_PLAYER_TYPE_JUMP ||
					m_pMotionPlayer->GetMotion() == CMotionPlayer::MOTION_PLAYER_TYPE_JUMP_FALL ||
					m_pMotionPlayer->GetMotion() == CMotionPlayer::MOTION_PLAYER_TYPE_DOUBLE_JUMP)
				{
					//着地モーションにする
					m_pMotionPlayer->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_LANDING);

					// パーティクルの生成
					m_pParticle = CParticleCircle::Create(m_pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						D3DCOLOR_RGBA(255, 255, 255, 55), 10, 3.0f);

					m_bJump = false;
					m_move.y = 0.0f;
				}
			}

			// 記録地点(x = 0以降)に着地したら
			if (m_pos.x > 0)
			{
				// 計測終了にする(ゲーム画面で結果を取得して更に処理させる)
				m_bLandFinish = true;
			}
		}

		// モーション
		m_pMotionPlayer->Update(this);

		// 影の追従
		ShadowCollision();

		// 位置取得
		m_pos = GetPos();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// プレイヤーのワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// プレイヤーの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// プレイヤーの位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// モデルの描画
	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{
		m_apModel[nCntModel]->Draw();
	}

}

//=============================================================================
// 生成処理
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumPlayer)
{
	// インスタンスの生成
	CPlayer *pPlayer = NULL;

	// ヌルチェック
	if (pPlayer == NULL)
	{
		// クラスの生成
		pPlayer = new CPlayer;
		if (pPlayer != NULL)
		{
			// 影の生成
			pPlayer->m_pShadow = CShadow::Create(D3DXVECTOR3(pos.x, 0.0f, pos.z), D3DXVECTOR3(40.0f, 0.0f, 40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			
			// プレイヤー操作のクラスを生成
			pPlayer->m_pControl = CControlPlayer::Create();

			// 変数の初期化
			pPlayer->m_nNum = nNumPlayer;
			pPlayer->m_rot = rot;

			// 初期化処理
			pPlayer->Init(pos, pPlayer->m_size);
		}
	}

	return pPlayer;
}

//=============================================================================
// 移動処理
//=============================================================================
void CPlayer::Move(void)
{
	// ヌルチェック
	if (m_pControl != NULL)
	{
		// プレイヤー操作のクラスにプレイヤーのポインタを入れ、移動量を取得
		m_pControl->Update(this);
		m_move = m_pControl->GetMove();
	}
}

//=============================================================================
// 当たり判定処理
//=============================================================================
bool CPlayer::Collision(void)
{
	return false;
}

//=============================================================================
// 1フレーム前の位置取得処理
//=============================================================================
D3DXVECTOR3 CPlayer::GetPosOld(void)
{
	return m_posOld;
}

//=============================================================================
// 向き設定処理
//=============================================================================
void CPlayer::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// 向き取得処理
//=============================================================================
D3DXVECTOR3 CPlayer::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// 移動量設定処理
//=============================================================================
void CPlayer::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// 移動量取得処理
//=============================================================================
D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_move;
}

//=============================================================================
// ジャンプ設定処理
//=============================================================================
void CPlayer::SetJump(bool bJump)
{
	m_bJump = bJump;
}

//=============================================================================
// ジャンプ取得処理
//=============================================================================
bool CPlayer::GetJump(void)
{
	return m_bJump;
}

//=============================================================================
// 着地設定処理
//=============================================================================
void CPlayer::SetLand(bool bLand)
{
	m_bLand = bLand;
}

//=============================================================================
// 着地取得処理
//=============================================================================
bool CPlayer::GetLand(void)
{
	return m_bLand;
}

//=============================================================================
// 着地でフィニッシュしたかどうか設定処理
//=============================================================================
void CPlayer::SetLandFinish(bool bLandFinish)
{
	m_bLandFinish = bLandFinish;
}

//=============================================================================
// 着地でフィニッシュしたかどうか取得処理
//=============================================================================
bool CPlayer::GetLandFinish(void)
{
	return m_bLandFinish;
}

//=============================================================================
// 止まっているかどうか設定処理
//=============================================================================
void CPlayer::SetStop(bool bStop)
{
	m_bStop = bStop;
}

//=============================================================================
// 止まっているかどうか設定処理
//=============================================================================
bool CPlayer::GetStop(void)
{
	return m_bStop;
}

//=============================================================================
// モデル毎の位置設定処理
//=============================================================================
void CPlayer::SetModelPos(int nCntModel, D3DXVECTOR3 pos)
{
	m_apModel[nCntModel]->SetPos(pos);
}

//=============================================================================
// モデル毎の位置取得処理
//=============================================================================
D3DXVECTOR3 CPlayer::GetModelPos(int nCntModel)
{
	return m_apModel[nCntModel]->GetPos();
}

//=============================================================================
// モデル毎の向き設定処理
//=============================================================================
void CPlayer::SetModelRot(int nCntModel, D3DXVECTOR3 rot)
{
	m_apModel[nCntModel]->SetRot(rot);
}

//=============================================================================
// モデル毎の向き取得処理
//=============================================================================
D3DXVECTOR3 CPlayer::GetModelRot(int nCntModel)
{
	return m_apModel[nCntModel]->GetRot();
}

//=============================================================================
// モーションプレイヤー取得処理
//=============================================================================
CMotionPlayer *CPlayer::GetMotionPlayer(void)
{
	return m_pMotionPlayer;
}

//=============================================================================
// オブジェクトとの当たり判定
//=============================================================================
void CPlayer::Collision(CScene *pScene)
{
	//オブジェクトの位置を取得
	D3DXVECTOR3 posObj = pScene->GetPos();
	//オブジェクトの1フレーム前の位置を取得
	D3DXVECTOR3 posObjOld = pScene->GetPosOld();
	//オブジェクトのサイズを取得
	D3DXVECTOR3 sizeObj = pScene->GetSize();

	if (posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
		posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
		posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
		posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
		posObj.y + sizeObj.y >= m_pos.y&&
		posObjOld.y + sizeObj.y <= m_pos.y)
	{
		m_pos.y = posObj.y + sizeObj.y;
		//位置を設定
		SetPos(m_pos);
		//1フレーム前の位置を設定
		SetPosOld(m_pos);
	}
	else if (posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
		posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
		posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
		posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
		posObj.y <= m_pos.y + m_size.y &&
		posObjOld.y >= m_pos.y + m_size.y)
	{
		m_pos.y = posObj.y - m_size.y;
		//位置を設定
		SetPos(m_pos);
		//1フレーム前の位置を設定
		SetPosOld(m_pos);
	}
	if (posObj.y + sizeObj.y < m_pos.y &&
		posObj.y > m_pos.y + m_size.y &&
		posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
		posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
		posObj.x + sizeObj.x / 2.0f <= m_pos.x - m_size.x / 2.0f &&
		posObjOld.x + sizeObj.x / 2.0f >= m_pos.x - m_size.x / 2.0f)
	{
		m_pos.x = posObj.x + sizeObj.x / 2.0f - m_size.x / 2.0f;
		//位置を設定
		SetPos(m_pos);
		//1フレーム前の位置を設定
		SetPosOld(m_pos);
	}
	else if (posObj.y + sizeObj.y < m_pos.y &&
		posObj.y > m_pos.y + m_size.y &&
		posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
		posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
		posObj.x - sizeObj.x / 2.0f >= m_pos.x + m_size.x / 2.0f &&
		posObjOld.x - sizeObj.x / 2.0f <= m_pos.x + m_size.x / 2.0f)
	{
		m_pos.x = posObj.x - sizeObj.x / 2.0f + m_size.x / 2.0f;
		//位置を設定
		SetPos(m_pos);
		//1フレーム前の位置を設定
		SetPosOld(m_pos);
	}
	if (posObj.y + sizeObj.y < m_pos.y &&
		posObj.y > m_pos.y + m_size.y &&
		posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
		posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
		posObj.z + sizeObj.z / 2.0f <= m_pos.z - m_size.x / 2.0f &&
		posObjOld.z + sizeObj.z / 2.0f >= m_pos.z - m_size.x / 2.0f)
	{
		m_pos.z = posObj.z - sizeObj.z / 2.0f + m_size.x / 2.0f;
		//位置を設定
		SetPos(m_pos);
		//1フレーム前の位置を設定
		SetPosOld(m_pos);
	}
	else if (posObj.y + sizeObj.y < m_pos.y &&
		posObj.y > m_pos.y + m_size.y &&
		posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
		posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
		posObj.z - sizeObj.z / 2.0f >= m_pos.z + m_size.x / 2.0f &&
		posObjOld.z - sizeObj.z / 2.0f <= m_pos.z + m_size.x / 2.0f)
	{
		m_pos.z = posObj.z + sizeObj.z / 2.0f - m_size.x / 2.0f;
		//位置を設定
		SetPos(m_pos);
		//1フレーム前の位置を設定
		SetPosOld(m_pos);
	}
}

//=============================================================================
////影の表示のためのオブジェクトとの当たり判定
//=============================================================================
void CPlayer::ShadowCollision(void)
{
	//オブジェクト情報を入れるポインタ
	CScene *pObject = NULL;
	//オブジェクト情報を保存するポインタ変数
	CScene *pSaveObject = NULL;

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CScene::PRIORITY_MODEL);

	while (pObject != NULL)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		if (pObject->GetObjType() == CScene::OBJECT_TYPE_MODEL)
		{
			// モデルシングルクラスにキャスト
			CModelSingle *pModelSingle = NULL;
			pModelSingle = (CModelSingle*)pObject;

			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 保存用の位置
			D3DXVECTOR3 posObj = pModelSingle->GetPos();		// オブジェクトの位置を取得
			D3DXVECTOR3 posObjOld = pModelSingle->GetPosOld();	// オブジェクトの1フレーム前の位置を取得
			D3DXVECTOR3 sizeObj = pModelSingle->GetSize();		// オブジェクトのサイズを取得

			if (posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
				posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
				posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
				posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
				posObj.y + sizeObj.y >= m_pos.y - 50.0f &&
				posObj.y + sizeObj.y <= m_pos.y)
			{
				//位置をモデルの上に
				pos.y = posObj.y + sizeObj.y;

				//影の追従
				m_pShadow->SetShadow(D3DXVECTOR3(m_pos.x, pos.y, m_pos.z), (m_pos.y - pos.y));

				//影を使っている状態にする
				m_pShadow->SetUseShadow(true);

				return;
			}
			else
			{
				//影を使っていない状態にする
				m_pShadow->SetUseShadow(false);
			}
		}

		pObject = pSaveObject->GetObjNext(pSaveObject);
	}

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CScene::PRIORITY_NONE);

	while (pObject != NULL)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		if (pObject->GetObjType() == CScene::OBJECT_TYPE_MODEL)
		{
			// メッシュフィールドクラスにキャスト
			CMeshField *pMeshField = NULL;
			pMeshField = (CMeshField*)pObject;

			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 保存用の位置
			D3DXVECTOR3 posObj = pMeshField->GetPos();			// オブジェクトの位置を取得
			D3DXVECTOR3 posObjOld = pMeshField->GetPosOld();	// オブジェクトの1フレーム前の位置を取得
			D3DXVECTOR3 sizeObj = pMeshField->GetSize();		// オブジェクトのサイズを取得

			if (posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
				posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
				posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
				posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
				posObj.y + sizeObj.y >= m_pos.y - 500.0f &&
				posObj.y + sizeObj.y <= m_pos.y + 10.0f)
			{
				//位置をフィールドの上に
				pos.y = posObj.y * 2;

				//影の追従
				m_pShadow->SetShadow(D3DXVECTOR3(m_pos.x, pos.y, m_pos.z), (m_pos.y - pos.y));

				//影を使っている状態にする
				m_pShadow->SetUseShadow(true);

				return;
			}
			else
			{
				//影を使っていない状態にする
				m_pShadow->SetUseShadow(false);
			}
		}

		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//=============================================================================
// プレイヤーの番号設定処理
//=============================================================================
void CPlayer::SetNum(int nNum)
{
	m_nNum = nNum;
}

//=============================================================================
// プレイヤーの番号取得処理
//=============================================================================
int CPlayer::GetNum(void)
{
	return m_nNum;
}

//=============================================================================
// プレイヤーの操作設定処理
//=============================================================================
void CPlayer::SetCommand(PLAYER_COMMAND command)
{
	m_command = command;
}

//=============================================================================
// プレイヤーの操作取得処理
//=============================================================================
CPlayer::PLAYER_COMMAND CPlayer::GetCommand(void)
{
	return m_command;
}