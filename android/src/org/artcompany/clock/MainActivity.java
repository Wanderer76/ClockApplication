package org.artcompany.clock;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Vibrator;
import org.qtproject.qt5.android.bindings.QtActivity;
import java.util.ArrayList;


public class MainActivity extends QtActivity {

	public static MainActivity m_instance;
	public static Vibrator m_vibrator;
	private static String TAG = "ClockApplication";
	//private static NotificationChannel notificationChannel;
	private static NotificationChannel timerChannel;
	public static NotificationManager m_notificationManager;

	public final static String BROADCAST_ACTION = "GET_BROADCAST_VALUE";
	public final static String PARAM_TIMER_TIME = "PARAM_TIMER_TIME";
	public static int timerTime = 0;

	AlarmBroadcastReceiver broadcastReceiver = new AlarmBroadcastReceiver();


	public MainActivity() {
		m_instance = this;
	}

	@Override
	protected void onStart() {
		super.onStart();
		registerReceiver(broadcastReceiver, new IntentFilter(BROADCAST_ACTION));
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		registerNotificationChannel();
	}

	@Override
	public void onStop() {
		super.onStop();
	}

	@Override
	public void onDestroy() {
		unregisterReceiver(broadcastReceiver);
		stopAlarmService();
		stopTimerService();
		m_instance = null;
		super.onDestroy();
	}

	public static void invoke(int x) {
		final int z = x;
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

	private void registerNotificationChannel() {
		if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
		        //notificationChannel = new NotificationChannel("Service", "Service Notifier", NotificationManager.IMPORTANCE_HIGH);
			//notificationChannel.enableVibration(true);

			timerChannel = new NotificationChannel("Timer", "Timer Service", NotificationManager.IMPORTANCE_HIGH);
			timerChannel.enableVibration(true);

			ArrayList<NotificationChannel> notificationChannels = new ArrayList<>();
			//notificationChannels.add(notificationChannel);
			notificationChannels.add(timerChannel);

			m_notificationManager = getSystemService(NotificationManager.class);
			m_notificationManager.createNotificationChannels(notificationChannels);
		}
	}

	public void startAlarmService() {
		Intent in = new Intent(getApplicationContext(), AlarmService.class);
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
			startForegroundService(in);
		} else
			startService(in);
	}

	public void stopAlarmService() {
		Intent in = new Intent(getApplicationContext(), AlarmService.class);
		stopService(in);
	}

        public void startTimerService(int time) {
	        if(time !=0)
		        timerTime = time;
		Intent timerIntent = new Intent(getApplicationContext(), TimerService.class);
		timerIntent.putExtra("timer_time", timerTime);
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
			startForegroundService(timerIntent);
		} else
	            startService(timerIntent);
	}

	public void stopTimerService() {
		Intent timerIntent = new Intent(getApplicationContext(), TimerService.class);
		stopService(timerIntent);
	}

}
