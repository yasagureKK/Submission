//=============================================================================
// �`���[�g���A���ł̃|�[�Y���� [tutorial_pause.h]
// Author : ���� ��
//=============================================================================
#ifndef _TUTORIAL_PAUSE_H_
#define _TUTORIAL_PAUSE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CTutorialPause : public CScene
{
public:
	CTutorialPause(int nPriority = PRIORITY_PAUSE);						// �R���X�g���N�^
	~CTutorialPause();													// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);					// ����������
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��
	static CTutorialPause *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
		int nTimer);													// ��������
	static void SetPause(bool bPause);									// �|�[�Y�ݒ菈��
	static bool GetPause(void);											// �|�[�Y�擾����

private:
	static bool m_bPause;												// �|�[�Y���Ă邩�ǂ���
	int m_nTimer;														// ���b�~�߂邩
};

#endif	// _TUTORIAL_PAUSE_H_