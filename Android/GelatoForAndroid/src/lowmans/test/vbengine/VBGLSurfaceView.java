package lowmans.test.vbengine;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.MotionEvent;

public class VBGLSurfaceView extends GLSurfaceView {

	private static final String TAG = "VBGLSurfaceView";
	private static final boolean DEBUG = false;

	private static final int VBTouchType_Begin = 0, VBTouchType_Move = 1, VBTouchType_End = 2, VBTouchType_Cancel = 3,
			INVALID_POINTER_ID = -1;

	private Context context;

	public VBGLSurfaceView(Context context) {
		super(context);
		this.context = context;
		VBGLSurfaceViewInit(false, 0, 0);
	}

	public VBGLSurfaceView(Context context, boolean translucent, int depth, int stencil) {
		super(context);
		this.context = context;
		VBGLSurfaceViewInit(translucent, depth, stencil);
	}

	private void VBGLSurfaceViewInit(boolean translucent, int depth, int stencil) {

		/*
		 * By default, GLSurfaceView() creates a RGB_565 opaque surface. If we want a translucent one, we should change
		 * the surface's format here, using PixelFormat.TRANSLUCENT for GL Surfaces is interpreted as any 32-bit surface
		 * with alpha by SurfaceFlinger.
		 */
		if (translucent) {
			this.getHolder().setFormat(PixelFormat.TRANSLUCENT);
		}

		/*
		 * Setup the context factory for 2.0 rendering. See ContextFactory class definition below
		 */
		setEGLContextFactory(new ContextFactory());

		/*
		 * We need to choose an EGLConfig that matches the format of our surface exactly. This is going to be done in
		 * our custom config chooser. See ConfigChooser class definition below.
		 */
		setEGLConfigChooser(translucent ? 
				new ConfigChooser(8, 8, 8, 8, depth, stencil) : new ConfigChooser(5, 6, 5, 0,depth, stencil));

		// debug check
		// setDebugFlags(DEBUG_CHECK_GL_ERROR | DEBUG_LOG_GL_CALLS);

		/* Set the renderer responsible for frame rendering */
		setRenderer(new VBGLSurfaceViewRenderer(context));
	}

	private static class ContextFactory implements GLSurfaceView.EGLContextFactory {
		private static int EGL_CONTEXT_CLIENT_VERSION = 0x3098;

		public EGLContext createContext(EGL10 egl, EGLDisplay display, EGLConfig eglConfig) {
			Log.w(TAG, "creating OpenGL ES 2.0 context");
			checkEglError("Before eglCreateContext", egl);
			int[] attrib_list = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL10.EGL_NONE };
			EGLContext context = egl.eglCreateContext(display, eglConfig, EGL10.EGL_NO_CONTEXT, attrib_list);
			checkEglError("After eglCreateContext", egl);
			return context;
		}

