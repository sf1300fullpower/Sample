package com.bgstation0.android.sample.viewpager_;

import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.content.Context;
import android.support.v4.view.PagerAdapter;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class CustomPagerAdapter extends PagerAdapter {

	// �����o�t�B�[���h�̒�`.
	private Context context = null;	// Context�^context��null�ŏ�����.
	private List<PageItem> list = null;	// List<PageItem>�C���X�^���Xlist��null�ŏ�����.
	private LayoutInflater inflater = null;	// LayoutInflater�^inflater��null�ŏ�����.
	
	// �R���X�g���N�^
	public CustomPagerAdapter(Context context){
		
		// �����o�ɃZ�b�g.
		this.context = context;	// ����context�������othis.context�ɃZ�b�g.
		this.list = new ArrayList<PageItem>();	// ArrayList�I�u�W�F�N�g��list�ɃZ�b�g.
		this.inflater = (LayoutInflater)context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);	// inflater����.
		
	}
	
	// �ǉ�.
	public void add(PageItem item){
		list.add(item);	// list.add��item��ǉ�.
	}
	
	@Override
	public Object instantiateItem(ViewGroup container, int position){
		
		// item���擾..
		PageItem item = list.get(position);	// this.get(position)��item���擾.
		
		// View�̐���.
		View view = inflater.inflate(R.layout.page_layout, container, false);	// inflater.inflate��view�𐶐�.
		TextView nametv = (TextView)view.findViewById(R.id.name_textview);	// nametv���擾.
		nametv.setText(item.name);	// nametv.setText��item.name���Z�b�g.
		TextView numtv = (TextView)view.findViewById(R.id.num_textview);	// numtv���擾.
		numtv.setText(String.valueOf(item.num));	// numtv.setText��item.num���Z�b�g.
		
		// �ǉ�.
		container.addView(view);	// container.addView��view��ǉ�.
		return view;	// view��Ԃ�.
		
	}
	
	@Override
    public void destroyItem(ViewGroup container, int position, Object object) {
        // container����object�폜.
        container.removeView((View) object);	// container.removeView��object�폜.
    }
	
	@Override
	public int getCount() {
		// TODO Auto-generated method stub
		return list.size();	// list.size()��Ԃ�.
	}

	@Override
	public boolean isViewFromObject(View arg0, Object arg1) {
		// TODO Auto-generated method stub
		return arg0 == (View) arg1;	// arg1��view���ǂ�������.
	}

}