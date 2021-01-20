package org.artcompany.clock;

import android.util.Log;
import android.os.Bundle;
import android.os.Vibrator;
import android.content.Context;
import android.media.AudioManager;
import android.widget.Toast;
import android.content.Intent;
import android.app.Activity;
import android.provider.Settings;
import android.database.Cursor;
import android.net.Uri;
import android.provider.MediaStore;
import android.provider.MediaStore.Audio.AudioColumns;
import java.io.File;


public class ClockApplication extends org.qtproject.qt5.android.bindings.QtActivity {
    public static Vibrator m_vibrator;
    public static ClockApplication m_instance;
    static String TAG = "ClockApplication";

    public ClockApplication(){
	m_instance = this;
	}

    @Override
    public void onCreate(Bundle savedInstanceState) {
	super.onCreate(savedInstanceState);
	this.setVolumeControlStream(AudioManager.STREAM_MUSIC);

	Log.w(TAG, "onCreate() called!!!!!!!");
	}

    @Override
       public void onStop() {
	   Log.w(TAG, "onStop() called!");
	   //NativeHelper.invokeVoidMethod(42);
	   super.onStop();
       }

   @Override
       public void onDestroy() {
	   Log.w(TAG, "onDestroy() called!");
	   super.onDestroy();
       }

   public static void invoke(int x) {
           final int z = x;
	   m_instance.runOnUiThread(new Runnable() {
	       public void run() {
		   Toast.makeText(m_instance, "Invoke from C++ => Java: " + String.valueOf(z) + " (Button)",
		                              Toast.LENGTH_SHORT).show();
	       }
	   });
           NativeHelper.invokeVoidMethod(x);
       }

   public static void vibrate(int x) {
          if (m_vibrator == null) {
	      if (m_instance != null) {
		m_vibrator = (Vibrator) m_instance.getSystemService(Context.VIBRATOR_SERVICE);
		m_vibrator.vibrate(x);
	      }
	  } else {
	      m_vibrator.vibrate(x);
	  }
          Log.w(TAG, "Vibro: Java");
      }

  public String getPath(Uri uri)
  {
      String fullFilePath = UriUtils.getPathFromUri(this,uri);
      Log.w(TAG, "FILEPATH - "+fullFilePath+"\\"+uri);
      return  "file://"+fullFilePath;
  }

}
