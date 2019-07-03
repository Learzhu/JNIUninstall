package com.learzhu.jniuninstall;

import android.util.Log;

/**
 * JNITest.java是用于测试JNI的类。
 *
 * @author Learzhu
 * @version 2.0.0 2019-07-03 15:37
 * @update Learzhu 2019-07-03 15:37
 * @updateDes
 * @include {@link }
 * @used {@link }
 * <p>
 * javac 的Tools设置args -encoding utf-8 -classpath $ClipboardContent$  $FilePath$
 */
public class JNITest {
    static {
        System.loadLibrary("JniLib");
    }

    public native String getString();

    /**
     * 尝试C调用Java啊
     * @param i
     * @param j
     * @return
     */
    public int sum(int i, int j) {
        Log.d("---", "我是java 我被C调用了" + (i + j));
        return i + j;
    }

    /**
     * C调用Java肯定要Java调用C的某个方法，在这个方法中调用java方法
     */
    public native String testHello();

    //定义一个方法，传递当前应用包名和当前系统版本
    public native void uninstall(String packageName, int versionCode);
}
