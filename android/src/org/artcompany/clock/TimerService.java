package org.artcompany.clock;

import android.app.Notification;
import android.content.Context;
import android.content.Intent;
import android.app.PendingIntent;
import android.graphics.BitmapFactory;
import android.media.RingtoneManager;
import android.app.TaskStackBuilder;
import android.util.Log;
import android.app.NotificationManager;
import android.graphics.Color;
import android.app.NotificationChannel;
import android.net.Uri;
import org.qtproject.qt5.android.bindings.QtService;


public class TimerService extends QtService {

	private NotificationManager manager;
	public static final int DEFAULT_NOTIFICATION_ID = 101;

	private static final String TAG = "TimerService";
	private static final String CHANNEL = "TimerServiceChannel";


	@Override
	public void onCreate() {
		super.onCreate();
		Log.w(TAG, "Create");
		if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
		  Notification.Builder builder = new Notification.Builder(this, "Timer")
		                            .setSmallIcon(R.drawable.icon)
					    .setLargeIcon(BitmapFactory.decodeResource(getResources(), R.drawable.icon))
					    .setContentTitle("Сервис")
					    .setContentText("Сервис запущуен")
					    .setDefaults(Notification.DEFAULT_ALL)
					    .setColor(Color.GREEN)
					    .setAutoCancel(true)
					    .setPriority(Notification.PRIORITY_HIGH)
					    .setCategory(Notification.CATEGORY_ALARM);


			   Intent intent = new Intent(this,ClockApplication.class);
			   intent.putExtra("notificationId",101);
			   PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, intent, PendingIntent.FLAG_UPDATE_CURRENT);
			   builder.setContentIntent(pendingIntent);
			   startForeground(101,builder.build());

	    }

	}

	@Override
	public void onDestroy() {
		super.onDestroy();
		Log.w(TAG, "Destroy");
	}





/*	@Override
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

    public static void startTimerService(Context context) {
	    context.startService(new Intent(context,TimerService.class));

    }*/

}
