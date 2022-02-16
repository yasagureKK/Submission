//=============================================================================
// �Q�[�����̔w�i�I�u�W�F�N�g�������� [game_object.h]
// Author : ���� ��
//=============================================================================
#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GAME_MAX_BACK_OBJECT	(20)	// �w�i�I�u�W�F�N�g�̍ő吔

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModelSingle;
class CBillboard;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CGameObject : public CScene
{
public:
	CGameObject();											// �R���X�g���N�^
	~CGameObject();											// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��
	static CGameObject *Create(D3DXVECTOR3 pos, 
		D3DXVECTOR3 size, int nNumPlayer);					// ��������

private:
	void DeleteObject();									// �I�u�W�F�N�g�̏�������
	D3DXVECTOR3 m_pos;										// �ʒu
	D3DXVECTOR3 m_size;										// �T�C�Y
	CModelSingle *m_apModelSingle[GAME_MAX_BACK_OBJECT];	// ���f��(�P��)�̃|�C���^
	CBillboard *m_apBilboard[GAME_MAX_BACK_OBJECT];			// �r���{�[�h�̃|�C���^
	int m_nNumPlayer;										// �ǂ̃v���C���[�ɑ΂�����̂�
};

#endif	// _GAME_OBJECT_H_