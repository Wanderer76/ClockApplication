package org.artcompany.clock;

import android.app.Notification;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.graphics.BitmapFactory;
import android.media.MediaPlayer;
import android.os.IBinder;
import android.os.Vibrator;
import android.net.Uri;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.os.Build;
import android.os.Bundle;
import java.io.IOException;

public class AlarmService extends Service {

    private static final String TAG = "TimerService";
    private static NotificationChannel notificationChannel;
    private static NotificationManager m_notificationManager;
    private MediaPlayer mediaPlayer;
    private Vibrator vibrator;

    @Override
    public void onCreate() {
	notificationChannel = new NotificationChannel("Service", "Service Notifier", NotificationManager.IMPORTANCE_HIGH);
	notificationChannel.enableVibration(true);
	m_notificationManager = getSystemService(NotificationManager.class);
	m_notificationManager.createNotificationChannel(notificationChannel);
	vibrator = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);

	mediaPlayer =  new MediaPlayer();
	mediaPlayer.setLooping(true);

	super.onCreate();
    }

    @Override
    public void onDestroy() {
	super.onDestroy();


	mediaPlayer.stop();
	vibrator.cancel();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
	int ret = super.onStartCommand(intent, flags, startId);
	createNotification();
	try{
	mediaPlayer.setDataSource(intent.getStringExtra("alarm_song"));
	} catch (IOException e) {
	e.printStackTrace();
    }
        mediaPlayer.start();
	long[] pattern = { 0, 100, 1000 };
	vibrator.vibrate(pattern, 0);

	return START_STICKY;
    }

    @Override
    public IBinder onBind(Intent intent) {
	return null;
    }

    private void createNotification() {
	if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
	    Notification.Builder builder = new Notification.Builder(this, "Service")
	            .setSmallIcon(R.drawable.icon)
		    .setLargeIcon(BitmapFactory.decodeResource(getResources(), R.drawable.icon))
		    .setContentTitle("Будильник")
		    .setContentText("Будильник поставлен")
		    .setDefaults(Notification.DEFAULT_ALL)
		    .setAutoCancel(true)
		    .setPriority(Notification.PRIORITY_LOW)
		    .setCategory(Notification.CATEGORY_SERVICE);

		startForeground(101, builder.build());
	}
    }

    private void createAlarmNotification() {
	if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
	    Notification.Builder builder = new Notification.Builder(this, "Service")
	            .setSmallIcon(R.drawable.icon)
		    .setLargeIcon(BitmapFactory.decodeResource(getResources(), R.drawable.icon))
		    .setContentTitle("Будильник")
		    .setContentText("10:00")
		    .setAutoCancel(true)
		    .setPriority(Notification.PRIORITY_LOW)
		    .setVibrate(new long[]{300,200,300,200,300,1000})
		    .setCategory(Notification.CATEGORY_SERVICE);

		Intent notifcationIntent = new Intent(this, MainActivity.class);
	    notifcationIntent.putExtra("notificationId", 102);
	    PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, notifcationIntent, PendingIntent.FLAG_UPDATE_CURRENT);
	    builder.setContentIntent(pendingIntent);
	    m_notificationManager.notify(102, builder.build());
	}
    }

}
