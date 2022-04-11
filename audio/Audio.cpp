#include "Audio.h"

ComPtr<IXAudio2> Audio::xAudio2;
IXAudio2MasteringVoice *Audio::masterVoice;

void Audio::Init()
{
    //xAudioエンジンのインスタンス作成
    HRESULT result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
    //マスターボイス作成
    result = xAudio2->CreateMasteringVoice(&masterVoice);
}

SoundData Audio::SoundLoadWave(const char *filename,bool loopFlag)
{
    //ファイル入力ストリームのインスタンス
    std::ifstream file;
    //.wavファイルをバイナリモードで開く
    file.open(filename, std::ios_base::binary);
    //オープン失敗を検出
    assert(file.is_open());

    //RIFTヘッダー読み込み
    RiffHeader riff;
    file.read((char *)&riff, sizeof(riff));
    //ファイルがRIFTかチェック
    if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
        assert(0);
    }
    //タイプがWAVEかチェック
    if (strncmp(riff.type, "WAVE", 4) != 0) {
        assert(0);
    }

    //フォーマットチャンクの読み込み
    FormatChunk format = {};
    //チャンクヘッダーの確認
    file.read((char *)&format, sizeof(ChunkHeader));
    //JUNKチャンク検出時
    if (strncmp(format.chunk.id, "JUNK", 4) == 0)
    {
        //読み取りをジャンクチャンクの終わりまで進める
        file.seekg(format.chunk.size, std::ios_base::cur);
        //再読み込み
        file.read((char *)&format, sizeof(ChunkHeader));
    }
    if (strncmp(format.chunk.id, "fmt ", 4) != 0)
    {
        assert(0);
    }
    //チャンク本体の読み込み
    assert(format.chunk.size <= sizeof(format.fmt));
    file.read((char *)&format.fmt, format.chunk.size);

    //Dataチャンクの読み込み
    ChunkHeader data;
    file.read((char *)&data, sizeof(data));
    //JUNKチャンク検出時
    if (strncmp(data.id, "JUNK", 4) == 0)
    {
        //読み取りをジャンクチャンクの終わりまで進める
        file.seekg(data.size, std::ios_base::cur);
        //再読み込み
        file.read((char *)&data, sizeof(data));
    }
    if (strncmp(data.id, "data", 4) != 0)
    {
        assert(0);
    }
    //dataチャンクのデータ部分読み込み
    char *pBuffer = new char[data.size];
    file.read(pBuffer, data.size);
    //wavを閉じる
    file.close();

    //返却するデータ
    SoundData soundData = {};
    soundData.wfex = format.fmt;
    soundData.pBuffer = reinterpret_cast<BYTE *>(pBuffer);
    soundData.bufferSize = data.size;
    soundData.sorceVoice = nullptr;

    HRESULT result;
    //波形フォーマットをもとにソースの作成
    result = xAudio2->CreateSourceVoice(&soundData.sorceVoice, &soundData.wfex);
    assert(SUCCEEDED(result));

    //再生する波形データの設定
    soundData.buf.pAudioData = soundData.pBuffer;
    soundData.buf.AudioBytes = soundData.bufferSize;
    soundData.buf.Flags = XAUDIO2_END_OF_STREAM;
    if (loopFlag)
    {
        soundData.buf.LoopCount = XAUDIO2_LOOP_INFINITE;
    }

    return soundData;
}

void Audio::SoundUnload(SoundData *data)
{
    //メモリ解放
    delete[] data->pBuffer;

    data->pBuffer = 0;
    data->bufferSize = 0;
    data->wfex = {};
}

void Audio::PlayLoadedSound(const SoundData &soundData,float volume)
{
    HRESULT result;

    result = soundData.sorceVoice->SetVolume(volume);
    //波形データ再生
    result = soundData.sorceVoice->SubmitSourceBuffer(&soundData.buf);
    result = soundData.sorceVoice->Start();
}

void Audio::StopLoadedSound(SoundData &soundData)
{
    HRESULT result;

    //波形データ停止
    result = soundData.sorceVoice->Stop();
    result = soundData.sorceVoice->FlushSourceBuffers();
    result = soundData.sorceVoice->SubmitSourceBuffer(&soundData.buf);
}