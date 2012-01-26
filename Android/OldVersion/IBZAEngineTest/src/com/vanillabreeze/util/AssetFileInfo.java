package com.vanillabreeze.util;

import java.io.FileDescriptor;

public class AssetFileInfo {
	public String path;
	public FileDescriptor fd;
	public int off;
	public int leng;

	public AssetFileInfo() {
	}

	public AssetFileInfo(String path, FileDescriptor fd, int off, int leng) {
		this.path = path;
		this.fd = fd;
		this.off = off;
		this.leng = leng;
	}
}
