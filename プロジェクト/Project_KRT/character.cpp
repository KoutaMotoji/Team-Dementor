//===============================================================================
//
//  �v���C���[����(character.cpp)
//								����F���n�O��
// 
//===============================================================================
#include "character.h"
#include "floor_stone.h"


namespace
{
	float Damage_Ratio = 0.2f;
	float _RADIUS = 200.0f;
};

//==========================================================================================
//�R���X�g���N�^
//==========================================================================================
CCharacter::CCharacter(int nPriority) :CObject(nPriority),
						m_nLife(1000),
						m_bMotion(false),
						m_bBlend(false),
						m_NowAllFrame(0),
						m_move( { 0.0f,0.0f,0.0f }),
						m_rot ( { 0.0f,0.0f,0.0f }),
						m_size ( { 1.0f,1.0f,1.0f }),
						m_Radius({ _RADIUS ,_RADIUS ,_RADIUS })
{

}

//==========================================================================================
//�f�X�g���N�^
//==========================================================================================
CCharacter::~CCharacter()
{

}

//==========================================================================================
//����������
//==========================================================================================
void CCharacter::Init()
{
	MotionInit();		//���[�V�����̏����ݒ�
}

//==========================================================================================
//�I������
//==========================================================================================
void CCharacter::Uninit()
{
	for (auto& e : m_apModelParts)
	{
		e->Uninit();
	}
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CCharacter::Update()
{
	if (!MotionBlending())	//���[�V�����u�����h�������f
	{//���[�V�����u�����h���łȂ���Βʏ�̃��[�V�����Đ�
		SetNextKey();
	}
	AddPos(m_move);

	//�ړ��ʂ��X�V
	m_move.x += (0.0f - m_move.x) * 0.14f;
	m_move.y += (0.0f - m_move.y) * 0.14f;
	m_move.z += (0.0f - m_move.z) * 0.17f;
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CCharacter::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;

	//�N�I�[�^�j�I�����쐬
	D3DXQuaternionRotationAxis(
		&m_quat,
		&m_vecAxis,
		m_fValueRot);

	//�N�I�[�^�j�I�������]�}�g���b�N�X���쐬
	D3DXMatrixRotationQuaternion(
		&mtxRot,
		&m_quat);
	m_mtxRot = mtxRot;		//��]�}�g���b�N�X��ۑ�

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�傫���𔽉f
	D3DXMatrixScaling(&mtxSize,
		m_size.y,
		m_size.x,
		m_size.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxSize);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y,
		m_rot.x,
		m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&m_mtxRot);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD,
		&m_mtxWorld);
	for (auto& e : m_apModelParts)
	{
		e->Draw();
	}
	int nCnt{};
	for (auto& e : m_pHitCircle)
	{
		if (e->GetEnable()) {
			D3DXVECTOR3 pos = e->CalcMtxPos(m_apModelParts[e->GetParentNum()]->GetWorldMatrix());
			m_pDebugCircle[nCnt]->Draw(pos);
		}
		++nCnt;
	}
}

//==========================================================================================
//��������
//==========================================================================================
CCharacter* CCharacter::Create(D3DXVECTOR3 pos)
{
	CCharacter* charactor = new CCharacter;

	charactor->m_pos = pos;
	charactor->Init();

	return charactor;
}


//==========================================================================================
// �v���C���[�̈ړ���������
//==========================================================================================
void CCharacter::FloorCollision()
{

}

//==========================================================================================
//���[�V�����̏���������
//==========================================================================================
void CCharacter::MotionInit()
{
	m_CurMotion = 0;
	m_CurKey = 0;
	m_NowFrame = 0;
	m_NowAllFrame = 0;
}

