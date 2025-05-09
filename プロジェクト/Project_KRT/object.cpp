//===============================================================================
// 
//  �S�I�u�W�F�N�g���N���X(object.cpp)
//								����F���n�O��
// 
//===============================================================================
#include "object.h"
#include "manager.h"


//�ÓI�����o�̏�����
int CObject::m_nNumAll = 0;
CObject* CObject::m_apObject[SET_PRIORITY][MAX_OBJECT] = {};


CObject::CObject(int nPriority)
{
	//�`�揇��ݒ�A�ꊇ�Ǘ��p�ɓo�^
	m_nPriority = nPriority;
	assert(!(m_nPriority < 0 || m_nPriority > SET_PRIORITY));
	
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_apObject[m_nPriority][i] == nullptr)
		{
			m_apObject[m_nPriority][i] = this;
			m_nID = i;
			m_nNumAll++;
			break;
		}
	}
}

//==========================================================================================
//�f�X�g���N�^
//==========================================================================================
CObject::~CObject()
{

}

//==========================================================================================
//���g�����
//==========================================================================================
void CObject::Release()
{
	int nID = m_nID;
	int nPriority = m_nPriority;
	if (m_apObject[nPriority][nID] != nullptr)
	{
		m_apObject[nPriority][nID]->Uninit();
		delete m_apObject[nPriority][nID];
		m_apObject[nPriority][nID] = nullptr;
		m_nNumAll--;
	}
}

//==========================================================================================
//�I�u�W�F�N�g�̃|�C���^��Ԃ�
//==========================================================================================
CObject* CObject::GetObjects(int nPriority,int nIdx)
{
	return m_apObject[nPriority][nIdx];
}

//==========================================================================================
//�^�C�v��ݒ�
//==========================================================================================
void CObject::SetType(TYPE type)
{
	m_type = type;
}

//==========================================================================================
//�^�C�v��Ԃ�
//==========================================================================================
CObject::TYPE CObject::GetType()
{
	return m_type;
}

//==========================================================================================
//���ׂĉ��
//==========================================================================================
void CObject::ReleaseAll()
{
	for (int j = 0; j < SET_PRIORITY; j++)
	{
		for (int i = 0; i < MAX_OBJECT; i++)
		{
			if (m_apObject[j][i] != nullptr)
			{
				m_apObject[j][i]->Release();
			}
		}
	}
}

//==========================================================================================
//���ׂčX�V
//==========================================================================================
void CObject::UpdateAll()
{
	for (int j = 0; j < SET_PRIORITY; j++)
	{
		for (int i = 0; i < MAX_OBJECT; i++)
		{
			if (m_apObject[j][i] != nullptr)
			{
				m_apObject[j][i]->Update();
			}
		}
	}
}

//==========================================================================================
//���ׂĕ`��
//==========================================================================================
void CObject::DrawAll()
{
	for (int j = 0; j < SET_PRIORITY; j++)
	{
		for (int i = 0; i < MAX_OBJECT; i++)
		{
			if (m_apObject[j][i] != nullptr)
			{
				m_apObject[j][i]->Draw();
			}
		}
	}
}