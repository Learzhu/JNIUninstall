#include "unistd.h"
//定义的log 这样可以将c代码中的日志输出到控制台
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, __VA_ARGS__)
JNIEXPORT void JNICALL Java_com_learzhu_jniuninstall_JNIUninstall_uninstall
  (JNIEnv * env, jobject, jstring, jint);
   int code = fork();
   //当fork的值>=0的时候 说明fork子进程和父进程成功，可以去做判断，当然一般都是子进程成功才去判断
   //app安装之后默认目录都是   /data/data/包名
   //一个1秒定时循环去fopen这个文件夹，当文件夹不存在的时候说明APP被卸载了，
    if (code >= 0) {
        int flag = 1;
        while (flag) {
            sleep(1);
            FILE *file;
            try {
                try {
                    file = fopen("/data/data/com.learzhu.jniuninstall", "rt");
                } catch (_JNIEnv env) {
                    LOGD("--- %s", "i一场了");
                }

                if (file == NULL) {
                    flag = 0;
                    if (versionCode < 17) {
                        execlp("am", "am", "start", "-a", "android.intent.action.VIEW", "-d",
                               "http://baidu.com", NULL);
                    } else {
                        execlp("am", "am", "start", "--user", "0", "-a",
                               "android.intent.action.VIEW",
                               "-d", "http://baidu.com", (char *) NULL);
                    }
                } else {
                    fclose(file);
                    LOGD("---%s", "我还在");
                }
  };
