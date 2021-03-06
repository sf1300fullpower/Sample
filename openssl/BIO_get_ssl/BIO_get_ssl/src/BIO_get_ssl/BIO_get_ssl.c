/* ヘッダファイルのインクルード */
#include <openssl/bio.h> /* BIO */
#include <openssl/ssl.h> /* SSL */
#include <openssl/err.h> /* エラー */

/* main関数の定義 */
int main(void){

  /* 変数の初期化 */
  SSL_CTX *ctx = NULL; /* SSL_CTX構造体へのポインタctxをNULLに初期化. */
  BIO *bio = NULL; /* BIO構造体へのポインタbioをNULLに初期化. */
  SSL *ssl = NULL; /* SSL接続情報を持つSSL構造体へのポインタsslをNULLに初期化. */

  /* SSLライブラリの初期化. */
  SSL_library_init(); /* SSL_library_initでSSLライブラリの初期化をする. */

  /* SSLコンテキストの作成. */
  ctx = SSL_CTX_new(SSLv23_client_method()); /* SSL_CTX_newでSSLコンテキストを作成し, SSL_CTX型ポインタとしてctxに格納. +/

  /* ctxの指すアドレスを出力. */
  printf("ctx = %08x\n", ctx); /* printfでctxの指すアドレスを出力. */

  /* 信頼できる証明書ストアのロード. */
  if (!SSL_CTX_load_verify_locations(ctx, "/etc/pki/tls/cert.pem", NULL)){ /* SSL_CTX_load_verify_locationsにctxとpemのパスを渡し, 失敗ならエラーメッセージ. */

    /* エラーメッセージ */
    printf("SSL_CTX_load_verify_locations error!\n"); /* "SSL_CTX_load_verify_locations error!"と出力. */
    SSL_CTX_free(ctx); /* SSL_CTX_freeでctxを解放. */
    return -1; /* -1を返して終了. */

  }

  /* ロード成功 */
  printf("SSL_CTX_load_verify_locations success!\n"); /* "SSL_CTX_load_verify_locations success!"と出力. */

  /* BIOのSSLコネクション作成. */
  bio = BIO_new_ssl_connect(ctx); /* BIO_new_ssl_connectにctxを渡してSSLコネクション作成. */
  if (bio == NULL){ /* bioがNULLなら. */

    /* エラーメッセージ */
    printf("BIO_new_ssl_connect error!\n"); /* "BIO_new_ssl_connect error!\n"と出力. */
    SSL_CTX_free(ctx); /* SSL_CTX_freeでctxを解放. */
    return -2; /* -2を返して終了. */

  }

  /* 作成成功 */
  printf("BIO_new_ssl_connect success! bio = %08x\n", bio); /* bioの値を出力. */

  /* SSL接続情報の取得. */
  BIO_get_ssl(bio, &ssl); /* BIO_get_sslでbioからsslを取得. */
  printf("ssl = %08x\n", ssl); /* sslの値を出力. */ 

  /* BIOのクローズと解放. */
  BIO_free_all(bio); /* BIO_free_allでbioをクローズ及び解放. */

  /* SSLコンテキストの解放. */
  SSL_CTX_free(ctx); /* SSL_CTX_freeでctxを解放. */

  /* プログラムの終了 */
  return 0; /* 0を返して終了. */

}
