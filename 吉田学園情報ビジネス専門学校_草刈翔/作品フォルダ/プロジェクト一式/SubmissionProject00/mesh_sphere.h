//=============================================================================
// ���b�V��(����)���� [mesh_sphere.h]
// Authore : ���� ��
//=============================================================================
#ifndef _MESH_SPHERE_H_
#define _MESH_SPHERE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
//�N���X�̒�`
//*****************************************************************************
class CMeshSphere : public CScene
{
public:
	CMeshSphere(int nPriority = PRIORITY_NONE);						// �R���X�g���N�^
	~CMeshSphere();													// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
	static CMeshSphere *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
		D3DXVECTOR3 rot, int nVertical, int nSide);					// ��������
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);					// �e�N�X�`����������

private:
	LPDIRECT3DTEXTURE9 m_pTexture;									// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;								// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;								// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;												// �ʒu
	D3DXVECTOR3	m_size;												// �T�C�Y
	D3DXVECTOR3 m_rot;												// ����
	D3DXMATRIX m_mtxWorld;											// ���[���h�}�g���b�N�X
	int m_nVertical;												// �c�̕�����
	int m_nSide;													// ���̕�����
};

#endif // _MESH_SPHERE_H_