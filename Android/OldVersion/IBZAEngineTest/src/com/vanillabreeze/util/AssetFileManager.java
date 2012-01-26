package com.vanillabreeze.util;

import java.io.FileDescriptor;
import java.io.IOException;
import java.util.ArrayList;

import android.content.Context;
import android.content.res.AssetFileDescriptor;

public class AssetFileManager {

	private Context context;

	public String[] pathArray;
	public FileDescriptor[] fdArray;
	public long[] offArray;
	public long[] lengArray;

	public AssetFileManager(Context context) {
		this.context = context;
		initData();

	}

	private void initData() {
		ArrayList<AssetFileInfo> assetFiles = new ArrayList<AssetFileInfo>();
		try {
			String[] fds = context.getApplicationContext().getAssets().list("");
			for (String path : fds) {
				if (!path.contains(".png") && !path.contains(".mp3"))
					continue;

				AssetFileDescriptor afd = context.getApplicationContext().getAssets().openFd(path);
				FileDescriptor fd = afd.getFileDescriptor();
				fd.sync();
				// Log.v("result", "first send loop fd.valid():" + fd.valid());
				int off = (int) afd.getStartOffset();
				int leng = (int) afd.getLength();

				// Log.v("__test", fd + " in off:" + off + ", leng:" + leng);
				assetFiles.add(new AssetFileInfo(path, fd, off, leng));
			}

			int size = assetFiles.size();
			if (size > 0) {
				pathArray = new String[size];
				fdArray = new FileDescriptor[size];
				offArray = new long[size];
				lengArray = new long[size];

				for (int i = 0; i < size; i++) {
					AssetFileInfo fileInfo = (AssetFileInfo) assetFiles.get(i);
					pathArray[i] = fileInfo.path;
					fdArray[i] = fileInfo.fd;
					offArray[i] = fileInfo.off;
					lengArray[i] = fileInfo.leng;
				}
			}
		} catch (IOException e) {
		}
	}
}
