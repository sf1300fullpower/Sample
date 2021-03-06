package com.bgstation0.android.sample.arrayadapter_;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        // ListItem配列で追加する要素を定義.
        ListItem[] listitems = new ListItem[3];	// ListItem配列listitems(要素数3)
        for (int i = 0; i < 3; i++){	// オブジェクト配列の作成と, インスタンスを生成・格納する作業は別なので注意!
        	listitems[i] = new ListItem();	// ListItemオブジェクトインスタンスを生成し, 各要素に格納.
        }
        listitems[0].name = "Taro";
        listitems[0].age = 20;
        listitems[0].address = "Tokyo";
        listitems[1].name = "Jiro";
        listitems[1].age = 18;
        listitems[1].address = "Osaka";
        listitems[2].name = "Saburo";
        listitems[2].age = 16;
        listitems[2].address = "Nagoya";
        
        // ListViewオブジェクトを取得.
        ListView listview1 = (ListView)findViewById(R.id.listview1);	// findViewByIdでlistview1を取得.
        
        // ListItemAdapterのadapterを生成して, listview1とadapterとlistitemsを紐付ける.
        ListItemAdapter adapter = new ListItemAdapter(this, R.layout.list_item, listitems);	// ListItemAdapterコンストラクタにListViewのアイテムテンプレートのlist_itemとリストデータのlistitemsをセット.
        listview1.setAdapter(adapter);	// listview1.setAdapterにadapterをセットして, ListViewとAdapterを紐付ける.
    }
}
