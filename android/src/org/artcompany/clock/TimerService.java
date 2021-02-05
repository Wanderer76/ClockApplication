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


public class TimerService extends Service {

    private static final String TAG = "TimerService";


    @Override
    public void onCreate() {
	super.onCreate();
    }

    @Override
    public void onDestroy() {
	super.onDestroy();
	Log.w(TAG, "Destroy");
	if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N) {
	    stopForeground(Service.STOP_FOREGROUND_DETACH);
	}
        stopSelf();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
	int ret = super.onStartCommand(intent, flags, startId);
	Log.w(TAG, "Create Service");
	//int time = intent.getIntExtra(ClockApplication.PARAM_TIME, 0);
	// int task = intent.getIntExtra(ClockApplication.PARAM_TASK, 0);

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
		    .setContentTitle("Сервис")
		    .setContentText("Сервис запущуен")
		    .setDefaults(Notification.DEFAULT_ALL)
		    .setAutoCancel(false)
		    .setPriority(Notification.PRIORITY_HIGH)
		    .setCategory(Notification.CATEGORY_SERVICE);

		Intent notifcationIntent = new Intent(this, ClockApplication.class);
	    notifcationIntent.putExtra("notificationId", 101);
	    PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, notifcationIntent, PendingIntent.FLAG_UPDATE_CURRENT);
	    builder.setContentIntent(pendingIntent);
	    startForeground(101, builder.build());
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
		resultIntent.setAction(ClockApplication.BROADCAST_ACTION);
		sendBroadcast(resultIntent);
		SystemClock.sleep(5000);
		}
	}
    }

}
