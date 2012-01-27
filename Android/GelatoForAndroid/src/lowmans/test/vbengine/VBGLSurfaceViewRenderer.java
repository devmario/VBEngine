package lowmans.test.vbengine;

import java.io.FileDescriptor;
import java.io.IOException;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.content.res.AssetFileDescriptor;
import android.opengl.GLSurfaceView;
import android.util.Log;

class VBGLSurfaceViewRenderer implements GLSurfaceView.Renderer {
	private static final String TAG = "VBGLSurfaceViewRenderer";
	private Context context;

	public VBGLSurfaceViewRenderer(Context context) {
		this.context = context;
		sendResourceToNative();
	}

	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		
		nativeInit();
		
	}

	public void onSurfaceChanged(GL10 gl, int w, int h) {
		// gl.glViewport(0, 0, w, h);
		nativeResize(w, h);
	}

	public void onDrawFrame(GL10 gl) {
		nativeRender();
	}

	public void sendResourceToNative() {
		try {
			String[] fds = context.getAssets().list("");
			for (String path : fds) {
				if (!path.contains(".png") && !path.contains(".mp3")) {
					continue;
				}

				AssetFileDescriptor afd = context.getAssets().openFd(path);
				FileDescriptor fd = afd.getFileDescriptor();
				fd.sync();
				long off = afd.getStartOffset();
				long leng = afd.getLength();
				nativeResourceInit("assets/" + path.substring(0, path.length() - 4), fd, off, leng);
			}
		} catch (IOException e) {
			Log.e(TAG, "message : " + e.toString());
		}
	}

	public native void nativeInit();

	public native void nativeResize(int w, int h);

	public native void nativeRender();

	// public native void nativeDone();

	public native void nativeResourceInit(String path, FileDescriptor fd, long offset, long length);
}