//==========================================================================================
//���̃��[�V�����Ɉڍs���鏈��
//==========================================================================================
void CCharacter::SetNextMotion(int nNextMotionNum)
{
	if (m_NextMotion == nNextMotionNum)
	{
		return;
	}
	m_NextMotion = nNextMotionNum;
	m_NowFrame = 0;
	m_NowAllFrame = 0;
	m_bBlend = true;
}
//==========================================================================================
//���̃��[�V�����Ɉڍs���鏈��(���[�V�����u�����h)
//==========================================================================================
void CCharacter::SetNextMotion(int nNextMotionNum,bool bBlend)
{
	if (m_NextMotion == nNextMotionNum)
	{
		return;
	}
	m_NextMotion = nNextMotionNum;
	m_NowFrame = 0;
	m_NowAllFrame = 0;
	m_bBlend = bBlend;
}
//==========================================================================================
//���̃L�[�̃��[�V��������
//==========================================================================================
void CCharacter::SetNextKey()
{
	//���݂̈ʒu�E�p�x
	D3DXVECTOR3 NowPos = {};
	D3DXVECTOR3 NowRot = {};

	//���̈ʒu�E�p�x
	D3DXVECTOR3 NextPos = {};
	D3DXVECTOR3 NextRot = {};

	//�����̍��������߂�p
	D3DXVECTOR3 DifPos = {};
	D3DXVECTOR3 DifRot = {};

	//�v�Z�p
	D3DXVECTOR3 DigitPos = {};
	D3DXVECTOR3 DigitRot = {};

	int nNowKey = m_CurKey;
	int nNowMotion = m_CurMotion;
	int nNextKey = (m_CurKey + 1) % m_aMotion[nNowMotion].nKeyNum;
	float fRatioFrame = (float)m_NowFrame / (float)m_aMotion[nNowMotion].aKetSet[nNowKey].nFrame;
	int nCntParts = 0;
	++m_NowAllFrame;
	int nCnt{};
	for (auto& e : m_pHitCircle)
	{
		if (e->GetMotionNum() == nNowMotion) {
			if (m_NowAllFrame >= e->GetStart() && m_NowAllFrame <= e->GetEnd()) {
				e->SetEnable();
			}
		}
		else {
			e->SetDisable();
		}
		++nCnt;
	}
	for (auto& e : m_apModelParts)
	{
		//���݂̌����ƈʒu�̏��
		NowPos = m_aMotion[nNowMotion].aKetSet[nNowKey].aKey[nCntParts].pos;
		NowRot = m_aMotion[nNowMotion].aKetSet[nNowKey].aKey[nCntParts].rot;

		//���̃L�[�̏��
		NextPos = m_aMotion[nNowMotion].aKetSet[nNextKey].aKey[nCntParts].pos;
		NextRot = m_aMotion[nNowMotion].aKetSet[nNextKey].aKey[nCntParts].rot;

		//���������߂�
		DifPos = NextPos - NowPos;
		DifRot = NextRot - NowRot;

		//-3.14�`3.14�̊Ԃ𒴂���ꍇ�̏C��
		if (DifRot.x >= D3DX_PI)
		{
			DifRot.x -= D3DX_PI * 2;
		}
		if (DifRot.y >= D3DX_PI)
		{
			DifRot.y -= D3DX_PI * 2;
		}
		if (DifRot.z >= D3DX_PI)
		{
			DifRot.z -= D3DX_PI * 2;
		}
		if (DifRot.x <= -D3DX_PI)
		{
			DifRot.x += D3DX_PI * 2;
		}
		if (DifRot.y <= -D3DX_PI)
		{
			DifRot.y += D3DX_PI * 2;
		}
		if (DifRot.z <= -D3DX_PI)
		{
			DifRot.z += D3DX_PI * 2;
		}

		DigitPos = DifPos * fRatioFrame + e->GetDefaultPos() + NowPos;
		DigitRot = DifRot * fRatioFrame + e->GetDefaultRot() + NowRot;

		e->SetPos(DigitPos);
		e->SetRot(DigitRot);

		++nCntParts;
	}

	++m_NowFrame;

	if (m_NowFrame >= m_aMotion[nNowMotion].aKetSet[nNowKey].nFrame)
	{
		++m_CurKey;
		m_NowFrame = 0;
		if (m_CurKey >= m_aMotion[nNowMotion].nKeyNum)
		{
			if (EndMotion())
			{
				if (!m_aMotion[nNowMotion].bLoop)
				{
					--m_CurKey;
					m_CurKey = 0;
					m_NowFrame = 0;
					m_NowAllFrame = 0;
					m_CurMotion = m_NextMotion = 0;
				}
				else
				{
					m_CurKey = 0;
					m_NowAllFrame = 0;
				}
			}
			else
			{
				m_CurKey = 0;
				m_NowAllFrame = 0;
				m_NowFrame = 0;
				m_CurMotion = m_NextMotion;
				m_bBlend = false;
			}
		}
	}
}
//==========================================================================================
//���[�V�����؂�ւ����̃u�����h����
//==========================================================================================
bool CCharacter::MotionBlending()
{
	if (!m_bBlend) {
		return false;
	}

	//���݂̈ʒu�E�p�x
	D3DXVECTOR3 NowPos = {};
	D3DXVECTOR3 NowRot = {};

	//���̈ʒu�E�p�x
	D3DXVECTOR3 NextPos = {};
	D3DXVECTOR3 NextRot = {};

	//�����̍��������߂�p
	D3DXVECTOR3 DifPos = {};
	D3DXVECTOR3 DifRot = {};

	//�v�Z�p
	D3DXVECTOR3 DigitPos = {};
	D3DXVECTOR3 DigitRot = {};

	int nLastKey = m_CurKey;
	int nNowMotion = m_CurMotion;

	float fRatioFrame = ((float)m_NowFrame / (float)m_aMotion[m_NextMotion].aKetSet[0].nFrame);
	int nCntParts = 0;

	for (auto& e : m_apModelParts)
	{
		//���݂̌����ƈʒu�̏��
		NowPos = m_aMotion[nNowMotion].aKetSet[nLastKey].aKey[nCntParts].pos;
		NowRot = m_aMotion[nNowMotion].aKetSet[nLastKey].aKey[nCntParts].rot;

		//���̃L�[�̏��
		NextPos = m_aMotion[m_NextMotion].aKetSet[0].aKey[nCntParts].pos;
		NextRot = m_aMotion[m_NextMotion].aKetSet[0].aKey[nCntParts].rot;

		//���������߂�
		DifPos = NextPos - NowPos;
		DifRot = NextRot - NowRot;

		//-3.14�`3.14�̊Ԃ𒴂���ꍇ�̏C��
		if (DifRot.x >= D3DX_PI)
		{
			DifRot.x -= D3DX_PI * 2;
		}
		if (DifRot.y >= D3DX_PI)
		{
			DifRot.y -= D3DX_PI * 2;
		}
		if (DifRot.z >= D3DX_PI)
		{
			DifRot.z -= D3DX_PI * 2;
		}
		if (DifRot.x <= -D3DX_PI)
		{
			DifRot.x += D3DX_PI * 2;
		}
		if (DifRot.y <= -D3DX_PI)
		{
			DifRot.y += D3DX_PI * 2;
		}
		if (DifRot.z <= -D3DX_PI)
		{
			DifRot.z += D3DX_PI * 2;
		}

		DigitPos = DifPos * fRatioFrame + e->GetDefaultPos() + NowPos;
		DigitRot = DifRot * fRatioFrame + e->GetDefaultRot() + NowRot;

		e->SetPos(DigitPos);
		e->SetRot(DigitRot);

		++nCntParts;
	}

	++m_NowFrame;

	if (m_NowFrame > m_aMotion[m_NextMotion].aKetSet[0].nFrame)
	{
		m_CurKey = 0;
		m_NowFrame = 0;
		m_CurMotion = m_NextMotion;
		SetNextKey();
		m_bBlend = false;
	}

	return m_bBlend;
}

