#include <string.h>
#include <jni.h>
#include <com_learzhu_jniuninstall_UninstallObserver.h>

#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <android/log.h>
#include <unistd.h>
#include <sys/inotify.h>

#define MEM_ZERO(pDest, destSize) memset(pDest, 0, destSize)
#define LOG_INFO(tag, msg) __android_log_write(ANDROID_LOG_INFO, tag, msg)
#define LOG_DEBUG(tag, msg) __android_log_write(ANDROID_LOG_DEBUG, tag, msg)
#define LOG_WARN(tag, msg) __android_log_write(ANDROID_LOG_WARN, tag, msg)
#define LOG_ERROR(tag, msg) __android_log_write(ANDROID_LOG_ERROR, tag, msg)

static char c_TAG[] = "onEvent";
static jboolean b_IS_COPY = JNI_TRUE;

JNIEXPORT jstring JNICALL Java_com_learzhu_jniuninstall_UninstallObserver_startWork(JNIEnv* env,
		jobject thiz, jstring path, jstring url, jint version) {
	jstring tag = (*env)->NewStringUTF(env, c_TAG);
	LOG_DEBUG((*env)->GetStringUTFChars(env, tag, &b_IS_COPY),
			(*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "init OK"), &b_IS_COPY));
	pid_t pid = fork();
	if (pid < 0) {
		LOG_ERROR((*env)->GetStringUTFChars(env, tag, &b_IS_COPY),
				(*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "fork failed !!!"), &b_IS_COPY));
	} else if (pid == 0) {
		int fileDescriptor = inotify_init();
		if (fileDescriptor < 0) {
			LOG_DEBUG((*env)->GetStringUTFChars(env, tag, &b_IS_COPY),
					(*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "inotify_init failed !!!"), &b_IS_COPY));

			exit(1);
		}

		int watchDescriptor;
		watchDescriptor = inotify_add_watch(fileDescriptor,
				(*env)->GetStringUTFChars(env, path, NULL), IN_DELETE);
		if (watchDescriptor < 0) {
			LOG_DEBUG((*env)->GetStringUTFChars(env, tag, &b_IS_COPY),
					(*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "inotify_add_watch failed !!!"), &b_IS_COPY));
			exit(1);
		}

		void *p_buf = malloc(sizeof(struct inotify_event));
		if (p_buf == NULL) {
			LOG_DEBUG((*env)->GetStringUTFChars(env, tag, &b_IS_COPY),
					(*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "malloc failed !!!"), &b_IS_COPY));

			exit(1);
		}

		LOG_DEBUG((*env)->GetStringUTFChars(env, tag, &b_IS_COPY),
				(*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "start observer"), &b_IS_COPY));

		size_t readBytes = read(fileDescriptor, p_buf,
				sizeof(struct inotify_event));
		free(p_buf);
		inotify_rm_watch(fileDescriptor, IN_DELETE);


		LOG_DEBUG((*env)->GetStringUTFChars(env, tag, &b_IS_COPY),
				(*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "uninstalled"), &b_IS_COPY));

		if (version >= 17) {
			execlp("am", "am", "start", "--user", "0", "-a",
					"android.intent.action.VIEW", "-d",
					(*env)->GetStringUTFChars(env, url, NULL), (char *) NULL);
		} else {
			execlp("am", "am", "start", "-a", "android.intent.action.VIEW",
					"-d", (*env)->GetStringUTFChars(env, url, NULL),
					(char *) NULL);
		}

		//处理卸载后的业务逻辑 可以发送网页请求或通过浏览器打开网页，此时可以把当前用户信息+设备信息+时间 发送到服务器上，记录当前应用卸载记录

	} else {

	}

	return (*env)->NewStringUTF(env, "Hello from JNI !");
}

