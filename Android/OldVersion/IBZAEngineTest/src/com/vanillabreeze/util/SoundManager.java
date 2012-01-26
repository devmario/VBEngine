package com.vanillabreeze.util;

import java.util.HashMap;

import android.content.Context;
import android.media.AudioManager;
import android.media.SoundPool;

public class SoundManager {

	private SoundPool soundPool;
	private HashMap<String, Integer> soundPoolMap;
	private AudioManager audioManager;
	private Context context;
	private String res[];

	public SoundManager(Context context) {

		this.context = context;
		// "fac1_eff", "fac2_eff","fac3_eff",
		res = new String[] { "addball_bt", "addball_eff", "cherry_eff", "clear_eff", "cream_eff", "equip_eff", "lev_sel_bt", "lev_swipe",
				"mech_eff", "menu_bt", "mixer_eff", "newball_bt", "newball_eff", "payment_eff", "pointout_eff", "recipe0_bt", "recipe1_bt",
				"refg_eff", "result_board_eff", "rightclose_eff", "rightopen_eff", "rightrec_eff", "rightrecback_eff", "rightrecswipe_eff",
				"score_count_eff", "smalltub_eff", "spoidact_eff", "spoon_eff", "sprinkle_eff", "star_eff", "text_eff", "topreclev_bt",
				"topreclev_eff", "toprecmove_eff", "tub_eff", "wrong_bt" };

		initSounds();
	}

	public void initSounds() {
		soundPool = new SoundPool(res.length, AudioManager.STREAM_MUSIC, 0);
		soundPoolMap = new HashMap<String, Integer>();
		audioManager = (AudioManager) context.getSystemService(Context.AUDIO_SERVICE);
	}

	public void addSound(String key, int SoundID) {
		soundPoolMap.put(key, soundPool.load(context, SoundID, 1));
	}

	public void addAll() {
		int index = 0;
		for (int i = 0; i < res.length; i++) {
			index = context.getResources().getIdentifier(res[i], "raw", "com.vanillabreeze.gelato");
			addSound(res[i], index);
		}
	}

	public void playSound(String key) {

		float streamCurrent = audioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
		float streamMax = audioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC);
		float streamVolume = streamCurrent / streamMax;
		soundPool.play(soundPoolMap.get(key), streamVolume, streamVolume, 1, 0, 1f);
	}

	public void playLoopedSound(int index) {

		int streamVolume = audioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
		soundPool.play(soundPoolMap.get(index), streamVolume, streamVolume, 1, -1, 1f);
	}

}