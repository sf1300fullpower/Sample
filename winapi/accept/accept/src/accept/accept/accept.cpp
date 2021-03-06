// ヘッダファイルのインクルード
#include <tchar.h>		// TCHAR型
#include <stdio.h>		// 標準入出力
#include <winsock2.h>	// Windowsソケット
#include <windows.h>	// 標準WindowsAPI

// _tmain関数の定義
int _tmain(int argc, TCHAR *argv[]){	// main関数のTCHAR版.

	// 変数の宣言
	WSADATA wsaData;				// WinSockの初期化に必要なWSADATA構造体変数wsaData.
	int iRet;						// 初期化の結果iRet.
	int soc;						// ソケットファイルディスクリプタsoc.
	u_short ns_port;				// ポート番号のネットワークバイトオ―ダ値.
	struct sockaddr_in server_addr;	// アドレス情報を持つsockaddr_in構造体server_addr.
	int optval = 1;					// オプション値optvalを1に初期化.
	int acc;						// アクセプトソケットファイルディスクリプタacc.
	struct sockaddr_in client_addr;	// アクセプトしたクライアントのアドレス情報client_addr.
	int client_addr_len;			// client_addrのサイズclient_addr_len.

	// WinSockの初期化
	iRet = WSAStartup(MAKEWORD(2, 2), &wsaData);	// WSAStartupでWinSockの初期化.
	if (iRet){	// 0でない場合.

		// エラー処理.
		_tprintf(_T("Error!(iRet = %d.)\n"), iRet);	// 戻り値を出力.
		WSACleanup();	// WSACleanupで終了処理.
		return -1;	// -1を返して異常終了.

	}

	// 初期化成功メッセージ.
	_tprintf(_T("WSAStartup success!\n"));	// "WSAStartup success!"と出力.

	// ソケットの作成
	soc = socket(AF_INET, SOCK_STREAM, 0);	// socketでソケット作成.
	if (soc == -1){	// socが-1なら.

		// エラー処理
		_tprintf(_T("socket Error!\n"));	// "socket Error!"と出力.
		WSACleanup();	// WSACleanupで終了処理.
		return -1;	// -1を返して異常終了.

	}

	// socの値を出力.
	_tprintf(_T("soc = %d\n"), soc);	// socの値を出力.

	// ポート番号の変換.
	ns_port = htons(4000);	// htonsでポート番号をネットワークバイトオ―ダに変換.

	// ポート番号の出力.
	_tprintf(_T("port = %04x, ns_port = %04x\n"), 4000, ns_port);	// ポート番号とネットワークバイトオ―ダなポート番号を出力.

	// バインドするアドレス情報server_addrの設定.
	server_addr.sin_family = AF_INET;				// IPv4ファミリーAF_INET
	server_addr.sin_port = ns_port;					// ポート番号はns_port( == 4000).
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY;	// すべてのローカルインターフェイスにバインド.(UNIXのin_addrとちょっと違う.)

	// SO_REUSEADDRの有効化.
	if (setsockopt(soc, SOL_SOCKET, SO_REUSEADDR, (const char *)&optval, sizeof(optval)) == -1){	// setsockoptでSO_REUSEADDRを有効化.

		// エラー処理
		_tprintf(_T("setsockopt(SO_REUSEADDR) error!\n"));	// "setsockopt(SO_REUSEADDR) error!"と出力.
		closesocket(soc);	// closesocketでsocを閉じる.
		WSACleanup();	// WSACleanupで終了処理.
		return -1;	// -1を返して異常終了.

	}

	// 成功したら"setsockopt(SO_REUSEADDR) success."と出力.
	_tprintf(_T("setsockopt(SO_REUSEADDR) success.\n"));	// "setsockopt(SO_REUSEADDR) success."と出力.

	// socにserver_addrをバインド.
	if (bind(soc, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){	// 戻り値が-1の時はエラー.

		// エラー処理
		_tprintf(_T("bind Error!\n"));	// "bind Error!"と出力.
		closesocket(soc);	// closesocketでsocを閉じる.
		WSACleanup();	// WSACleanupで終了処理.
		return -1;	// -1を返して異常終了.

	}

	// 成功したら"bind Success.".
	_tprintf(_T("bind Success.\n"));	// "bind Success."と出力.

	// リッスン開始.
	if (listen(soc, 5) == -1){	// listenで5つまで接続をリッスンする.

		// エラー処理
		_tprintf(_T("listen Error!\n"));	// "listen Error!"と出力.
		closesocket(soc);	// closesocketでsocを閉じる.
		WSACleanup();	// WSACleanupで終了処理.
		return -1;	// -1を返して異常終了.

	}

	// 成功したら"listen success."と出力.
	_tprintf(_T("listen success.\n"));	// "listen success."と出力.

	// acceptに渡すclient_addr_lenのセット.
	client_addr_len = sizeof(client_addr);	// client_addr_lenにsizeof(client_addr)をセット.

	// アクセプト待ち.
	acc = accept(soc, (struct sockaddr *)&client_addr, &client_addr_len);	// acceptでアクセプトしたら, クライアントソケットをaccに格納.
	if (acc == -1){	// accが-1なら.

		// エラー処理
		_tprintf(_T("accept Error!\n"));	// "accept Error!"と出力.
		closesocket(soc);	// closesocketでsocを閉じる.
		WSACleanup();	// WSACleanupで終了処理.
		return -1;	// -1を返して異常終了.

	}

	// アクセプトソケットファイルディスクリプタの出力.
	_tprintf(_T("acc = %d\n"), acc);	// accを出力.

	// アクセプトソケットを閉じる.
	closesocket(acc);	// closesocketでaccを閉じる.

	// ソケットファイルディスクリプタを閉じる.
	closesocket(soc);	// closesocketでsocを閉じる.

	// WinSockの終了処理.
	WSACleanup();	// WSACleanupで終了処理.

	// プログラムの終了.
	return 0;

}