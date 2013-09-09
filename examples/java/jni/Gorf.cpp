
#include <iostream>
#include <jni.h>

#include "JNIutils.h"

#include "Gorf.h"

JNIEXPORT jint JNICALL
Java_Gorf_kazz (JNIEnv *env, jobject obj, jint x )
{
  // compute return value
  jint y;
  if ( ! utils::jni::getJniFieldValue( env, obj, "val", y ) ) {
    return -1;
  }

  jdouble z;
  if ( ! utils::jni::getJniFieldValue( env, obj, "ddd", z ) ) {
    return -1;
  }

  std::cerr << z << "\n"; 
  
  return x * y;
}
