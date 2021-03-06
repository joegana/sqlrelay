/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_firstworks_sqlrelay_SQLRCursor */

#ifndef _Included_com_firstworks_sqlrelay_SQLRCursor
#define _Included_com_firstworks_sqlrelay_SQLRCursor
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    delete
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_delete
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    setResultSetBufferSize
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_setResultSetBufferSize
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getResultSetBufferSize
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getResultSetBufferSize
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    dontGetColumnInfo
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_dontGetColumnInfo
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnInfo
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnInfo
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    mixedCaseColumnNames
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_mixedCaseColumnNames
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    upperCaseColumnNames
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_upperCaseColumnNames
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    lowerCaseColumnNames
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_lowerCaseColumnNames
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    cacheToFile
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_cacheToFile
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    setCacheTtl
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_setCacheTtl
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getCacheFileName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getCacheFileName
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    cacheOff
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_cacheOff
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getDatabaseList
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getDatabaseList
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getTableList
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getTableList
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnList
 * Signature: (Ljava/lang/String;Ljava/lang/String)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnList
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    sendQuery
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_sendQuery__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    sendQuery
 * Signature: (Ljava/lang/String;I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_sendQuery__Ljava_lang_String_2I
  (JNIEnv *, jobject, jstring, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    sendFileQuery
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_sendFileQuery
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    prepareQuery
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_prepareQuery__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    prepareQuery
 * Signature: (Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_prepareQuery__Ljava_lang_String_2I
  (JNIEnv *, jobject, jstring, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    prepareFileQuery
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_prepareFileQuery
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    clearBinds
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_clearBinds
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    substitution
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_substitution__Ljava_lang_String_2Ljava_lang_String_2
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    substitution
 * Signature: (Ljava/lang/String;J)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_substitution__Ljava_lang_String_2J
  (JNIEnv *, jobject, jstring, jlong);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    substitution
 * Signature: (Ljava/lang/String;DII)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_substitution__Ljava_lang_String_2DII
  (JNIEnv *, jobject, jstring, jdouble, jint, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    countBindVariables
 * Signature: ()S
 */
JNIEXPORT jshort JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_countBindVariables
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    inputBind
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_inputBind__Ljava_lang_String_2Ljava_lang_String_2
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    inputBind
 * Signature: (Ljava/lang/String;Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_inputBind__Ljava_lang_String_2Ljava_lang_String_2I
  (JNIEnv *, jobject, jstring, jstring, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    inputBind
 * Signature: (Ljava/lang/String;J)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_inputBind__Ljava_lang_String_2J
  (JNIEnv *, jobject, jstring, jlong);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    inputBind
 * Signature: (Ljava/lang/String;DII)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_inputBind__Ljava_lang_String_2DII
  (JNIEnv *, jobject, jstring, jdouble, jint, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    inputBindBlob
 * Signature: (Ljava/lang/String;[BJ)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_inputBindBlob
  (JNIEnv *, jobject, jstring, jbyteArray, jlong);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    inputBindClob
 * Signature: (Ljava/lang/String;Ljava/lang/String;J)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_inputBindClob
  (JNIEnv *, jobject, jstring, jstring, jlong);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    defineOutputBindString
 * Signature: (Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_defineOutputBindString
  (JNIEnv *, jobject, jstring, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    defineOutputBindInteger
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_defineOutputBindInteger
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    defineOutputBindDouble
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_defineOutputBindDouble
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    defineOutputBindBlob
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_defineOutputBindBlob
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    defineOutputBindClob
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_defineOutputBindClob
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    defineOutputBindCursor
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_defineOutputBindCursor
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    substitutions
 * Signature: ([Ljava/lang/String;[Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_substitutions___3Ljava_lang_String_2_3Ljava_lang_String_2
  (JNIEnv *, jobject, jobjectArray, jobjectArray);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    substitutions
 * Signature: ([Ljava/lang/String;[J)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_substitutions___3Ljava_lang_String_2_3J
  (JNIEnv *, jobject, jobjectArray, jlongArray);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    substitutions
 * Signature: ([Ljava/lang/String;[D[I[I)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_substitutions___3Ljava_lang_String_2_3D_3I_3I
  (JNIEnv *, jobject, jobjectArray, jdoubleArray, jintArray, jintArray);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    inputBinds
 * Signature: ([Ljava/lang/String;[Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_inputBinds___3Ljava_lang_String_2_3Ljava_lang_String_2
  (JNIEnv *, jobject, jobjectArray, jobjectArray);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    inputBinds
 * Signature: ([Ljava/lang/String;[J)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_inputBinds___3Ljava_lang_String_2_3J
  (JNIEnv *, jobject, jobjectArray, jlongArray);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    inputBinds
 * Signature: ([Ljava/lang/String;[D[I[I)V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_inputBinds___3Ljava_lang_String_2_3D_3I_3I
  (JNIEnv *, jobject, jobjectArray, jdoubleArray, jintArray, jintArray);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    validateBinds
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_validateBinds
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    validBind
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_validBind
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    executeQuery
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_executeQuery
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    fetchFromBindCursor
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_fetchFromBindCursor
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getOutputBindString
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getOutputBindString
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getOutputBindBlob
 * Signature: (Ljava/lang/String;)LB
 */
JNIEXPORT jbyteArray JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getOutputBindBlob
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getOutputBindClob
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getOutputBindClob
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getOutputBindAsByteArray
 * Signature: (Ljava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getOutputBindAsByteArray
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getOutputBindInteger
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getOutputBindInteger
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getOutputBindDouble
 * Signature: (Ljava/lang/String;)D
 */
JNIEXPORT jdouble JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getOutputBindDouble
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getOutputBindLength
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getOutputBindLength
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    openCachedResultSet
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_openCachedResultSet
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    colCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_colCount
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    rowCount
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_rowCount
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    totalRows
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_totalRows
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    affectedRows
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_affectedRows
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    firstRowIndex
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_firstRowIndex
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    endOfResultSet
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_endOfResultSet
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    errorMessage
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_errorMessage
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getNullsAsEmptyStrings
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getNullsAsEmptyStrings
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getNullsAsNulls
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getNullsAsNulls
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getField
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getField__JI
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getField
 * Signature: (JLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getField__JLjava_lang_String_2
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getFieldAsInteger
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getFieldAsInteger__JI
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getFieldAsInteger
 * Signature: (JLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getFieldAsInteger__JLjava_lang_String_2
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getFieldAsDouble
 * Signature: (JI)D
 */
JNIEXPORT jdouble JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getFieldAsDouble__JI
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getFieldAsDouble
 * Signature: (JLjava/lang/String;)D
 */
JNIEXPORT jdouble JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getFieldAsDouble__JLjava_lang_String_2
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getFieldAsByteArray
 * Signature: (JI)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getFieldAsByteArray__JI
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getFieldAsByteArray
 * Signature: (JLjava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getFieldAsByteArray__JLjava_lang_String_2
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getFieldLength
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getFieldLength__JI
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getFieldLength
 * Signature: (JLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getFieldLength__JLjava_lang_String_2
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getRow
 * Signature: (J)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getRow
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getRowLengths
 * Signature: (J)[J
 */
JNIEXPORT jlongArray JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getRowLengths
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnNames
 * Signature: ()[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnNames
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnName
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnName
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnType
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnType__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnType
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnType__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnPrecision
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnPrecision__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnPrecision
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnPrecision__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnScale
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnScale__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnScale
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnScale__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnIsNullable
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnIsNullable__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnIsNullable
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnIsNullable__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnIsPrimaryKey
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnIsPrimaryKey__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnIsPrimaryKey
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnIsPrimaryKey__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnIsUnique
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnIsUnique__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnIsUnique
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnIsUnique__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnIsPartOfKey
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnIsPartOfKey__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnIsPartOfKey
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnIsPartOfKey__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnIsUnsigned
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnIsUnsigned__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnIsUnsigned
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnIsUnsigned__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnIsZeroFilled
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnIsZeroFilled__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnIsZeroFilled
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnIsZeroFilled__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnIsBinary
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnIsBinary__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnIsBinary
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnIsBinary__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnIsAutoIncrement
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnIsAutoIncrement__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnIsAutoIncrement
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnIsAutoIncrement__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnLength
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnLength__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getColumnLength
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getColumnLength__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getLongest
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getLongest__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getLongest
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getLongest__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    suspendResultSet
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_suspendResultSet
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getResultSetId
 * Signature: ()S
 */
JNIEXPORT jshort JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getResultSetId
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    resumeResultSet
 * Signature: (S)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_resumeResultSet
  (JNIEnv *, jobject, jshort);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    resumeCachedResultSet
 * Signature: (SLjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_resumeCachedResultSet
  (JNIEnv *, jobject, jshort, jstring);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    closeResultSet
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_closeResultSet
  (JNIEnv *, jobject);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    alloc
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_alloc
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_firstworks_sqlrelay_SQLRCursor
 * Method:    getOutputBindCursorInternal
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jlong JNICALL Java_com_firstworks_sqlrelay_SQLRCursor_getOutputBindCursorInternal
  (JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif
