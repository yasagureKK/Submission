//=============================================================================
// �Q�[�����̔w�i�I�u�W�F�N�g�������� [game_object.cpp]
// Author : ���� ��
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "game_object.h"
#include "manager.h"
#include "texture.h"
#include "model_single.h"
#include "billboard.h"
#include "player.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGameObject::CGameObject()
{
	// �ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	memset(&m_apModelSingle, NULL, sizeof(m_apModelSingle));
	memset(&m_apBilboard, NULL, sizeof(m_apBilboard));
	m_nNumPlayer = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameObject::~CGameObject()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGameObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;
	D3DXVECTOR3 ObjPos = pos;
	int nRandumPattern = rand() % 4;

	if (m_nNumPlayer == 1)
	{
		ObjPos.z = 10000.0f;
	}
	
	switch (nRandumPattern)
	{
		//���z�u���鎞�͈̖̔͂ڈ��cX����(pos.x - 120 �` pos.x + 480)�AZ����(pos.z + 120 �` pos.z + 370)��
		//���z�u���̓��f�����r���{�[�h(�������O�Ɍ�������)
		// �؁{�΂݁{��
	case 0:
		/************************************************************************************************************/
		// �r���{�[�h
		/************************************************************************************************************/
		m_apBilboard[0] = CBillboard::Create(D3DXVECTOR3(ObjPos.x - 80.0f, 95.0f, ObjPos.z + 340.0f), D3DXVECTOR3(360.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[0]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TREE));
		m_apBilboard[0]->SetShadow(true, 5.0f);

		m_apBilboard[1] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 450.0f, 95.0f, ObjPos.z + 270.0f), D3DXVECTOR3(360.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[1]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TREE));
		m_apBilboard[1]->SetShadow(true, 5.0f);

		m_apBilboard[2] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 560.0f, 15.0f, ObjPos.z + 240.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[2]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_05));

		m_apBilboard[3] = CBillboard::Create(D3DXVECTOR3(ObjPos.x - 320.0f, 95.0f, ObjPos.z + 230.0f), D3DXVECTOR3(360.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[3]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TREE));
		m_apBilboard[3]->SetShadow(true, 5.0f);

		m_apBilboard[4] = CBillboard::Create(D3DXVECTOR3(ObjPos.x - 220.0f, 25.0f, ObjPos.z + 210.0f), D3DXVECTOR3(260.0f, 140.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[4]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_BUSH_00));
		m_apBilboard[4]->SetShadow(true, 10.0f);

		m_apBilboard[5] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 200.0f, 95.0f, ObjPos.z + 210.0f), D3DXVECTOR3(360.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[5]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TREE));
		m_apBilboard[5]->SetShadow(true, 5.0f);

		m_apBilboard[6] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 160.0f, 25.0f, ObjPos.z + 170.0f), D3DXVECTOR3(180.0f, 140.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[6]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_BUSH_00));
		m_apBilboard[6]->SetShadow(true, 10.0f);

		m_apBilboard[7] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 10.0f, 15.0f, ObjPos.z + 165.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[7]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_00));

		m_apBilboard[8] = CBillboard::Create(D3DXVECTOR3(ObjPos.x - 100.0f, 15.0f, ObjPos.z + 150.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[8]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_00));

		m_apBilboard[9] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 470.0f, 15.0f, ObjPos.z + 145.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[9]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_00));

		m_apBilboard[10] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 260.0f, 25.0f, ObjPos.z + 140.0f), D3DXVECTOR3(220.0f, 140.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[10]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_BUSH_00));
		m_apBilboard[10]->SetShadow(true, 10.0f);

		m_apBilboard[11] = CBillboard::Create(D3DXVECTOR3(ObjPos.x - 50.0f, 15.0f, ObjPos.z + 140.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[11]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_01));

		break;

		// ��{�؁{�΂݁{��
	case 1:
		/************************************************************************************************************/
		// ���f��
		/************************************************************************************************************/
		m_apModelSingle[0] = CModelSingle::Create(D3DXVECTOR3(ObjPos.x + 20.0f, 0.0f, ObjPos.z + 210.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_ROCK, CModelSingle::MODEL_SINGLE_TYPE_NONE);
		m_apModelSingle[0]->SetShadow(true, 0.0f);

		m_apModelSingle[1] = CModelSingle::Create(D3DXVECTOR3(ObjPos.x + 490.0f, 0.0f, ObjPos.z + 250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_ROCK, CModelSingle::MODEL_SINGLE_TYPE_NONE);
		m_apModelSingle[1]->SetShadow(true, 0.0f);

		/************************************************************************************************************/
		// �r���{�[�h
		/************************************************************************************************************/
		m_apBilboard[0] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 350.0f, 15.0f, ObjPos.z + 340.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[0]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_05));

		m_apBilboard[1] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 310.0f, 15.0f, ObjPos.z + 310.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[1]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_04));

		m_apBilboard[2] = CBillboard::Create(D3DXVECTOR3(ObjPos.x - 130.0f, 15.0f, ObjPos.z + 250.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[2]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_02));

		m_apBilboard[3] = CBillboard::Create(D3DXVECTOR3(ObjPos.x - 80.0f, 15.0f, ObjPos.z + 210.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[3]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_01));

		m_apBilboard[4] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 340.0f, 25.0f, ObjPos.z + 190.0f), D3DXVECTOR3(180.0f, 140.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[4]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_BUSH_00));
		m_apBilboard[4]->SetShadow(true, 10.0f);

		m_apBilboard[5] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 260.0f, 95.0f, ObjPos.z + 170.0f), D3DXVECTOR3(360.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[5]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TREE));
		m_apBilboard[5]->SetShadow(true, 5.0f);

		m_apBilboard[6] = CBillboard::Create(D3DXVECTOR3(ObjPos.x - 330.0f, 27.5f, ObjPos.z + 165.0f), D3DXVECTOR3(220.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[6]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_BUSH_00));
		m_apBilboard[6]->SetShadow(true, 10.0f);

		m_apBilboard[7] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 620.0f, 95.0f, ObjPos.z + 150.0f), D3DXVECTOR3(360.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[7]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TREE));
		m_apBilboard[7]->SetShadow(true, 5.0f);

		m_apBilboard[8] = CBillboard::Create(D3DXVECTOR3(ObjPos.x - 220.0f, 20.0f, ObjPos.z + 135.0f), D3DXVECTOR3(240.0f, 120.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[8]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_BUSH_00));
		m_apBilboard[8]->SetShadow(true, 10.0f);

		break;

		// �j���W���{�؁{�ԁ{�΂�
	case 2:
		/************************************************************************************************************/
		// ���f��
		/************************************************************************************************************/
		m_apModelSingle[0] = CModelSingle::Create(D3DXVECTOR3(ObjPos.x + 130.0f, 0.0f, ObjPos.z + 160.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_CARROT, CModelSingle::MODEL_SINGLE_TYPE_NONE);
		m_apModelSingle[0]->SetShadow(true, 0.0f);
		m_apModelSingle[1] = CModelSingle::Create(D3DXVECTOR3(ObjPos.x + 590.0f, 0.0f, ObjPos.z + 190.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_CARROT, CModelSingle::MODEL_SINGLE_TYPE_NONE);
		m_apModelSingle[1]->SetShadow(true, 0.0f);
		m_apModelSingle[2] = CModelSingle::Create(D3DXVECTOR3(ObjPos.x - 340.0f, 0.0f, ObjPos.z + 330.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_CARROT, CModelSingle::MODEL_SINGLE_TYPE_NONE);
		m_apModelSingle[2]->SetShadow(true, 0.0f);

		/************************************************************************************************************/
		// �r���{�[�h
		/************************************************************************************************************/
		m_apBilboard[0] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 220.0f, 95.0f, ObjPos.z + 270.0f), D3DXVECTOR3(360.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[0]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TREE));
		m_apBilboard[0]->SetShadow(true, 5.0f);

		m_apBilboard[1] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 330.0f, 15.0f, ObjPos.z + 360.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[1]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_04));

		m_apBilboard[2] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 380.0f, 15.0f, ObjPos.z + 340.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[2]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_02));

		m_apBilboard[3] = CBillboard::Create(D3DXVECTOR3(ObjPos.x, 25.0f, ObjPos.z + 340.0f), D3DXVECTOR3(220.0f, 140.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[3]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_BUSH_00));
		m_apBilboard[3]->SetShadow(true, 10.0f);

		m_apBilboard[4] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 400.0f, 32.5f, ObjPos.z + 230.0f), D3DXVECTOR3(220.0f, 170.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[4]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_BUSH_00));
		m_apBilboard[4]->SetShadow(true, 10.0f);

		m_apBilboard[5] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 460.0f, 27.5f, ObjPos.z + 200.0f), D3DXVECTOR3(220.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[5]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_BUSH_00));
		m_apBilboard[5]->SetShadow(true, 10.0f);

		m_apBilboard[6] = CBillboard::Create(D3DXVECTOR3(ObjPos.x - 110.0f, 15.0f, ObjPos.z + 180.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[6]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_05));

		m_apBilboard[7] = CBillboard::Create(D3DXVECTOR3(ObjPos.x - 260.0f, 95.0f, ObjPos.z + 155.0f), D3DXVECTOR3(360.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[7]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TREE));
		m_apBilboard[7]->SetShadow(true, 5.0f);

		m_apBilboard[8] = CBillboard::Create(D3DXVECTOR3(ObjPos.x - 20.0f, 15.0f, ObjPos.z + 140.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[8]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_02));
		break;

		// �؁{�΂݁{��{�j���W���{��
	case 3:
		/************************************************************************************************************/
		// ���f��
		/************************************************************************************************************/
		m_apModelSingle[0] = CModelSingle::Create(D3DXVECTOR3(ObjPos.x -240.0f, 0.0f, ObjPos.z + 190.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_ROCK, CModelSingle::MODEL_SINGLE_TYPE_NONE);
		m_apModelSingle[0]->SetShadow(true, 0.0f);

		m_apModelSingle[1] = CModelSingle::Create(D3DXVECTOR3(ObjPos.x + 370.0f, 0.0f, ObjPos.z + 320.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_CARROT, CModelSingle::MODEL_SINGLE_TYPE_NONE);
		m_apModelSingle[1]->SetShadow(true, 0.0f);

		/************************************************************************************************************/
		// �r���{�[�h
		/************************************************************************************************************/
		m_apBilboard[0] = CBillboard::Create(D3DXVECTOR3(ObjPos.x - 120.0f, 95.0f, ObjPos.z + 300.0f), D3DXVECTOR3(360.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[0]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TREE));
		m_apBilboard[0]->SetShadow(true, 5.0f);

		m_apBilboard[1] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 600.0f, 15.0f, ObjPos.z + 260.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[1]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_02));

		m_apBilboard[2] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 480.0f, 15.0f, ObjPos.z + 240.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[2]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_04));

		m_apBilboard[3] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 150.0f, 95.0f, ObjPos.z + 200.0f), D3DXVECTOR3(360.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[3]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TREE));
		m_apBilboard[3]->SetShadow(true, 5.0f);

		m_apBilboard[4] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 10.0f, 15.0f, ObjPos.z + 170.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[4]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_00));

		m_apBilboard[5] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 660.0f, 95.0f, ObjPos.z + 170.0f), D3DXVECTOR3(360.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[5]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TREE));
		m_apBilboard[5]->SetShadow(true, 5.0f);

		m_apBilboard[6] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 50.0f, 15.0f, ObjPos.z + 160.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[6]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_04));

		m_apBilboard[7] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 380.0f, 15.0f, ObjPos.z + 160.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[7]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_02));

		m_apBilboard[8] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 520.0f, 15.0f, ObjPos.z + 155.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[8]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_05));

		m_apBilboard[9] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 225, 25.0f, ObjPos.z + 150.0f), D3DXVECTOR3(220.0f, 140.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[9]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_BUSH_00));
		m_apBilboard[9]->SetShadow(true, 10.0f);

		m_apBilboard[10] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 615, 20.0f, ObjPos.z + 135.0f), D3DXVECTOR3(260.0f, 120.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[10]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_BUSH_00));
		m_apBilboard[10]->SetShadow(true, 10.0f);

		m_apBilboard[11] = CBillboard::Create(D3DXVECTOR3(ObjPos.x - 70.0f, 15.0f, ObjPos.z + 130.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[11]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_04));
		break;

		// �m�F�p�F�r���{�[�h
	case 99:
		m_apBilboard[0] = CBillboard::Create(D3DXVECTOR3(ObjPos.x - 40.0f, 20.0f, ObjPos.z + 50.0f), D3DXVECTOR3(80.0f, 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[0]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_00));
		m_apBilboard[1] = CBillboard::Create(D3DXVECTOR3(ObjPos.x - 0.0f, 20.0f, ObjPos.z + 50.0f), D3DXVECTOR3(80.0f, 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[1]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_01));
		m_apBilboard[2] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 40.0f, 20.0f, ObjPos.z + 50.0f), D3DXVECTOR3(80.0f, 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[2]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_02));
		m_apBilboard[3] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 80.0f, 20.0f, ObjPos.z + 50.0f), D3DXVECTOR3(80.0f, 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[3]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_03));
		m_apBilboard[4] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 120.0f, 20.0f, ObjPos.z + 50.0f), D3DXVECTOR3(80.0f, 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[4]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_04));
		m_apBilboard[5] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 160.0f, 20.0f, ObjPos.z + 50.0f), D3DXVECTOR3(80.0f, 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[5]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FLOWER_05));
		m_apBilboard[6] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 200.0f, 95.0f, ObjPos.z + 50.0f), D3DXVECTOR3(360.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[6]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TREE));
		m_apBilboard[6]->SetShadow(true, 5.0f);
		m_apBilboard[7] = CBillboard::Create(D3DXVECTOR3(ObjPos.x + 280.0f, 25.0f, ObjPos.z + 50.0f), D3DXVECTOR3(160.0f, 140.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_EFFECT);
		m_apBilboard[7]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_BUSH_00));
		m_apBilboard[7]->SetShadow(true, 10.0f);
		break;

		// �m�F�p�F�I�u�W�F�N�g
	case 100:
		m_apModelSingle[0] = CModelSingle::Create(D3DXVECTOR3(ObjPos.x - 30.0f, 0.0f, ObjPos.z + 160.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_CARROT, CModelSingle::MODEL_SINGLE_TYPE_NONE);
		m_apModelSingle[0]->SetShadow(true, 0.0f);
		m_apModelSingle[1] = CModelSingle::Create(D3DXVECTOR3(ObjPos.x + 310.0f, 0.0f, ObjPos.z + 160.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_ROCK, CModelSingle::MODEL_SINGLE_TYPE_NONE);
		m_apModelSingle[1]->SetShadow(true, 0.0f);
		break;
	default:
		break;
	}

	
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGameObject::Uninit(void)
{
	// �I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGameObject::Update(void)
{
	// �I�u�W�F�N�g��������|�C���^�E���̏���ۑ�����|�C���^
	CScene *pObject = NULL;
	CScene *pSaveObject = NULL;

	// �擪�̃|�C���^����
	pObject = pObject->GetTopObj(CScene::PRIORITY_MODEL);

	while (pObject != NULL)
	{
		// ���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;

		if (pObject->GetObjType() == CScene::OBJECT_TYPE_PLAYER)
		{
			// �v���C���[�N���X�ɃL���X�g
			CPlayer *pPlayer = NULL;
			pPlayer = (CPlayer*)pObject;

			// �ԍ����v���C���[�̔ԍ��ƈ�v���Ă�����
			if (m_nNumPlayer == pPlayer->GetNum())
			{
				// �v���C���[�̈ʒu���擾
				D3DXVECTOR3 pos = pPlayer->GetPos();

				// �ʒu�{�T�C�Y�̈ʒu�Ƀv���C���[�����������
				if (pos.x > m_pos.x + m_size.x)
				{
					// �I�u�W�F�N�g��������
					DeleteObject();

					// �ʒu�����炷
					m_pos.x += m_size.x * 2;

					Init(m_pos, m_size);
				}
			}
		}
		// ���̃I�u�W�F�N�g���擾
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CGameObject::Draw(void)
{

}

//=============================================================================
// ��������
//=============================================================================
CGameObject *CGameObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumPlayer)
{
	// �C���X�^���X�̐���
	CGameObject *pGameObject = NULL;

	// �k���`�F�b�N
	if (pGameObject == NULL)
	{
		// �N���X�̐���
		pGameObject = new CGameObject;
		if (pGameObject != NULL)
		{
			// �ϐ��̏�����
			pGameObject->m_nNumPlayer = nNumPlayer;

			// ����������
			pGameObject->Init(pos, size);
		}
	}

	return pGameObject;
}

//=============================================================================
// �I�u�W�F�N�g�̏�������
//=============================================================================
void CGameObject::DeleteObject(void)
{
	// ���f��������
	for (int nCntModel = 0; nCntModel < GAME_MAX_BACK_OBJECT; nCntModel++)
	{
		if (m_apModelSingle[nCntModel] != NULL)
		{
			m_apModelSingle[nCntModel]->DeleteShadow();
			m_apModelSingle[nCntModel]->Uninit();
			delete m_apModelSingle[nCntModel];
			m_apModelSingle[nCntModel] = NULL;
		}
	}

	// �r���{�[�h������
	for (int nCntBillboard = 0; nCntBillboard < GAME_MAX_BACK_OBJECT; nCntBillboard++)
	{
		if (m_apBilboard[nCntBillboard] != NULL)
		{
			m_apBilboard[nCntBillboard]->DeleteShadow();
			m_apBilboard[nCntBillboard]->Uninit();
			delete m_apBilboard[nCntBillboard];
			m_apBilboard[nCntBillboard] = NULL;
		}
	}
}