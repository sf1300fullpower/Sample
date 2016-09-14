package com.bgstation0.android.sample.framelayout_;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends Activity implements OnClickListener{	// View.OnClickListener������.

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        // clearButton���擾��, OnClickListener�Ƃ��Ď��g���Z�b�g.
        Button clearButton = (Button)findViewById(R.id.clearbutton);	// R.id.clearbutton���擾.
        clearButton.setOnClickListener(this);	// clearButton.setOnClickListener��this(���g)���Z�b�g.   
    
    }
    
    // View.OnClickListener�C���^�t�F�[�X�̃I�[�o�[���C�h���\�b�h������.
    public void onClick(View v){	// onClick���I�[�o�[���C�h.
    	// �{�^����id�����Ƃɏ�����U�蕪����.
    	switch (v.getId()) {	// v.getId��View(Button)��id���擾.
    		case R.id.clearbutton:	// R.id.clearbutton�̎�.
    			EditText edittext1 = (EditText)findViewById(R.id.edittext1);	// R.id.edittext1���擾.
    			edittext1.setText("");	// edittext1.setText��""���Z�b�g.
    			break;	// break�Ŕ�����.
    	}
    }
    
}