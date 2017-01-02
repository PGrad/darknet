import java.util.concurrent.atomic.AtomicInteger;
class DarknetTest {
	static {
		System.loadLibrary("DarknetTest");
	}
	public native boolean Detect(String filename);

	public static void main(String[] args) {
        	if(args.length == 1) {
			final int BUF_SZ = 3;
			DarknetTest detector = new DarknetTest();
			Runnable[] buffer = new Runnable[BUF_SZ];
			Thread[] tasks = new Thread[BUF_SZ];
			for(int detTask = 0; detTask < BUF_SZ; ++detTask) {
				final int count = counts[detTask];
				buffer[detTask]  = () -> {
				};
				
				tasks[detTask] = new Thread(buffer[detTask]);
				tasks[detTask].start();
			}
    		}
	}

}

