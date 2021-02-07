package org.artcompany.clock;

import android.app.Notification;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.graphics.BitmapFactory;
import android.os.Build;
import android.os.IBinder;
import android.os.SystemClock;


public class TimerService extends Service {

        private static int time;

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

		time = intent.getIntExtra("timer_time", 0);

		createNotification();

		new ProcessTimer(time * 1000).start();

		return START_STICKY;
	}

        @Override
	public IBinder onBind(Intent intent) {
	        return null;
	}

        private void createNotification() {
	        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
		        Notification.Builder builder = new Notification.Builder(this, "Timer")
			                .setSmallIcon(R.drawable.icon)
					.setLargeIcon(BitmapFactory.decodeResource(getResources(), R.drawable.icon))
					.setContentTitle("Таймер")
					.setContentText("Таймер поставлен")
					.setDefaults(Notification.DEFAULT_ALL)
					.setAutoCancel(true)
					.setPriority(Notification.PRIORITY_LOW)
					.setCategory(Notification.CATEGORY_SERVICE);

			startForeground(201, builder.build());
		}
	}

        public void notificationStop() {
	        Notification.Builder builder = new Notification.Builder(this, "Timer")
		                                                .setSmallIcon(R.drawable.icon)
								.setLargeIcon(BitmapFactory.decodeResource(getResources(), R.drawable.icon))
								.setContentTitle("Время вышло!")
								.setPriority(Notification.PRIORITY_HIGH)
								.setCategory(Notification.CATEGORY_ALARM);

		Intent intent = new Intent(this, MainActivity.class);
		intent.putExtra("notificationId",202);
		PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, intent, PendingIntent.FLAG_UPDATE_CURRENT);
		builder.setContentIntent(pendingIntent);

		 MainActivity.m_notificationManager.notify(202, builder.build());
	}

        class ProcessTimer extends Thread {
	        int time;

		ProcessTimer(int time) {
		        this.time = time;
		}

	        @Override
		public void run() {
		        SystemClock.sleep(time);
			//Intent resultIntent = new Intent();
			//resultIntent.putExtra("result", 50);
			//resultIntent.setAction(MainActivity.BROADCAST_ACTION);
			//sendBroadcast(resultIntent);
			notificationStop();
		}
	}
}
