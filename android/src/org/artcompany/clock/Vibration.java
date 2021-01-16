package org.artcompany.clock;

import android.app.Activity;
import android.os.Vibrator;
import android.os.Bundle;
import android.content.Intent;
import android.content.Context;


public class Vibration{
    static Vibrator vibrator;
    static Vibration vib;

    public Vibration(){
	vib = this;
	}


    public static void Vibrate(Context context,int x){
	vibrator = (Vibrator)context.getSystemService(Context.VIBRATOR_SERVICE);
	vibrator.vibrate(x);
    }

}
