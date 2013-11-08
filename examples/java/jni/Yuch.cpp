
#include <iostream>
#include <jni.h>
#include "Yuch.h"

JNIEXPORT jint JNICALL 
Java_Yuch_quizling (JNIEnv *env, jobject)
{
  // call the krab method passing two random double values
  
  // return the results

  jint results = 2;

  return results;
}

JNIEXPORT void JNICALL
Java_Yuch_nobble (JNIEnv *env, jobject, jint count )
{
  std::cout << count << "\n";
}
