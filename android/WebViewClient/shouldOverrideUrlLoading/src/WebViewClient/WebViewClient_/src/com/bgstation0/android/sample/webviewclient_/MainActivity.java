package com.bgstation0.android.sample.webviewclient_;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends Activity implements OnClickListener{	// View.OnClickListenerを実装.

	// メンバフィールドの定義
	public WebView webView;	// WebViewオブジェクトwebView
	public CustomWebViewClient customWC;	// CustomWebViewClientオブジェクトcustomWC
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        // loadbuttonを取得し, OnClickListenerとして自身をセット.
        Button loadButton = (Button)findViewById(R.id.loadbutton);	// loadButtonを取得.
        loadButton.setOnClickListener(this);	// loadButton.setOnClickListenerでthisをセット.
        
        // WebViewの初期設定.
        webView = (WebView)findViewById(R.id.webview);	// webViewを取得.
        customWC = new CustomWebViewClient(this);	// CustomWebViewClientオブジェクトcustomWCを作成.
        webView.setWebViewClient(customWC);	// webView.setWebViewClientでcustomWCをセット.
    }
    
    // View.OnClickListenerインタフェースのオーバーライドメソッドを実装.
    public void onClick(View v){	// onClickをオーバーライド.
    	
    	// ボタンのidをごとに処理を振り分ける.
    	switch (v.getId()) {	// v.getIdでView(Button)のidを取得.
    		
    		case R.id.loadbutton:	// R.id.loadbuttonの時.
    			
    			// navigateButtonブロック
				{
					
					// urlBarのurlを取得.
    				EditText urlBar = (EditText)findViewById(R.id.urlbar);	// urlBarを取得.
    				String url = urlBar.getText().toString();	// urlBar.getText().toString()でurlを取得.
  
    				// webViewでurlのサイトを表示.
    				webView.loadUrl(url);	// webView.loadUrlでurlのサイトを表示.
    				
    				// 抜ける.
    				break;	// breakで抜ける.
    				
				}
				
    	}
    	
    }
    
}