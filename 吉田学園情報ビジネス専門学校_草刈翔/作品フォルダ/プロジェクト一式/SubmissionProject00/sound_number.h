//=============================================================================
// �T�E���h�i���o�[���� [sound_number.h]
// Authore : ���� ��
//=============================================================================
#ifndef _SOUND_NUMBER_H_
#define _SOUND_NUMBER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SOUND_NUMBER_DIGIT (3)	// �Ȃ̍ő包��

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSoundNumber : public CScene
{
public:
	CSoundNumber(int nPriority = PRIORITY_UI);			// �R���X�g���N�^
	~CSoundNumber();									// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��
	static CSoundNumber *Create(D3DXVECTOR3 pos,
		D3DXVECTOR3 size, D3DXCOLOR col);				// ��������
	void SetNumber(int nNumber);						// �i���o�[�ݒ菈��

private:
	void PlaySound(int nNum);							// �T�E���h�Đ�����

	CNumber *m_apNumber[MAX_SOUND_NUMBER_DIGIT];		// �i���o�[�̃|�C���^
	int m_nSoundNumber;									// ���݂̐�
	D3DXVECTOR3 m_pos;									// �ʒu
	D3DXVECTOR3 m_size;									// �T�C�Y
	D3DXCOLOR m_col;									// �J���[
};

#endif	//_SOUND_NUMBER_H_