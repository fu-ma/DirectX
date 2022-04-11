#pragma once
#include<Windows.h>

//WindowsAPI
class WinApp
{
public://定数
	//ウィンドウ横幅
	static const int window_width = 1280;
	static const int window_height = 720;

private://メンバ変数

	//ウィンドウハンドル
	HWND hwnd = nullptr;

	//ウィンドウクラスの設定
	WNDCLASSEX w{};

public://静的メンバ関数

	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public://Getter

	const HWND &GetHwnd() { return hwnd; }
	const HINSTANCE &GetHInstance() { return w.hInstance; }

public://メンバ変数

	//初期化
	void Innitialize();

	//メッセージの処理
	bool ProcessMessage();

	//終了
	void Finalize();
};

