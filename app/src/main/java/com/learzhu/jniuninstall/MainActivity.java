package com.learzhu.jniuninstall;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.TextView;

/**
 * Android Studio 3.0 JNI的实现
 * https://blog.csdn.net/ziyoutiankoong/article/details/79696279
 */
public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
//        new JNITest().uninstall("com.learzhu.jniuninstall", 1);
        final TextView textView = findViewById(R.id.tv);
        textView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                textView.setText("结果：" + new JNITest().getString() + "\n" +
                        new JNITest().testHello());
            }
        });
        //监听卸载事件
        listening();
    }

    private void listening() {
        UninstallObserver.startWork("/data/data/" + getPackageName(), "https://www.baidu.com", android.os.Build.VERSION.SDK_INT);
    }
}
