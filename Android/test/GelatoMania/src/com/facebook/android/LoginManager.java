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

import android.app.Activity;
import android.os.Bundle;

import com.facebook.android.Facebook.DialogListener;
import com.facebook.android.SessionEvents.AuthListener;
import com.facebook.android.SessionEvents.LogoutListener;

public class LoginManager {

	private Facebook mFb;
	private SessionListener mSessionListener = new SessionListener();
	private String[] mPermissions;
	private Activity mActivity;


	public LoginManager(final Activity activity, final Facebook fb) {
		init(activity, fb, new String[] {});
	}

	public void init(final Activity activity, final Facebook fb, final String[] permissions) {
		mActivity = activity;
		mFb = fb;
		mPermissions = permissions;

		SessionEvents.addAuthListener(mSessionListener);
		SessionEvents.addLogoutListener(mSessionListener);
	}

	public void login(BaseDialogListener listener) {
		if (!mFb.isSessionValid()) {
			mFb.authorize(mActivity, mPermissions, listener);
		}
	}
	
	public void logout() {
		if (mFb.isSessionValid()) {
			SessionEvents.onLogoutBegin();
			AsyncFacebookRunner asyncRunner = new AsyncFacebookRunner(mFb);
			asyncRunner.logout(mActivity, new LogoutRequestListener());
		} 
	}

	class LoginDialogListener implements DialogListener {
		public void onComplete(Bundle values) {
			SessionEvents.onLoginSuccess();
		}

		public void onFacebookError(FacebookError error) {
			SessionEvents.onLoginError(error.getMessage());
		}

		public void onError(DialogError error) {
			SessionEvents.onLoginError(error.getMessage());
		}

		public void onCancel() {
			SessionEvents.onLoginError("Action Canceled");
		}
	}

	class LogoutRequestListener extends BaseRequestListener {
		public void onComplete(String response, final Object state) {
			SessionEvents.onLogoutFinish();
		}
	}

	class SessionListener implements AuthListener, LogoutListener {

		public void onAuthSucceed() {
			SessionStore.save(mFb, mActivity);
		}

		public void onAuthFail(String error) {
		}

		public void onLogoutBegin() {
		}

		public void onLogoutFinish() {
			SessionStore.clear(mActivity);
		}
	}

}
