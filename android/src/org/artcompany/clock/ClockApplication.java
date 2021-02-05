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
import java.util.ArrayList;

import org.qtproject.qt5.android.bindings.QtActivity;


public class ClockApplication extends QtActivity {

    public static ClockApplication m_instance;
    public static Vibrator m_vibrator;
    private static String TAG = "ClockApplication";
    public Notifier notifier;
    private static NotificationChannel notificationChannel;
    private static NotificationChannel timerChannel;
    public static NotificationManager m_notificationManager;

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
    }

    @Override
    public void onStop() {
	super.onStop();
    }

    @Override
    public void onDestroy() {
	super.onDestroy();
	unregisterReceiver(broadcastReceiver);
	stopService();
	m_instance = null;
    }

    public static void invoke(int x) {
        final int z = x;
	    //startService();
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
    }

    public String getPath(Uri uri) {
	String fullFilePath = UriUtils.getPathFromUri(this, uri);
        return "file://" + fullFilePath;
    }


    public void startService() {
	Intent in = new Intent(getApplicationContext(),TimerService.class);
	if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O){
	     startForegroundService(in);
	}
        else
	    startService(in);
     }

  public void stopService() {
      Intent in = new Intent(getApplicationContext(),TimerService.class);
      stopService(in);
      }
     private void registerNotificationChannel() {
	 if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
	         notificationChannel = new NotificationChannel("Service", "Service Notifier",  NotificationManager.IMPORTANCE_HIGH);
		 notificationChannel.enableVibration(true);

		 timerChannel = new NotificationChannel("Timer", "Timer Service",  NotificationManager.IMPORTANCE_HIGH);
		 timerChannel.enableVibration(true);

		 ArrayList<NotificationChannel> notificationChannels = new ArrayList<>();
		 notificationChannels.add(notificationChannel);
		 notificationChannels.add(timerChannel);

		 m_notificationManager = getSystemService(NotificationManager.class);
		 m_notificationManager.createNotificationChannels(notificationChannels);
	}
    }
}
