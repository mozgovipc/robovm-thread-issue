//
//  backend.c
//  rvm-thread
//
//  Created by Vladimir Caruntu on 11/10/14.
//  Copyright (c) 2014 Vladimir Caruntu. All rights reserved.
//

#include "backend.h"
#include "jni.h"
#include "robovm.h"
#include "robovm/exception.h"
#include "robovm/method.h"
#include <unistd.h>

static JavaVM *java_vm;
static pthread_t the_main_thread;

static jobject the_instance;

static jmethodID main_thread_send1_method_id;

static JNIEnv *
attach_thread(void) {
    JNIEnv *env;
    JavaVMAttachArgs args;
    
    args.version = JNI_VERSION_1_4;
    args.name = "main-thread";
    args.group = NULL;
    
    if ((*java_vm)->AttachCurrentThread(java_vm, &env, &args) < 0) {
        printf ("attach_thread fail!!!\n");
        return NULL;
    }
    return env;
}

void
detach_thread (void *env) {
    (*java_vm)->DetachCurrentThread (java_vm);
}

static void
main_send1 (int data1) {
    JNIEnv *env = attach_thread ();
    (*env)->CallVoidMethod (env, the_instance, main_thread_send1_method_id, data1);
    detach_thread (env);
}

static jint main_send1_count = 0;

static void *
main_thread () {
    printf ("main_thread starting...\n");
    while (1) {
        usleep (500);
        //printf ("main_thread exec\n");
        for (int i=0; i<20; i++)
            main_send1 (++main_send1_count);
    }
    printf ("main_thread exited\n");
    return NULL;
}

JNIEXPORT void JNICALL
Java_com_mgrvm_thread_Backend_start (JNIEnv* env, jobject thiz) {
    printf ("start\n");
    the_instance = (*env)->NewGlobalRef(env, thiz);
    pthread_create(&the_main_thread, NULL, &main_thread, NULL);
    printf ("start OK\n");
}

JNIEXPORT jboolean JNICALL
Java_com_mgrvm_thread_Backend_clsInit (JNIEnv* env, jclass klass) {
    
    jint ret = (*env)->GetJavaVM(env, &java_vm);
    printf ("GetJavaVM = %d, vm=%p\n", ret, java_vm);
    
    main_thread_send1_method_id = (*env)->GetMethodID(env, klass, "main_thread_send1", "(I)V");
    
    printf ("clsInit ready\n");
    
    return JNI_TRUE;
}
