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

public class AlarmService extends Service {

    private static final String TAG = "TimerService";

    @Override
    public void onCreate() {
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
	new ProcessData().start();

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
	.setPriority(Notification.PRIORITY_HIGH)
	.setCategory(Notification.CATEGORY_SERVICE);

	Intent notifcationIntent = new Intent(this, MainActivity.class);
	notifcationIntent.putExtra("notificationId", 102);
	PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, notifcationIntent, PendingIntent.FLAG_UPDATE_CURRENT);
	builder.setContentIntent(pendingIntent);
	startForeground(102, builder.build());
	}
    }

class ProcessData extends Thread {

    @Override
    public void run() {
	while (true) {
	    Log.w(TAG, "Process Service");
	    SystemClock.sleep(10000);
	    Log.w(TAG, "Timer Start");
	    Intent resultIntent = new Intent();
	    resultIntent.putExtra("result", 50);
	    resultIntent.setAction(MainActivity.BROADCAST_ACTION);
	    sendBroadcast(resultIntent);
	    createNotification();
	    SystemClock.sleep(5000);
	}
    }
}

}
