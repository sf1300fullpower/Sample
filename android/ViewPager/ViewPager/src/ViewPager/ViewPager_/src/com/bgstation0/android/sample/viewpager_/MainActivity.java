package com.bgstation0.android.sample.viewpager_;

import android.app.Activity;
import android.os.Bundle;
import android.support.v4.view.ViewPager;
import android.view.Menu;
import android.view.MenuItem;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        // CustomPagerAdapter�𐶐�.
        CustomPagerAdapter adapter = new CustomPagerAdapter(this);	// CustomPagerAdapter�I�u�W�F�N�gadapter�𐶐�.
        PageItem item1 = new PageItem();	// PageItem�I�u�W�F�N�gitem1�𐶐�.
        item1.name = "Taro";	// "Taro"
        item1.num = 10;	// 10
        PageItem item2 = new PageItem();	// PageItem�I�u�W�F�N�gitem2�𐶐�.
        item2.name = "Jiro";	// "Jiro"
        item2.num = 20;	// 20
        PageItem item3 = new PageItem();	// PageItem�I�u�W�F�N�gitem3�𐶐�.
        item3.name = "Saburo";	// "Saburo"
        item3.num = 30;	// 30
        adapter.add(item1);	// adapter��item1��ǉ�.
        adapter.add(item2);	// adapter��item2��ǉ�.
        adapter.add(item3);	// adapter��item3��ǉ�.
        
        // ViewPager�ɔ��f.
        ViewPager viewpager = (ViewPager)this.findViewById(R.id.viewpager);	// viewpager���擾.
        viewpager.setAdapter(adapter);	// viewpager.setAdapter��adapter���Z�b�g.
        
    }
}