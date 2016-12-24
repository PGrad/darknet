class HelloJni {
    static {
        System.loadLibrary("HelloJni");
    }

    public native void getJniString(String greeting);

    public static void main(String[] args) {
        new HelloJni().getJniString("Hello");
    }
}
