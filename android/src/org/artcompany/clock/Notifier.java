package org.artcompany.clock;

import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;
import android.content.Intent;
import android.app.PendingIntent;
import android.graphics.Color;
import android.graphics.BitmapFactory;
import android.app.NotificationChannel;



public class Notifier {
    private static NotificationManager m_notificationManager;
    private static Notification.Builder m_builder;

    public Notifier(){}

    public static void notify(Context context, String message) {

	try {
	       m_notificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);

	       if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
		   int importance = NotificationManager.IMPORTANCE_HIGH;
		   NotificationChannel notificationChannel = new NotificationChannel("Clock", "Clock Notifier", importance);
		   m_notificationManager.createNotificationChannel(notificationChannel);
		   m_builder = new Notification.Builder(context, notificationChannel.getId());

	       } else {
	           m_builder = new Notification.Builder(context);
	       }

	  // m_notificationManager.setSound();

	       m_builder.setSmallIcon(R.drawable.icon)
	               .setLargeIcon(BitmapFactory.decodeResource(context.getResources(), R.drawable.icon))
		       .setContentTitle("Таймер")
		       .setContentText(message)
		       .setDefaults(Notification.DEFAULT_ALL)
		       .setColor(Color.GREEN)
		       .setAutoCancel(true)
		       .setPriority(Notification.PRIORITY_HIGH)
		       .setCategory(Notification.CATEGORY_ALARM)
		       .setVibrate(new long[]{100,320,100,320,100});

		       m_notificationManager.notify(0, m_builder.build());
	   } catch (Exception e) {
	       e.printStackTrace();
	   }
       }
}
