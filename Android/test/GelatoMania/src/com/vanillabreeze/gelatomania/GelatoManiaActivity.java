package com.vanillabreeze.gelatomania;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Date;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.Typeface;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.EditText;

import com.facebook.android.BaseDialogListener;
import com.facebook.android.BaseRequestListener;
import com.facebook.android.FacebookUtil;
import com.facebook.android.LoginManager;

public class GelatoManiaActivity extends Cocos2dxActivity {
	private static final String TAG = "GelatoManiaActivity";

	private Cocos2dxGLSurfaceView mGLView;
	private SharedPreferences sp;
	private SharedPreferences.Editor e;

	// modify lowmans -> use facebook api
	private static FacebookUtil fbUtil;
	private static LoginManager loginMgr;
	private static Activity activity;
	private static AssetManager mAsset;
	
	static {
		System.loadLibrary("stlport_shared");
		System.loadLibrary("cocos2d");
		System.loadLibrary("cocosdenshion");
		System.loadLibrary("vanillaworld");
		System.loadLibrary("gamelogic");
	}

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		mAsset = getAssets();
		
		// get the packageName,it's used to set the resource path
		String packageName = getApplication().getPackageName();
		super.setPackageName(packageName);

		sp = getSharedPreferences("pref", Activity.MODE_PRIVATE);
		e = sp.edit();

		if (sp.getBoolean("isFirst", true)) {
			//CopyAssets();
		}

		setContentView(R.layout.game_demo);
		mGLView = (Cocos2dxGLSurfaceView) findViewById(R.id.game_gl_surfaceview);
		mGLView.setTextField((EditText) findViewById(R.id.textField));
		// Get the size of the mGLView after the layout happens
		mGLView.post(new Runnable() {
			@Override
			public void run() {
				Cocos2dxActivity.screenHeight = mGLView.getHeight();
				Cocos2dxActivity.screenWidth = mGLView.getWidth();
			}
		});

		// modify lowmans -> facebook instance
		fbUtil = new FacebookUtil(this);
		loginMgr = new LoginManager(this, fbUtil.mFacebook);

