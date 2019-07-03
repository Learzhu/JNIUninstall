package com.learzhu.jniuninstall;

/**
 * UninstallObserver.java是监听卸载动作的类。
 *
 * @author Learzhu
 * @version 2.0.0 2019-07-03 22:33
 * @update Learzhu 2019-07-03 22:33
 * @updateDes
 * @include {@link }
 * @used {@link }
 */
public class UninstallObserver {
    static {
        System.loadLibrary("UninstallObserver");
    }

    public static native String startWork(String path, String url, int version);
}
