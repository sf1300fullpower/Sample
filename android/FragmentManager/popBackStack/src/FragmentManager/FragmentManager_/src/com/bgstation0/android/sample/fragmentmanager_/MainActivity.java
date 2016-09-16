package com.bgstation0.android.sample.fragmentmanager_;

import android.app.Activity;
import android.app.Fragment;
import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;

public class MainActivity extends Activity {

	// メンバフィールドの定義
	FragmentManager fragmentManager = null;	// FragmentManagerオブジェクトfragmentManagerをnullに初期化.
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        // FragmentManagerの取得.
        fragmentManager = getFragmentManager();	// getFragmentManagerでfragmentManagerを取得.
        
    }
    
    // メニューが作成された時.
    @Override
    public boolean onCreateOptionsMenu(Menu menu){
    	
    	// メニューの作成
    	getMenuInflater().inflate(R.menu.main, menu);	// getMenuInflaterでMenuItemを取得し, そのままinflateで指定されたR.menu.mainを元にmenuを作成.
    	return true;	// trueを返す.
    	
    }
    
    // メニューが選択された時.
    @Override
    public boolean onOptionsItemSelected(MenuItem item){
    
    	// どのメニューが選択されたか.
    	switch (item.getItemId()){	// アイテムIDごとに振り分け.
    	
    		// Menu1
    		case R.id.menu_menu1:
    			
    			// Menu1ブロック
    			{
    				
    				// フラグメントの置換
    				FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();	// fragmentManager.beginTransactionでfragmentTransactionを取得.
    				Fragment fragment = new MainFragment();	// MainFragmentオブジェクトを作成し, Fragment型のfragmentに格納.
    				Bundle args = new Bundle();	// 置換するFragmentに渡すパラメータargsをBundleオブジェクトとして作成.
    				args.putString("text", "fragment1");	// キーは"text", 値は"fragment1".
    				args.putString("color", "red");	// キーは"color", 値は"red".
    				fragment.setArguments(args);	// fragment.setArgumentsでargsをセット.
    				fragmentTransaction.add(R.id.framelayout1, fragment, "tag1");	// fragmentTransaction.addでR.id.framelayout1にfragmentを追加.("tag1"をタグ付け.)
    				//fragmentTransaction.replace(R.id.framelayout1, fragment, "tag1");	// fragmentTransaction.replaceでR.id.framelayout1をfragmentに置換.("tag1"をタグ付け.)
    				fragmentTransaction.addToBackStack("tag1");	// fragmentTransaction.addToBackStackで置換前の状態をバックスタックに保存.(タグ"tag1"を付けておく.)
    				fragmentTransaction.commit();	// fragmentTransaction.commitで確定.
    				
    			}
    			
    			break;
    			
    		// Menu2
    		case R.id.menu_menu2:
    			
    			//　Menu2ブロック
    			{

    				// フラグメントの置換
    				FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();	// fragmentManager.beginTransactionでfragmentTransactionを取得.
    				Fragment fragment = new MainFragment();	// MainFragmentオブジェクトを作成し, Fragment型のfragmentに格納.
    				Bundle args = new Bundle();	// 置換するFragmentに渡すパラメータargsをBundleオブジェクトとして作成.
    				args.putString("text", "fragment2");	// キーは"text", 値は"fragment2".
    				args.putString("color", "green");	// キーは"color", 値は"green".
    				fragment.setArguments(args);	// fragment.setArgumentsでargsをセット.
    				fragmentTransaction.add(R.id.framelayout1, fragment, "tag2");	// fragmentTransaction.addでR.id.framelayout1にfragmentを追加.("tag2"をタグ付け.)
    				//fragmentTransaction.replace(R.id.framelayout1, fragment, "tag2");	// fragmentTransaction.replaceでR.id.framelayout1をfragmentに置換.("tag2"をタグ付け.)
    				fragmentTransaction.addToBackStack("tag2");	// fragmentTransaction.addToBackStackで置換前の状態をバックスタックに保存.(タグ"tag2"を付けておく.)
    				fragmentTransaction.commit();	// fragmentTransaction.commitで確定.

    			}
    					
    			break;
    	
    		// Menu3
    		case R.id.menu_menu3:
    			
    			// Menu3ブロック
    			{

    				// フラグメントの置換
    				FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();	// fragmentManager.beginTransactionでfragmentTransactionを取得.
    				Fragment fragment = new MainFragment();	// MainFragmentオブジェクトを作成し, Fragment型のfragmentに格納.
    				Bundle args = new Bundle();	// 置換するFragmentに渡すパラメータargsをBundleオブジェクトとして作成.
    				args.putString("text", "fragment3");	// キーは"text", 値は"fragment3".
    				args.putString("color", "blue");	// キーは"color", 値は"blue".
    				fragment.setArguments(args);	// fragment.setArgumentsでargsをセット.
    				fragmentTransaction.add(R.id.framelayout1, fragment, "tag3");	// fragmentTransaction.addでR.id.framelayout1にfragmentを追加.("tag3"をタグ付け.)
    				//fragmentTransaction.replace(R.id.framelayout1, fragment, "tag3");	// fragmentTransaction.replaceでR.id.framelayout1をfragmentに置換.("tag3"をタグ付け.)
    				fragmentTransaction.addToBackStack("tag3");	// fragmentTransaction.addToBackStackで置換前の状態をバックスタックに保存.(タグ"tag3"を付けておく.)
    				fragmentTransaction.commit();	// fragmentTransaction.commitで確定.

    			}
    			
    			break;
    			
    		// Menu4
    		case R.id.menu_menu4:
    			
    			// Menu4ブロック
    			{
    				
    				// トランザクション"tag1"に戻る.(fragment1を表示.)
    				fragmentManager.popBackStack("tag1", 0);	// fragmentManager.popBackStackで"tag1"のトランザクションに戻る.
    				
    			}
    			
    			break;
    			
    		// Menu5
    		case R.id.menu_menu5:
    			
    			// Menu5ブロック
    			{
    				
    				// トランザクション"tag2"に戻る.(fragment2を表示.)
    				fragmentManager.popBackStack("tag2", 0);	// fragmentManager.popBackStackで"tag2"のトランザクションに戻る.
    				
    			}
    			
    			break;
    			
    		// Menu6
    		case R.id.menu_menu6:
    			
    			// Menu6ブロック
    			{
    				
    				// トランザクション"tag3"に戻る.(fragment3を表示.)
    				fragmentManager.popBackStack("tag3", 0);	// fragmentManager.popBackStackで"tag3"のトランザクションに戻る.
    				
    			}
    			
    			break;
    			
    		// Menu7
    		case R.id.menu_menu7:
    			
    			// Menu7ブロック
    			{
    				
    				// 1つ前のトランザクションに戻る.
    				fragmentManager.popBackStack();	// fragmentManager.popBackStackで1つ前のトランザクションに戻る.
    				
    			}
    			
    			break;
    			
    	}
    	
    	return super.onOptionsItemSelected(item);	// 親クラス既定処理
    	
    }
    
}
