package com.mgrvm.thread;

import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

import org.robovm.apple.foundation.NSAutoreleasePool;
import org.robovm.apple.uikit.UIApplication;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.backends.iosrobovm.IOSApplication;
import com.badlogic.gdx.backends.iosrobovm.IOSApplicationConfiguration;
import com.mgrvm.thread.MgrvmThreadGame;

public class IOSLauncher extends IOSApplication.Delegate {
	
	private Backend backend;
	private int count1 = 0;
	
    @Override
    protected IOSApplication createApplication() {
        IOSApplicationConfiguration config = new IOSApplicationConfiguration();
        MgrvmThreadGame theGame = new MgrvmThreadGame();
        backend = new Backend();
        Backend.clsInit();
        backend.start();
        
        ScheduledExecutorService ses = Executors.newSingleThreadScheduledExecutor();
		ses.scheduleAtFixedRate(new Runnable() {
		    @Override
		    public void run() {
		    	Gdx.app.log ("IOSApplication", "IOSApplication step " + (++count1));
		    }
		}, 1, 1, TimeUnit.SECONDS);
		
        return new IOSApplication(theGame, config);
    }

    public static void main(String[] argv) {
        NSAutoreleasePool pool = new NSAutoreleasePool();
        UIApplication.main(argv, null, IOSLauncher.class);
        pool.close();
    }
    
    static {
    	StaticStuff.static_stuff_init();
    }
}