package org.artcompany.clock;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Vibrator;
import android.util.Log;
import android.widget.Toast;
import android.content.BroadcastReceiver;
import android.content.IntentFilter;

import org.qtproject.qt5.android.bindings.QtActivity;


public class ClockApplication extends QtActivity {

    public static ClockApplication m_instance;
    public static Vibrator m_vibrator;
    private static String TAG = "ClockApplication";
    public Notifier notifier;
    private static NotificationChannel notificationChannel;
    private static NotificationChannel timerChannel;
    private static NotificationManager m_notificationManager;
    public Intent forService;

    public final static String BROADCAST_ACTION = "GET_BROADCAST_VALUE";

    AlarmBroadcastReceiver broadcastReceiver = new AlarmBroadcastReceiver();


    public ClockApplication() {
        m_instance = this;

    }


    @Override
    protected void onStart() {
	super.onStart();
	registerReceiver(broadcastReceiver,new IntentFilter(BROADCAST_ACTION));
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
	super.onCreate(savedInstanceState);
	registerNotificationChannel();
	notifier = new Notifier();
	forService = new Intent(ClockApplication.this,TimerService.class);
	Log.w(TAG, "onCreate() called!!!!!!!");
	startService();
    }

    @Override
    public void onStop() {
        Log.w(TAG, "onStop() called!");
	super.onStop();
	// NativeHelper.invokeVoidMethod(50);
    }

    @Override
    public void onDestroy() {
	super.onDestroy();
	unregisterReceiver(broadcastReceiver);
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


    private void startService() {
	if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O){
	     startForegroundService(forService);
	} else {
	     startService(forService);
	}
     }


     private void registerNotificationChannel() {
	 if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
	         notificationChannel = new NotificationChannel("Service", "Service Notifier",  NotificationManager.IMPORTANCE_HIGH);
		 notificationChannel.enableVibration(true);

		 timerChannel = new NotificationChannel("Timer", "Timer Service",  NotificationManager.IMPORTANCE_HIGH);
		 timerChannel.enableVibration(true);

		 m_notificationManager = getSystemService(NotificationManager.class);
		 m_notificationManager.createNotificationChannel(notificationChannel);
		 m_notificationManager.createNotificationChannel(timerChannel);
		}
    }
}
