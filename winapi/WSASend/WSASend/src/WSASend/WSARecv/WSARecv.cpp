// ヘッダファイルのインクルード
#include <tchar.h>		// TCHAR型
#include <stdio.h>		// 標準入出力
#include <string.h>		// 文字列処理
#include <winsock2.h>	// Windowsソケット
#include <windows.h>	// 標準WindowsAPI

// _tmain関数の定義
int _tmain(int argc, TCHAR *argv[]){	// main関数のTCHAR版.

	// 変数の宣言・初期化.
	WSADATA wsaData;					// WinSockの初期化に必要なWSADATA構造体変数wsaData.
	int iRet;							// 初期化の結果iRet.
	SOCKET soc;							// SOCKET型のソケットファイルディスクリプタsoc.
	u_short ns_port;					// ポート番号のネットワークバイトオ―ダ値.
	struct sockaddr_in saiServerAddr;	// アドレス情報を持つsockaddr_in構造体saiServerAddr.
	int optval = 1;						// オプション値optvalを1に初期化.
	SOCKET acc;							// SOCKET型のアクセプトソケットファイルディスクリプタacc.
	struct sockaddr_in saiClientAddr;	// アクセプトしたクライアントのアドレス情報saiClientAddr.
	int iClientAddrLen;					// saiClientAddrのサイズiClientAddrLen.
	char *client_ip_addr_str;			// クライアントのIPアドレス文字列client_ip_addr_str.
	u_short client_port;				// アクセプトしたクライアントのポート番号.
	WSABUF wsaBuf;						// WSABUF型変数wsaBuf.
	BYTE btBuf[256];					// BYTE型バッファbtBuf.
	DWORD dwRecvLen = 0;				// 受信したメッセージの長さdwRecvLen.
	int iExitFlag = 0;					// メッセージループを抜けるフラグiExitFlagを0に初期化.
	int iResult;						// WSARecvの結果を格納するiResult.
	DWORD dwFlags = 0;					// WSARecvに指定するフラグ.(必要.)

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
	soc = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, 0);	// WSASocketでソケット作成.
	if (soc == INVALID_SOCKET){	// socがINVALID_SOCKET( == -1)なら.

		// エラー処理
		_tprintf(_T("WSASocket Error!\n"));	// "WSASocket Error!"と出力.
		WSACleanup();	// WSACleanupで終了処理.
		return -1;	// -1を返して異常終了.

	}

	// socの値を出力.
	_tprintf(_T("soc = %lu\n"), soc);	// socの値を出力.

	// ポート番号の変換.
	WSAHtons(soc, 4000, &ns_port);	// WSAHtonsでポート番号をネットワークバイトオ―ダに変換.

	// ポート番号の出力.
	_tprintf(_T("port = %04x, ns_port = %04x\n"), 4000, ns_port);	// ポート番号とネットワークバイトオ―ダなポート番号を出力.

	// バインドするアドレス情報addrの設定.
	saiServerAddr.sin_family = AF_INET;					// IPv4ファミリーAF_INET
	saiServerAddr.sin_port = ns_port;					// ポート番号はns_port( == 4000).
	saiServerAddr.sin_addr.S_un.S_addr = INADDR_ANY;	// すべてのローカルインターフェイスにバインド.(UNIXのin_addrとちょっと違う.)

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

	// socにsaiServerAddrをバインド.
	if (bind(soc, (struct sockaddr *)&saiServerAddr, sizeof(saiServerAddr)) == -1){	// 戻り値が-1の時はエラー.

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

	// acceptに渡すiClientAddrLenのセット.
	iClientAddrLen = sizeof(saiClientAddr);	// iClientAddrLenにsizeof(saiClientAddr)でサイズをセット.

	// アクセプト待ち.
	acc = WSAAccept(soc, (struct sockaddr *)&saiClientAddr, &iClientAddrLen, NULL, NULL);	// WSAAcceptでアクセプトしたら, クライアントソケットをaccに格納.
	if (acc == INVALID_SOCKET){	// accがINVALID_SOCKET( == -1)なら.

		// エラー処理
		_tprintf(_T("accept Error!\n"));	// "accept Error!"と出力.
		closesocket(soc);	// closesocketでsocを閉じる.
		WSACleanup();	// WSACleanupで終了処理.
		return -1;	// -1を返して異常終了.

	}

	// アクセプトソケットファイルディスクリプタの出力.
	_tprintf(_T("acc = %d\n"), acc);	// accを出力.

	// クライアントのIPアドレス文字列とポート番号を出力.
	client_ip_addr_str = inet_ntoa(saiClientAddr.sin_addr);								// inet_ntoaでクライアントのsaiClientAddr.sin_addrをIPアドレス文字列に変換.
	WSANtohs(acc, saiClientAddr.sin_port, &client_port);								// WSANtohsでクライアントのポート番号をホストバイトオーダに変換.
	printf("accept!(IPAddress = %s, Port = %hu)\n", client_ip_addr_str, client_port);	// IPアドレスとポート番号を出力.

	// バッファをクリア.
	memset(btBuf, 0, sizeof(BYTE) * 256);	// memsetでbtBufを0で埋める.

	// wsaBufのセット.
	wsaBuf.buf = (char *)btBuf;	// wsaBuf.bufにbtBufをキャストしてセット.
	wsaBuf.len = sizeof(BYTE) * 256;	// wsaBuf.lenにsizeof(BYTE) * 256をセット.

	// メッセージ処理ループ
	while (!iExitFlag){	// iExitFlag == 1なら, このループから抜ける.

		// クライアントからメッセージ受信.
		iResult = WSARecv(acc, &wsaBuf, 1, &dwRecvLen, &dwFlags, NULL, NULL);	// WSARecvで受信.(第2引数はWSABUF型配列の先頭ポインタを渡すので, 第3引数はその配列の要素数だから1となる.また第5引数は必要.)
		if (iResult == SOCKET_ERROR){	// SOCKET_ERRORなら.

			// エラー処理.
			_tprintf(_T("WSARecv Error!\n"));	// "WSARecv Error!"と出力.
			break;	// 抜ける.

		}

		// 改行コードの除去.
		btBuf[dwRecvLen - 1] = 0x0;	// "\r\n"がbtBufに入ってしまうので, 最後の文字から"\n"を除去.
		btBuf[dwRecvLen - 2] = 0x0;	// "\r\n"がbtBufに入ってしまうので, 最後から2番目の文字から"\r"を除去.

		// "end"なら抜ける.
		if (strcmp((char *)btBuf, "end") == 0){	// strcmpで比較して"q"なら.

			// 抜ける.
			iExitFlag = 1;	// iExitFlagを1にする.

		}
		else{	// そうでないならbtBufの内容を出力.

			// btBufを出力.
			printf("%s\n", (char *)btBuf);	// printfでbtBufを出力.

		}

	}

	// アクセプトソケットを閉じる.
	closesocket(acc);	// closesocketでaccを閉じる.

	// ソケットファイルディスクリプタを閉じる.
	closesocket(soc);	// closesocketでsocを閉じる.

	// WinSockの終了処理.
	WSACleanup();	// WSACleanupで終了処理.

	// プログラムの終了.
	return 0;

}