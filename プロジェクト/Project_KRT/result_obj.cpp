//===============================================================================
//
//  ���U���g�I�u�W�F�N�g(result_obj.cpp)
//								����F���n�O��
// 
//===============================================================================
#include"result_obj.h"
#include "inimanager.h"

namespace
{
	struct _FILENAME	//�t�@�C���̃p�X�Ǘ��\����
	{
		std::string config;		//�t�@�C���̃p�X
		std::string section;	//�Z�N�V������
		std::string keyword;	//�L�[���[�h��
	};
	_FILENAME player_filename = {				//�v���C���[�̃��f���E���[�V�����p�t�@�C���p�X
		"data\\TEXT\\Config.ini",
		 "ModelData",
		 "ResultPlayerMotion"
	};
	_FILENAME enemy_filename = {				//�v���C���[�̃��f���E���[�V�����p�t�@�C���p�X
		"data\\TEXT\\Config.ini",
		 "ModelData",
		 "ResultBossMotion"
	};
	std::string GROUND_FILENAME = "data\\MODEL\\title_field.x";

	D3DXVECTOR3 R_PLAYER_POS = { 100.0f,-110.0f,0.0f };
	D3DXVECTOR3 R_FIELD_POS = { 0.0f,500.0f,0.0f };
	float TREE_RADIUS = 200.0f;
	D3DXVECTOR3 LogoPos = { 770.0f,170.0f, 0.0f };
	D3DXVECTOR2 LogoSize = { 260.0f,105.0f };
	D3DXVECTOR3 RankPos = { 1050.0f,520.0f, 0.0f };
	D3DXVECTOR2 RankSize = { 250.0f,300.0f };
}

//==========================================================================================
//�g�̏���������
//==========================================================================================
void CResultBG::Init()
{
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\Result001.png");
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//�g�̏���������
//==========================================================================================
void CResultBG::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�e�N�X�`���g�厞�ɐF���ߎ��l�ɂ���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	//�X�e���V���}�X�N�̐ݒ莞�ɖ���������Z�o�b�t�@�����Ƃɂ��ǂ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//�A���t�@�e�X�g�ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2D::Draw();

	//�e�N�X�`���g�厞�̐F����`���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

//==========================================================================================
//�g�̐�������
//==========================================================================================
CResultBG* CResultBG::Create()
{
	CResultBG* bg = new CResultBG;

	bg->SetPolygonParam({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f }, SCREEN_HEIGHT, SCREEN_WIDTH);
	bg->Init();

	return bg;
}

//==========================================================================================
//�g�̏���������
//==========================================================================================
void CResultBGBack::Init()
{
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\Result000.png");
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//�g�̏���������
//==========================================================================================
void CResultBGBack::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�e�N�X�`���g�厞�ɐF���ߎ��l�ɂ���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	//�X�e���V���}�X�N�̐ݒ莞�ɖ���������Z�o�b�t�@�����Ƃɂ��ǂ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//�A���t�@�e�X�g�ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2D::Draw();

	//�e�N�X�`���g�厞�̐F����`���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

//==========================================================================================
//�g�̐�������
//==========================================================================================
CResultBGBack* CResultBGBack::Create()
{
	CResultBGBack* bg = new CResultBGBack;

	bg->SetPolygonParam({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f }, SCREEN_HEIGHT, SCREEN_WIDTH);
	bg->Init();

	return bg;
}

//==========================================================================================
//�g�̏���������
//==========================================================================================
void CResultReview::Init()
{
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\Result002.png");
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 2, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//�g�̏���������
//==========================================================================================
void CResultReview::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�e�N�X�`���g�厞�ɐF���ߎ��l�ɂ���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	//�X�e���V���}�X�N�̐ݒ莞�ɖ���������Z�o�b�t�@�����Ƃɂ��ǂ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//�A���t�@�e�X�g�ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2D::Draw();

	//�e�N�X�`���g�厞�̐F����`���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

//==========================================================================================
//�g�̐�������
//==========================================================================================
CResultReview* CResultReview::Create(bool bResult)
{
	CResultReview* bg = new CResultReview;

	bg->SetPolygonParam({ LogoPos.x,LogoPos.y,0.0f }, LogoSize.y, LogoSize.x);
	bg->Init();
	if (bResult)bg->SetAnim({ 1,1 });
	return bg;
}
//==========================================================================================
//�g�̏���������
//==========================================================================================
void CResultRank::Init()
{
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\Rank.png");
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 4, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//�g�̏���������
//==========================================================================================
void CResultRank::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�e�N�X�`���g�厞�ɐF���ߎ��l�ɂ���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	//�X�e���V���}�X�N�̐ݒ莞�ɖ���������Z�o�b�t�@�����Ƃɂ��ǂ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//�A���t�@�e�X�g�ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2D::Draw();

	//�e�N�X�`���g�厞�̐F����`���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

//==========================================================================================
//�g�̐�������
//==========================================================================================
CResultRank* CResultRank::Create(int nResult)
{
	CResultRank* bg = new CResultRank;

	bg->SetPolygonParam({ RankPos.x,RankPos.y,0.0f }, RankSize.y, RankSize.x);
	bg->Init();
	bg->SetAnim({ nResult * 0.25f,1 });
	return bg;
}
CR_Graound::CR_Graound(int nPriority) :CObjectX(nPriority)
{

}

CR_Graound::~CR_Graound()
{

}

//==========================================================================================
//����������
//==========================================================================================
void CR_Graound::Init()
{
	CObject::SetType(TYPE_3D_TITLEMESH);
	CObjectX::Init();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CR_Graound::Draw()
{
	CObjectX::Draw();
}

//==========================================================================================
//��������
//==========================================================================================
CR_Graound* CR_Graound::Create()
{
	CR_Graound* enemy = new CR_Graound;
	enemy->BindModel(GROUND_FILENAME.c_str());
	enemy->SetModelParam(R_FIELD_POS);
	enemy->Init();
	return enemy;
}
