#include <com_learzhu_jniuninstall_JNITest.h>
#include<stdio.h>
#include "unistd.h"
/*
 * Class:     com_learzhu_jniuninstall_JNITest
 * Method:    getString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_learzhu_jniuninstall_JNITest_getString
  (JNIEnv * env, jobject jobject){
  return  (*env).NewStringUTF("成功调用JNI内容");
  }

//默认生成的C方法为
JNIEXPORT jstring JNICALL Java_com_learzhu_jniuninstall_JNITest_testHello
    (JNIEnv *env, jobject){
    //调用的java方法在JNI类中，想想java可以通过反射来调用另一个类的方法，那么C其实也是通过反射的，首先我们定义要调用方法的路径，JNI类全路径为jnidemo.hlq.com.jnidemo.JNI，在C中将.替换为/
    const char *className = "com/learzhu/jniuninstall/JNITest";
    //方法名为sum
    const char *sum = "sum";
    //通过findClass获取class对象，然后通过AllocObject获取类的实例
    jclass jclass1 = env->FindClass(className);
    jobject jobject1 = env->AllocObject(jclass1);
    //然后我们获取到要调用方法的methodId
    //第一个参数是class对象，第二个参数是函数名，第三个参数是方法签名
    jmethodID jmethodID1 = env->GetMethodID(jclass1, sum,"(II)I");

    //复制项目app\build\intermediates\classes\debug文件路径，打开cmd，进入路径，（如果之前没有编译过项目记得先编译一下，这样才能获取class文件），使用命令 javap -s jnidemo.hlq.com.jnidemo.JNI jnidemo.hlq.com.jnidemo.JNI是调用方法的全路径。
    //获取到方法的jmethodID1之后调用CallIntMethod即可调用方法
    jint value = env->CallIntMethod(jobject1, jmethodID1,1,2);

    printf("c 运行结果为 %d",value);
    return (env)->NewStringUTF("huanglinqing");
    };

    //用于卸载的方法
#include "unistd.h"
//定义的log 这样可以将c代码中的日志输出到控制台
#include <android/log.h>
#define LOG_TAG "System.out"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
JNIEXPORT void JNICALL Java_com_learzhu_jniuninstall_JNITest_uninstall
  (JNIEnv * env, jobject, jstring jstring, jint versionCode){
   int code = fork();
   //当fork的值>=0的时候 说明fork子进程和父进程成功，可以去做判断，当然一般都是子进程成功才去判断
   //app安装之后默认目录都是   /data/data/包名
   //一个1秒定时循环去fopen这个文件夹，当文件夹不存在的时候说明APP被卸载了，
   // error: cannot use 'try' with exceptions disabled  在Application.mk   APP_CPPFLAGS += -fexceptions
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
             }
             catch (_JNIEnv env) {
                                 LOGD("--- %s", "i一场了");
                             }
        }
    }
}



