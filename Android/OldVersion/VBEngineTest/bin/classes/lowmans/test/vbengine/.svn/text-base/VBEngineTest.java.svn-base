package lowmans.test.vbengine;

import android.app.Activity;
import android.app.ProgressDialog;
import android.os.Bundle;
import android.util.Log;

public class VBEngineTest extends Activity {

	//private static final String TAG = "VBEngineTest";
	private VBGLSurfaceView mGLView;
	private static ProgressDialog dialog;
	static {
		System.loadLibrary("VBEngine");
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		dialog = new ProgressDialog(this);
		dialog.setMessage("Please wait while loading...");
		//dialog.setIndeterminate(true);
		dialog.setCancelable(true);
		dialog.show();
		
		mGLView = new VBGLSurfaceView(this);
		setContentView(mGLView);
		
	}

	@Override
	protected void onPause() {
		//Log.i(TAG , "onPause()");
		mGLView.onPause();
		super.onPause();
	}

	@Override
	protected void onResume() {
		//Log.i(TAG , "onResume()");
		mGLView.onResume();
		super.onResume();
	}

	@Override
	protected void onDestroy() {
		//Log.i(TAG , "onDestroy()");
		mGLView.onDestroy();
		super.onDestroy();
	}
	
	public static void dismissDialog(){
		//Log.i(TAG , "dismissDialog()");
		if(dialog != null && dialog.isShowing()){	
			dialog.dismiss();
			dialog = null;
		}
	}
}