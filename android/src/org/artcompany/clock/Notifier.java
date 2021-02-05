package org.artcompany.clock;

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

    //private static Notification.Builder m_builder;

    public static void notify(Context context, String message) {
	Notification.Builder m_builder = new Notification.Builder(context, "Timer");
	m_builder.setSmallIcon(R.drawable.icon)
				.setLargeIcon(BitmapFactory.decodeResource(context.getResources(), R.drawable.icon))
				.setContentTitle("Таймер")
				.setContentText(message)
				.setDefaults(Notification.DEFAULT_ALL)
				.setColor(Color.GREEN)
				.setAutoCancel(true)
				.setPriority(Notification.PRIORITY_HIGH)
				.setCategory(Notification.CATEGORY_ALARM);

	Intent intent = new Intent(context,ClockApplication.class);
	intent.putExtra("notificationId","Clock");
	intent.putExtra("message",message);
	intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);

	PendingIntent pendingIntent = PendingIntent.getActivity(context, 0, intent, PendingIntent.FLAG_UPDATE_CURRENT);
	m_builder.setContentIntent(pendingIntent);

	ClockApplication.m_notificationManager.notify(5, m_builder.build());
	}
}
