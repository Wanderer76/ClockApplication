package org.artcompany.clock;

import android.util.Log;
import android.os.Bundle;
import android.os.Vibrator;
import android.content.Context;
import android.media.AudioManager;
import android.widget.Toast;
import android.content.Intent;
import android.app.Activity;
import android.provider.Settings;
import android.database.Cursor;
import android.net.Uri;
import android.provider.MediaStore;
import android.provider.MediaStore.Audio.AudioColumns;
import android.os.Build;
import org.qtproject.qt5.android.bindings.QtActivity;

public class ClockApplication extends QtActivity {

    public static ClockApplication m_instance;

    public static Vibrator m_vibrator;
    static String TAG = "ClockApplication";
    public Notifier notifier;


    public ClockApplication() {
        m_instance = this;

    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
	notifier = new Notifier();
	notifier.createNotificationChannel(this);
	this.setVolumeControlStream(AudioManager.STREAM_MUSIC);
        Log.w(TAG, "onCreate() called!!!!!!!");
	super.onCreate(savedInstanceState);
    }

    @Override
    public void onStop() {
        Log.w(TAG, "onStop() called!");
        //NativeHelper.invokeVoidMethod(42);
        super.onStop();
    }

    @Override
    public void onDestroy() {
        Log.w(TAG, "onDestroy() called!");
        m_instance = null;
        super.onDestroy();
    }

    public static void invoke(int x) {
        final int z = x;
        m_instance.runOnUiThread(new Runnable() {
            public void run() {
                Toast.makeText(m_instance, "Invoke from C++ => Java: " + String.valueOf(z) + " (Button)",
                        Toast.LENGTH_SHORT).show();
            }
        });
        NativeHelper.invokeVoidMethod(x);
    }

    public static void vibrate(int x) {
        if (m_vibrator == null) {
            if (m_instance != null) {
                m_vibrator = (Vibrator) m_instance.getSystemService(Context.VIBRATOR_SERVICE);
                m_vibrator.vibrate(x);
            }
        } else {
            m_vibrator.vibrate(x);
        }
        Log.w(TAG, "Vibro: Java");
    }

    public String getPath(Uri uri) {
	String fullFilePath = UriUtils.getPathFromUri(this, uri);
	Log.w(TAG, "FILEPATH - " + fullFilePath);
        return "file://" + fullFilePath;
    }

}
