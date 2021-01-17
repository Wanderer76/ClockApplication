package org.artcompany.clock;

import android.app.Service;
import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;
import android.content.Intent;
import android.app.PendingIntent;
import android.graphics.Color;
import android.graphics.BitmapFactory;
import android.app.NotificationChannel;
import android.media.RingtoneManager;
import android.net.Uri;
import android.app.TaskStackBuilder;


public class Notifier {

    private static NotificationManager m_notificationManager;
    private static Notification.Builder m_builder;
    private static Uri alarmSound;
    private static long[] pattern = { 100, 300, 300, 300 };

    public Notifier() {
	alarmSound = RingtoneManager.getDefaultUri(RingtoneManager.TYPE_ALARM);
    }

    public static void notify(Context context, String message) {

	m_notificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);

	if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {

	    int importance = NotificationManager.IMPORTANCE_HIGH;
	    NotificationChannel notificationChannel = new NotificationChannel("Clock", "Clock Notifier", importance);
	    notificationChannel.enableVibration(true);
	    notificationChannel.setVibrationPattern(pattern);
	    //notificationChannel.setSound(alarmSound);

	    m_notificationManager.createNotificationChannel(notificationChannel);
	    m_builder = new Notification.Builder(context, notificationChannel.getId());

	} else {
	    m_builder = new Notification.Builder(context);
	}

        m_builder.setSmallIcon(R.drawable.icon)
				.setLargeIcon(BitmapFactory.decodeResource(context.getResources(), R.drawable.icon))
				.setContentTitle("Таймер")
				.setContentText(message)
				.setDefaults(Notification.DEFAULT_ALL)
				.setColor(Color.GREEN)
				.setAutoCancel(true)
				.setSound(alarmSound)
				.setPriority(Notification.PRIORITY_HIGH)
				.setCategory(Notification.CATEGORY_ALARM)
				.setVibrate(pattern);

	Intent intent = new Intent(context,ClockApplication.class);
	intent.putExtra("notificationId","Clock");
	intent.putExtra("message",message);
	intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);

	PendingIntent pendingIntent = PendingIntent.getActivity(context,1,intent,PendingIntent.FLAG_UPDATE_CURRENT);
	m_builder.setContentIntent(pendingIntent);

	m_notificationManager.notify(1, m_builder.build());
	}
}
