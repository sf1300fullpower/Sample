// ヘッダファイルのインクルード
#include <windows.h>	// 標準WindowsAPI
#include <tchar.h>		// TCHAR型
#include <stdio.h>		// 標準入出力

// スレッドの引数として渡す構造体THREAD_PARAMの定義.
typedef struct{
	int m_iNo;					// スレッド番号
	TCHAR m_tszMessage[32];		// スレッドが出力するメッセージ.
	CRITICAL_SECTION *m_pCS;	// クリティカルセクション構造体ポインタm_pCS.
}THREAD_PARAM;	// これでTHREAD_PARAM型の完成.

// ThreadProc関数の定義
DWORD WINAPI ThreadProc(LPVOID lpParameter){

	// 変数の宣言
	int i;	// ループ用変数i
	THREAD_PARAM *pTP;	// THREAD_PARAM型ポインタpTP.

	// 引数lpParameterをTHREAD_PARAM型のポインタにキャスト.
	pTP = (THREAD_PARAM *)lpParameter;	// lpParameterをTHREAD_ARG型のポインタにキャストして, pTPに格納.

	// クリティカルセクションの開始.
	EnterCriticalSection(pTP->m_pCS);	// EnterCriticalSectionでここから先はクリティカルセクションオブジェクトが取得できるまで待機.

	// 1から5までを出力.
	for (i = 1; i <= 5; i++){	// 1から5まで5回繰り返す.

		// i, pTP->m_iNo, pTP->m_tszMessageを出力.
		_tprintf(_T("i = %d, m_iNo = %d, m_tszMessage = %s\n"), i, pTP->m_iNo, pTP->m_tszMessage);	// _tprintfでi, pTP->m_iNo, pTP->m_tszMessageの値を出力.
		Sleep(1000);	// Sleepで1秒休止.

	}

	// クリティカルセクションの終了.
	LeaveCriticalSection(pTP->m_pCS);	// LeaveCriticalSectionでここでクリティカルセクションオブジェクトを解放.

	// スレッドの終了
	ExitThread((DWORD)pTP->m_iNo);	// ExitThreadにpTP->m_iNoを(DWORD)にキャストしたものを渡してスレッドを終了する.

}

// _tmain関数の定義
int _tmain(int argc, TCHAR *argv[]){	// main関数のTCHAR版.

	// 配列の宣言
	HANDLE hThread[5];		// HANDLE型スレッドハンドル配列hThread(要素数5)
	DWORD dwThreadId[5];	// DWORD型スレッドID配列dwThreadId(要素数5)
	THREAD_PARAM tp[5];		// 引数として渡すTHREAD_PARAM型配列tp.(要素数5)
	int i;					// ループ用変数i.
	DWORD dwExitCode[5];	// DWORD型終了コード配列dwExitCode(要素数5)
	CRITICAL_SECTION cs;	// クリティカルセクション構造体変数cs.

	// クリティカルセクション構造体の初期化.
	InitializeCriticalSection(&cs);	// InitializeCriticalSectionでcsを初期化.

	// スレッドの一斉開始
	tp[0].m_iNo = 0;	// m_iNo = 0
	_tcscpy(tp[0].m_tszMessage, _T("No.0"));	// m_tszMessage = "No.0"
	tp[0].m_pCS = &cs;	// csのアドレスをm_pCSにセット.
	hThread[0] = CreateThread(NULL, 0, ThreadProc, &tp[0], 0, &dwThreadId[0]);	// CreateThreadでスレッド生成及び開始.(引数にtp[0]を渡している.)
	tp[1].m_iNo = 1;	// m_iNo = 1
	_tcscpy(tp[1].m_tszMessage, _T("No.1"));	// m_tszMessage = "No.1"
	tp[1].m_pCS = &cs;	// csのアドレスをm_pCSにセット.
	hThread[1] = CreateThread(NULL, 0, ThreadProc, &tp[1], 0, &dwThreadId[1]);	// CreateThreadでスレッド生成及び開始.(引数にtp[1]を渡している.)
	tp[2].m_iNo = 2;	// m_iNo = 2
	_tcscpy(tp[2].m_tszMessage, _T("No.2"));	// m_tszMessage = "No.2"
	tp[2].m_pCS = &cs;	// csのアドレスをm_pCSにセット.
	hThread[2] = CreateThread(NULL, 0, ThreadProc, &tp[2], 0, &dwThreadId[2]);	// CreateThreadでスレッド生成及び開始.(引数にtp[2]を渡している.)
	tp[3].m_iNo = 3;	// m_iNo = 3
	_tcscpy(tp[3].m_tszMessage, _T("No.3"));	// m_tszMessage = "No.3"
	tp[3].m_pCS = &cs;	// csのアドレスをm_pCSにセット.
	hThread[3] = CreateThread(NULL, 0, ThreadProc, &tp[3], 0, &dwThreadId[3]);	// CreateThreadでスレッド生成及び開始.(引数にtp[3]を渡している.)
	tp[4].m_iNo = 4;	// m_iNo = 4
	_tcscpy(tp[4].m_tszMessage, _T("No.4"));	// m_tszMessage = "No.4"
	tp[4].m_pCS = &cs;	// csのアドレスをm_pCSにセット.
	hThread[4] = CreateThread(NULL, 0, ThreadProc, &tp[4], 0, &dwThreadId[4]);	// CreateThreadでスレッド生成及び開始.(引数にtp[4]を渡している.)

	// 全てのスレッドがシグナル状態になるまで待機.
	WaitForMultipleObjects(5, hThread, TRUE, INFINITE);	// WaitForMultipleObjectsでスレッドハンドル配列hThreadのすべてのスレッドがシグナル状態になるまで待機.

	// 終了コード取得.
	for (i = 0; i < 5; i++){	// 5回繰り返す.

		// i番目スレッドの終了コードを取得.
		GetExitCodeThread(hThread[i], &dwExitCode[i]);	// GetExitCodeThreadで各スレッドの終了コードを取得.
		_tprintf(_T("dwExitCode[%d] = %lu\n"), i, dwExitCode[i]);	// dwExitCode[i]の値を出力.
		if (hThread[i] != NULL){	// hThread[i]がNULLでない.
			CloseHandle(hThread[i]);	// CloseHandleでhThread[i]を閉じる.
		}

	}

	// クリティカルセクション構造体の削除.
	DeleteCriticalSection(&cs);	// DeleteCriticalSectionでcsを削除.

	// プログラムの終了
	return 0;

}