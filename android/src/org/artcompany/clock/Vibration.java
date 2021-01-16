package org.artcompany.clock;

import android.app.Activity;
import android.os.Vibrator;
import android.os.Bundle;
import android.content.Intent;
import android.content.Context;


public class Vibration extends org.qtproject.qt5.android.bindings.QtActivity{
    static Vibrator vibrator;
    static Vibration vib;

    public Vibration(){
	vib = this;
	}

   @Override
    public void onCreate(Bundle savedInstanceState) {
	vibrator = (Vibrator)vib.getSystemService(Context.VIBRATOR_SERVICE);
	super.onCreate(savedInstanceState);

    }
    public static void Vibrate(int x){
	vibrator.vibrate(x);
    }

}
