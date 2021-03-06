package com.bgstation0.android.sample.framelayout_;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends Activity implements OnClickListener{	// View.OnClickListenerを実装.

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        // clearButtonを取得し, OnClickListenerとして自身をセット.
        Button clearButton = (Button)findViewById(R.id.clearbutton);	// R.id.clearbuttonを取得.
        clearButton.setOnClickListener(this);	// clearButton.setOnClickListenerでthis(自身)をセット.   
    
    }
    
    // View.OnClickListenerインタフェースのオーバーライドメソッドを実装.
    public void onClick(View v){	// onClickをオーバーライド.
    	// ボタンのidをごとに処理を振り分ける.
    	switch (v.getId()) {	// v.getIdでView(Button)のidを取得.
    		case R.id.clearbutton:	// R.id.clearbuttonの時.
    			EditText edittext1 = (EditText)findViewById(R.id.edittext1);	// R.id.edittext1を取得.
    			edittext1.setText("");	// edittext1.setTextで""をセット.
    			break;	// breakで抜ける.
    	}
    }
    
}