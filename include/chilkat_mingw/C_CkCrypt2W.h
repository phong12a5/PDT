// This is a generated source file for Chilkat version 9.5.0.79
#ifndef _C_CkCrypt2WH
#define _C_CkCrypt2WH
#include "chilkatDefs.h"

#include "Chilkat_C.h"


CK_VISIBLE_PUBLIC void CkCrypt2W_setAbortCheck(HCkCrypt2W cHandle, BOOL (*fnAbortCheck)(void));
CK_VISIBLE_PUBLIC void CkCrypt2W_setPercentDone(HCkCrypt2W cHandle, BOOL (*fnPercentDone)(int pctDone));
CK_VISIBLE_PUBLIC void CkCrypt2W_setProgressInfo(HCkCrypt2W cHandle, void (*fnProgressInfo)(const wchar_t *name, const wchar_t *value));
CK_VISIBLE_PUBLIC void CkCrypt2W_setTaskCompleted(HCkCrypt2W cHandle, void (*fnTaskCompleted)(HCkTaskW hTask));

CK_VISIBLE_PUBLIC HCkCrypt2W CkCrypt2W_Create(void);
CK_VISIBLE_PUBLIC void CkCrypt2W_Dispose(HCkCrypt2W handle);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_getAbortCurrent(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putAbortCurrent(HCkCrypt2W cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkCrypt2W_getBCryptWorkFactor(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putBCryptWorkFactor(HCkCrypt2W cHandle, int newVal);
CK_VISIBLE_PUBLIC int CkCrypt2W_getBlockSize(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_getCadesEnabled(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putCadesEnabled(HCkCrypt2W cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkCrypt2W_getCadesSigPolicyHash(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putCadesSigPolicyHash(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_cadesSigPolicyHash(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void CkCrypt2W_getCadesSigPolicyId(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putCadesSigPolicyId(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_cadesSigPolicyId(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void CkCrypt2W_getCadesSigPolicyUri(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putCadesSigPolicyUri(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_cadesSigPolicyUri(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void CkCrypt2W_getCharset(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putCharset(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_charset(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void CkCrypt2W_getCipherMode(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putCipherMode(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_cipherMode(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void CkCrypt2W_getCmsOptions(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putCmsOptions(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_cmsOptions(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void CkCrypt2W_getCompressionAlgorithm(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putCompressionAlgorithm(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_compressionAlgorithm(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void CkCrypt2W_getCryptAlgorithm(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putCryptAlgorithm(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_cryptAlgorithm(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void CkCrypt2W_getDebugLogFilePath(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putDebugLogFilePath(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_debugLogFilePath(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void CkCrypt2W_getEncodingMode(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putEncodingMode(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_encodingMode(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_getFirstChunk(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putFirstChunk(HCkCrypt2W cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkCrypt2W_getHashAlgorithm(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putHashAlgorithm(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_hashAlgorithm(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC int CkCrypt2W_getHavalRounds(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putHavalRounds(HCkCrypt2W cHandle, int newVal);
CK_VISIBLE_PUBLIC int CkCrypt2W_getHeartbeatMs(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putHeartbeatMs(HCkCrypt2W cHandle, int newVal);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_getIncludeCertChain(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putIncludeCertChain(HCkCrypt2W cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkCrypt2W_getInitialCount(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putInitialCount(HCkCrypt2W cHandle, int newVal);
CK_VISIBLE_PUBLIC int CkCrypt2W_getIterationCount(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putIterationCount(HCkCrypt2W cHandle, int newVal);
CK_VISIBLE_PUBLIC void CkCrypt2W_getIV(HCkCrypt2W cHandle, HCkByteData retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putIV(HCkCrypt2W cHandle, HCkByteData newVal);
CK_VISIBLE_PUBLIC int CkCrypt2W_getKeyLength(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putKeyLength(HCkCrypt2W cHandle, int newVal);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_getLastChunk(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putLastChunk(HCkCrypt2W cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkCrypt2W_getLastErrorHtml(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_lastErrorHtml(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void CkCrypt2W_getLastErrorText(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_lastErrorText(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void CkCrypt2W_getLastErrorXml(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_lastErrorXml(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_getLastMethodSuccess(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putLastMethodSuccess(HCkCrypt2W cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkCrypt2W_getMacAlgorithm(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putMacAlgorithm(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_macAlgorithm(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC int CkCrypt2W_getNumSignerCerts(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void CkCrypt2W_getOaepHash(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putOaepHash(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_oaepHash(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void CkCrypt2W_getOaepMgfHash(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putOaepMgfHash(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_oaepMgfHash(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_getOaepPadding(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putOaepPadding(HCkCrypt2W cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkCrypt2W_getPaddingScheme(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putPaddingScheme(HCkCrypt2W cHandle, int newVal);
CK_VISIBLE_PUBLIC void CkCrypt2W_getPbesAlgorithm(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putPbesAlgorithm(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_pbesAlgorithm(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void CkCrypt2W_getPbesPassword(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putPbesPassword(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_pbesPassword(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void CkCrypt2W_getPkcs7CryptAlg(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putPkcs7CryptAlg(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_pkcs7CryptAlg(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC int CkCrypt2W_getRc2EffectiveKeyLength(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putRc2EffectiveKeyLength(HCkCrypt2W cHandle, int newVal);
CK_VISIBLE_PUBLIC void CkCrypt2W_getSalt(HCkCrypt2W cHandle, HCkByteData retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putSalt(HCkCrypt2W cHandle, HCkByteData newVal);
CK_VISIBLE_PUBLIC void CkCrypt2W_getSecretKey(HCkCrypt2W cHandle, HCkByteData retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putSecretKey(HCkCrypt2W cHandle, HCkByteData newVal);
CK_VISIBLE_PUBLIC void CkCrypt2W_getSigningAlg(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putSigningAlg(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_signingAlg(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void CkCrypt2W_getSigningAttributes(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putSigningAttributes(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_signingAttributes(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void CkCrypt2W_getUuFilename(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putUuFilename(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_uuFilename(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void CkCrypt2W_getUuMode(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putUuMode(HCkCrypt2W cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_uuMode(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_getVerboseLogging(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void  CkCrypt2W_putVerboseLogging(HCkCrypt2W cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkCrypt2W_getVersion(HCkCrypt2W cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_version(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void CkCrypt2W_AddEncryptCert(HCkCrypt2W cHandle, HCkCertW cert);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_AddPfxSourceData(HCkCrypt2W cHandle, HCkByteData pfxBytes, const wchar_t *pfxPassword);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_AddPfxSourceFile(HCkCrypt2W cHandle, const wchar_t *pfxFilePath, const wchar_t *pfxPassword);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_AesKeyUnwrap(HCkCrypt2W cHandle, const wchar_t *kek, const wchar_t *wrappedKeyData, const wchar_t *encoding, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_aesKeyUnwrap(HCkCrypt2W cHandle, const wchar_t *kek, const wchar_t *wrappedKeyData, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_AesKeyWrap(HCkCrypt2W cHandle, const wchar_t *kek, const wchar_t *keyData, const wchar_t *encoding, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_aesKeyWrap(HCkCrypt2W cHandle, const wchar_t *kek, const wchar_t *keyData, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_BCryptHash(HCkCrypt2W cHandle, const wchar_t *password, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_bCryptHash(HCkCrypt2W cHandle, const wchar_t *password);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_BCryptVerify(HCkCrypt2W cHandle, const wchar_t *password, const wchar_t *bcryptHash);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_BytesToString(HCkCrypt2W cHandle, HCkByteData inData, const wchar_t *charset, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_bytesToString(HCkCrypt2W cHandle, HCkByteData inData, const wchar_t *charset);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_ByteSwap4321(HCkCrypt2W cHandle, HCkByteData data, HCkByteData outBytes);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_CkDecryptFile(HCkCrypt2W cHandle, const wchar_t *srcFile, const wchar_t *destFile);
CK_VISIBLE_PUBLIC HCkTaskW CkCrypt2W_CkDecryptFileAsync(HCkCrypt2W cHandle, const wchar_t *srcFile, const wchar_t *destFile);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_CkEncryptFile(HCkCrypt2W cHandle, const wchar_t *srcFile, const wchar_t *destFile);
CK_VISIBLE_PUBLIC HCkTaskW CkCrypt2W_CkEncryptFileAsync(HCkCrypt2W cHandle, const wchar_t *srcFile, const wchar_t *destFile);
CK_VISIBLE_PUBLIC void CkCrypt2W_ClearEncryptCerts(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_CompressBytes(HCkCrypt2W cHandle, HCkByteData data, HCkByteData outData);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_CompressBytesENC(HCkCrypt2W cHandle, HCkByteData data, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_compressBytesENC(HCkCrypt2W cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_CompressString(HCkCrypt2W cHandle, const wchar_t *str, HCkByteData outData);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_CompressStringENC(HCkCrypt2W cHandle, const wchar_t *str, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_compressStringENC(HCkCrypt2W cHandle, const wchar_t *str);
CK_VISIBLE_PUBLIC unsigned long CkCrypt2W_CrcBytes(HCkCrypt2W cHandle, const wchar_t *crcAlg, HCkByteData byteData);
CK_VISIBLE_PUBLIC unsigned long CkCrypt2W_CrcFile(HCkCrypt2W cHandle, const wchar_t *crcAlg, const wchar_t *path);
CK_VISIBLE_PUBLIC HCkTaskW CkCrypt2W_CrcFileAsync(HCkCrypt2W cHandle, const wchar_t *crcAlg, const wchar_t *path);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_CreateDetachedSignature(HCkCrypt2W cHandle, const wchar_t *inFilePath, const wchar_t *sigFilePath);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_CreateP7M(HCkCrypt2W cHandle, const wchar_t *inFilename, const wchar_t *p7mPath);
CK_VISIBLE_PUBLIC HCkTaskW CkCrypt2W_CreateP7MAsync(HCkCrypt2W cHandle, const wchar_t *inFilename, const wchar_t *p7mPath);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_CreateP7S(HCkCrypt2W cHandle, const wchar_t *inFilename, const wchar_t *p7sPath);
CK_VISIBLE_PUBLIC HCkTaskW CkCrypt2W_CreateP7SAsync(HCkCrypt2W cHandle, const wchar_t *inFilename, const wchar_t *p7sPath);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_Decode(HCkCrypt2W cHandle, const wchar_t *str, const wchar_t *encoding, HCkByteData outData);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_DecodeString(HCkCrypt2W cHandle, const wchar_t *inStr, const wchar_t *charset, const wchar_t *encoding, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_decodeString(HCkCrypt2W cHandle, const wchar_t *inStr, const wchar_t *charset, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_DecryptBd(HCkCrypt2W cHandle, HCkBinDataW bd);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_DecryptBytes(HCkCrypt2W cHandle, HCkByteData data, HCkByteData outData);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_DecryptBytesENC(HCkCrypt2W cHandle, const wchar_t *str, HCkByteData outData);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_DecryptEncoded(HCkCrypt2W cHandle, const wchar_t *encodedEncryptedData, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_decryptEncoded(HCkCrypt2W cHandle, const wchar_t *encodedEncryptedData);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_DecryptSb(HCkCrypt2W cHandle, HCkBinDataW bdIn, HCkStringBuilderW sbOut);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_DecryptSecureENC(HCkCrypt2W cHandle, const wchar_t *cipherText, HCkSecureStringW secureStr);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_DecryptStream(HCkCrypt2W cHandle, HCkStreamW strm);
CK_VISIBLE_PUBLIC HCkTaskW CkCrypt2W_DecryptStreamAsync(HCkCrypt2W cHandle, HCkStreamW strm);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_DecryptString(HCkCrypt2W cHandle, HCkByteData data, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_decryptString(HCkCrypt2W cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_DecryptStringENC(HCkCrypt2W cHandle, const wchar_t *str, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_decryptStringENC(HCkCrypt2W cHandle, const wchar_t *str);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_Encode(HCkCrypt2W cHandle, HCkByteData byteData, const wchar_t *encoding, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_encode(HCkCrypt2W cHandle, HCkByteData byteData, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_EncodeBytes(HCkCrypt2W cHandle, const unsigned char *pByteData, unsigned long szByteData, const wchar_t *encoding, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_encodeBytes(HCkCrypt2W cHandle, const unsigned char * pByteData, unsigned long szByteData, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_EncodeInt(HCkCrypt2W cHandle, int value, int numBytes, BOOL littleEndian, const wchar_t *encoding, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_encodeInt(HCkCrypt2W cHandle, int value, int numBytes, BOOL littleEndian, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_EncodeString(HCkCrypt2W cHandle, const wchar_t *strToEncode, const wchar_t *charsetName, const wchar_t *toEncodingName, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_encodeString(HCkCrypt2W cHandle, const wchar_t *strToEncode, const wchar_t *charsetName, const wchar_t *toEncodingName);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_EncryptBd(HCkCrypt2W cHandle, HCkBinDataW bd);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_EncryptBytes(HCkCrypt2W cHandle, HCkByteData data, HCkByteData outData);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_EncryptBytesENC(HCkCrypt2W cHandle, HCkByteData data, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_encryptBytesENC(HCkCrypt2W cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_EncryptEncoded(HCkCrypt2W cHandle, const wchar_t *str, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_encryptEncoded(HCkCrypt2W cHandle, const wchar_t *str);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_EncryptSb(HCkCrypt2W cHandle, HCkStringBuilderW sbIn, HCkBinDataW bdOut);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_EncryptSecureENC(HCkCrypt2W cHandle, HCkSecureStringW secureStr, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_encryptSecureENC(HCkCrypt2W cHandle, HCkSecureStringW secureStr);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_EncryptStream(HCkCrypt2W cHandle, HCkStreamW strm);
CK_VISIBLE_PUBLIC HCkTaskW CkCrypt2W_EncryptStreamAsync(HCkCrypt2W cHandle, HCkStreamW strm);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_EncryptString(HCkCrypt2W cHandle, const wchar_t *str, HCkByteData outData);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_EncryptStringENC(HCkCrypt2W cHandle, const wchar_t *str, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_encryptStringENC(HCkCrypt2W cHandle, const wchar_t *str);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_GenEncodedSecretKey(HCkCrypt2W cHandle, const wchar_t *password, const wchar_t *encoding, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_genEncodedSecretKey(HCkCrypt2W cHandle, const wchar_t *password, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_GenerateSecretKey(HCkCrypt2W cHandle, const wchar_t *password, HCkByteData outData);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_GenerateUuid(HCkCrypt2W cHandle, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_generateUuid(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_GenRandomBytesENC(HCkCrypt2W cHandle, int numBytes, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_genRandomBytesENC(HCkCrypt2W cHandle, int numBytes);
CK_VISIBLE_PUBLIC HCkCertW CkCrypt2W_GetDecryptCert(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_GetEncodedAad(HCkCrypt2W cHandle, const wchar_t *encoding, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_getEncodedAad(HCkCrypt2W cHandle, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_GetEncodedAuthTag(HCkCrypt2W cHandle, const wchar_t *encoding, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_getEncodedAuthTag(HCkCrypt2W cHandle, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_GetEncodedIV(HCkCrypt2W cHandle, const wchar_t *encoding, HCkString outIV);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_getEncodedIV(HCkCrypt2W cHandle, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_GetEncodedKey(HCkCrypt2W cHandle, const wchar_t *encoding, HCkString outKey);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_getEncodedKey(HCkCrypt2W cHandle, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_GetEncodedSalt(HCkCrypt2W cHandle, const wchar_t *encoding, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_getEncodedSalt(HCkCrypt2W cHandle, const wchar_t *encoding);
CK_VISIBLE_PUBLIC HCkCertW CkCrypt2W_GetLastCert(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_GetSignatureSigningTime(HCkCrypt2W cHandle, int index, SYSTEMTIME *outSysTime);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_GetSignatureSigningTimeStr(HCkCrypt2W cHandle, int index, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_getSignatureSigningTimeStr(HCkCrypt2W cHandle, int index);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_GetSignedAttributes(HCkCrypt2W cHandle, int signerIndex, HCkBinDataW pkcs7Der, HCkStringBuilderW sbJson);
CK_VISIBLE_PUBLIC HCkCertW CkCrypt2W_GetSignerCert(HCkCrypt2W cHandle, int index);
CK_VISIBLE_PUBLIC HCkCertChainW CkCrypt2W_GetSignerCertChain(HCkCrypt2W cHandle, int index);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_HashBdENC(HCkCrypt2W cHandle, HCkBinDataW bd, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_hashBdENC(HCkCrypt2W cHandle, HCkBinDataW bd);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_HashBeginBytes(HCkCrypt2W cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_HashBeginString(HCkCrypt2W cHandle, const wchar_t *strData);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_HashBytes(HCkCrypt2W cHandle, HCkByteData data, HCkByteData outData);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_HashBytesENC(HCkCrypt2W cHandle, HCkByteData data, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_hashBytesENC(HCkCrypt2W cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_HashFile(HCkCrypt2W cHandle, const wchar_t *path, HCkByteData outBytes);
CK_VISIBLE_PUBLIC HCkTaskW CkCrypt2W_HashFileAsync(HCkCrypt2W cHandle, const wchar_t *path);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_HashFileENC(HCkCrypt2W cHandle, const wchar_t *path, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_hashFileENC(HCkCrypt2W cHandle, const wchar_t *path);
CK_VISIBLE_PUBLIC HCkTaskW CkCrypt2W_HashFileENCAsync(HCkCrypt2W cHandle, const wchar_t *path);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_HashFinal(HCkCrypt2W cHandle, HCkByteData outBytes);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_HashFinalENC(HCkCrypt2W cHandle, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_hashFinalENC(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_HashMoreBytes(HCkCrypt2W cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_HashMoreString(HCkCrypt2W cHandle, const wchar_t *strData);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_HashString(HCkCrypt2W cHandle, const wchar_t *str, HCkByteData outData);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_HashStringENC(HCkCrypt2W cHandle, const wchar_t *str, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_hashStringENC(HCkCrypt2W cHandle, const wchar_t *str);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_HasSignatureSigningTime(HCkCrypt2W cHandle, int index);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_HmacBytes(HCkCrypt2W cHandle, HCkByteData inBytes, HCkByteData outHmac);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_HmacBytesENC(HCkCrypt2W cHandle, HCkByteData inBytes, HCkString outEncodedHmac);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_hmacBytesENC(HCkCrypt2W cHandle, HCkByteData inBytes);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_HmacString(HCkCrypt2W cHandle, const wchar_t *inText, HCkByteData outHmac);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_HmacStringENC(HCkCrypt2W cHandle, const wchar_t *inText, HCkString outEncodedHmac);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_hmacStringENC(HCkCrypt2W cHandle, const wchar_t *inText);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_Hotp(HCkCrypt2W cHandle, const wchar_t *secret, const wchar_t *secretEnc, const wchar_t *counterHex, int numDigits, int truncOffset, const wchar_t *hashAlg, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_hotp(HCkCrypt2W cHandle, const wchar_t *secret, const wchar_t *secretEnc, const wchar_t *counterHex, int numDigits, int truncOffset, const wchar_t *hashAlg);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_InflateBytes(HCkCrypt2W cHandle, HCkByteData data, HCkByteData outData);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_InflateBytesENC(HCkCrypt2W cHandle, const wchar_t *str, HCkByteData outData);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_InflateString(HCkCrypt2W cHandle, HCkByteData data, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_inflateString(HCkCrypt2W cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_InflateStringENC(HCkCrypt2W cHandle, const wchar_t *str, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_inflateStringENC(HCkCrypt2W cHandle, const wchar_t *str);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_IsUnlocked(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC HCkJsonObjectW CkCrypt2W_LastJsonData(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_MacBdENC(HCkCrypt2W cHandle, HCkBinDataW bd, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_macBdENC(HCkCrypt2W cHandle, HCkBinDataW bd);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_MacBytes(HCkCrypt2W cHandle, HCkByteData inBytes, HCkByteData outBytes);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_MacBytesENC(HCkCrypt2W cHandle, HCkByteData inBytes, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_macBytesENC(HCkCrypt2W cHandle, HCkByteData inBytes);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_MacString(HCkCrypt2W cHandle, const wchar_t *inText, HCkByteData outBytes);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_MacStringENC(HCkCrypt2W cHandle, const wchar_t *inText, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_macStringENC(HCkCrypt2W cHandle, const wchar_t *inText);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_MySqlAesDecrypt(HCkCrypt2W cHandle, const wchar_t *strEncryptedHex, const wchar_t *strPassword, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_mySqlAesDecrypt(HCkCrypt2W cHandle, const wchar_t *strEncryptedHex, const wchar_t *strPassword);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_MySqlAesEncrypt(HCkCrypt2W cHandle, const wchar_t *strData, const wchar_t *strPassword, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_mySqlAesEncrypt(HCkCrypt2W cHandle, const wchar_t *strData, const wchar_t *strPassword);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_OpaqueSignBd(HCkCrypt2W cHandle, HCkBinDataW bd);
CK_VISIBLE_PUBLIC HCkTaskW CkCrypt2W_OpaqueSignBdAsync(HCkCrypt2W cHandle, HCkBinDataW bd);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_OpaqueSignBytes(HCkCrypt2W cHandle, HCkByteData data, HCkByteData outData);
CK_VISIBLE_PUBLIC HCkTaskW CkCrypt2W_OpaqueSignBytesAsync(HCkCrypt2W cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_OpaqueSignBytesENC(HCkCrypt2W cHandle, HCkByteData data, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_opaqueSignBytesENC(HCkCrypt2W cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC HCkTaskW CkCrypt2W_OpaqueSignBytesENCAsync(HCkCrypt2W cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_OpaqueSignString(HCkCrypt2W cHandle, const wchar_t *str, HCkByteData outData);
CK_VISIBLE_PUBLIC HCkTaskW CkCrypt2W_OpaqueSignStringAsync(HCkCrypt2W cHandle, const wchar_t *str);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_OpaqueSignStringENC(HCkCrypt2W cHandle, const wchar_t *str, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_opaqueSignStringENC(HCkCrypt2W cHandle, const wchar_t *str);
CK_VISIBLE_PUBLIC HCkTaskW CkCrypt2W_OpaqueSignStringENCAsync(HCkCrypt2W cHandle, const wchar_t *str);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_OpaqueVerifyBd(HCkCrypt2W cHandle, HCkBinDataW bd);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_OpaqueVerifyBytes(HCkCrypt2W cHandle, HCkByteData p7s, HCkByteData outOriginal);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_OpaqueVerifyBytesENC(HCkCrypt2W cHandle, const wchar_t *p7s, HCkByteData outOriginal);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_OpaqueVerifyString(HCkCrypt2W cHandle, HCkByteData p7s, HCkString outOriginal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_opaqueVerifyString(HCkCrypt2W cHandle, HCkByteData p7s);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_OpaqueVerifyStringENC(HCkCrypt2W cHandle, const wchar_t *p7s, HCkString outOriginal);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_opaqueVerifyStringENC(HCkCrypt2W cHandle, const wchar_t *p7s);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_Pbkdf1(HCkCrypt2W cHandle, const wchar_t *password, const wchar_t *charset, const wchar_t *hashAlg, const wchar_t *salt, int iterationCount, int outputKeyBitLen, const wchar_t *encoding, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_pbkdf1(HCkCrypt2W cHandle, const wchar_t *password, const wchar_t *charset, const wchar_t *hashAlg, const wchar_t *salt, int iterationCount, int outputKeyBitLen, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_Pbkdf2(HCkCrypt2W cHandle, const wchar_t *password, const wchar_t *charset, const wchar_t *hashAlg, const wchar_t *salt, int iterationCount, int outputKeyBitLen, const wchar_t *encoding, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_pbkdf2(HCkCrypt2W cHandle, const wchar_t *password, const wchar_t *charset, const wchar_t *hashAlg, const wchar_t *salt, int iterationCount, int outputKeyBitLen, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_Pkcs7ExtractDigest(HCkCrypt2W cHandle, int signerIndex, const wchar_t *pkcs7, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_pkcs7ExtractDigest(HCkCrypt2W cHandle, int signerIndex, const wchar_t *pkcs7);
CK_VISIBLE_PUBLIC void CkCrypt2W_RandomizeIV(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC void CkCrypt2W_RandomizeKey(HCkCrypt2W cHandle);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_ReadFile(HCkCrypt2W cHandle, const wchar_t *filename, HCkByteData outBytes);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_ReEncode(HCkCrypt2W cHandle, const wchar_t *encodedData, const wchar_t *fromEncoding, const wchar_t *toEncoding, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_reEncode(HCkCrypt2W cHandle, const wchar_t *encodedData, const wchar_t *fromEncoding, const wchar_t *toEncoding);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_SaveLastError(HCkCrypt2W cHandle, const wchar_t *path);
#if defined(CK_CSP_INCLUDED)
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_SetCSP(HCkCrypt2W cHandle, HCkCspW csp);
#endif
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_SetDecryptCert(HCkCrypt2W cHandle, HCkCertW cert);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_SetDecryptCert2(HCkCrypt2W cHandle, HCkCertW cert, HCkPrivateKeyW key);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_SetEncodedAad(HCkCrypt2W cHandle, const wchar_t *aadStr, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_SetEncodedAuthTag(HCkCrypt2W cHandle, const wchar_t *authTagStr, const wchar_t *encoding);
CK_VISIBLE_PUBLIC void CkCrypt2W_SetEncodedIV(HCkCrypt2W cHandle, const wchar_t *ivStr, const wchar_t *encoding);
CK_VISIBLE_PUBLIC void CkCrypt2W_SetEncodedKey(HCkCrypt2W cHandle, const wchar_t *keyStr, const wchar_t *encoding);
CK_VISIBLE_PUBLIC void CkCrypt2W_SetEncodedSalt(HCkCrypt2W cHandle, const wchar_t *saltStr, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_SetEncryptCert(HCkCrypt2W cHandle, HCkCertW cert);
CK_VISIBLE_PUBLIC void CkCrypt2W_SetHmacKeyBytes(HCkCrypt2W cHandle, HCkByteData keyBytes);
CK_VISIBLE_PUBLIC void CkCrypt2W_SetHmacKeyEncoded(HCkCrypt2W cHandle, const wchar_t *key, const wchar_t *encoding);
CK_VISIBLE_PUBLIC void CkCrypt2W_SetHmacKeyString(HCkCrypt2W cHandle, const wchar_t *key);
CK_VISIBLE_PUBLIC void CkCrypt2W_SetIV(HCkCrypt2W cHandle, const unsigned char *pByteData, unsigned long szByteData);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_SetMacKeyBytes(HCkCrypt2W cHandle, HCkByteData keyBytes);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_SetMacKeyEncoded(HCkCrypt2W cHandle, const wchar_t *key, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_SetMacKeyString(HCkCrypt2W cHandle, const wchar_t *key);
CK_VISIBLE_PUBLIC void CkCrypt2W_SetSecretKey(HCkCrypt2W cHandle, const unsigned char *pByteData, unsigned long szByteData);
CK_VISIBLE_PUBLIC void CkCrypt2W_SetSecretKeyViaPassword(HCkCrypt2W cHandle, const wchar_t *password);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_SetSigningCert(HCkCrypt2W cHandle, HCkCertW cert);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_SetSigningCert2(HCkCrypt2W cHandle, HCkCertW cert, HCkPrivateKeyW privateKey);
CK_VISIBLE_PUBLIC void CkCrypt2W_SetTsaHttpObj(HCkCrypt2W cHandle, HCkHttpW http);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_SetVerifyCert(HCkCrypt2W cHandle, HCkCertW cert);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_SignBdENC(HCkCrypt2W cHandle, HCkBinDataW dataToSign, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_signBdENC(HCkCrypt2W cHandle, HCkBinDataW dataToSign);
CK_VISIBLE_PUBLIC HCkTaskW CkCrypt2W_SignBdENCAsync(HCkCrypt2W cHandle, HCkBinDataW dataToSign);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_SignBytes(HCkCrypt2W cHandle, HCkByteData data, HCkByteData outData);
CK_VISIBLE_PUBLIC HCkTaskW CkCrypt2W_SignBytesAsync(HCkCrypt2W cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_SignBytesENC(HCkCrypt2W cHandle, HCkByteData data, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_signBytesENC(HCkCrypt2W cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC HCkTaskW CkCrypt2W_SignBytesENCAsync(HCkCrypt2W cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_SignSbENC(HCkCrypt2W cHandle, HCkStringBuilderW sb, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_signSbENC(HCkCrypt2W cHandle, HCkStringBuilderW sb);
CK_VISIBLE_PUBLIC HCkTaskW CkCrypt2W_SignSbENCAsync(HCkCrypt2W cHandle, HCkStringBuilderW sb);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_SignString(HCkCrypt2W cHandle, const wchar_t *str, HCkByteData outData);
CK_VISIBLE_PUBLIC HCkTaskW CkCrypt2W_SignStringAsync(HCkCrypt2W cHandle, const wchar_t *str);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_SignStringENC(HCkCrypt2W cHandle, const wchar_t *str, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_signStringENC(HCkCrypt2W cHandle, const wchar_t *str);
CK_VISIBLE_PUBLIC HCkTaskW CkCrypt2W_SignStringENCAsync(HCkCrypt2W cHandle, const wchar_t *str);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_StringToBytes(HCkCrypt2W cHandle, const wchar_t *inStr, const wchar_t *charset, HCkByteData outBytes);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_Totp(HCkCrypt2W cHandle, const wchar_t *secret, const wchar_t *secretEnc, const wchar_t *t0, const wchar_t *tNow, int tStep, int numDigits, int truncOffset, const wchar_t *hashAlg, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_totp(HCkCrypt2W cHandle, const wchar_t *secret, const wchar_t *secretEnc, const wchar_t *t0, const wchar_t *tNow, int tStep, int numDigits, int truncOffset, const wchar_t *hashAlg);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_TrimEndingWith(HCkCrypt2W cHandle, const wchar_t *inStr, const wchar_t *ending, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCrypt2W_trimEndingWith(HCkCrypt2W cHandle, const wchar_t *inStr, const wchar_t *ending);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_UnlockComponent(HCkCrypt2W cHandle, const wchar_t *unlockCode);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_UseCertVault(HCkCrypt2W cHandle, HCkXmlCertVaultW vault);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_VerifyBdENC(HCkCrypt2W cHandle, HCkBinDataW data, const wchar_t *encodedSig);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_VerifyBytes(HCkCrypt2W cHandle, HCkByteData data, HCkByteData sig);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_VerifyBytesENC(HCkCrypt2W cHandle, HCkByteData data, const wchar_t *encodedSig);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_VerifyDetachedSignature(HCkCrypt2W cHandle, const wchar_t *inFilename, const wchar_t *p7sFilename);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_VerifyP7M(HCkCrypt2W cHandle, const wchar_t *p7mPath, const wchar_t *destPath);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_VerifyP7S(HCkCrypt2W cHandle, const wchar_t *inFilename, const wchar_t *p7sFilename);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_VerifySbENC(HCkCrypt2W cHandle, HCkStringBuilderW sb, const wchar_t *encodedSig);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_VerifyString(HCkCrypt2W cHandle, const wchar_t *str, HCkByteData sig);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_VerifyStringENC(HCkCrypt2W cHandle, const wchar_t *str, const wchar_t *encodedSig);
CK_VISIBLE_PUBLIC BOOL CkCrypt2W_WriteFile(HCkCrypt2W cHandle, const wchar_t *filename, HCkByteData fileData);
#endif
