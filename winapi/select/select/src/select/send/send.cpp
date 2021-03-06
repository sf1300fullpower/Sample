// ヘッダファイルのインクルード
#include <tchar.h>		// TCHAR型
#include <stdio.h>		// 標準入出力
#include <winsock2.h>	// Windowsソケット
#include <windows.h>	// 標準WindowsAPI

// _tmain関数の定義
int _tmain(int argc, TCHAR *argv[]){	// main関数のTCHAR版.

	// 変数の宣言
	WSADATA wsaData;				// WinSockの初期化に必要なWSADATA構造体変数wsaData.
	char hostname[256];				// ホスト名hostname.
	int port;						// ポート番号port.
	u_short ns_port;				// ポート番号のネットワークバイトオ―ダ値.
	struct hostent *host;			// ホスト情報を格納するhostent構造体へのポインタhost.
	int iRet;						// 初期化の結果iRet.
	int soc;						// ソケットファイルディスクリプタsoc.
	struct sockaddr_in target_addr;	// 接続先サーバのの情報target_addr.
	char input_buf[256];			// 入力されたメッセージ文字列を格納するバッファinput_buf.(サーバに送信するメッセージ.)(長さ256)
	int input_len;					// 入力文字列の長さinput_len.(入力文字列末尾の改行を除去するときに使う.)
	int exit_flg = 0;				// メッセージ処理ループを抜けるかどうかのフラグexit_flg.
	char tmp = '\0';				// 改行文字読み飛ばし用変数tmpを'\0'に初期化.
	int send_len = 0;				// 送信したメッセージ文字列の長さsend_len.

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

	// ホスト名の入力.
	_tprintf(_T("hostname: "));	// hostnameの入力フォーム.
	scanf("%s", hostname);	// 入力されたホスト名をhostnameに格納.

	// ポート番号の入力.
	_tprintf(_T("port: "));		// portの入力フォーム.
	scanf("%d", &port);			// 入力されたポート番号をportに格納.

	// 改行読み飛ばし.
	scanf("%*c", tmp);	// この後の入力に影響を残さないため.

	// ホスト情報の取得.
	host = gethostbyname(hostname);	// gethostbynameで指定したホスト名のホスト情報を取得.
	if (host == NULL){	// hostがNULLなら.

		// エラー
		_tprintf(_T("gethostbyname Error!\n"));	// エラーメッセージ出力.
		WSACleanup();	// WSACleanupで終了処理.
		return -1;	// -1を返して終了.

	}

	// ホスト名から導き出されたIPアドレス情報.
	_tprintf(_T("host->h_addr_list[0][0] = %02x, host->h_addr_list[0][1] = %02x, host->h_addr_list[0][3] = %02x, host->h_addr_list[0][3] = %02x\n"), host->h_addr_list[0][0], host->h_addr_list[0][1], host->h_addr_list[0][2], host->h_addr_list[0][3]);	// host->h_addr_listの中身を出力.

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
	ns_port = htons(port);	// htonsでポート番号をネットワークバイトオ―ダに変換.

	// ポート番号の出力.
	_tprintf(_T("port = %04x, ns_port = %04x\n"), port, ns_port);	// ポート番号とネットワークバイトオ―ダなポート番号を出力.

	// 接続先サーバ情報target_addrの設定.
	target_addr.sin_family = AF_INET;									// IPv4ファミリーAF_INET
	target_addr.sin_port = ns_port;										// ポート番号はns_port.
	target_addr.sin_addr.S_un.S_addr = *(u_long *)host->h_addr_list[0];	// hostのIPアドレス情報をセット.(u_longとする.)

	// 接続
	if (connect(soc, (struct sockaddr *)&target_addr, sizeof(target_addr)) == -1){	// connectで接続先サーバに接続.(-1が返ったらエラー.)

		// エラー処理
		_tprintf(_T("connect Error!\n"));	// "connectt Error!"と出力.
		closesocket(soc);	// closesocketでsocを閉じる.
		WSACleanup();	// WSACleanupで終了処理.
		return -1;	// -1を返して異常終了.

	}

	// 成功したら"connect success."
	_tprintf(_T("connect success.\n"));	// _tprintfで"connect success."と出力.

	// メッセージ処理ループ
	while (!exit_flg){	// exit_flg == 1なら, このループから抜ける.

		// バッファをクリア.
		memset(input_buf, 0, sizeof(char) * 256);	// memsetでinput_bufを0で埋める.

		// 入力フォームの出力.
		fputs(">", stdout);	// fputsで入力フォーム">"を標準出力stdoutに出力.

		// 入力文字列をバッファに格納.
		fgets(input_buf, 256, stdin);	// fputsでinput_bufに標準入力stdinから入力された文字列を格納.

		// input_bufの改行("\n")を除去.
		input_len = strlen(input_buf);	// input_buf内の文字列の長さをstrlenで取得し, input_lenに格納.
		if (input_buf[input_len - 1] == '\n'){	// 末尾が'\n'なら.
			input_buf[input_len - 1] = '\0';	// '\0'を入れる.
			input_len = strlen(input_buf);		// 改めて除去後の長さを格納.
		}

		// "fin"が格納されていたら, メッセージ入力ループを抜ける.
		if (strcmp(input_buf, "fin") == 0){	// strcmpでinput_bufが"fin"なら.

			// 抜ける.
			exit_flg = 1;	// exit_flgを1とする.

			// "end\r\n"を送信.
			send(soc, "end\r\n", 5, 0);	// sendで送信.

		}
		else{	// そうでない場合は接続先サーバに送信.

			// 改行コード("\r\n")を付加.
			input_buf[input_len] = '\r';	// '\r'を付ける.
			input_buf[input_len + 1] = '\n';	// '\n'を付ける.

			// input_bufを送信.
			send_len = send(soc, input_buf, input_len + 2, 0);	// sendで送信.
			if (send_len <= 0){	// send_lenが0以下.

				// 抜ける.
				break;	// breakで抜ける.

			}

		}

	}

	// ソケットを閉じる.
	closesocket(soc);	// closesocketでsocを閉じる.

	// WinSockの終了処理.
	WSACleanup();	// WSACleanupで終了処理.

	// プログラムの終了.
	return 0;

}