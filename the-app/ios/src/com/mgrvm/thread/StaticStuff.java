package com.mgrvm.thread;

import org.robovm.apple.foundation.NSObject;
import org.robovm.objc.ObjCClass;
import org.robovm.objc.ObjCRuntime;
import org.robovm.objc.annotation.Method;
import org.robovm.objc.annotation.NativeClass;
import org.robovm.rt.bro.annotation.ByVal;
import org.robovm.rt.bro.annotation.Library;

@Library(Library.INTERNAL)
@NativeClass()
public class StaticStuff extends NSObject {
	private static final ObjCClass objCClass = ObjCClass.getByType(StaticStuff.class);
	static {
		ObjCRuntime.bind(StaticStuff.class);
	}
	
	@Method(selector = "static_stuff_init")
    public static native @ByVal int static_stuff_init();
}
