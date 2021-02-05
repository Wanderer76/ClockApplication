package org.artcompany.clock;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;


public class AlarmBroadcastReceiver extends  BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent) {
	int result = intent.getIntExtra("result",0);
	NativeHelper.invokeVoidMethod(result);
    }
}
