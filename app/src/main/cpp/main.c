#include "../../../../../../AppData/Local/Android/Sdk/ndk/21.1.6352462/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/jni.h"
#include "../../../../../../AppData/Local/Android/Sdk/ndk/21.1.6352462/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/android/log.h"
#include "../../../../../../AppData/Local/Android/Sdk/ndk/21.1.6352462/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/android/asset_manager.h"
#include "../../../../../../AppData/Local/Android/Sdk/ndk/21.1.6352462/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/android/asset_manager_jni.h"
#include "../../../../../../AppData/Local/Android/Sdk/ndk/21.1.6352462/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/stdio.h"
#include "openssl/include/openssl/aes.h"
#include "openssl/include/openssl/bio.h"
#include "openssl/include/openssl/err.h"
#include "crypto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>


/* A 256 bit key */
unsigned char *key = (unsigned char *) "01234567890123456789012345678901";

/* A 128 bit IV */
unsigned char *iv = (unsigned char *) "0123456789012345";

JNIEXPORT jbyteArray JNICALL
Java_com_samplendkapp_MainActivity_encryptFromJNI(JNIEnv *env, jobject thiz, jstring message) {

    int ciphertext_len;
/*
 * Buffer for ciphertext. Ensure the buffer is long enough for the
 * ciphertext which may be longer than the plaintext, depending on the
 * algorithm and mode.
 */
    unsigned char ciphertext[128];

    /* Message to be encrypted */
    unsigned char *plaintext = (*env)->GetStringUTFChars(env, message, 0);

    /* Encrypt the plaintext */
    ciphertext_len = encrypt(plaintext, strlen((char *) plaintext), key, iv,
                             ciphertext);
    printf("Ciphertext is:\n");
    BIO_dump_fp(stdout, (const char *) ciphertext, ciphertext_len);

    __android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "Log from main.c %s", ciphertext);

    jbyteArray array = (*env)->NewByteArray(env, ciphertext_len);
    (*env)->SetByteArrayRegion(env, array, 0, ciphertext_len, (jbyte *) (ciphertext));
    return array;

}

JNIEXPORT jstring JNICALL
Java_com_samplendkapp_MainActivity_decryptFromJNI(JNIEnv *env, jobject thiz, jbyteArray message) {

    int decryptedtext_len;

/* Buffer for the decrypted text */
    unsigned char decryptedtext[128];

    /* Message to be encrypted */
    int len = (*env)->GetArrayLength (env, message);
    unsigned char encryptedText[len];
    (*env)->GetByteArrayRegion (env, message, 0, len, (jbyte*) (encryptedText));

    __android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "Log from decrypt %s ", encryptedText);

    /* Decrypt the ciphertext */
    decryptedtext_len = decrypt(encryptedText, len, key, iv,
                                decryptedtext);

    /* Add a NULL terminator. We are expecting printable text */
    decryptedtext[decryptedtext_len] = '\0';

    return (*env)->NewStringUTF(env, decryptedtext);


}