package org.artcompany.clock;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;


public class AlarmBroadcastReceiver extends  BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent) {
	int result = intent.getIntExtra("result",0);
	Intent i = new Intent();
	i.setClassName("org.artcompany.clock", "org.artcompany.clock.MainActivity");
	i.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TASK | Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_NEW_TASK);
	//context.startActivity(i);
	NativeHelper.invokeVoidMethod(result);
    }
}
