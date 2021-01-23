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

    private static final String TAG = "TimerService";
    private static final String CHANNEL = "TimerServiceChannel";

    @Override
    public void onCreate() {
	super.onCreate();
	Log.w(TAG, "Create");
    }

    @Override
    public void onDestroy() {
	stopForeground(true);
	stopSelf();
	super.onDestroy();
	Log.w(TAG, "Destroy");
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
	createNotificationChannel();


	int ret = super.onStartCommand(intent,flags,startId);
	Log.w(TAG, "SERVICE!!!!!!!!!");

	Intent notificationIntent = new Intent(this,ClockApplication.class);
	PendingIntent pendingIntent = PendingIntent.getActivity(this,0,notificationIntent, 0);

	Notification notification = new Notification.Builder(this,CHANNEL)
	                                            .setLargeIcon(BitmapFactory.decodeResource(getResources(), R.drawable.icon))
						    .setContentTitle("Таймер")
						    .setContentText("Таймер запущен")
						    .setDefaults(Notification.DEFAULT_ALL)
						    .setAutoCancel(true)
						    .setPriority(Notification.PRIORITY_HIGH)
						    .setCategory(Notification.CATEGORY_ALARM)
						    .build();

	       startForeground(1, notification);

	       return START_NOT_STICKY;
    }



    private void createNotificationChannel() {
	if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
	    NotificationChannel notChannel = new NotificationChannel(CHANNEL,"foreground channel", NotificationManager.IMPORTANCE_DEFAULT);

	    NotificationManager manager = getSystemService(NotificationManager.class);
	    manager.createNotificationChannel(notChannel);
	}
    }

public static void startQtAndroidService(Context context) {
        context.startService(new Intent(context, TimerService.class));
}

}
