//=============================================================================
//
// サウンド処理 [sound.h]
// Author : Akira Tanaka
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"


class CSound
{
public:
	//サウンド一覧
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
	CSound();								//コンストラクタ
	~CSound();								//デストラクタ
	HRESULT Init(HWND hWnd);			//初期化
	void Uninit(void);					//終了
	HRESULT PlaySound(SOUND_LABEL label);	//サウンド再生
	void StopSound(SOUND_LABEL label);		//サウンド停止(ラベル指定)
	void StopSound(void);					//サウンド停止(すべて)

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
private:
	typedef struct
	{
		const char* pFilename;	// ファイル名
		int nCntLoop;			// ループカウント
		float fVolume;
	} SOUNDINFO;
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

	// サウンドの情報
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{"data/SOUND/BGM/title.wav", -1,0.2f},	//タイトル画面BGM
		{"data/SOUND/BGM/result.wav", -1,0.2f},	//チュートリアル画面BGM
		{"data/SOUND/SE/super_parry.wav", 0,0.1f},		//パリィSE
		{"data/SOUND/SE/boss1_attack00.wav", 0,0.1f},	//ボス１通常攻撃SE
		{"data/SOUND/SE/boss1_attack01.wav", 0,0.1f},		//ボス１飛び込み攻撃SE
		{"data/SOUND/SE/enemy_attack00.wav", 0,0.1f},		//雑魚敵攻撃SE
		{"data/SOUND/SE/player_attack00.wav", 0,0.1f},		//プレイヤー攻撃SE

	};
};

#endif
