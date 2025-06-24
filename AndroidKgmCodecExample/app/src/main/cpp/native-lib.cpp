#include <jni.h>
#include <string>
#include <string>
#include "KgmCodec.h"
#include "KgmUtils.h"

extern "C" JNIEXPORT jstring

JNICALL
Java_cn_thinkbit_androidkgmcodecexample_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

/**
 * 这里应该在子线程中操作，demo 就不处理了
 */
extern "C"
JNIEXPORT jint JNICALL
Java_cn_thinkbit_androidkgmcodecexample_MainActivity_decodeKgm(JNIEnv *env, jobject thiz,
                                                               jstring jinput_path,
                                                               jstring joutput_path) {

    char *input_path = const_cast<char *>(env->GetStringUTFChars(jinput_path, NULL));
    char *output_path = const_cast<char *>(env->GetStringUTFChars(joutput_path, NULL));
    KgmCodec *kgmCodec = new KgmCodec();


    DecodeResult *result = kgmCodec->decodeKgm(input_path);

    char out[50] = "";

    strcpy(out,output_path);

    strcat(out, result->ext);

    writeFile(out, result->data);


    env->ReleaseStringUTFChars(jinput_path, input_path);
    env->ReleaseStringUTFChars(joutput_path, output_path);
    delete result;
    delete kgmCodec;
    kgmCodec = nullptr;
    result = nullptr;
    return 1;
}