		public void destroyContext(EGL10 egl, EGLDisplay display, EGLContext context) {
			egl.eglDestroyContext(display, context);
		}
	}

	private static void checkEglError(String prompt, EGL10 egl) {
		int error;
		while ((error = egl.eglGetError()) != EGL10.EGL_SUCCESS) {
			Log.e(TAG, String.format("%s: EGL error: 0x%x", prompt, error));
		}
	}

	private static class ConfigChooser implements GLSurfaceView.EGLConfigChooser {

		public ConfigChooser(int r, int g, int b, int a, int depth, int stencil) {
			mRedSize = r;
			mGreenSize = g;
			mBlueSize = b;
			mAlphaSize = a;
			mDepthSize = depth;
			mStencilSize = stencil;
		}

		/*
		 * This EGL config specification is used to specify 2.0 rendering. We use a minimum size of 4 bits for
		 * red/green/blue, but will perform actual matching in chooseConfig() below.
		 */
		private static int EGL_OPENGL_ES2_BIT = 4;
		private static int[] s_configAttribs2 = { EGL10.EGL_RED_SIZE, 4, EGL10.EGL_GREEN_SIZE, 4, EGL10.EGL_BLUE_SIZE,
				4, EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL10.EGL_NONE };

		public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display) {

			/*
			 * Get the number of minimally matching EGL configurations
			 */
			int[] num_config = new int[1];
			egl.eglChooseConfig(display, s_configAttribs2, null, 0, num_config);

			int numConfigs = num_config[0];

			if (numConfigs <= 0) {
				throw new IllegalArgumentException("No configs match configSpec");
			}

			/*
			 * Allocate then read the array of minimally matching EGL configs
			 */
			EGLConfig[] configs = new EGLConfig[numConfigs];
			egl.eglChooseConfig(display, s_configAttribs2, configs, numConfigs, num_config);

			if (DEBUG) {
				printConfigs(egl, display, configs);
			}
			/*
			 * Now return the "best" one
			 */
			return chooseConfig(egl, display, configs);
		}

		public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display, EGLConfig[] configs) {
			for (EGLConfig config : configs) {
				int d = findConfigAttrib(egl, display, config, EGL10.EGL_DEPTH_SIZE, 0);
				int s = findConfigAttrib(egl, display, config, EGL10.EGL_STENCIL_SIZE, 0);

				// We need at least mDepthSize and mStencilSize bits
				if (d < mDepthSize || s < mStencilSize)
					continue;

				// We want an *exact* match for red/green/blue/alpha
				int r = findConfigAttrib(egl, display, config, EGL10.EGL_RED_SIZE, 0);
				int g = findConfigAttrib(egl, display, config, EGL10.EGL_GREEN_SIZE, 0);
				int b = findConfigAttrib(egl, display, config, EGL10.EGL_BLUE_SIZE, 0);
				int a = findConfigAttrib(egl, display, config, EGL10.EGL_ALPHA_SIZE, 0);

				if (r == mRedSize && g == mGreenSize && b == mBlueSize && a == mAlphaSize)
					return config;
			}
			return null;
		}

		private int findConfigAttrib(EGL10 egl, EGLDisplay display, EGLConfig config, int attribute, int defaultValue) {

			if (egl.eglGetConfigAttrib(display, config, attribute, mValue)) {
				return mValue[0];
			}
			return defaultValue;
		}

		private void printConfigs(EGL10 egl, EGLDisplay display, EGLConfig[] configs) {
			int numConfigs = configs.length;
			Log.w(TAG, String.format("%d configurations", numConfigs));
			for (int i = 0; i < numConfigs; i++) {
				Log.w(TAG, String.format("Configuration %d:\n", i));
				printConfig(egl, display, configs[i]);
			}
		}

		private void printConfig(EGL10 egl, EGLDisplay display, EGLConfig config) {
			int[] attributes = { EGL10.EGL_BUFFER_SIZE, EGL10.EGL_ALPHA_SIZE, EGL10.EGL_BLUE_SIZE,
					EGL10.EGL_GREEN_SIZE, EGL10.EGL_RED_SIZE, EGL10.EGL_DEPTH_SIZE, EGL10.EGL_STENCIL_SIZE,
					EGL10.EGL_CONFIG_CAVEAT, EGL10.EGL_CONFIG_ID, EGL10.EGL_LEVEL, EGL10.EGL_MAX_PBUFFER_HEIGHT,
					EGL10.EGL_MAX_PBUFFER_PIXELS, EGL10.EGL_MAX_PBUFFER_WIDTH,
					EGL10.EGL_NATIVE_RENDERABLE,
					EGL10.EGL_NATIVE_VISUAL_ID,
					EGL10.EGL_NATIVE_VISUAL_TYPE,
					0x3030, // EGL10.EGL_PRESERVED_RESOURCES,
					EGL10.EGL_SAMPLES, EGL10.EGL_SAMPLE_BUFFERS, EGL10.EGL_SURFACE_TYPE, EGL10.EGL_TRANSPARENT_TYPE,
					EGL10.EGL_TRANSPARENT_RED_VALUE, EGL10.EGL_TRANSPARENT_GREEN_VALUE,
					EGL10.EGL_TRANSPARENT_BLUE_VALUE,
					0x3039, // EGL10.EGL_BIND_TO_TEXTURE_RGB,
					0x303A, // EGL10.EGL_BIND_TO_TEXTURE_RGBA,
					0x303B, // EGL10.EGL_MIN_SWAP_INTERVAL,
					0x303C, // EGL10.EGL_MAX_SWAP_INTERVAL,
					EGL10.EGL_LUMINANCE_SIZE, EGL10.EGL_ALPHA_MASK_SIZE, EGL10.EGL_COLOR_BUFFER_TYPE,
					EGL10.EGL_RENDERABLE_TYPE, 0x3042 // EGL10.EGL_CONFORMANT
			};
			String[] names = { "EGL_BUFFER_SIZE", "EGL_ALPHA_SIZE", "EGL_BLUE_SIZE", "EGL_GREEN_SIZE", "EGL_RED_SIZE",
					"EGL_DEPTH_SIZE", "EGL_STENCIL_SIZE", "EGL_CONFIG_CAVEAT", "EGL_CONFIG_ID", "EGL_LEVEL",
					"EGL_MAX_PBUFFER_HEIGHT", "EGL_MAX_PBUFFER_PIXELS", "EGL_MAX_PBUFFER_WIDTH",
					"EGL_NATIVE_RENDERABLE", "EGL_NATIVE_VISUAL_ID", "EGL_NATIVE_VISUAL_TYPE",
					"EGL_PRESERVED_RESOURCES", "EGL_SAMPLES", "EGL_SAMPLE_BUFFERS", "EGL_SURFACE_TYPE",
					"EGL_TRANSPARENT_TYPE", "EGL_TRANSPARENT_RED_VALUE", "EGL_TRANSPARENT_GREEN_VALUE",
					"EGL_TRANSPARENT_BLUE_VALUE", "EGL_BIND_TO_TEXTURE_RGB", "EGL_BIND_TO_TEXTURE_RGBA",
					"EGL_MIN_SWAP_INTERVAL", "EGL_MAX_SWAP_INTERVAL", "EGL_LUMINANCE_SIZE", "EGL_ALPHA_MASK_SIZE",
					"EGL_COLOR_BUFFER_TYPE", "EGL_RENDERABLE_TYPE", "EGL_CONFORMANT" };
			int[] value = new int[1];
			for (int i = 0; i < attributes.length; i++) {
				int attribute = attributes[i];
				String name = names[i];
				if (egl.eglGetConfigAttrib(display, config, attribute, value)) {
					Log.w(TAG, String.format("  %s: %d\n", name, value[0]));
				} else {
					// Log.w(TAG, String.format("  %s: failed\n", name));
					while (egl.eglGetError() != EGL10.EGL_SUCCESS)
						;
				}
			}
		}

		// Subclasses can adjust these values:
		protected int mRedSize;
		protected int mGreenSize;
		protected int mBlueSize;
		protected int mAlphaSize;
		protected int mDepthSize;
		protected int mStencilSize;
		private int[] mValue = new int[1];
	}

