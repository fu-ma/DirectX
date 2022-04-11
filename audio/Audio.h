#pragma once

#include <xaudio2.h>
#include <fstream>
#include <assert.h>
#include <wrl.h>

#pragma comment(lib,"xaudio2.lib")

using namespace Microsoft::WRL;

//音声データ管理構造体
struct ChunkHeader
{
	char id[4];   //チャンクiD
	int32_t size; //チャンクサイズ
};

//RIFFヘッダチャンク
struct RiffHeader
{
	ChunkHeader chunk;
	char type[4];
};

//FMTチャンク
struct FormatChunk
{
	ChunkHeader  chunk; //"fmt "
	WAVEFORMATEX fmt;   //波形フォーマット
};

//音声データ
struct SoundData
{
	//波形フォーマット
	WAVEFORMATEX wfex;
	//バッファ先頭アドレス
	BYTE *pBuffer;
	//バッファサイズ
	unsigned int bufferSize;
	IXAudio2SourceVoice *sorceVoice;
	//バッファ
	XAUDIO2_BUFFER buf{};
};


class Audio
{
public:

	static ComPtr<IXAudio2>        xAudio2;
	static IXAudio2MasteringVoice *masterVoice;
public:
	Audio()
	{
		//xAudioエンジンのインスタンス作成
		HRESULT result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
		//マスターボイス作成
		result = xAudio2->CreateMasteringVoice(&masterVoice);
		//ボリューム初期化(50%)
	}

	//初期化
	static void Init();

	//サウンドデータの読み込み,音量,ループするか否か
	SoundData SoundLoadWave(const char *filename,bool loopFlag);
	//サウンドデータのアンロード
	void SoundUnload(SoundData *data);

	//再生
	void PlayLoadedSound(const SoundData &soundData,float volume);
	//停止
	void StopLoadedSound(SoundData &soundData);

};