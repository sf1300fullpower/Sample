package com.bgstation0.android.sample.view.onclicklistener_;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        // button1�I�u�W�F�N�g���擾��, OnClickListener���Z�b�g.
        Button button1 = (Button)findViewById(R.id.button1);	// findViewById��R.id.button1��Button���擾��, button1�Ɋi�[.
        button1.setOnClickListener(new View.OnClickListener() {	// button1.setOnClickListener��View.OnClickListener�̓����N���X���`��, �C���X�^���X��n��.
			
        	// �N���b�N���ꂽ��.
			@Override
			public void onClick(View v) {	// onClick�̒�`(�I�[�o�[���C�h)
				// TODO Auto-generated method stub
				Button b1 = (Button)v;	// �C�x���g�������I�u�W�F�N�gv��View�ŕԂ����̂�Button�ɃL���X�g����b1�Ɋi�[.
				b1.setText("Clicked!");	// b1.setText�ŕ\������"Clicked!"�ɕύX.
			}
		});
    }
}