package com.vanillabreeze.gelato;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.MotionEvent;

public class GameSurface extends GLSurfaceView {
	private static final String TAG = "GameSurface";
	private GameRenderer renderer;

	public GameSurface(Context context) {
		this(context, null);

	}
	public GameSurface(Context context, AttributeSet attrs) {
		super(context, attrs);
		renderer = new GameRenderer(context);
		setRenderer(renderer);
	}

	@Override
	public void onPause() {
		nativePause();
		// super.onPause();
	}

	@Override
	public void onResume() {
		nativeResume();
		// super.onResume();
	}

	public void onDestroy() {
		nativeDestroy();
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {
		if (event.getAction() == MotionEvent.ACTION_DOWN) {
			// Log.d("TAG " , "Down " + event.getX() + "  " + event.getY());
			nativeTouch(event.getX(), event.getY(), 1);
			return false;
		} else if (event.getAction() == MotionEvent.ACTION_MOVE) {
			// Log.d("TAG " , "Move " + event.getX() + "  " + event.getY());
			nativeTouch(event.getX(), event.getY(), 2);
			return false;
		} else if (event.getAction() == MotionEvent.ACTION_UP) {
			// Log.d("TAG " , "Up " + event.getX() + "  " + event.getY());
			nativeTouch(event.getX(), event.getY(), 3);
			return false;
		} else if (event.getAction() == MotionEvent.ACTION_CANCEL) {
			// Log.d("TAG " , "Cancel " + event.getX() + "  " + event.getY());
			nativeTouch(event.getX(), event.getY(), 0);
			return false;
		}
		return false;
	}

	public native void nativeTouch(float x, float y, int type);

	public native void nativePause();

	public native void nativeResume();

	public native void nativeDestroy();

}
