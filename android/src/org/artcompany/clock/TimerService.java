package org.artcompany.clock;

import android.graphics.BitmapFactory;
import android.content.Context;
import android.util.Log;
import org.qtproject.qt5.android.bindings.QtService;
import android.app.Notification;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

import android.app.NotificationManager;
import android.graphics.Color;
import android.app.NotificationChannel;
import android.net.Uri;


public class TimerService extends QtService {

	private NotificationManager manager;
	public static final int DEFAULT_NOTIFICATION_ID = 101;

	private static final String TAG = "TimerService";
	private static final String CHANNEL = "TimerServiceChannel";


	@Override
	public void onCreate() {
		super.onCreate();
		Log.w(TAG, "Create");
		createNotificationChannel();
		manager = (NotificationManager) this.getSystemService(this.NOTIFICATION_SERVICE);
	}

	@Override
	public void onDestroy() {
		super.onDestroy();
		manager.cancel(DEFAULT_NOTIFICATION_ID);
		stopSelf();
		Log.w(TAG, "Destroy");
	}


	@Override
	public IBinder onBind(Intent intent) {
		return null;
	}

	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		createNotificationChannel();


		int ret = super.onStartCommand(intent, flags, startId);
		Log.w(TAG, "SERVICE!!!!!!!!!");

		Intent notificationIntent = new Intent(this, ClockApplication.class);
		notificationIntent.setAction(Intent.ACTION_MAIN);
		notificationIntent.addCategory(Intent.CATEGORY_LAUNCHER);

		PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, notificationIntent, PendingIntent.FLAG_UPDATE_CURRENT);

		Notification.Builder builder = new Notification.Builder(this);
		builder.setContentIntent(pendingIntent)
				.setOngoing(true)
				.setLargeIcon(BitmapFactory.decodeResource(getResources(), R.drawable.icon))
				.setContentTitle("Таймер")
				.setContentText("Таймер запущен")
				.setDefaults(Notification.DEFAULT_ALL)
				.setAutoCancel(true)
				.setPriority(Notification.PRIORITY_HIGH)
				.setCategory(Notification.CATEGORY_ALARM);

		Notification notification = builder.build();
		startForeground(DEFAULT_NOTIFICATION_ID, notification);
		return START_NOT_STICKY;
	}


	private void createNotificationChannel() {
		Log.w(TAG, "CREATESERVICECHANNEL");
		if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
			NotificationChannel notChannel = new NotificationChannel(CHANNEL, "foreground channel", NotificationManager.IMPORTANCE_DEFAULT);
			manager.createNotificationChannel(notChannel);
		}
	}

}
