package org.artcompany.clock;

import android.app.Notification;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;
import android.graphics.BitmapFactory;
import android.os.Build;
import android.os.IBinder;
import android.os.SystemClock;
import android.util.Log;
import android.app.NotificationChannel;
import android.app.NotificationManager;

public class AlarmService extends Service {

    private static final String TAG = "TimerService";
    private NotificationChannel notificationChannel;
    private NotificationManager m_notificationManager;
    @Override
    public void onCreate() {
	notificationChannel = new NotificationChannel("Service", "Service Notifier", NotificationManager.IMPORTANCE_HIGH);
	notificationChannel.enableVibration(true);

	m_notificationManager = getSystemService(NotificationManager.class);
	m_notificationManager.createNotificationChannel(notificationChannel);

        super.onCreate();
    }

    @Override
    public void onDestroy() {
        super.onDestroy();

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N) {
            stopForeground(Service.STOP_FOREGROUND_DETACH);
        }
        stopSelf();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        int ret = super.onStartCommand(intent, flags, startId);

        createNotification();
	for(int i = 0; i < 3; i++) {
	    Log.w(TAG, "Process Service");
	    SystemClock.sleep(10000);
	    Log.w(TAG, "Timer Start");
	    Intent resultIntent = new Intent();
	    resultIntent.putExtra("result", 50);
	    resultIntent.setAction(MainActivity.BROADCAST_ACTION);
	    createAlarmNotification();
	    sendBroadcast(resultIntent);
	    SystemClock.sleep(5000);
	}

        return START_NOT_STICKY;
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
		    .setCategory(Notification.CATEGORY_SERVICE);

            Intent notifcationIntent = new Intent(this, MainActivity.class);
            notifcationIntent.putExtra("notificationId", 102);
            PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, notifcationIntent, PendingIntent.FLAG_UPDATE_CURRENT);
            builder.setContentIntent(pendingIntent);
	    m_notificationManager.notify(102, builder.build());
        }
    }

    class ProcessData extends Thread {

        @Override
        public void run() {
	    for(int i = 0; i < 3; i++) {
                Log.w(TAG, "Process Service");
                SystemClock.sleep(10000);
                Log.w(TAG, "Timer Start");
                Intent resultIntent = new Intent();
                resultIntent.putExtra("result", 50);
                resultIntent.setAction(MainActivity.BROADCAST_ACTION);
                createAlarmNotification();
		sendBroadcast(resultIntent);
                SystemClock.sleep(5000);
            }
        }
    }
}
