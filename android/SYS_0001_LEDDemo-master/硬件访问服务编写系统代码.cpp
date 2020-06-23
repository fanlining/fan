1  写一个 ADLE文件 定义接口
2  然后编译生成 java 的  interface接口
3  然后新建一个class文件 继承 interface接口
   新的class  继承的 是  interface接口的  stub类
   
   注意 这个服务类 是干啥用的？ 调用  native c function 控制硬件的！
   /* call native c function to access hardware */
   
4   这个服务类要实现   ADLE文件定义的接口（也就是 interface接口的  stub类得方法了）
    实现得这个服务类方法  要调用 c库

public class LedService extends ILedService.Stub {
    private static final String TAG = "LedService";

	/* call native c function to access hardware */
	public int ledCtrl(int which, int status) throws android.os.RemoteException
	{
		return native_ledCtrl(which, status);
	}

	public LedService() {
		native_ledOpen();
	}

	public static native int native_ledOpen();
	public static native void native_ledClose();
	public static native int native_ledCtrl(int which, int status);
}

5  在  SystemServer.java  文件中添加

            Slog.i(TAG, "Led Service");
            ServiceManager.addService("led", new LedService());
			
6   在  SystemServer.java  文件中  会加载c库

	System.loadLibrary("android_servers");
	
7	android_servers 这个库  是  onload.cpp 生成得！

8    onload.cpp 中添加 如下

int register_android_server_LedService(JNIEnv *env);
调用得是 com_android_server_LedService.cpp 文件得函数

9   SystemServer.java  会注册到 servicemanager.c 中  
