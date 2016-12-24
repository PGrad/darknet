class DarknetTest {
    static {
        System.loadLibrary("DarknetTest");
    }

    public native boolean Detect(String filename);

    public static void main(String[] args) {
        if(args.length == 1)
        	System.out.println(new DarknetTest().Detect(args[0]) ? "DETECTED" : "NOT DETECTED");
    }
}

