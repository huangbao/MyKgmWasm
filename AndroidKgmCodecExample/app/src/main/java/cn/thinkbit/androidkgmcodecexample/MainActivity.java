package cn.thinkbit.androidkgmcodecexample;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.content.pm.PackageManager;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import cn.thinkbit.androidkgmcodecexample.databinding.ActivityMainBinding;

/**
 * adb push ../data/bb.kgm /sdcard/
 * <p>
 * adb pull /sdcard/tmp2.flacflac
 */
public class MainActivity extends AppCompatActivity {

    // Used to load the 'androidkgmcodecexample' library on application startup.
    static {
        System.loadLibrary("androidkgmcodecexample");
    }

    String inputPath = "/sdcard/bb.kgm";
    String outputPath = "/sdcard/tmp2.";
    TextView textview;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);

        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        textview = findViewById(R.id.textview);

        findViewById(R.id.btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                newThread();
            }
        });


        requestStoragePermission();
    }

    private void newThread() {

        if (this.textview.getText().toString().equals("解密中...")) {
            return;
        }

        new Thread(new Runnable() {

            @Override
            public void run() {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {

                        textview.setText("解密中...");
                    }
                });
                int ret = decodeKgm(inputPath, outputPath);
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {

                        textview.setText("解密成功");
                    }
                });
            }
        }).start();


    }

    private void requestStoragePermission() {
//        ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, REQUEST_STORAGE_PERMISSION);
    }

    public native String stringFromJNI();


    public native int decodeKgm(String inputPath, String outputPath);


}