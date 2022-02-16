//=============================================================================
// サウンドナンバー処理 [sound_number.cpp]
// Authore : 草刈 翔
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "sound_number.h"
#include "number.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "ui.h"
#include "input_keyboard.h"
#include "input_pad.h"
#include "sound.h"
#include "fade.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CSoundNumber::CSoundNumber(int nPriority) : CScene(nPriority)
{
	memset(&m_apNumber, NULL, sizeof(m_apNumber));
	m_nSoundNumber = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CSoundNumber::~CSoundNumber()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSoundNumber::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 変数の初期化
	m_pos = pos;
	m_size = size;

	for (int nCntScore = 0; nCntScore < MAX_SOUND_NUMBER_DIGIT; nCntScore++)
	{
		// ナンバーの生成
		m_apNumber[nCntScore] = CNumber::Create(D3DXVECTOR3(m_pos.x + (nCntScore * (m_size.x / 5 * 4)), m_pos.y, m_pos.z), m_size, m_col);
	}

	// 位置・サイズの設定
	SetPos(m_pos);
	SetSize(m_size);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSoundNumber::Uninit(void)
{
	// ナンバーの破棄
	for (int nCntScore = 0; nCntScore < MAX_SOUND_NUMBER_DIGIT; nCntScore++)
	{
		// ヌルチェック
		if (m_apNumber[nCntScore] != NULL)
		{
			m_apNumber[nCntScore]->Uninit();
			delete m_apNumber[nCntScore];
			m_apNumber[nCntScore] = NULL;
		}
	}

	// オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CSoundNumber::Update(void)
{
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ゲームパッド取得処理
	CInputPad *pInputPad;
	pInputPad = CManager::GetInputPad();

	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//フェード取得処理
	CFade *pFade;
	pFade = CManager::GetFade();

	for (int nCntNumber = 0; nCntNumber < MAX_SOUND_NUMBER_DIGIT; nCntNumber++)
	{
		if (nCntNumber == MAX_SOUND_NUMBER_DIGIT - 1)
		{
			// 最後は10のn乗が使えなくなるため、決め打ちで処理
			m_apNumber[nCntNumber]->SetNumber(m_nSoundNumber % 10 / 1);
		}
		else
		{
			// ＜スコア % 10×n / 10×(n-1)＞ で出た値をそれぞれのナンバーに設定
			//※powf(float x, float y) … xのy乗の値
			m_apNumber[nCntNumber]->SetNumber(m_nSoundNumber % (int)powf(10, MAX_SOUND_NUMBER_DIGIT - (float)nCntNumber) / (int)powf(10, MAX_SOUND_NUMBER_DIGIT - ((float)nCntNumber + 1)));
		}
	}

	// フェードしていない時のみ操作できる
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		for (int nNum = 0; nNum < MAX_PLAYER_NUM; nNum++)
		{
			int nLeft, nRight;

			if (nNum == 0)
			{
				nLeft = DIK_A;
				nRight = DIK_D;
			}
			else if (nNum == 1)
			{
				nLeft = DIK_LEFT;
				nRight = DIK_RIGHT;
			}

			//***********************************************************************
			// 選択 (1P:W/S、2P:↑/↓ または パッド左スティック/十字キー)
			//***********************************************************************
			//左
			if (pInputKeyboard->GetTrigger(nLeft) == true ||
				pInputPad->GetTrigger(CInputPad::PAD_INPUTTYPE_LSTICK_LEFT, nNum) == true ||
				pInputPad->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_LEFT, nNum) == true)
			{
				// SEの再生
				pSound->Play(CSound::SOUND_LABEL_CURSOR);
				pSound->ControllVoice(CSound::SOUND_LABEL_CURSOR, 0.4f);

				m_nSoundNumber--;
			}
			//右
			else if (pInputKeyboard->GetTrigger(nRight) == true ||
				pInputPad->GetTrigger(CInputPad::PAD_INPUTTYPE_LSTICK_RIGHT, nNum) == true ||
				pInputPad->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_RIGHT, nNum) == true)
			{
				// SEの再生
				pSound->Play(CSound::SOUND_LABEL_CURSOR);
				pSound->ControllVoice(CSound::SOUND_LABEL_CURSOR, 0.4f);

				m_nSoundNumber++;
			}

			// 選択肢の制限
			if (m_nSoundNumber < 0)
			{
				m_nSoundNumber = 8;
			}
			else if (m_nSoundNumber > 8)
			{
				m_nSoundNumber = 0;
			}

			//***********************************************************************
			// 決定 (Enter/Space または パッドAボタン)
			//***********************************************************************
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
				pInputKeyboard->GetTrigger(DIK_SPACE) == true ||
				pInputPad->GetButtonTrigger(XINPUT_GAMEPAD_A, nNum) == true)
			{
				// 再生の前にBGMをストップ
				pSound->Stop();

				// BGMを再生する
				PlaySound(m_nSoundNumber);
			}
		}
	}

	// ナンバーを更新
	SetNumber(m_nSoundNumber);
}

//=============================================================================
// 描画処理
//=============================================================================
void CSoundNumber::Draw(void)
{
	for (int nCntScore = 0; nCntScore < MAX_SOUND_NUMBER_DIGIT; nCntScore++)
	{
		// ヌルチェック
		if (m_apNumber[nCntScore] != NULL)
		{
			m_apNumber[nCntScore]->Draw();
		}
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CSoundNumber *CSoundNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col)
{
	// インスタンスの生成
	CSoundNumber *pSoundNumber = NULL;

	// ヌルチェック
	if (pSoundNumber == NULL)
	{
		pSoundNumber = new CSoundNumber;
		if (pSoundNumber != NULL)
		{
			// 変数の設定
			pSoundNumber->m_col = col;

			// 初期化処理
			pSoundNumber->Init(pos, size);
		}
	}
	return pSoundNumber;
}

//=============================================================================
// スコア設定処理
//=============================================================================
void CSoundNumber::SetNumber(int nNumber)
{
	m_nSoundNumber = nNumber;
}

//=============================================================================
// サウンド再生処理
//=============================================================================
void CSoundNumber::PlaySound(int nNum)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	// 指定された数字(int型)を列挙型にキャストする
	CSound::SOUND_LABEL num = (CSound::SOUND_LABEL)nNum;

	// BGMの再生
	pSound->Play(num);
	pSound->ControllVoice(num, 0.4f);
}