		activity = this;

	}

	@Override
	protected void onPause() {
		super.onPause();
		mGLView.onPause();
	}

	@Override
	protected void onResume() {
		super.onResume();
		mGLView.onResume();
	}

	// modify lowmans -> Assets Copy to <data/data> or <sdcard>
	private boolean makeDir(String fname) {
		File f = new File(fname);
		if (f.isDirectory() && f.exists()) {
			return false;
		}
		f.setLastModified(new Date().getTime());// 수정일
		return f.mkdir();
	}

	// private void CopyAssets() {
	//
	// // makeDir("/sdcard/.vanillaworld/");
	// // makeDir("/sdcard/.vanillaworld/gelatomania/");
	// // makeDir("/sdcard/.vanillaworld/gelatomania/resource");
	// // makeDir("/sdcard/.vanillaworld/gelatomania/document");
	//
	// makeDir("/data/data/com.vanillabreeze.gelatomania/files/");
	// makeDir("/data/data/com.vanillabreeze.gelatomania/files/resource");
	// makeDir("/data/data/com.vanillabreeze.gelatomania/files/document");
	//
	// AssetManager assetManager = getAssets();
	// String[] files = null;
	// InputStream in = null;
	// OutputStream out = null;
	// try {
	// files = assetManager.list("");
	// for (String filename : files) {
	// in = assetManager.open(filename);
	// // String tmp = "/sdcard/.vanillaworld/gelatomania/resource/" + filename;
	// String tmp = "/data/data/com.vanillabreeze.gelatomania/files/resource/" + filename;
	// Log.i("#@#", tmp);
	// out = new FileOutputStream(tmp);
	// copyFile(in, out);
	// }
	// } catch (Exception e) {
	// Log.e("tag", "try : " + e.getMessage());
	// } finally {
	// try {
	// in.close();
	// out.flush();
	// out.close();
	// } catch (IOException e) {
	// Log.e("tag", "finally : " + e.getMessage());
	// }
	// }
	//
	// // 초기 한번만 실행하기 위해서 플래그 세팅
	// e.putBoolean("isFirst", false);
	// }

	private void CopyAssets() {

		makeDir("/sdcard/.vanillaworld/");
		makeDir("/sdcard/.vanillaworld/gelatomania/");
		makeDir("/sdcard/.vanillaworld/gelatomania/resource");
		makeDir("/sdcard/.vanillaworld/gelatomania/document");

		makeDir("/data/data/com.vanillabreeze.gelatomania/files/");
		makeDir("/data/data/com.vanillabreeze.gelatomania/files/resource");
		makeDir("/data/data/com.vanillabreeze.gelatomania/files/document");

		AssetManager assetManager = getAssets();
		String[] files = null;
		String tmp = "";
		InputStream in = null;
		OutputStream out = null;
		try {
			files = assetManager.list("");
		} catch (IOException e) {
			Log.e("assetManager", e.getMessage());
		}
		for (String filename : files) {
			try {
				in = assetManager.open(filename);
				tmp = "/data/data/com.vanillabreeze.gelatomania/files/resource/" + filename;
				// tmp = "/sdcard/.vanillaworld/gelatomania/resource/" + filename;
				Log.i("#@#", tmp);
				out = new FileOutputStream(tmp);
				copyFile(in, out);
			} catch (Exception e) {
				Log.e("#@#", tmp);
				Log.e("#@#", "getMessage :" + e.getMessage());
			} finally {
				try {
					in.close();
					in = null;
					out.flush();
					out.close();
					out = null;
				} catch (Exception e) {
					Log.e("#@#", "finally : " + tmp);
					Log.e("#@#", "finally getMessage :" + e.getMessage());
				}
			}
		}
		// 초기 한번만 실행하기 위해서 플래그 세팅
		e.putBoolean("isFirst", false);
	}

	private static void copyFile(InputStream in, OutputStream out) throws IOException {
		byte[] buffer = new byte[1024];
		int read;
		while ((read = in.read(buffer)) != -1) {
			out.write(buffer, 0, read);
		}
	}

	public static Handler handler = new Handler() {
		public void handleMessage(android.os.Message msg) {
			if (msg.what == 0) {
				Log.d("GelatoManiaActivity", "facebookLogin() ret: " + fbUtil.isLogin());
				loginMgr.login(new BaseDialogListener() {

					@Override
					public void onComplete(Bundle values) {
						nativeFacebookLogin(fbUtil.isLogin());
					}
				});
			} else if (msg.what == 1) {
				if (fbUtil.isLogin()) {
					fbUtil.mFacebook.dialog(activity, "apprequests", msg.getData(), new BaseDialogListener() {
						@Override
						public void onComplete(Bundle values) {
						}
					});
				}
			} else if (msg.what == 2) {
				if (fbUtil.isLogin()) {
					fbUtil.mFacebook.dialog(activity, "feed", msg.getData(), new BaseDialogListener() {
						@Override
						public void onComplete(Bundle values) {
						}
					});
				}
			}
		};
	};

	// modify lowmans -> facebook dialog feed-back
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		fbUtil.mFacebook.authorizeCallback(requestCode, resultCode, data);
	}

	private static Bitmap getTextImageWithSizeDetail(String _txt, String _fontName, float _text_size, int _width, int _height,
			int _colorCode, int _shadowColorCode, float _shadowOffsetX, float _shadowOffsetY, int align) {

		
		Bitmap textBitmap = Bitmap.createBitmap(_width, _height, Bitmap.Config.ARGB_8888);

		// textBitmap.eraseColor(0x8844ff44);
		Canvas canvas = new Canvas(textBitmap);
		Typeface typeface = Typeface.create(_fontName, Typeface.NORMAL);
		Paint textPaint = new Paint();
		setAutoTextSize(_text_size, textPaint, _txt, _width);
		textPaint.setAntiAlias(true);
		textPaint.setColor(_colorCode);
		textPaint.setShadowLayer(2f, _shadowOffsetX, _shadowOffsetY, _shadowColorCode);
		textPaint.setTypeface(typeface);
		Rect bounds = new Rect();
		textPaint.getTextBounds(_txt, 0, _txt.length(), bounds);
		float measureTxt = textPaint.measureText(_txt);
		float w = 0f, h = Math.abs(bounds.top); // 상단정렬
		// h = _height - Math.abs(bounds.bottom); //하단정렬
		if (align == -1) {
			h += (_height - h - Math.abs(bounds.bottom)) / 2;
		} else if (align == 0) {
			w = (_width - measureTxt) / 2;
			h += (_height - h - Math.abs(bounds.bottom)) / 2;
		} else if (align == 1) {
			w = _width - measureTxt;
			h += (_height - h - Math.abs(bounds.bottom)) / 2;
		}
		canvas.drawText(_txt, w, h, textPaint);

		return textBitmap;
		
	}
	
	static void setAutoTextSize(float textSize, Paint paint, String text, int width) {
		paint.setTextSize(textSize);
		float _measureSize = paint.measureText(text);
		if (_measureSize >= width) {
			setAutoTextSize(--textSize, paint, text, width);
		}
	}

	// modify lowmans -> facebook method linked JNI Function call
	private static boolean facebookIsLogin() {
		Log.d("GelatoManiaActivity", "facebookIsLogin() ret: " + fbUtil.isLogin());
		return fbUtil.isLogin();
	}

	private static void facebookLogin() {
		handler.sendEmptyMessage(0);
	}

	private static boolean facebookLogout() {
		loginMgr.logout();
		Log.d("GelatoManiaActivity", "facebookLogout() ret: " + fbUtil.isLogin());
		return fbUtil.isLogin() ? false : true;
	}

	// PlatformFacebookRequestGraphPath
	private static void facebookRequestGraphPath(int type) {
		String graphPath = "";
		if (type == 0) {
			graphPath = "me";
		} else if (type == 1) {
			graphPath = "platform/posts";
		} else {
			graphPath = "me/friends";
		}
		if (fbUtil.isLogin()) {
			fbUtil.request(graphPath, new BaseRequestListener() {
				public void onComplete(final String response, final Object state) {
					Log.d("java facebookRequestGraphPath", "Response: " + response.toString());
					nativeFacebookRequestGraphPath(response);
				}
			});
		}
	}

	// PlatformFacebookAppRequest
	private static void facebookAppRequest(String message, String to, String notification_text) {
		Bundle parameters;
		parameters = new Bundle();
		parameters.putString("message", message);
		parameters.putString("to", to);
		parameters.putString("notification_text", notification_text);

		Message msg = handler.obtainMessage();
		msg.what = 1;
		msg.setData(parameters);
		handler.sendMessage(msg);
	}

	// PlatformFacebookFeed
	private static void facebookFeed(String name, String caption, String description, String link, String picture) {
		Bundle parameters;
		parameters = new Bundle();
		parameters.putString("name", name);
		parameters.putString("caption", caption);
		parameters.putString("description", description);
		parameters.putString("link", link);
		parameters.putString("picture", picture);

		Message msg = handler.obtainMessage();
		msg.what = 2;
		msg.setData(parameters);
		handler.sendMessage(msg);

	}

	private static boolean fileCopy(String srcPath, String dstPath) {
		InputStream in = null;
		OutputStream out = null;
		boolean ret = false;
		
		try {
			in = mAsset.open(srcPath, AssetManager.ACCESS_RANDOM);
			out = new FileOutputStream(dstPath);
			copyFile(in, out);
		} catch (Exception e) {
			e.printStackTrace();
			ret = false;
		} finally {
			try {
				in.close();
				in = null;
				out.flush();
				out.close();
				out = null;
				ret = true;
			} catch (Exception e) {
				e.printStackTrace();
				ret = false;
			}
			
		}
		
		Log.d(TAG, "fileCopy() src: " + srcPath + " dst: " + dstPath +" ret: " + ret);
		
		return ret;
	}
	
	native static void nativeFacebookLogin(boolean isLogin);

	native static void nativeFacebookRequestGraphPath(String response);

	native static void nativeFacebookAppRequest(String response);

	native static void nativeFacebookFeed(String response);
}
