package com.learzhu.jniuninstall;

/**
 * JNIUninstall.java是液总汇的类。
 *
 * @author Learzhu
 * @version 2.0.0 2019-07-03 21:24
 * @update Learzhu 2019-07-03 21:24
 * @updateDes
 * @include {@link }
 * @used {@link }
 */
public class JNIUninstall {
    //定义一个方法，传递当前应用包名和当前系统版本
    public native void uninstall(String packageName, int versionCode);
}
