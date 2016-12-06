package com.bgstation0.android.sample.fragmenttabhost_;

import android.support.v4.app.FragmentActivity;
import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTabHost;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TabHost;

public class MainActivity extends FragmentActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        // fragmentManagerの取得.
        FragmentManager fragmentManager = getSupportFragmentManager();	// getSupportFragmentManagerでfragmentManagerを取得.
        
        // tabHostの取得.
        FragmentTabHost tabHost = (FragmentTabHost)findViewById(android.R.id.tabhost);	// findViewByIdでtabHostを取得.
        
        // tabHostの準備.
        tabHost.setup(this, fragmentManager, R.id.content);	// tabHost.setupで準備(this, fragmentManagerとフラグメントの挿入先R.id.contentを渡す.)

        // tab1の追加.
        TabHost.TabSpec tabSpec1 = tabHost.newTabSpec("tab1");	// tabSpec1"tab1"の生成.
        tabSpec1.setIndicator("タブ1");	// tabSpec1.setIndicatorで表示名"タブ1"をセット.
        Bundle bundle1 = new Bundle();	// bundle1生成.
        bundle1.putString("name", "tab1"); 	// bundle1.putStringで"name", "tab1"の組で登録.
        tabHost.addTab(tabSpec1, TabFragment.class, bundle1);	// tabHost.addTabでtabSpec1, TabFragment.class, bundle1を追加.
        
        // tab2の追加.
        TabHost.TabSpec tabSpec2 = tabHost.newTabSpec("tab2");	// tabSpec"tab2"の生成.
        tabSpec2.setIndicator("タブ2");	// tabSpec2.setIndicatorで表示名"タブ2"をセット.
        Bundle bundle2 = new Bundle();	// bundle2生成.
        bundle2.putString("name", "tab2"); 	// bundle2.putStringで"name", "tab2"の組で登録.
        tabHost.addTab(tabSpec2, TabFragment.class, bundle2);	// tabHost.addTabでtabSpec2, TabFragment.class, bundle2を追加.
        
    }
}
