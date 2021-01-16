#pragma once
#include<jni.h>

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL Java_org_artcompany_clock_NativeHelper_invokeVoidMethod
  (JNIEnv *, jclass, jint);

#ifdef __cplusplus
}
#endif
