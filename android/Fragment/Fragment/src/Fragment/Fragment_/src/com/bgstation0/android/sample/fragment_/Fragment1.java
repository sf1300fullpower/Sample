package com.bgstation0.android.sample.fragment_;

import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

// Fragment1クラスの定義.
public class Fragment1 extends Fragment{
	
	// フラグメントのビュー生成時.
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState){
		// Fragment1のリソースをベースにレイアウト作成.
		return inflater.inflate(R.layout.fragment1_main, null);	// inflater.inflaceでR.layout.fragment1_mainをベースにレイアウト作成.
	}
}