//	public boolean onTouchEvent(final MotionEvent event) {
//		// Log.i(TAG, "onTouchEvent");
//		int action = event.getAction();
//		int touch_id; // ��ġ �ĺ���
//		int touch_mode; // ��ġ ����, ����Ʈ�� VBTouchType_End�� �س��� ���ø� �˴ϴ�.
//		float x, y; // ��ġ ��ǥ
//		switch (action & MotionEvent.ACTION_MASK) {
//		case MotionEvent.ACTION_DOWN: {
//			touch_id = event.getPointerId(0);
//			touch_mode = VBTouchType_Begin;
//			x = event.getX();
//			y = event.getY();
//			// Log.i(TAG, "[ACTION_DOWN]  X:" + x + " Y:" + y);
//			nativeTouch(touch_mode, 0, 1, x, y);
//			break;
//		}
//		case MotionEvent.ACTION_CANCEL:
//			touch_id = event.getPointerId(0);
//			touch_mode = VBTouchType_Cancel;
//			x = event.getX();
//			y = event.getY();
//			// Log.i(TAG, "[ACTION_UP]    X:" + x + " Y:" + y);
//			nativeTouch(touch_mode, 0, 1, x, y);
//			break;
//		case MotionEvent.ACTION_UP: {
//			touch_id = event.getPointerId(0);
//			touch_mode = VBTouchType_End;
//			x = event.getX();
//			y = event.getY();
//			// Log.i(TAG, "[ACTION_UP]    X:" + x + " Y:" + y);
//			nativeTouch(touch_mode, 0, 1, x, y);
//			break;
//		}
//		case MotionEvent.ACTION_MOVE: {
//			int count = event.getPointerCount();
//			for (int i = 0; i < count; ++i) {
//				int pointer_id = event.findPointerIndex(i);
//				if (pointer_id == INVALID_POINTER_ID)
//					continue;
//				touch_id = i;
//				touch_mode = VBTouchType_Move;
//				x = event.getX(pointer_id);
//				y = event.getY(pointer_id);
//				// Log.i(TAG, "[ACTION_MOVE " + i + "]  X:" + x + " Y:" + y);
//				nativeTouch(touch_mode, touch_id, count, x, y);
//			}
//			break;
//		}
//		case MotionEvent.ACTION_POINTER_DOWN: {
//			int pointer_index = (action & MotionEvent.ACTION_POINTER_ID_MASK) >> MotionEvent.ACTION_POINTER_ID_SHIFT;
//			int count = event.getPointerCount();
//			int pointer_id = event.getPointerId(pointer_index);
//			if (pointer_id != INVALID_POINTER_ID) {
//				touch_id = pointer_index;
//				touch_mode = VBTouchType_Begin;
//				x = event.getX(pointer_id);
//				y = event.getY(pointer_id);
//				// Log.i(TAG, "[ACTION_POINTER_DOWN]  X:" + x + " Y:" + y);
//				nativeTouch(touch_mode, touch_id, count, x, y);
//			}
//			break;
//		}
//
//		case MotionEvent.ACTION_POINTER_UP: {
//			int pointer_index = (action & MotionEvent.ACTION_POINTER_ID_MASK) >> MotionEvent.ACTION_POINTER_ID_SHIFT;
//			int count = event.getPointerCount();
//			int pointer_id = event.getPointerId(pointer_index);
//			if (pointer_id != INVALID_POINTER_ID) {
//				touch_id = pointer_index;
//				touch_mode = VBTouchType_End;
//				x = event.getX(pointer_id);
//				y = event.getY(pointer_id);
//				// Log.i(TAG, "[ACTION_POINTER_UP]  X:" + x + " Y:" + y);
//				nativeTouch(touch_mode, touch_id, count, x, y);
//			}
//			break;
//		}
//
//		}
//		return true;
//	}

	@Override
	public void onResume() {
		// super.onResume();
		nativeResume();
	}

	@Override
	public void onPause() {
		// super.onPause();
		nativePause();
	}

	protected void onDestroy() {
		nativeDestroy();
	}


	public native void nativeResume();

	public native void nativePause();

	public native void nativeDestroy();

	// public native void nativeTouch(int touch_mode, int touch_id, int touch_count, float x, float y);

}
