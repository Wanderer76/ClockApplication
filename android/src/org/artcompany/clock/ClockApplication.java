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
import android.app.NotificationManager;
import android.graphics.Color;
import android.app.NotificationChannel;
import android.net.Uri;

public class ClockApplication extends QtActivity {

    public static ClockApplication m_instance;   
    public static Vibrator m_vibrator;
    static String TAG = "ClockApplication";
    public Notifier notifier;
    private static NotificationChannel notificationChannel;
    private static NotificationManager m_notificationManager;
    private Intent forService;

    public ClockApplication() {
        m_instance = this;

    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
	if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
	    notificationChannel = new NotificationChannel("Timer", "Timer Notifier",  NotificationManager.IMPORTANCE_HIGH);
	    notificationChannel.enableVibration(true);
	    m_notificationManager = getSystemService(NotificationManager.class);
	    m_notificationManager.createNotificationChannel(notificationChannel);
	}

        forService = new Intent(ClockApplication.this,TimerService.class);
	Log.w(TAG, "onCreate() called!!!!!!!");
	notifier = new Notifier();
	startService();
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
	super.onDestroy();
        Log.w(TAG, "onDestroy() called!");
        m_instance = null;
	stopService(forService);
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

public static void Toast(){
     NativeHelper.invokeVoidMethod(50);
    }
    private void startService() {
	if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O){
	     startForegroundService(forService);
	} else {
	     startService(forService);
	}
     }
}
