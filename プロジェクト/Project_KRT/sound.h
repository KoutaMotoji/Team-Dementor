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
		SOUND_LABEL_BGM_TUTORIAL,
		SOUND_LABEL_BGM_GAME,
		SOUND_LABEL_BGM_RESULT,
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
	} SOUNDINFO;
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

	// サウンドの情報
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{"data/SOUND/BGM_title.wav", -1},	//タイトル画面BGM
		{"data/SOUND/BGM_tutorial.wav", -1},	//チュートリアル画面BGM
		{"data/SOUND/BGM_game.wav", -1},		//ゲーム画面BGM
		{"data/SOUND/BGM_result.wav", -1},	//リザルト画面BGM
	};
};

#endif
