package org.artcompany.clock;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.ContextWrapper;
import android.content.Intent;
import android.graphics.BitmapFactory;
import android.os.Build;
import android.app.PendingIntent;



public class AlarmBroadcastReceiver extends  BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent) {

	int hour = intent.getIntExtra("alarm_hour", 0);
	int minute = intent.getIntExtra("alarm_minute", 0);
	AlarmService notificationHelper = new AlarmService(context);
	Notification.Builder nb = notificationHelper.getChannelNotification(hour + ":" + minute);
	notificationHelper.getManager().notify(1, nb.build());
	NativeHelper.invokeVoidMethod(50);
    }


    public class AlarmService extends ContextWrapper {

	public static final String channelID = "channelID";
	public static final String channelName = "Channel Name";
	private NotificationManager mManager;

	public AlarmService(Context base) {
	    super(base);
	    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
		createChannel();
		}
	}

        private void createChannel() {
	    NotificationChannel channel = new NotificationChannel(channelID, channelName, NotificationManager.IMPORTANCE_HIGH);
	    getManager().createNotificationChannel(channel);
	}

        public NotificationManager getManager() {
	    if (mManager == null) {
		    mManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
		}
	    return mManager;
	}

        public Notification.Builder getChannelNotification(String time) {
	    Notification.Builder builder = new Notification.Builder(getApplicationContext(), channelID)
	            .setSmallIcon(R.drawable.icon)
		    .setLargeIcon(BitmapFactory.decodeResource(getResources(), R.drawable.icon))
		    .setContentTitle("Будильник")
		    .setContentText(time)
		    .setAutoCancel(true)
		    .setPriority(Notification.PRIORITY_MAX)
		    .setVibrate(new long[]{300, 200, 300, 200, 300, 1000})
		    .setCategory(Notification.CATEGORY_ALARM);
		    Intent intent = new Intent(this, MainActivity.class);
		    PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, intent, PendingIntent.FLAG_UPDATE_CURRENT);
		    builder.setContentIntent(pendingIntent);
		    return builder;
		}
    }
}
