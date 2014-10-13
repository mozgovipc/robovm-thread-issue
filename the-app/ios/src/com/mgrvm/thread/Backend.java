package com.mgrvm.thread;

import java.text.SimpleDateFormat;
import java.util.Date;

public class Backend {
	
	public static native boolean clsInit();
	public native void start();
	
	public void main_thread_send1(int param1) {
		System.out.println(String.format("%s: Backend => main_thread_send1 %d", new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS").format(new Date()), param1));
	}
	
}
