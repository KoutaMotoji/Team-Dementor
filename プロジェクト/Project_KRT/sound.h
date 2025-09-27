//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Akira Tanaka
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"


class CSound
{
public:
	//�T�E���h�ꗗ
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,
		SOUND_LABEL_BGM_RESULT,
		SOUND_LABEL_SE_PARRY,
		SOUND_LABEL_SE_BOSS1_ATTACK,
		SOUND_LABEL_SE_BOSS1_SWING,
		SOUND_LABEL_SE_ENEMY_ATTACK,
		SOUND_LABEL_SE_PLAYER_ATTACK,
		SOUND_LABEL_MAX

	} SOUND_LABEL;
	CSound();								//�R���X�g���N�^
	~CSound();								//�f�X�g���N�^
	HRESULT Init(HWND hWnd);			//������
	void Uninit(void);					//�I��
	HRESULT PlaySound(SOUND_LABEL label);	//�T�E���h�Đ�
	void StopSound(SOUND_LABEL label);		//�T�E���h��~(���x���w��)
	void StopSound(void);					//�T�E���h��~(���ׂ�)

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
private:
	typedef struct
	{
		const char* pFilename;	// �t�@�C����
		int nCntLoop;			// ���[�v�J�E���g
		float fVolume;
	} SOUNDINFO;
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

	// �T�E���h�̏��
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{"data/SOUND/BGM/title.wav", -1,0.2f},	//�^�C�g�����BGM
		{"data/SOUND/BGM/result.wav", -1,0.2f},	//�`���[�g���A�����BGM
		{"data/SOUND/SE/super_parry.wav", 0,0.1f},		//�p���BSE
		{"data/SOUND/SE/boss1_attack00.wav", 0,0.1f},	//�{�X�P�ʏ�U��SE
		{"data/SOUND/SE/boss1_attack01.wav", 0,0.1f},		//�{�X�P��э��ݍU��SE
		{"data/SOUND/SE/enemy_attack00.wav", 0,0.1f},		//�G���G�U��SE
		{"data/SOUND/SE/player_attack00.wav", 0,0.1f},		//�v���C���[�U��SE

	};
};

#endif
