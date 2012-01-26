package com.vanillabreeze.util;

import android.content.Context;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.util.Log;

public class MusicManager {
	private static final String TAG = "MusicManager";
	private MediaPlayer mediaPlayer;
	private Context context;

	private String current = "";

	public MusicManager(Context context) {
		this.context = context;
		// mediaPlayer = new MediaPlayer();
	}

	public boolean loadAudio(String res) {
		if (res.compareTo(current) == 0) {
			// Log.e(TAG, "data compare to same");
			return false;
		}

		if (mediaPlayer != null) {
			if (mediaPlayer.isPlaying()) {
				mediaPlayer.stop();
			}
			mediaPlayer.release();
		}

		try {
			// mediaPlayer.setDataSource(path);
			int index = context.getResources().getIdentifier(res, "raw", "com.vanillabreeze.gelato");
			mediaPlayer = MediaPlayer.create(context, index);
			// mediaPlayer.prepareAsync();
			mediaPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);
			mediaPlayer.setLooping(true);
			current = res;
			return true;
		} catch (Exception e) {
			Log.e(TAG, "loadAudio : " + e.getMessage());
			return false;
		}
	}

	public void playMusic(String code) {
		if (loadAudio(code)) {
			if (!mediaPlayer.isPlaying()) {
				try {
					mediaPlayer.start();
				} catch (IllegalStateException e) {
					Log.e(TAG, "playMusic : " + e.getMessage());
				}
			}
		} else {
			startMusic();
		}
	}

	public void pauseMusic() {

		if (mediaPlayer != null && mediaPlayer.isPlaying()) {
			mediaPlayer.pause();
		}
	}

	public void startMusic() {
		if (mediaPlayer != null && !mediaPlayer.isPlaying()) {
			mediaPlayer.start();
		}
	}

	public void stopMusic() {
		if (mediaPlayer == null) {
			return;
		}
		if (mediaPlayer.isPlaying()) {
			mediaPlayer.stop();
		}
		mediaPlayer.reset();
	}

	public void releaseMusic() {
		if (mediaPlayer != null) {
			if (mediaPlayer.isPlaying()) {
				mediaPlayer.stop();
			}
			mediaPlayer.release();
		}
	}
}
