package com.vanillabreeze.gelato;

import java.io.FileDescriptor;
import java.util.ArrayList;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.media.AudioManager;
import android.os.Bundle;
import android.os.Handler;
import android.view.ViewGroup.LayoutParams;
import android.view.WindowManager;
import android.widget.RelativeLayout;

import com.vanillabreeze.util.AssetFileManager;
import com.vanillabreeze.util.MusicManager;
import com.vanillabreeze.util.SoundManager;
import com.vanillabreeze.util.XMLData;
import com.vanillabreeze.util.XMLParsing;

public class Gelato extends Activity {
	private static final String TAG = "Gelato";
	private GameSurface glSurfaceView;
	private SoundManager soundManager;
	private MusicManager musicManager;
	private SharedPreferences pref;
	private SharedPreferences.Editor editor;
	private RelativeLayout layout;
	private Context context;
	private Thread thread;

	static {
		System.loadLibrary("Gelato");
	}

	private Handler handler = new Handler() {
		public void handleMessage(android.os.Message msg) {
			glSurfaceView = new GameSurface(context);
			addContentView(glSurfaceView, new LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));
			layout.removeAllViews();
			layout = null;
			thread = null;
		};
	};

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		setVolumeControlStream(AudioManager.STREAM_MUSIC);
		setContentView(R.layout.splash);
		context = this;
		layout = (RelativeLayout) findViewById(R.id.splashLayout);

		// splash screen ������ ���ؼ� Thread ~ Handler ó����
		if (thread == null) {
			thread = new Thread() {
				@Override
				public void run() {
					// ȿ���� �� ����� ����
					soundManager = new SoundManager(context);
					soundManager.addAll();
					musicManager = new MusicManager(context);

					// data ��������
					pref = getSharedPreferences("Gelato", Activity.MODE_PRIVATE);
					editor = pref.edit();

					// native �ʱ�ȭ
					nativeInit();

					// xml parsing �� data �� native �� ���
					ArrayList<XMLData> xmlData = XMLParsing.getData(context);
					for (int i = 0; i < xmlData.size(); i++) {
						nativeLoadXML(xmlData.get(i));
					}

					// Assets �� Resouce �� native �� ��� (fileName, fd, off, len)
					AssetFileManager afm = new AssetFileManager(context);
					if (afm.pathArray != null && afm.fdArray != null && afm.offArray != null && afm.lengArray != null) {
						nativeLoadResInfo(afm.pathArray, afm.fdArray, afm.offArray, afm.lengArray);
					}
					// Resource�� native�� load �� engine view ��
					handler.sendEmptyMessage(0);
				}

			};
			try {
				thread.join();
			} catch (InterruptedException e) {
			}
			thread.start();
		}
	}

	@Override
	protected void onPause() {
		if (glSurfaceView != null)
			glSurfaceView.onPause();

		if (musicManager != null)
			musicManager.pauseMusic();
		super.onPause();

	}

	@Override
	protected void onResume() {
		if (glSurfaceView != null)
			glSurfaceView.onResume();
		if (musicManager != null)
			musicManager.startMusic();
		super.onResume();

	}

	@Override
	protected void onDestroy() {
		if (glSurfaceView != null)
			glSurfaceView.onDestroy();

		if (musicManager != null)
			musicManager.releaseMusic();
		super.onDestroy();
	}

	public void saveRecord(int score) {
		editor.putString("key", "value");
		editor.commit();

	}

	public int loadRecord() {
		// Log.i(TAG, (String) pref.getAll().get("key"));
		return 0;
	}

	public void playSound(String code) {
		soundManager.playSound(code);
	}

	public void playMusic(String code) {
		musicManager.playMusic(code);
	}

	public native void nativeInit();

	public native void nativeLoadXML(XMLData data);

	public native void nativeLoadResInfo(String[] pathArray, FileDescriptor[] fdArray, long[] offArray, long[] lengArray);
}