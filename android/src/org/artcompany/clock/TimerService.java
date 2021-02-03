package org.artcompany.clock;


import java.util.Timer;
import java.util.TimerTask;
import android.os.SystemClock;
import android.app.Notification;
import android.app.PendingIntent;
import android.content.Intent;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.os.IBinder;
import android.util.Log;

import org.qtproject.qt5.android.bindings.QtService;


public class TimerService extends QtService {

        private static final String TAG = "TimerService";
	static Timer timer;


	@Override
	public void onCreate() {
	    super.onCreate();
	    timer = new Timer();
	}

	@Override
	public void onDestroy() {
	    super.onDestroy();
	    Log.w(TAG, "Destroy");
	}

        @Override
	public int onStartCommand(Intent intent, int flags, int startId) {
	    int ret = super.onStartCommand(intent, flags, startId);
	    Log.w(TAG, "Create Service");
	    //int time = intent.getIntExtra(ClockApplication.PARAM_TIME, 0);
	   // int task = intent.getIntExtra(ClockApplication.PARAM_TASK, 0);

	    createNotification();
	    new ProcessData().start();

	    return START_NOT_STICKY;
}

    /*private void stopForegroundService() {
	stopForeground(true);
	stopSelf();
    }*/

    private void createNotification() {
	if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
	        Notification.Builder builder = new Notification.Builder(this, "Service")
		                                                .setSmallIcon(R.drawable.icon)
								.setLargeIcon(BitmapFactory.decodeResource(getResources(), R.drawable.icon))
								.setContentTitle("Сервис")
								.setContentText("Сервис запущуен")
								.setDefaults(Notification.DEFAULT_ALL)
								.setColor(Color.GREEN)
								.setAutoCancel(true)
								.setPriority(Notification.PRIORITY_HIGH)
								.setCategory(Notification.CATEGORY_ALARM);

		   Intent notifcationIntent = new Intent(this,ClockApplication.class);
		   notifcationIntent.putExtra("notificationId",101);
		   PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, notifcationIntent, PendingIntent.FLAG_UPDATE_CURRENT);
		   builder.setContentIntent(pendingIntent);
		   startForeground(101,builder.build());
	}
    }

    class ProcessData extends Thread {
	@Override
	public void run() {
	    while(true) {
		Log.w(TAG, "Process Service");
		SystemClock.sleep(10000);
		Log.w(TAG, "Timer Start");
		Intent resultIntent = new Intent();
		resultIntent.putExtra("result",50);
		resultIntent.setAction(ClockApplication.BROADCAST_ACTION);
		sendBroadcast(resultIntent);
	    }
	}
    }

}
