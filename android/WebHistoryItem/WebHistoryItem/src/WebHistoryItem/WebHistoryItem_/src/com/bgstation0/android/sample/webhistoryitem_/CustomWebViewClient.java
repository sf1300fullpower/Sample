package com.bgstation0.android.sample.webhistoryitem_;

import android.app.Activity;
import android.content.Context;
import android.webkit.WebBackForwardList;
import android.webkit.WebHistoryItem;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Toast;

public class CustomWebViewClient extends WebViewClient {

	// メンバフィールドの定義
	private Context context;	// Context型context
	private EditText urlBar;	// EditText型urlBar
	
	// コンストラクタ
	public CustomWebViewClient(Context context){
		
		// メンバの初期化
		this.context = context;	// 引数のcontextをメンバのcontextにセット.
		Activity activity = (Activity)context;	// contextをActivity型のactivityにキャスト.
		urlBar = (EditText)activity.findViewById(R.id.urlbar);	// urlBarを取得.
		
	}
	
	// ロードするURLが変わった時.
	@Override
	public boolean shouldOverrideUrlLoading(WebView view, String url){
		
		// URLの更新
		urlBar.setText(url);	// urlBar.setTextでurlをセット.
		
		// falseを返すと, 必ずこのWebViewで処理するようになる.
		return false;	// falseを返す.
		
	}
	
	// ページのロードが終了した時.
	@Override
	public void onPageFinished (WebView view, String url){
		
		// WebBackForwardListの取得.
		WebBackForwardList bfList = view.copyBackForwardList();	// view.copyBackForwardListでバックフォワードリストを取得し, bfListに格納.
		WebHistoryItem hi = bfList.getCurrentItem();	// bfList.getCurrentItemで現在のヒストリアイテムを取得し, hiに格納.
		Toast.makeText(context, hi.getTitle(), Toast.LENGTH_LONG).show();	// hi.getTitleでタイトルを取得し, それをToastで表示.
		Toast.makeText(context, hi.getUrl(), Toast.LENGTH_LONG).show();	// hi.getUrlでURLを取得し, それをToastで表示.
		// ListItem配列で追加する要素を定義.
		int c = bfList.getSize();	// bfList.getSizeでサイズを取得し, cに格納.
        ListItem[] listitems = new ListItem[c];	// ListItem配列listitems(要素数3)
        for (int i = 0; i < c; i++){	// オブジェクト配列の作成と, インスタンスを生成・格納する作業は別なので注意!
        	listitems[i] = new ListItem();	// ListItemオブジェクトインスタンスを生成し, 各要素に格納.
        	listitems[i].url = bfList.getItemAtIndex(i).getUrl();	// bfList.getItemAtIndexで要素を取得, getUrlでURLを取得し, listitemsに格納.
        }
        // ListViewオブジェクトを取得.
        ListView listview = (ListView)((Activity)context).findViewById(R.id.listview);	// findViewByIdでlistviewを取得.
        // ListItemAdapterのadapterを生成して, listviewとadapterとlistitemsを紐付ける.
        ListItemAdapter adapter = new ListItemAdapter(context, R.layout.list_item, listitems);	// ListItemAdapterコンストラクタにListViewのアイテムテンプレートのlist_itemとリストデータのlistitemsをセット.
        listview.setAdapter(adapter);	// listview1.setAdapterにadapterをセットして, ListViewとAdapterを紐付ける.
        adapter.notifyDataSetChanged();	// adapter.notifyDataSetChangedでデータが変化したことを通知.
        
	}
	
}