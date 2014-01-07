package soft.rw.service;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Collections;
import java.util.Date;
import java.util.List;
import java.util.Locale;

import soft.rw.tool.l;
import android.app.Service;
import android.app.WallpaperManager;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.IBinder;

public class RealtimeWallpaper extends Service {
    private static final String HOST = "192.168.0.100";
    private static final int PORT = 9123;
    private static final int FLAG = 2;
    private static final int SUCCESS = 0;
    private static final int FAILURE = 1;
    private static final int DELAY = 5;
    
    private Thread thread = null;
    private volatile boolean run = false;
    
    private String host = null;
    
    @Override
    public void onCreate() {
        super.onCreate();
        l.og("oncreate");
        
        /*
        Drawable drawable = getResources().getDrawable(R.drawable.ic_launcher);
        
        WallpaperManager wm = WallpaperManager.getInstance(this);
        BitmapDrawable bd = (BitmapDrawable)drawable;
        Bitmap bitmap = bd.getBitmap();
        try {
            wm.setBitmap(bitmap);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }*/
    }
    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        l.og("onstartcommand");
        
        host = intent.getStringExtra("HOST");
        l.og(host);
        if (host == null || host.trim().length() == 0) host = HOST;
        l.og(host);
        
        if (thread == null || thread.isAlive() == false) {
            thread = new ServiceThread();
            thread.start();
        }
        
        return super.onStartCommand(intent, flags, startId);
    }
    @Override
    public void onDestroy() {
        super.onDestroy();
        
        run = false;
        try {
            thread.join(5000);
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        
        l.og("ondestroy");
    }
    @Override
    public IBinder onBind(Intent intent) {
        l.og("onbind");
        return null;
    }
    @Override
    public void onRebind(Intent intent) {
        l.og("onrebind");
        super.onRebind(intent);
    }
    @Override
    public boolean onUnbind(Intent intent) {
        l.og("onunbind");
        return super.onUnbind(intent);
    }
    private class ServiceThread extends Thread {
        @Override
        public void run() {
            run = true;
            int delay = DELAY;
            while (run) {
                l.og(new SimpleDateFormat("yyyy-MM-dd HH:mm:ss", Locale.US).format(new Date()));
                
                delay++;
                if (delay > DELAY) {
                    delay = 0;
                    try {
                        Socket socket = new Socket(host, PORT);
                        l.og("connected");
                        
                        OutputStream os = socket.getOutputStream();
                        
                        l.og("send", FLAG);
                        os.write(FLAG);
                        os.flush();
                        
                        InputStream is = socket.getInputStream();
                        Byte[] buffer1 = new Byte[Integer.SIZE / Byte.SIZE];
                        l.og(Arrays.toString(buffer1));
                        for (int i=0, max=buffer1.length; i<max; i++) buffer1[i] = (byte)is.read();
                        l.og(Arrays.toString(buffer1));
                        List<Byte> list = Arrays.asList(buffer1);
                        Collections.reverse(list);
                        l.og(Arrays.toString(buffer1));
                        byte[] buffer2 = new byte[buffer1.length];
                        l.og(Arrays.toString(buffer2));
                        for (int i=0, max=buffer1.length; i<max; i++) buffer2[i] = buffer1[i];
                        l.og(Arrays.toString(buffer2));
                        ByteBuffer bb = ByteBuffer.wrap(buffer2);
                        int size = bb.getInt();
                        l.og(size);
                        
                        buffer2 = new byte[size];
                        int r = 0, count = 0;
                        while (true) {
                            r = is.read(buffer2, count, size-count);
                            count += r;
                            l.og(r, count);
                            if (r < 0 || count >= size) break;
                        }
                        
                        os.write(SUCCESS);
                        os.flush();
                        
                        os.close();
                        is.close();
                        socket.close();
                        
                        Bitmap bitmap = BitmapFactory.decodeByteArray(buffer2, 0, buffer2.length);
                        l.og(bitmap);
                        WallpaperManager wm = WallpaperManager.getInstance(RealtimeWallpaper.this);
                        if (bitmap != null) {
                            try {
                                wm.setBitmap(bitmap);
                            } catch (IOException e) {
                                l.og(e.getClass().getName(), e.getMessage());
                                // TODO Auto-generated catch block
//                                e.printStackTrace();
                            }
                        }
                    } catch (UnknownHostException e) {
                        // TODO Auto-generated catch block
                        l.og(e.getClass().getName(), e.getMessage());
//                        e.printStackTrace();
                    } catch (IOException e) {
                        // TODO Auto-generated catch block
                        l.og(e.getClass().getName(), e.getMessage());
//                        e.printStackTrace();
                    }
                }
                
                try { Thread.sleep(1000); } catch (InterruptedException e) { }
            }
        }
    }
}