//==========================================================================================
//���[�V�������t�@�C������ǂݍ���
//==========================================================================================
void CCharacter::MotionDataLoad(std::string filename)
{
	char LoadData[128];
	char ModelPath[128];

	int nNumModel = 0;
	FILE* pFile;
	int nCnt = 0;

	int nMotionCnt = 0;
	int nKeySet = 0;
	int nKey = 0;
	D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f };
	int nFilenameCnt = 0;
	int nParent = 0;
	int nIndex = 0;
	int nModelCnt = 0;
	Motion GetMotionData;
	Key GetKeyData;
	KeySet GetKeySetData;


	pFile = fopen(filename.c_str(), "r");

	if (pFile != nullptr)
	{
		while (1)
		{
			fscanf(pFile, "%s", LoadData);

			if (!strcmp(LoadData, "END_SCRIPT"))	// �t�@�C���̍Ō�
			{
				fclose(pFile);
				break;
			}

			if (LoadData[0] == '#')		// ������΂�
			{
				continue;
			}

			//���f���̓ǂݍ���
			if (!strcmp(LoadData, "NUM_MODEL"))
			{
				fscanf(pFile, "%s", LoadData);
				fscanf(pFile, "%d", &m_ModelParts);
			}
			//���f���̃t�@�C�����ǂݍ���
			if (!strcmp(LoadData, "MODEL_FILENAME"))
			{
				fscanf(pFile, "%s", LoadData);

				fscanf(pFile, "%s", ModelPath);

				m_pModelFileName.push_back(ModelPath);

				m_apModelParts.push_back(CModelParts::Create(pos, m_pModelFileName[nFilenameCnt]));

				++nFilenameCnt;
			}
			//�L�����N�^�[�̐ݒ�̓ǂݍ��݊J�n
			if (!strcmp(LoadData, "CHARACTERSET"))
			{
				while (1)
				{
					fscanf(pFile, "%s", LoadData);

					if (!strcmp(LoadData, "END_CHARACTERSET"))//�ǂݍ��݂��I��
					{
						break;
					}
					else if (!strcmp(LoadData, "PARTSSET"))
					{
						while (1)
						{
							fscanf(pFile, "%s", LoadData);

							if (LoadData[0] == '#')
							{//������΂�
								fgets(LoadData, 100, pFile);
								continue;
							}

							if (!strcmp(LoadData, "END_PARTSSET"))
							{
								//�ǂݍ��݂��I��
								break;
							}
							//�e�p�[�c�̃��[�V����pos�l
							else if (!strcmp(LoadData, "INDEX"))
							{
								fscanf(pFile, "%s", LoadData);
								fscanf(pFile, "%d", &nIndex);
							}

							//�e�p�[�c�̃��[�V����rot�l
							else if (!strcmp(LoadData, "PARENT"))
							{
								fscanf(pFile, "%s", LoadData);
								fscanf(pFile, "%d", &nParent);
							}
							//�e�p�[�c�̃��[�V����pos�l
							else if (!strcmp(LoadData, "POS"))
							{
								fscanf(pFile, "%s", LoadData);
								fscanf(pFile, "%f", &pos.x);
								fscanf(pFile, "%f", &pos.y);
								fscanf(pFile, "%f", &pos.z);
							}

							//�e�p�[�c�̃��[�V����rot�l
							else if (!strcmp(LoadData, "ROT"))
							{
								fscanf(pFile, "%s", LoadData);
								fscanf(pFile, "%f", &rot.x);
								fscanf(pFile, "%f", &rot.y);
								fscanf(pFile, "%f", &rot.z);
							}
						}
						m_apModelParts[nModelCnt]->SetPos(pos);
						m_apModelParts[nModelCnt]->SetRot(rot);

						m_apModelParts[nModelCnt]->SetDefault();
						m_apModelParts[nModelCnt]->SetIndex(nIndex);
						if (nParent != -1)
						{
							m_apModelParts[nModelCnt]->SetParent(m_apModelParts[nParent]);
						}
						++nModelCnt;
					}
				}
			}

			//���[�V�����̓ǂݍ��݊J�n
			if (!strcmp(LoadData, "MOTIONSET"))
			{
				while (1)
				{
					fscanf(pFile, "%s", LoadData);

					if (!strcmp(LoadData, "END_MOTIONSET"))//�ǂݍ��݂��I��
					{
						m_aMotion.push_back(GetMotionData);
						GetMotionData.aKetSet.clear();
						break;
					}
					//���[�v�̔��f
					else if (!strcmp(LoadData, "LOOP"))
					{
						int bloop;
					
						fscanf(pFile, "%s", LoadData);
						fscanf(pFile, "%d", &bloop);
						GetMotionData.bLoop = bloop;
					}

					//�S�̂̃L�[���̓ǂݍ���
					else  if (!strcmp(LoadData, "NUM_KEY"))
					{
						int nNum;
						fscanf(pFile, "%s", LoadData);
						fscanf(pFile, "%d", &nNum);
						GetMotionData.nKeyNum = nNum;
					}
					//�����蔻��̗L��
					else  if (!strcmp(LoadData, "COLLISION"))
					{
						D3DXVECTOR3 POS, RADIUS;
						int PARENT,START_F,END_F;
						float FLOAT_RADIUS;
						fscanf(pFile, "%s", LoadData);
						fscanf(pFile, "%d", &PARENT);
						fscanf(pFile, "%f", &POS.x);
						fscanf(pFile, "%f", &POS.y);
						fscanf(pFile, "%f", &POS.z);
						fscanf(pFile, "%f", &FLOAT_RADIUS);
						fscanf(pFile, "%d", &START_F);
						fscanf(pFile, "%d", &END_F);
						RADIUS = { FLOAT_RADIUS ,FLOAT_RADIUS ,FLOAT_RADIUS };
						m_pHitCircle.push_back(CHitCircle::Create(RADIUS, POS, PARENT, START_F, END_F,nMotionCnt));
						m_pDebugCircle.push_back(CDebugLineSphire::Create(FLOAT_RADIUS));
					}
					//�e�L�[��ǂݍ���
					if (!strcmp(LoadData, "KEYSET"))
					{
						while (1)
						{
							fscanf(pFile, "%s", LoadData);

							if (LoadData[0] == '#')
							{//������΂�
								fgets(LoadData, 100, pFile);
								continue;
							}

							if (!strcmp(LoadData, "END_KEYSET"))
							{
								GetMotionData.aKetSet.push_back(GetKeySetData);
								GetKeySetData.aKey.clear();
								//�ǂݍ��݂��I��
								break;
							}

							//���݂̃L�[�̃t���[������ǂݍ���
							else if (!strcmp(LoadData, "FRAME"))
							{
								int nFrame;
								fscanf(pFile, "%s", LoadData);
								fscanf(pFile, "%d", &nFrame);
								GetKeySetData.nFrame = nFrame;
							}

							//���݂̃L�[�̓ǂݍ���
							if (!strcmp(LoadData, "KEY"))
							{
								while (1)
								{
									fscanf(pFile, "%s", LoadData);

									if (!strcmp(LoadData, "END_KEY"))
									{
										GetKeySetData.aKey.push_back(GetKeyData);
										// �ǂݍ��݂��I��
										break;
									}

									//�e�p�[�c�̃��[�V����pos�l
									else if (!strcmp(LoadData, "POS"))
									{

										fscanf(pFile, "%s", LoadData);
										fscanf(pFile, "%f", &GetKeyData.pos.x);
										fscanf(pFile, "%f", &GetKeyData.pos.y);
										fscanf(pFile, "%f", &GetKeyData.pos.z);
									}

									//�e�p�[�c�̃��[�V����rot�l
									else if (!strcmp(LoadData, "ROT"))
									{
										fscanf(pFile, "%s", LoadData);
										fscanf(pFile, "%f", &GetKeyData.rot.x);
										fscanf(pFile, "%f", &GetKeyData.rot.y);
										fscanf(pFile, "%f", &GetKeyData.rot.z);
									}
								}

							}
						}

					}
				}
				++nMotionCnt;
			}
		}
	}
	else
	{
		assert(pFile == nullptr);
	}
}