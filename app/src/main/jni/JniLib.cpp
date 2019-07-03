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





