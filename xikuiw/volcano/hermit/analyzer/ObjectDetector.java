package xikuiw.volcano.hermit.analyzer;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;
class ObjectDetector {
	static {
		System.loadLibrary("ObjectDetector");
	}
	public native int[][] GetDarknetObjectBounds(String filename);
	private static final ScheduledExecutorService ses = Executors.newScheduledThreadPool(5);
	private static int count = 0;	
	public static void main(String[] args) {	
		if(args.length == 1) {         
		    Runnable nana = new Detector(args[0]);
		    ScheduledFuture sfa = ses.scheduleAtFixedRate(nana, 0, 5000, TimeUnit.MILLISECONDS);
		}
	}
	static class Detector implements Runnable {
		final ObjectDetector detector = new ObjectDetector();
		int[][] rects;
		String filename;
		public Detector(String filename) {
			this.filename = filename;
		}
		public void run() {
			rects = detector.GetDarknetObjectBounds(filename);
			if(rects != null) {
				for(int i = 0; i < rects.length; ++i)
					for(int j = 0; j < rects[i].length; ++j)
						System.out.println(rects[i][j]);
			}
			System.out.println(count++);
		}
	}
}

