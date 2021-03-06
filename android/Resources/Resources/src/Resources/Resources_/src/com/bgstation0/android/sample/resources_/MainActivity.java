package com.bgstation0.android.sample.resources_;

import android.app.Activity;
import android.content.res.Resources;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        // Resourcesからhello_worldを取得してToastで表示.
        Resources res = getResources();	// getResourcesでresを取得.
        String strHello = res.getString(R.string.hello_world);	// res.getStringでR.string.hello_worldに定義されている文字列を取得.
        Toast.makeText(this, strHello, Toast.LENGTH_LONG).show();	// strHelloをToastで表示.
        
    }
}
