//===============================================================================
//
//  �t�B�[���h�Ǘ��N���X(field_manager.cpp)
//								����F���n�O��
// 
//===============================================================================
#include "manager.h"
#include "field_manager.h"
#include "floor_stone.h"

namespace
{
	//��ʐ؂�ւ�
	D3DXVECTOR3 DISSOLVE_POS = {
		SCREEN_WIDTH * 0.5f,
		-SCREEN_HEIGHT * 1.5f,
		0.0f
	};
	D3DXVECTOR3 DISSOLVE_SIZE = {
		SCREEN_WIDTH,
		SCREEN_HEIGHT * 3,
		0.0f
	};
	float DISSOLVE_SPEED = 50.0f;
}
std::shared_ptr<CField_Manager> CField_Manager::_instance = nullptr;

void CField_Manager::Init() {

	m_FieldDissolve = FieldDissolve::Create();
}
void CField_Manager::Uninit() {
	m_FieldDissolve->Uninit();
};
void CField_Manager::Update()
{
	if (!m_bActibateManager)return;

	//�f�B�]���u�������ɓ��B���Ă��邩�m�F
	if (!m_FieldDissolve->GetReach())return;


	for (auto& e : m_vecFieldObj)
	{
		e->Release();
	}

	m_vecFieldObj.clear();
	//���̃}�b�v�𐶐�(���͉��A��X�Ή������t�@�C���ǂݍ��݂Ȃǂɒu������)
	CMeshGround::Create({ 0.0f,0.0f,0.0f }, 0);
	m_FieldDissolve->RestartDissolve();
	m_bActibateManager = false;
}

//�O������I�u�W�F�N�g�Ĕz�u�X�^�[�g�p�̊֐�
void CField_Manager::SetField()
{
	m_FieldDissolve->StartDissolve();
	m_bActibateManager = true;
}

void FieldDissolve::Init()
{
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\fieldDissolve_nega.png");
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);
	CObject2D::Init();
}

void FieldDissolve::Update()
{
	if (m_bUse)
	{
		CObject2D::AddPos({ 0.0f,DISSOLVE_SPEED,0.0f });
	}
	CObject2D::Update();
	if ((CObject2D::GetPos().y >= (SCREEN_HEIGHT * 0.5f ) + DISSOLVE_SPEED && CObject2D::GetPos().y <= (SCREEN_HEIGHT * 0.5f) + (DISSOLVE_SPEED * 2)))
	{
		m_bReachHalf = true;
	}
	if (CObject2D::GetPos().y >= SCREEN_HEIGHT * 3)
	{
		m_bReachHalf = m_bDraw = m_bUse = false;
	}
}
void FieldDissolve::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	if (m_bDraw)
	{
		CObject2D::Draw();
	}
}

FieldDissolve* FieldDissolve::Create()
{
	FieldDissolve* pDisolve = new FieldDissolve;
	pDisolve->SetPolygonParam(DISSOLVE_POS, DISSOLVE_SIZE.y, DISSOLVE_SIZE.x);
	pDisolve->Init();
	return pDisolve;
}

//=================================================================================================================
//�f�B�]���u�̃X�^���_�[�h�E���X�^�[�g
void FieldDissolve::StartDissolve()
{
	m_bReachHalf = false;
	m_bDraw = true;
	m_bUse = true;
	CObject2D::SetPos(DISSOLVE_POS);
}
void FieldDissolve::RestartDissolve()
{
	m_bReachHalf = false;
	m_bDraw = true;
	CObject2D::SetPos({SCREEN_WIDTH*0.5f,SCREEN_HEIGHT*0.5f,0.0f});
}
//=================================================================================================================
