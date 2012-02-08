/*
 * Copyright 2010 Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.facebook.android;

import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

import android.content.Context;
import android.os.Bundle;
import android.util.Log;

import com.facebook.android.AsyncFacebookRunner.RequestListener;
import com.facebook.android.SessionEvents.AuthListener;
import com.facebook.android.SessionEvents.LogoutListener;

public class FacebookUtil {

	public static final String TAG = "";
	public static final String APP_ID = "243309602411008";
	public static Facebook mFacebook;
	public AsyncFacebookRunner mAsyncRunner;

	// private static FacebookUtil instance;

	/** Called when the activity is first created. */

	// public static FacebookUtil getInstance(Context context) {
	// if (instance == null) {
	// instance = new FacebookUtil(context);
	// }
	// return instance;
	// }

	public FacebookUtil(Context context) {

		mFacebook = new Facebook(APP_ID);
		mAsyncRunner = new AsyncFacebookRunner(mFacebook);

		SessionStore.restore(mFacebook, context);
		SessionEvents.addAuthListener(new FBAuthListener());
		SessionEvents.addLogoutListener(new FBLogoutListener());

	}

	public boolean isLogin() {
		return mFacebook.isSessionValid();
	}

	public void request(String request, BaseRequestListener listener) {
		mAsyncRunner.request(request, listener);
	}

	public void request(Bundle parameters, RequestListener listener) {
		mAsyncRunner.request(parameters, listener);
	}

	public void request(String graphPath, Bundle parameters, RequestListener listener) {
		mAsyncRunner.request(graphPath, parameters, listener);
	}

	public void request(String graphPath, Bundle parameters, String httpMethod, RequestListener listener) {
		mAsyncRunner.request(graphPath, parameters, httpMethod, listener, null);
	}

	public void update(String request, BaseRequestListener listener) {
		Bundle params = new Bundle();
		params.putString("method", "photos.upload");

		URL uploadFileUrl = null;
		try {
			uploadFileUrl = new URL("http://www.facebook.com/images/devsite/iphone_connect_btn.jpg");
		} catch (MalformedURLException e) {
			e.printStackTrace();
		}
		try {
			HttpURLConnection conn = (HttpURLConnection) uploadFileUrl.openConnection();
			conn.setDoInput(true);
			conn.connect();
			int length = conn.getContentLength();

			byte[] imgData = new byte[length];
			InputStream is = conn.getInputStream();
			is.read(imgData);
			params.putByteArray("picture", imgData);

		} catch (IOException e) {
			e.printStackTrace();
		}

		mAsyncRunner.request(null, params, "POST", listener, null);
	}

	public class FBAuthListener implements AuthListener {

		public void onAuthSucceed() {
		}

		public void onAuthFail(String error) {
			Log.e(TAG, "Login Failed: " + error);
		}
	}

	public class FBLogoutListener implements LogoutListener {
		public void onLogoutBegin() {
			Log.e(TAG, "Logging out...");
		}

		public void onLogoutFinish() {
			Log.e(TAG, "You have logged out! ");
		}
	}
}
