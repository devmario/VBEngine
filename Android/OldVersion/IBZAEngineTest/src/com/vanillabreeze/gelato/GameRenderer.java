package com.vanillabreeze.gelato;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLSurfaceView;

public class GameRenderer implements GLSurfaceView.Renderer {
	
	public GameRenderer(Context context) {
		super();
	}

	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		nativeInitGame();
	}

	public void onSurfaceChanged(GL10 gl, int w, int h) {
		nativeResize(w, h);
	}

	public void onDrawFrame(GL10 gl) {
		nativeRender();
	}

	public native void nativeResize(int w, int h);

	public native void nativeRender();

	public native void nativeInitGame();

}
