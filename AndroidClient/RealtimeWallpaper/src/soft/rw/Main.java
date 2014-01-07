package soft.rw;

import soft.rw.service.RealtimeWallpaper;
import soft.rw.tool.l;
import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class Main extends Activity {
    private EditText et = null;
    private Button buttonStart = null, buttonStop = null;
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        et = (EditText)findViewById(R.id.input_main_host);
        
        ButtonListener bl = new ButtonListener();
        
        buttonStart = (Button)findViewById(R.id.button_main_start);
        buttonStart.setOnClickListener(bl);
        buttonStop = (Button)findViewById(R.id.button_main_stop);
        buttonStop.setOnClickListener(bl);
    }
    
    private class ButtonListener implements View.OnClickListener {
        @Override
        public void onClick(View v) {
            if (v instanceof Button) {
                Button button = (Button)v;
//                Intent intent = new Intent(getString(R.string.service_uri));
                Intent intent = new Intent(Main.this, RealtimeWallpaper.class);
                l.og(getString(R.string.service_uri));
                if (button.getId() == R.id.button_main_start) {
                    String host = et.getText().toString().trim();
                    intent.putExtra("HOST", host);
                    l.og("click start");
                    ComponentName cn = startService(intent);
                    l.og(cn, cn == null ? cn : cn.getClassName());
                    finish();
                }
                else if (button.getId() == R.id.button_main_stop) {
                    l.og("click stop");
                    boolean b = stopService(intent);
                    l.og(b);
                    finish();
                }
            }
        }
    }
}