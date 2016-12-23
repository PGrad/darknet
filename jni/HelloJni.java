class HelloJni {
    static {
        System.loadLibrary("HelloJni");
    }

    public native String getJniString();

    public static void main(String[] args) {
        System.out.println(new HelloJni().getJniString());
    }
}
