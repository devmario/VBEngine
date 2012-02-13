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
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;

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
	
	static {
		System.loadLibrary("stlport_shared");
		System.loadLibrary("cocos2d");
		System.loadLibrary("cocosdenshion");
		System.loadLibrary("vanillaworld");
		System.loadLibrary("gamelogic");
	}

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// get the packageName,it's used to set the resource path
		String packageName = getApplication().getPackageName();
		super.setPackageName(packageName);

		sp = getSharedPreferences("pref", Activity.MODE_PRIVATE);
		e = sp.edit();

		if (sp.getBoolean("isFirst", true)) {
			CopyAssets();
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

//	private void CopyAssets() {
//
//		// makeDir("/sdcard/.vanillaworld/");
//		// makeDir("/sdcard/.vanillaworld/gelatomania/");
//		// makeDir("/sdcard/.vanillaworld/gelatomania/resource");
//		// makeDir("/sdcard/.vanillaworld/gelatomania/document");
//
//		makeDir("/data/data/com.vanillabreeze.gelatomania/files/");
//		makeDir("/data/data/com.vanillabreeze.gelatomania/files/resource");
//		makeDir("/data/data/com.vanillabreeze.gelatomania/files/document");
//
//		AssetManager assetManager = getAssets();
//		String[] files = null;
//		InputStream in = null;
//		OutputStream out = null;
//		try {
//			files = assetManager.list("");
//			for (String filename : files) {
//				in = assetManager.open(filename);
//				// String tmp = "/sdcard/.vanillaworld/gelatomania/resource/" + filename;
//				String tmp = "/data/data/com.vanillabreeze.gelatomania/files/resource/" + filename;
//				Log.i("#@#", tmp);
//				out = new FileOutputStream(tmp);
//				copyFile(in, out);
//			}
//		} catch (Exception e) {
//			Log.e("tag", "try : " + e.getMessage());
//		} finally {
//			try {
//				in.close();
//				out.flush();
//				out.close();
//			} catch (IOException e) {
//				Log.e("tag", "finally : " + e.getMessage());
//			}
//		}
//		
//		// 초기 한번만 실행하기 위해서 플래그 세팅
//		e.putBoolean("isFirst", false);
//	}

	
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
	
	private void copyFile(InputStream in, OutputStream out) throws IOException {
		byte[] buffer = new byte[1024];
		int read;
		while ((read = in.read(buffer)) != -1) {
			out.write(buffer, 0, read);
		}
	}

	public static Handler handler = new Handler(){
		public void handleMessage(android.os.Message msg) {
			if(msg.what == 0){
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

	private static Bitmap getTextImageWithSizeDetail(String text, int size, int width, int height) {
		Log.d("GelatoManiaActivity", "getTextImageWithSizeDetail() text: " + text + " size: " + size +" width: " + width + " height: " + height);
		
		Bitmap bm = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
        Canvas c = new Canvas(bm);
        Paint p = new Paint();
        p.setFlags(Paint.ANTI_ALIAS_FLAG);
		p.setColor(Color.WHITE);
		p.setTextSize(size);
		c.drawText(text, 50, 50, p);
		
		return bm;
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
		if(type == 0){
			graphPath = "me";
		}else if(type == 1){
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

	native static void nativeFacebookLogin(boolean isLogin);
	
	native static void nativeFacebookRequestGraphPath(String response);

	native static void nativeFacebookAppRequest(String response);

	native static void nativeFacebookFeed(String response);
}
