#ifndef BYTE_STORE_H_
#define BYTE_STORE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif /* getline() support */

#if __APPLE__
    #ifndef HOST_NAME_MAX
        #define HOST_NAME_MAX _POSIX_HOST_NAME_MAX
    #endif
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <float.h>
#include <errno.h>
#include <bzlib.h>
#include <microhttpd.h>
#include <netdb.h>
#include <limits.h>
#include "mt19937.h"

#define BUF_MAX_LEN 4096
#define CHR_MAX_LEN 256
#define COORD_MAX_LEN 20
#define SCORE_MAX_LEN 5
#define DELIMITER_LEN 1
#define OUTPUT_LINE_MAX_LEN (CHR_MAX_LEN * 2) + (COORD_MAX_LEN * 4) + SCORE_MAX_LEN + (DELIMITER_LEN * 6) + 1
#define ID_MAX_LEN 524288
#define FN_MAX_LEN 1024
#define QUERY_MAX_LEN 524288
#define ENTRY_MAX_LEN 20
#define OFFSET_MAX_LEN 20
#define MD_OFFSET_MAX_LEN 20
#define BLOCK_STR_MAX_LEN 13
#define NORMALIZATION_FACTOR_STR_MAX_LEN 13
#define LINE_ID_STR_MAX_LEN 13
#define MULT_IDX_MAX_NUM 4096
#define HOSTNAME_MAX_LEN 8192
#define UPLOAD_FILESIZE_MAX 1048576
#define INITIAL_BUF_CAPACITY 1024

#define PR_SIZET "z"

#define swap(x,y) do                                                    \
        { unsigned char swap_temp[sizeof(x) == sizeof(y) ? (signed)sizeof(x) : -1]; \
            memcpy(swap_temp,&y,sizeof(x));                             \
            memcpy(&y,&x,       sizeof(x));                             \
            memcpy(&x,swap_temp,sizeof(x));                             \
        } while(0)

    typedef unsigned char byte_t;
    typedef float score_t;
    typedef float rank_t;

    extern const byte_t kNANEncodedByte;
    const byte_t kNANEncodedByte = 0xca;

    extern const char* kTestVectorA;
    extern const char* kTestVectorB;
    extern const char* kTestVectorC;
    extern const char* kTestVectorX;
    extern const char* kTestVectorY;
    extern const char* kTestVectorZ;
    extern const char* kTestVectorJ1;
    extern const char* kTestVectorJ2;
    extern const char* kTestVectorJ3;
    extern const char* kTestVectorJz;
    extern const char* kTestVectorJu;
    extern const char* kTestVectorO1;
    extern const char* kTestVectorO2;
    extern const char* kTestVectorO3;
    extern const char* kTestVectorOz;
    extern const char* kTestVectorOu;
    extern const char* kTestVectorH1;
    extern const char* kTestVectorH2;
    extern const char* kTestVectorH3;
    extern const char* kTestVectorHz;
    extern const char* kTestVectorHu;
    extern const char* kTestVectorT1;
    extern const char* kTestVectorT2;
    extern const char* kTestVectorT3;
    extern const char* kTestVectorTz;
    extern const char* kTestVectorTu;
    extern const char* kTestVectorM1;
    extern const char* kTestVectorM2;
    extern const char* kTestVectorMz;
    extern const char* kTestVectorMu;
    const score_t kTestVectorDNormFactor;
    const char* kTestVectorD1;
    const char* kTestVectorD2;
    const char* kTestVectorD3;
    const char* kTestVectorDz;
    const char* kTestVectorDu;
    const char* kTestVectorI1;
    const char* kTestVectorI2;
    const char* kTestVectorI3;
    const char* kTestVectorIz;
    const char* kTestVectorIu;

    const char* kTestVectorA = "20,8,10,31,50,51,15,41,28,28,11,25,23,21,13,19,14,16,36,38,24,15,35,24,61,31,18,49,19,14,27,19,12,18,15,116,21,28,22,16,11,22,29,31,18,17,9,17,8,14,35,43,10,24,13,19,17,119,33,23,40,10,19,60,12,18,22,7,5,27,40,12,7,21,7,18,6,34,26,6,16,11";
    const char* kTestVectorB = "17,10,9,42,57,56,5,49,24,27,14,22,25,16,21,23,22,10,20,29,14,29,34,14,70,33,5,35,11,13,13,20,15,15,55,19,32,26,10,11,12,16,25,22,31,7,8,2,10,9,14,50,9,38,20,21,14,27,31,14,24,15,14,18,16,26,6,3,8,10,58,16,8,19,10,53,4,76,17,14,29,27";
    const char* kTestVectorC = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
    const char* kTestVectorX = "1,2,3,20,4";
    const char* kTestVectorY = "2,3,1,15,9";
    const char* kTestVectorZ = "2,NAN,1,15,9";
    const char* kTestVectorJ1 = "0,1,0,0,0,1,1";
    const char* kTestVectorJ2 = "0,1,0,1,1,1,1";
    const char* kTestVectorJ3 = "0,1,NAN,0,0,0,1";
    const char* kTestVectorJz = "0,0,0,0,0,0,0";
    const char* kTestVectorJu = "1,1,1,1,1,1,1";
    const char* kTestVectorO1 = "0,1,1,0,0,1,1";
    const char* kTestVectorO2 = "0,1,0,1,0,0,1";
    const char* kTestVectorO3 = "0,1,1,0,1,NAN,0";
    const char* kTestVectorOz = "0,0,0,0,0,0,0";
    const char* kTestVectorOu = "1,1,1,1,1,1,1";
    const char* kTestVectorH1 = "0,1,1,0,0,1,0";
    const char* kTestVectorH2 = "1,0,0,1,1,0,1";
    const char* kTestVectorH3 = "0,1,0,0,0,0,0";
    const char* kTestVectorHz = "0,0,0,0,0,0,0";
    const char* kTestVectorHu = "1,1,1,1,1,1,1";
    const char* kTestVectorT1 = "0,1,1,0,0,1,1";
    const char* kTestVectorT2 = "0,1,0,1,0,0,1";
    const char* kTestVectorT3 = "0,1,1,0,1,NAN,0";
    const char* kTestVectorTz = "0,0,0,0,0,0,0";
    const char* kTestVectorTu = "1,1,1,1,1,1,1";
    const char* kTestVectorM1 = "0,1,0,0,0,1,0,1,0,1,0,0";
    const char* kTestVectorM2 = "0,1,1,1,1,0,1,0,1,0,1,1";
    const char* kTestVectorM3 = "0,1,1,1,1,0,1,0,1,0,NAN,1";
    const char* kTestVectorMz = "0,0,0,0,0,0,0,0,0";
    const char* kTestVectorMu = "1,1,1,1,1,1,1,1,1";
    const score_t kTestVectorDNormFactor = 10.0f;
    const char* kTestVectorD1 = "1,5,5,2";
    const char* kTestVectorD2 = "3,0,1,1";
    const char* kTestVectorD3 = "0,1,1,NAN";
    const char* kTestVectorDz = "0,0,0,0";
    const char* kTestVectorDu = "5,5,5,5";
    const char* kTestVectorI1 = "0.3,0.0,0.6,0.1";
    const char* kTestVectorI2 = "0.2,0.1,0.1,0.6";
    const char* kTestVectorI3 = "0.0,0.1,0.4,NAN";
    const char* kTestVectorIz = "0.0,0.0,0.0,0.0";
    const char* kTestVectorIu = "1.0,1.0,1.0,1.0";

    extern const score_t kPearsonRTestABCorrelationUnencoded;
    extern const score_t kPearsonRTestABCorrelationEncoded;
    extern const byte_t kPearsonRTestABCorrelationEncodedByte;
    extern const score_t kPearsonRTestACCorrelationUnencoded;
    extern const score_t kPearsonRTestACCorrelationEncoded;
    extern const byte_t kPearsonRTestACCorrelationEncodedByte;

    const score_t kPearsonRTestABCorrelationUnencoded = 0.4134264f;
    const score_t kPearsonRTestABCorrelationEncoded = 0.41f;
    const byte_t kPearsonRTestABCorrelationEncodedByte = 0x8e;
    const score_t kPearsonRTestACCorrelationUnencoded = NAN;
    const score_t kPearsonRTestACCorrelationEncoded = NAN;
    const byte_t kPearsonRTestACCorrelationEncodedByte = 0xca;

    /*
        Sanity checks courtesy of R, e.g.:

        > x <- c(1,2,3,20,4)
        > y <- c(2,3,1,5,4)
        > cor(x, y, use="all", method="spearman")
        [1] 0.7

        etc.
    */
    extern const score_t kSpearmanRhoTestXYCorrelationUnencoded;
    extern const score_t kSpearmanRhoTestXYCorrelationEncoded;
    extern const score_t kSpearmanRhoTestXZCorrelationUnencoded;
    extern const score_t kSpearmanRhoTestXZCorrelationEncoded;
    extern const byte_t kSpearmanRhoTestXZCorrelationEncodedByte;
    extern const score_t kSpearmanRhoTestABCorrelationUnencoded;
    extern const score_t kSpearmanRhoTestABCorrelationEncoded;
    extern const score_t kSpearmanRhoTestACCorrelationUnencoded;
    extern const score_t kSpearmanRhoTestACCorrelationEncoded;
    extern const byte_t kSpearmanRhoTestACCorrelationEncodedByte;

    const score_t kSpearmanRhoTestXYCorrelationUnencoded = 0.7f;
    const score_t kSpearmanRhoTestXYCorrelationEncoded = 0.70f;
    const byte_t kSpearmanRhoTestXYCorrelationEncodedByte = 0xab;
    const score_t kSpearmanRhoTestABCorrelationUnencoded = 0.6152396f;
    const score_t kSpearmanRhoTestABCorrelationEncoded = 0.61f;
    const byte_t kSpearmanRhoTestABCorrelationEncodedByte = 0xa2;
    const score_t kSpearmanRhoTestXZCorrelationUnencoded = NAN;
    const score_t kSpearmanRhoTestXZCorrelationEncoded = NAN;
    const byte_t kSpearmanRhoTestXZCorrelationEncodedByte = 0xca;
    const score_t kSpearmanRhoTestACCorrelationUnencoded = NAN;
    const score_t kSpearmanRhoTestACCorrelationEncoded = NAN;
    const byte_t kSpearmanRhoTestACCorrelationEncodedByte = 0xca;

    extern const score_t kNormalizedEuclideanDistanceTestD1D2Unencoded;
    extern const score_t kNormalizedEuclideanDistanceTestD1D2Encoded;
    extern const byte_t kNormalizedEuclideanDistanceTestD1D2EncodedByte;
    extern const score_t kNormalizedEuclideanDistanceTestD1D3Unencoded;
    extern const score_t kNormalizedEuclideanDistanceTestD1D3Encoded;
    extern const byte_t kNormalizedEuclideanDistanceTestD1D3EncodedByte;
    extern const score_t kNormalizedEuclideanDistanceTestDzDzUnencoded;
    extern const score_t kNormalizedEuclideanDistanceTestDzDzEncoded;
    extern const byte_t kNormalizedEuclideanDistanceTestDzDzEncodedByte;
    extern const score_t kNormalizedEuclideanDistanceTestDzDuUnencoded;
    extern const score_t kNormalizedEuclideanDistanceTestDzDuEncoded;
    extern const byte_t kNormalizedEuclideanDistanceTestDzDuEncodedByte;
    extern const score_t kNormalizedEuclideanDistanceTestDuDuUnencoded;
    extern const score_t kNormalizedEuclideanDistanceTestDuDuEncoded;
    extern const byte_t kNormalizedEuclideanDistanceTestDuDuEncodedByte;

    const score_t kNormalizedEuclideanDistanceTestD1D2Unencoded = 0.6782330f;
    const score_t kNormalizedEuclideanDistanceTestD1D2Encoded = 0.67f;
    const byte_t kNormalizedEuclideanDistanceTestD1D2EncodedByte = 0xa8;
    const score_t kNormalizedEuclideanDistanceTestD1D3Unencoded = NAN;
    const score_t kNormalizedEuclideanDistanceTestD1D3Encoded = NAN;
    const byte_t kNormalizedEuclideanDistanceTestD1D3EncodedByte = 0xca;
    const score_t kNormalizedEuclideanDistanceTestDzDzUnencoded = 0.0f;
    const score_t kNormalizedEuclideanDistanceTestDzDzEncoded = +0.0f;
    const byte_t kNormalizedEuclideanDistanceTestDzDzEncodedByte = 0x65;
    const score_t kNormalizedEuclideanDistanceTestDzDuUnencoded = 1.0f;
    const score_t kNormalizedEuclideanDistanceTestDzDuEncoded = 1.0f;
    const byte_t kNormalizedEuclideanDistanceTestDzDuEncodedByte = 0xc9;
    const score_t kNormalizedEuclideanDistanceTestDuDuUnencoded = 0.0f;
    const score_t kNormalizedEuclideanDistanceTestDuDuEncoded = +0.0f;
    const byte_t kNormalizedEuclideanDistanceTestDuDuEncodedByte = 0x65;

    extern const score_t kCosineSimilarityTestI1I2Unencoded;
    extern const score_t kCosineSimilarityTestI1I2Encoded;
    extern const byte_t kCosineSimilarityTestI1I2EncodedByte;
    extern const score_t kCosineSimilarityTestI1I3Unencoded;
    extern const score_t kCosineSimilarityTestI1I3Encoded;
    extern const byte_t kCosineSimilarityTestI1I3EncodedByte;
    extern const score_t kCosineSimilarityTestIzIzUnencoded;
    extern const score_t kCosineSimilarityTestIzIzEncoded;
    extern const byte_t kCosineSimilarityTestIzIzEncodedByte;
    extern const score_t kCosineSimilarityTestIzIuUnencoded;
    extern const score_t kCosineSimilarityTestIzIuEncoded;
    extern const byte_t kCosineSimilarityTestIzIuEncodedByte;
    extern const score_t kCosineSimilarityTestIuIuUnencoded;
    extern const score_t kCosineSimilarityTestIuIuEncoded;
    extern const byte_t kCosineSimilarityTestIuIuEncodedByte;

    const score_t kCosineSimilarityTestI1I2Unencoded = 0.4095142f;
    const score_t kCosineSimilarityTestI1I2Encoded = 0.40f;
    const byte_t kCosineSimilarityTestI1I2EncodedByte = 0x8d;
    const score_t kCosineSimilarityTestI1I3Unencoded = NAN;
    const score_t kCosineSimilarityTestI1I3Encoded = NAN;
    const byte_t kCosineSimilarityTestI1I3EncodedByte = 0xca;
    const score_t kCosineSimilarityTestIzIzUnencoded = NAN;
    const score_t kCosineSimilarityTestIzIzEncoded = NAN;
    const byte_t kCosineSimilarityTestIzIzEncodedByte = 0xca;
    const score_t kCosineSimilarityTestIzIuUnencoded = NAN;
    const score_t kCosineSimilarityTestIzIuEncoded = NAN;
    const byte_t kCosineSimilarityTestIzIuEncodedByte = 0xca;
    const score_t kCosineSimilarityTestIuIuUnencoded = 1.0f;
    const score_t kCosineSimilarityTestIuIuEncoded = +1.0f;
    const byte_t kCosineSimilarityTestIuIuEncodedByte = 0xc9;

    extern const score_t kJaccardIndexTestJ1J2Unencoded;
    extern const score_t kJaccardIndexTestJ1J2Encoded;
    extern const byte_t kJaccardIndexTestJ1J2EncodedByte;
    extern const score_t kJaccardIndexTestJ1J3Unencoded;
    extern const score_t kJaccardIndexTestJ1J3Encoded;
    extern const byte_t kJaccardIndexTestJ1J3EncodedByte;
    extern const score_t kJaccardIndexTestJzJzUnencoded;
    extern const score_t kJaccardIndexTestJzJzEncoded;
    extern const byte_t kJaccardIndexTestJzJzEncodedByte;
    extern const score_t kJaccardIndexTestJzJuUnencoded;
    extern const score_t kJaccardIndexTestJzJuEncoded;
    extern const byte_t kJaccardIndexTestJzJuEncodedByte;
    extern const score_t kJaccardIndexTestJuJuUnencoded;
    extern const score_t kJaccardIndexTestJuJuEncoded;
    extern const byte_t kJaccardIndexTestJuJuEncodedByte;

    const score_t kJaccardIndexTestJ1J2Unencoded = 0.6f;
    const score_t kJaccardIndexTestJ1J2Encoded = 0.60f;
    const byte_t kJaccardIndexTestJ1J2EncodedByte = 0xa1;
    const score_t kJaccardIndexTestJ1J3Unencoded = NAN;
    const score_t kJaccardIndexTestJ1J3Encoded = NAN;
    const byte_t kJaccardIndexTestJ1J3EncodedByte = 0xca;
    const score_t kJaccardIndexTestJzJzUnencoded = NAN;
    const score_t kJaccardIndexTestJzJzEncoded = NAN;
    const byte_t kJaccardIndexTestJzJzEncodedByte = 0xca;
    const score_t kJaccardIndexTestJzJuUnencoded = 0.00f;
    const score_t kJaccardIndexTestJzJuEncoded = +0.00f;
    const byte_t kJaccardIndexTestJzJuEncodedByte = 0x65;
    const score_t kJaccardIndexTestJuJuUnencoded = 1.0f;
    const score_t kJaccardIndexTestJuJuEncoded = 1.00f;
    const byte_t kJaccardIndexTestJuJuEncodedByte = 0xc9;

    extern const score_t kOchiaiSimilarityTestO1O2Unencoded;
    extern const score_t kOchiaiSimilarityTestO1O2Encoded;
    extern const byte_t kOchiaiSimilarityTestO1O2EncodedByte;
    extern const score_t kOchiaiSimilarityTestO1O3Unencoded;
    extern const score_t kOchiaiSimilarityTestO1O3Encoded;
    extern const byte_t kOchiaiSimilarityTestO1O3EncodedByte;
    extern const score_t kOchiaiSimilarityTestOzOzUnencoded;
    extern const score_t kOchiaiSimilarityTestOzOzEncoded;
    extern const byte_t kOchiaiSimilarityTestOzOzEncodedByte;
    extern const score_t kOchiaiSimilarityTestOzOuUnencoded;
    extern const score_t kOchiaiSimilarityTestOzOuEncoded;
    extern const byte_t kOchiaiSimilarityTestOzOuEncodedByte;
    extern const score_t kOchiaiSimilarityTestOuOuUnencoded;
    extern const score_t kOchiaiSimilarityTestOuOuEncoded;
    extern const byte_t kOchiaiSimilarityTestOuOuEncodedByte;

    const score_t kOchiaiSimilarityTestO1O2Unencoded = 0.5773503f;
    const score_t kOchiaiSimilarityTestO1O2Encoded = 0.57f;
    const byte_t kOchiaiSimilarityTestO1O2EncodedByte = 0x9e;
    const score_t kOchiaiSimilarityTestO1O3Unencoded = NAN;
    const score_t kOchiaiSimilarityTestO1O3Encoded = NAN;
    const byte_t kOchiaiSimilarityTestO1O3EncodedByte = 0xca;
    const score_t kOchiaiSimilarityTestOzOzUnencoded = 1.0f;
    const score_t kOchiaiSimilarityTestOzOzEncoded = 1.00f;
    const byte_t kOchiaiSimilarityTestOzOzEncodedByte = 0xc9;
    const score_t kOchiaiSimilarityTestOzOuUnencoded = 0.00f;
    const score_t kOchiaiSimilarityTestOzOuEncoded = +0.00f;
    const byte_t kOchiaiSimilarityTestOzOuEncodedByte = 0x65;
    const score_t kOchiaiSimilarityTestOuOuUnencoded = 1.0f;
    const score_t kOchiaiSimilarityTestOuOuEncoded = 1.00f;
    const byte_t kOchiaiSimilarityTestOuOuEncodedByte = 0xc9;

    extern const score_t kPearsonPhiSimilarityTestH1H2Unencoded;
    extern const score_t kPearsonPhiSimilarityTestH1H2Encoded;
    extern const byte_t kPearsonPhiSimilarityTestH1H2EncodedByte;
    extern const score_t kPearsonPhiSimilarityTestH1H3Unencoded;
    extern const score_t kPearsonPhiSimilarityTestH1H3Encoded;
    extern const byte_t kPearsonPhiSimilarityTestH1H3EncodedByte;
    extern const score_t kPearsonPhiSimilarityTestHzHzUnencoded;
    extern const score_t kPearsonPhiSimilarityTestHzHzEncoded;
    extern const byte_t kPearsonPhiSimilarityTestHzHzEncodedByte;
    extern const score_t kPearsonPhiSimilarityTestHzHuUnencoded;
    extern const score_t kPearsonPhiSimilarityTestHzHuEncoded;
    extern const byte_t kPearsonPhiSimilarityTestHzHuEncodedByte;
    extern const score_t kPearsonPhiSimilarityTestHuHuUnencoded;
    extern const score_t kPearsonPhiSimilarityTestHuHuEncoded;
    extern const byte_t kPearsonPhiSimilarityTestHuHuEncodedByte;

    const score_t kPearsonPhiSimilarityTestH1H2Unencoded = -1.0000000f;
    const score_t kPearsonPhiSimilarityTestH1H2Encoded = -1.00f;
    const byte_t kPearsonPhiSimilarityTestH1H2EncodedByte = 0x00;
    const score_t kPearsonPhiSimilarityTestH1H3Unencoded = 0.4714045f;
    const score_t kPearsonPhiSimilarityTestH1H3Encoded = 0.47f;
    const byte_t kPearsonPhiSimilarityTestH1H3EncodedByte = 0x94;
    const score_t kPearsonPhiSimilarityTestHzHzUnencoded = 1.0f;
    const score_t kPearsonPhiSimilarityTestHzHzEncoded = 1.00f;
    const byte_t kPearsonPhiSimilarityTestHzHzEncodedByte = 0xc9;
    const score_t kPearsonPhiSimilarityTestHzHuUnencoded = -1.00f;
    const score_t kPearsonPhiSimilarityTestHzHuEncoded = -1.00f;
    const byte_t kPearsonPhiSimilarityTestHzHuEncodedByte = 0x00;
    const score_t kPearsonPhiSimilarityTestHuHuUnencoded = 1.0f;
    const score_t kPearsonPhiSimilarityTestHuHuEncoded = 1.00f;
    const byte_t kPearsonPhiSimilarityTestHuHuEncodedByte = 0xc9;

    extern const score_t kRogersAndTanimotoSimilarityTestT1T2Unencoded;
    extern const score_t kRogersAndTanimotoSimilarityTestT1T2Encoded;
    extern const byte_t kRogersAndTanimotoSimilarityTestT1T2EncodedByte;
    extern const score_t kRogersAndTanimotoSimilarityTestT1T3Unencoded;
    extern const score_t kRogersAndTanimotoSimilarityTestT1T3Encoded;
    extern const byte_t kRogersAndTanimotoSimilarityTestT1T3EncodedByte;
    extern const score_t kRogersAndTanimotoSimilarityTestTzTzUnencoded;
    extern const score_t kRogersAndTanimotoSimilarityTestTzTzEncoded;
    extern const byte_t kRogersAndTanimotoSimilarityTestTzTzEncodedByte;
    extern const score_t kRogersAndTanimotoSimilarityTestTzTuUnencoded;
    extern const score_t kRogersAndTanimotoSimilarityTestTzTuEncoded;
    extern const byte_t kRogersAndTanimotoSimilarityTestTzTuEncodedByte;
    extern const score_t kRogersAndTanimotoSimilarityTestTuTuUnencoded;
    extern const score_t kRogersAndTanimotoSimilarityTestTuTuEncoded;
    extern const byte_t kRogersAndTanimotoSimilarityTestTuTuEncodedByte;

    const score_t kRogersAndTanimotoSimilarityTestT1T2Unencoded = 0.40f;
    const score_t kRogersAndTanimotoSimilarityTestT1T2Encoded = 0.40f;
    const byte_t kRogersAndTanimotoSimilarityTestT1T2EncodedByte = 0x8d;
    const score_t kRogersAndTanimotoSimilarityTestT1T3Unencoded = NAN;
    const score_t kRogersAndTanimotoSimilarityTestT1T3Encoded = NAN;
    const byte_t kRogersAndTanimotoSimilarityTestT1T3EncodedByte = 0xca;
    const score_t kRogersAndTanimotoSimilarityTestTzTzUnencoded = 1.0f;
    const score_t kRogersAndTanimotoSimilarityTestTzTzEncoded = 1.00f;
    const byte_t kRogersAndTanimotoSimilarityTestTzTzEncodedByte = 0xc9;
    const score_t kRogersAndTanimotoSimilarityTestTzTuUnencoded = 0.0f;
    const score_t kRogersAndTanimotoSimilarityTestTzTuEncoded = +0.00f;
    const byte_t kRogersAndTanimotoSimilarityTestTzTuEncodedByte = 0x65;
    const score_t kRogersAndTanimotoSimilarityTestTuTuUnencoded = 1.0f;
    const score_t kRogersAndTanimotoSimilarityTestTuTuEncoded = 1.00f;
    const byte_t kRogersAndTanimotoSimilarityTestTuTuEncodedByte = 0xc9;

    extern const score_t kNormalizedPointwiseMutualInformationTestM1M2Unencoded;
    extern const score_t kNormalizedPointwiseMutualInformationTestM1M2Encoded;
    extern const byte_t kNormalizedPointwiseMutualInformationTestM1M2EncodedByte;
    extern const score_t kNormalizedPointwiseMutualInformationTestM1M3Unencoded;
    extern const score_t kNormalizedPointwiseMutualInformationTestM1M3Encoded;
    extern const byte_t kNormalizedPointwiseMutualInformationTestM1M3EncodedByte;
    extern const score_t kNormalizedPointwiseMutualInformationTestMzMzUnencoded;
    extern const score_t kNormalizedPointwiseMutualInformationTestMzMzEncoded;
    extern const byte_t kNormalizedPointwiseMutualInformationTestMzMzEncodedByte;
    extern const score_t kNormalizedPointwiseMutualInformationTestMzMuUnencoded;
    extern const score_t kNormalizedPointwiseMutualInformationTestMzMuEncoded;
    extern const byte_t kNormalizedPointwiseMutualInformationTestMzMuEncodedByte;
    extern const score_t kNormalizedPointwiseMutualInformationTestMuMuUnencoded;
    extern const score_t kNormalizedPointwiseMutualInformationTestMuMuEncoded;
    extern const byte_t kNormalizedPointwiseMutualInformationTestMuMuEncodedByte;

    const score_t kNormalizedPointwiseMutualInformationTestM1M2Unencoded = 0.3947147f;
    const score_t kNormalizedPointwiseMutualInformationTestM1M2Encoded = 0.39f;
    const byte_t kNormalizedPointwiseMutualInformationTestM1M2EncodedByte = 0x8c;
    const score_t kNormalizedPointwiseMutualInformationTestM1M3Unencoded = NAN;
    const score_t kNormalizedPointwiseMutualInformationTestM1M3Encoded = NAN;
    const byte_t kNormalizedPointwiseMutualInformationTestM1M3EncodedByte = 0xca;
    const score_t kNormalizedPointwiseMutualInformationTestMzMzUnencoded = 1.0f;
    const score_t kNormalizedPointwiseMutualInformationTestMzMzEncoded = 1.0f;
    const byte_t kNormalizedPointwiseMutualInformationTestMzMzEncodedByte = 0xc9;
    const score_t kNormalizedPointwiseMutualInformationTestMzMuUnencoded = -1.0f;
    const score_t kNormalizedPointwiseMutualInformationTestMzMuEncoded = -1.0f;
    const byte_t kNormalizedPointwiseMutualInformationTestMzMuEncodedByte = 0x00;
    const score_t kNormalizedPointwiseMutualInformationTestMuMuUnencoded = 1.0f;
    const score_t kNormalizedPointwiseMutualInformationTestMuMuEncoded = 1.0f;
    const byte_t kNormalizedPointwiseMutualInformationTestMuMuEncodedByte = 0xc9;

    typedef int boolean_t;
    extern const boolean_t kTrue;
    extern const boolean_t kFalse;
    const boolean_t kTrue = 1;
    const boolean_t kFalse = 0;

    /* encoding to two decimals of precision specifies needed accuracy */
    extern const score_t kEpsilon;
    extern const score_t kEpsilonLessStringent;
    const score_t kEpsilon = 0.0000001f;
    const score_t kEpsilonLessStringent = 0.001f;

    extern const score_t kSelfCorrelationScore;
    const score_t kSelfCorrelationScore = +1.0f;

    extern const score_t kNoCorrelationScore;
    const score_t kNoCorrelationScore = +0.0f;

    extern const int kQueryIndexDelim;
    const int kQueryIndexDelim = (int) '-';

    extern const int kQueryRangeBetweenDelim;
    const int kQueryRangeBetweenDelim = (int) '-';

    extern const int kQueryRangeWithinDelim;
    const int kQueryRangeWithinDelim = (int) ':';

    extern const int kQueryMultipleIndexDelim;
    const int kQueryMultipleIndexDelim = (int) ',';

    extern const int kSignalDelim;
    const int kSignalDelim = (int) ',';

    extern const int kSignalByteAlignment;
    const int kSignalByteAlignment = 64;

    typedef struct signal {
        uint32_t n;
        score_t* data;
        boolean_t data_contains_nan;
        score_t mean;
        score_t sd;
        rank_t* ranks;
        score_t mean_ranks;
        score_t sd_ranks;
    } signal_t;

    typedef struct element {
        char* chr;
        uint64_t start;
        uint64_t stop;
        char* id;
        signal_t* signal;
    } element_t;

    typedef struct lookup {
        uint64_t capacity;
        uint32_t nelems;
        element_t** elems;
    } lookup_t;

    typedef struct store_attr {
        uint32_t nelems;
        uint64_t nbytes;
        char* fn;
    } store_attr_t;

    typedef struct sut_store {
        store_attr_t* attr;
    } sut_store_t;

    typedef struct sqr_store {
        store_attr_t* attr;
    } sqr_store_t;

    typedef struct store_buf_node {
        byte_t data;
        struct store_buf_node* next;
    } store_buf_node_t;

    typedef struct store_buf_row_node {
        struct store_buf_node* head;
        struct store_buf_node* tail;
    } store_buf_row_node_t;

    typedef enum store_type {
        kStorePearsonRSUT = 0,
        kStorePearsonRSquareMatrix,
        kStorePearsonRSquareMatrixSplit,
        kStorePearsonRSquareMatrixSplitSingleChunk,
        kStorePearsonRSquareMatrixSplitSingleChunkMetadata,
        kStorePearsonRSquareMatrixBzip2,
        kStorePearsonRSquareMatrixBzip2Split,
        kStoreSpearmanRhoSquareMatrix,
        kStoreSpearmanRhoSquareMatrixSplit,
        kStoreSpearmanRhoSquareMatrixSplitSingleChunk,
        kStoreSpearmanRhoSquareMatrixSplitSingleChunkMetadata,
        kStoreSpearmanRhoSquareMatrixBzip2,
        kStoreSpearmanRhoSquareMatrixBzip2Split,
        kStoreNormalizedEuclideanDistanceSquareMatrix,
        kStoreNormalizedEuclideanDistanceSquareMatrixSplit,
        kStoreNormalizedEuclideanDistanceSquareMatrixSplitSingleChunk,
        kStoreNormalizedEuclideanDistanceSquareMatrixSplitSingleChunkMetadata,
        kStoreCosineSimilaritySquareMatrix,
        kStoreCosineSimilaritySquareMatrixSplit,
        kStoreCosineSimilaritySquareMatrixSplitSingleChunk,
        kStoreCosineSimilaritySquareMatrixSplitSingleChunkMetadata,
        kStoreJaccardIndexSquareMatrix,
        kStoreJaccardIndexSquareMatrixSplit,
        kStoreJaccardIndexSquareMatrixSplitSingleChunk,
        kStoreJaccardIndexSquareMatrixSplitSingleChunkMetadata,
        kStoreOchiaiSimilaritySquareMatrix,
        kStoreOchiaiSimilaritySquareMatrixSplit,
        kStoreOchiaiSimilaritySquareMatrixSplitSingleChunk,
        kStoreOchiaiSimilaritySquareMatrixSplitSingleChunkMetadata,
        kStorePearsonPhiSimilaritySquareMatrix,
        kStorePearsonPhiSimilaritySquareMatrixSplit,
        kStorePearsonPhiSimilaritySquareMatrixSplitSingleChunk,
        kStorePearsonPhiSimilaritySquareMatrixSplitSingleChunkMetadata,
        kStoreRogersAndTanimotoSimilaritySquareMatrix,
        kStoreRogersAndTanimotoSimilaritySquareMatrixSplit,
        kStoreRogersAndTanimotoSimilaritySquareMatrixSplitSingleChunk,
        kStoreRogersAndTanimotoSimilaritySquareMatrixSplitSingleChunkMetadata,
        kStoreNormalizedPointwiseMutualInformationSquareMatrix,
        kStoreNormalizedPointwiseMutualInformationSquareMatrixSplit,
        kStoreNormalizedPointwiseMutualInformationSquareMatrixSplitSingleChunk,
        kStoreNormalizedPointwiseMutualInformationSquareMatrixSplitSingleChunkMetadata,
        kStoreRandomSUT,
        kStoreRandomSquareMatrix,
        kStoreRandomBufferedSquareMatrix,
        kStoreUndefined
    } store_type_t;

    /* the order here is important, due to the integer value being used in metadata */

    typedef enum score_variety {
        kScoreVarietyPearsonR = 0,
        kScoreVarietySpearmanRho,
        kScoreVarietyJaccardIndex,
        kScoreVarietyOchiaiSimilarity,
        kScoreVarietyPearsonPhiSimilarity,
        kScoreVarietyRogersAndTanimotoSimilarity,
        kScoreVarietyNormalizedPointwiseMutualInformation,
        kScoreVarietyNormalizedEuclideanDistance,
        kScoreVarietyCosineSimilarity,
        kScoreVarietyUndefined
    } score_variety_t;

    extern const char* kStorePearsonRSUTStr;
    extern const char* kStorePearsonRSquareMatrixStr;
    extern const char* kStorePearsonRSquareMatrixSplitStr;
    extern const char* kStorePearsonRSquareMatrixSplitSingleChunkStr;
    extern const char* kStorePearsonRSquareMatrixSplitSingleChunkMetadataStr;
    extern const char* kStorePearsonRSquareMatrixBzip2Str;
    extern const char* kStorePearsonRSquareMatrixBzip2SplitStr;
    extern const char* kStoreSpearmanRhoSquareMatrixStr;
    extern const char* kStoreSpearmanRhoSquareMatrixSplitStr;
    extern const char* kStoreSpearmanRhoSquareMatrixSplitSingleChunkStr;
    extern const char* kStoreSpearmanRhoSquareMatrixSplitSingleChunkMetadataStr;
    extern const char* kStoreSpearmanRhoSquareMatrixBzip2Str;
    extern const char* kStoreSpearmanRhoSquareMatrixBzip2SplitStr;
    extern const char* kStoreNormalizedEuclideanDistanceSquareMatrixStr;
    extern const char* kStoreNormalizedEuclideanDistanceSquareMatrixSplitStr;
    extern const char* kStoreNormalizedEuclideanDistanceSquareMatrixSplitSingleChunkStr;
    extern const char* kStoreNormalizedEuclideanDistanceSquareMatrixSplitSingleChunkMetadataStr;
    extern const char* kStoreCosineSimilaritySquareMatrixStr;
    extern const char* kStoreCosineSimilaritySquareMatrixSplitStr;
    extern const char* kStoreCosineSimilarityMatrixSplitSingleChunkStr;
    extern const char* kStoreCosineSimilaritySplitSingleChunkMetadataStr;
    extern const char* kStoreJaccardIndexSquareMatrixStr;
    extern const char* kStoreJaccardIndexSquareMatrixSplitStr;
    extern const char* kStoreJaccardIndexSquareMatrixSplitSingleChunkStr;
    extern const char* kStoreJaccardIndexSquareMatrixSplitSingleChunkMetadataStr;
    extern const char* kStoreOchiaiSimilaritySquareMatrixStr;
    extern const char* kStoreOchiaiSimilaritySquareMatrixSplitStr;
    extern const char* kStoreOchiaiSimilaritySquareMatrixSplitSingleChunkStr;
    extern const char* kStoreOchiaiSimilaritySquareMatrixSplitSingleChunkMetadataStr;
    extern const char* kStorePearsonPhiSimilaritySquareMatrixStr;
    extern const char* kStorePearsonPhiSimilaritySquareMatrixSplitStr;
    extern const char* kStorePearsonPhiSimilaritySquareMatrixSplitSingleChunkStr;
    extern const char* kStorePearsonPhiSimilaritySquareMatrixSplitSingleChunkMetadataStr;
    extern const char* kStoreRogersAndTanimotoSimilaritySquareMatrixStr;
    extern const char* kStoreRogersAndTanimotoSimilaritySquareMatrixSplitStr;
    extern const char* kStoreRogersAndTanimotoSimilaritySquareMatrixSplitSingleChunkStr;
    extern const char* kStoreRogersAndTanimotoSimilaritySquareMatrixSplitSingleChunkMetadataStr;
    extern const char* kStoreNormalizedPointwiseMutualInformationSquareMatrixStr;
    extern const char* kStoreNormalizedPointwiseMutualInformationSquareMatrixSplitStr;
    extern const char* kStoreNormalizedPointwiseMutualInformationSquareMatrixSplitSingleChunkStr;
    extern const char* kStoreNormalizedPointwiseMutualInformationSquareMatrixSplitSingleChunkMetadataStr;
    extern const char* kStoreRandomSUTStr;
    extern const char* kStoreRandomSquareMatrixStr;
    extern const char* kStoreRandomBufferedSquareMatrixStr;

    const char* kStorePearsonRSUTStr = "pearson-r-sut";
    const char* kStorePearsonRSquareMatrixStr = "pearson-r-sqr";
    const char* kStorePearsonRSquareMatrixSplitStr = "pearson-r-sqr-split";
    const char* kStorePearsonRSquareMatrixSplitSingleChunkStr = "pearson-r-sqr-split-single-chunk";
    const char* kStorePearsonRSquareMatrixSplitSingleChunkMetadataStr = "pearson-r-sqr-split-single-chunk-metadata";
    const char* kStorePearsonRSquareMatrixBzip2Str = "pearson-r-sqr-bzip2";
    const char* kStorePearsonRSquareMatrixBzip2SplitStr = "pearson-r-sqr-bzip2-split";
    const char* kStoreSpearmanRhoSquareMatrixStr = "spearman-rho-sqr";
    const char* kStoreSpearmanRhoSquareMatrixSplitStr = "spearman-rho-sqr-split";
    const char* kStoreSpearmanRhoSquareMatrixSplitSingleChunkStr = "spearman-rho-sqr-split-single-chunk";
    const char* kStoreSpearmanRhoSquareMatrixSplitSingleChunkMetadataStr = "spearman-rho-sqr-split-single-chunk-metadata";
    const char* kStoreSpearmanRhoSquareMatrixBzip2Str = "spearman-rho-sqr-bzip2";
    const char* kStoreSpearmanRhoSquareMatrixBzip2SplitStr = "spearman-rho-sqr-bzip2-split";
    const char* kStoreNormalizedEuclideanDistanceSquareMatrixStr = "normalized-euclidean-distance-sqr";
    const char* kStoreNormalizedEuclideanDistanceSquareMatrixSplitStr = "normalized-euclidean-distance-sqr-split";
    const char* kStoreNormalizedEuclideanDistanceSquareMatrixSplitSingleChunkStr = "normalized-euclidean-distance-sqr-split-single-chunk";
    const char* kStoreNormalizedEuclideanDistanceSquareMatrixSplitSingleChunkMetadataStr = "normalized-euclidean-distance-sqr-split-single-chunk-metadata";
    const char* kStoreCosineSimilaritySquareMatrixStr = "cosine-similarity-sqr";
    const char* kStoreCosineSimilaritySquareMatrixSplitStr = "cosine-similarity-sqr-split";
    const char* kStoreCosineSimilaritySquareMatrixSplitSingleChunkStr = "cosine-similarity-sqr-split-single-chunk";
    const char* kStoreCosineSimilaritySquareMatrixSplitSingleChunkMetadataStr = "cosine-similarity-sqr-split-single-chunk-metadata";
    const char* kStoreJaccardIndexSquareMatrixStr = "jaccard-index-sqr";
    const char* kStoreJaccardIndexSquareMatrixSplitStr = "jaccard-index-sqr-split";
    const char* kStoreJaccardIndexSquareMatrixSplitSingleChunkStr = "jaccard-index-sqr-split-single-chunk";
    const char* kStoreJaccardIndexSquareMatrixSplitSingleChunkMetadataStr = "jaccard-index-sqr-split-single-chunk-metadata";
    const char* kStoreOchiaiSimilaritySquareMatrixStr = "ochiai-similarity-sqr";
    const char* kStoreOchiaiSimilaritySquareMatrixSplitStr = "ochiai-similarity-sqr-split";
    const char* kStoreOchiaiSimilaritySquareMatrixSplitSingleChunkStr = "ochiai-similarity-sqr-split-single-chunk";
    const char* kStoreOchiaiSimilaritySquareMatrixSplitSingleChunkMetadataStr = "ochiai-similarity-sqr-split-single-chunk-metadata";
    const char* kStorePearsonPhiSimilaritySquareMatrixStr = "pearson-phi-similarity-sqr";
    const char* kStorePearsonPhiSimilaritySquareMatrixSplitStr = "pearson-phi-similarity-sqr-split";
    const char* kStorePearsonPhiSimilaritySquareMatrixSplitSingleChunkStr = "pearson-phi-similarity-sqr-split-single-chunk";
    const char* kStorePearsonPhiSimilaritySquareMatrixSplitSingleChunkMetadataStr = "pearson-phi-similarity-sqr-split-single-chunk-metadata";
    const char* kStoreRogersAndTanimotoSimilaritySquareMatrixStr = "rogers-and-tanimoto-similarity-sqr";
    const char* kStoreRogersAndTanimotoSimilaritySquareMatrixSplitStr = "rogers-and-tanimoto-similarity-sqr-split";
    const char* kStoreRogersAndTanimotoSimilaritySquareMatrixSplitSingleChunkStr = "rogers-and-tanimoto-similarity-sqr-split-single-chunk";
    const char* kStoreRogersAndTanimotoSimilaritySquareMatrixSplitSingleChunkMetadataStr = "rogers-and-tanimoto-similarity-sqr-split-single-chunk-metadata";
    const char* kStoreNormalizedPointwiseMutualInformationSquareMatrixStr = "normalized-pointwise-mutual-information-sqr";
    const char* kStoreNormalizedPointwiseMutualInformationSquareMatrixSplitStr = "normalized-pointwise-mutual-information-sqr-split";
    const char* kStoreNormalizedPointwiseMutualInformationSquareMatrixSplitSingleChunkStr = "normalized-pointwise-mutual-information-sqr-split-single-chunk";
    const char* kStoreNormalizedPointwiseMutualInformationSquareMatrixSplitSingleChunkMetadataStr = "normalized-pointwise-mutual-information-sqr-split-single-chunk-metadata";
    const char* kStoreRandomSUTStr = "random-sut";
    const char* kStoreRandomSquareMatrixStr = "random-sqr";
    const char* kStoreRandomBufferedSquareMatrixStr = "random-buffered-sqr";

    typedef enum encoding_strategy {
        kEncodingStrategyFull = 0,
        kEncodingStrategyMidQuarterZero,
        kEncodingStrategyCustom,
        kEncodingStrategyUndefined
    } encoding_strategy_t;

    extern const char* kEncodingStrategyFullStr;
    extern const char* kEncodingStrategyMidQuarterZeroStr;
    extern const char* kEncodingStrategyCustomStr;
    extern const score_t kEncodingStrategyDefaultCutoff;

    const char* kEncodingStrategyFullStr = "full";
    const char* kEncodingStrategyMidQuarterZeroStr = "mid-quarter-zero";
    const char* kEncodingStrategyCustomStr = "custom";
    const score_t kEncodingStrategyDefaultCutoff = -DBL_MAX;

    extern const uint32_t kRowChunkDefaultSize;
    extern const uint32_t kRowChunkDefaultOffset;

    const uint32_t kRowChunkDefaultSize = UINT32_MAX;
    const uint32_t kRowChunkDefaultOffset = UINT32_MAX;

    extern const char* kRawMetadataSplitFn;
    extern const char* kRawMetadataSplitDirSuffix;

    const char* kRawMetadataSplitFn = "blocks.md";
    const char* kRawMetadataSplitDirSuffix = ""; /* formerly set to "blocks" -- see kCompressionMetadataSplitDirSuffix */

    extern const char* kRawFrequencySuffixFn;

    const char* kRawFrequencySuffixFn = "frequency.txt";

    extern const uint32_t kCompressionRowChunkMaximumSize;
    extern const uint32_t kCompressionBzip2BlockSize100k;
    extern const uint32_t kCompressionBzip2BlockSizeFactor;
    extern const uint32_t kCompressionBzip2Verbosity;
    extern const uint32_t kCompressionBzip2WorkFactor;
    extern const uint32_t kCompressionBzip2AbandonPolicy;
    extern const uint32_t kCompressionBzip2SmallPolicy;

    const uint32_t kCompressionRowChunkMaximumSize = 512;
    const uint32_t kCompressionBzip2BlockSize100k = 9;
    const uint32_t kCompressionBzip2BlockSizeFactor = 100000;
    const uint32_t kCompressionBzip2Verbosity = 0;
    const uint32_t kCompressionBzip2WorkFactor = 30;
    const uint32_t kCompressionBzip2AbandonPolicy = 0;
    const uint32_t kCompressionBzip2SmallPolicy = 0;

    extern const char kCompressionMetadataDelimiter;
    extern const float kCompressionMetadataVersion;
    extern const float kCompressionMetadataVersion1p0;
    extern const float kCompressionMetadataVersion1p1;
    extern const float kCompressionMetadataVersion1p2;
    extern const char* kCompressionMetadataSplitFn;
    extern const char* kCompressionMetadataSplitDirSuffix;

    const char kCompressionMetadataDelimiter = '|';
    const float kCompressionMetadataVersion1p0 = 1.0f;
    const float kCompressionMetadataVersion1p1 = 1.1f;
    const float kCompressionMetadataVersion1p2 = 1.2f;
    const float kCompressionMetadataVersion = 1.2f;
    const char* kCompressionMetadataSplitFn = "blocks.md";
    const char* kCompressionMetadataSplitDirSuffix = ""; /* formerly set to "blocks" -- this should match kRawMetadataSplitDirSuffix */

    extern const uint32_t kPermutationTestDefaultCount;
    extern const score_t kPermutationTestDefaultPrecision;
    extern const score_t kPermutationTestDefaultAlpha;
    extern const uint32_t kPermutationTestDefaultSignificanceLevel;

    const uint32_t kPermutationTestDefaultCount = 0;
    const score_t kPermutationTestDefaultPrecision = 0.01f;
    const score_t kPermutationTestDefaultAlpha = 0.01f;
    const uint32_t kPermutationTestDefaultSignificanceLevel = 3;

    typedef struct metadata {
        score_variety_t score_variety;
        off_t* offsets;
        size_t count;
        size_t block_row_size;
        score_t normalization_factor;
        double version;
    } metadata_t;

    extern const uint32_t kQueryIndexDefaultStart;
    extern const uint32_t kQueryIndexDefaultEnd;
    extern const char* kQueryRangeDefaultChromosome;
    extern const uint64_t kQueryRangeDefaultStart;
    extern const uint64_t kQueryRangeDefaultEnd;

    const uint32_t kQueryIndexDefaultStart = 0;
    const uint32_t kQueryIndexDefaultEnd = 0;
    const char* kQueryRangeDefaultChromosome = "chrXYZ";
    const uint64_t kQueryRangeDefaultStart = 0;
    const uint64_t kQueryRangeDefaultEnd = 0;

    typedef struct bed {
        char* chromosome;
        uint64_t start;
        uint64_t end;
    } bed_t;

    typedef enum query_kind {
        kQueryKindIndex,
        kQueryKindMultipleIndices,
        kQueryKindMultipleIndicesFromFile,
        kQueryKindMultipleRowAndColumnIndicesFromFile,
        kQueryKindRange,
        kQueryKindDiagonalOffset,
        kQueryKindUndefined
    } query_kind_t;

    extern const query_kind_t kQueryKindDefaultKind;

    const query_kind_t kQueryKindDefaultKind = kQueryKindUndefined;

    typedef enum score_filter {
        kScoreFilterNone = 0,
        kScoreFilterGtEq,
        kScoreFilterGt,
        kScoreFilterEq,
        kScoreFilterLtEq,
        kScoreFilterLt,
        kScoreFilterRangedWithinExclusive,
        kScoreFilterRangedWithinInclusive,
        kScoreFilterRangedOutsideExclusive,
        kScoreFilterRangedOutsideInclusive,
        kScoreFilterUndefined
    } score_filter_t;

    extern const score_filter_t kScoreDefaultFilter;
    const score_filter_t kScoreDefaultFilter = kScoreFilterNone;

    extern const char* kScoreFilterGtEqStr;
    extern const char* kScoreFilterGtStr;
    extern const char* kScoreFilterEqStr;
    extern const char* kScoreFilterLtEqStr;
    extern const char* kScoreFilterLtStr;
    extern const char* kScoreFilterRangedWithinExclusiveStr;
    extern const char* kScoreFilterRangedWithinInclusiveStr;
    extern const char* kScoreFilterRangedOutsideExclusiveStr;
    extern const char* kScoreFilterRangedOutsideInclusiveStr;

    const char* kScoreFilterGtEqStr = "greater-than-inclusive";
    const char* kScoreFilterGtStr = "greater-than-exclusive";
    const char* kScoreFilterEqStr = "equal";
    const char* kScoreFilterLtEqStr = "less-than-inclusive";
    const char* kScoreFilterLtStr = "less-than-exclusive";
    const char* kScoreFilterRangedWithinExclusiveStr = "within-exclusive";
    const char* kScoreFilterRangedWithinInclusiveStr = "within-inclusive";
    const char* kScoreFilterRangedOutsideExclusiveStr = "outside-exclusive";
    const char* kScoreFilterRangedOutsideInclusiveStr = "outside-inclusive";

    typedef enum diagonal_side {
        kDiagonalSideLowerTriangle = 0,
        kDiagonalSideUpperTriangle,
        kDiagonalSideUndefined
    } diagonal_side_t;
    
    static struct bs_globals_t {
        boolean_t store_create_flag;
        boolean_t store_query_flag;
        boolean_t store_query_daemon_flag;
        int32_t store_query_daemon_port;
        char* store_query_daemon_hostname;
        boolean_t store_frequency_flag;
        query_kind_t store_query_kind;
        char store_query_str[QUERY_MAX_LEN];
        size_t store_query_idx_start;
        size_t store_query_idx_end;
        size_t* store_query_indices;
        uint32_t store_query_indices_num;
        uint32_t store_query_indices_capacity;
        size_t* store_query_indices_starts;
        size_t* store_query_indices_ends;
        bed_t* store_query_range_start;
        bed_t* store_query_range_end;
        score_filter_t store_filter;
        score_t score_filter_cutoff;
        score_t score_filter_cutoff_lower_bound;
        score_t score_filter_cutoff_upper_bound; /* for threshold ranges */
        boolean_t score_filter_range_set;
        boolean_t store_filter_mutual_set;
        boolean_t rng_seed_flag;
        uint32_t rng_seed_value;
        char lookup_fn[FN_MAX_LEN];
        char store_fn[FN_MAX_LEN];
        char store_type_str[BUF_MAX_LEN];
        store_type_t store_type;
        encoding_strategy_t encoding_strategy;
        char encoding_strategy_str[BUF_MAX_LEN];
        score_t encoding_cutoff_zero_min;
        score_t encoding_cutoff_zero_max;
        uint32_t store_row_chunk_size;
        uint32_t store_row_chunk_offset;
        boolean_t store_chunk_size_specified_flag;
        boolean_t store_single_chunk_flag;
        boolean_t store_compression_flag;
        boolean_t lookup_frequency_flag;
        boolean_t permutation_test_flag;
        uint32_t permutation_count;
        score_t permutation_precision;
        score_t permutation_alpha;
        uint32_t permutation_significance_level;
        boolean_t zero_sd_warning_issued;
        score_t* score_ptr;
        lookup_t* lookup_ptr;
        sqr_store_t* sqr_store_ptr;
        char* bedextract_path;
        char* bedops_path;
        char* bedmap_path;
        char* sortbed_path;
        boolean_t enable_ssl;
        char* ssl_key_pem;
        char* ssl_cert_pem;
        uint32_t diagonal_offset_value;
        diagonal_side_t diagonal_offset_side;
        boolean_t score_normalization_factor_specified_flag;
        score_t score_normalization_factor;
    } bs_globals;

    static struct option bs_client_long_options[] = {
        { "store-type",                                          required_argument, NULL, 't' },
        { "store-create",                                        no_argument,       NULL, 'c' },
        { "store-query",                                         no_argument,       NULL, 'q' },
        { "store-query-daemon",                                  required_argument, NULL, 'Q' },
        { "store-frequency",                                     no_argument,       NULL, 'f' },
        { "store-row-chunk-size",                                required_argument, NULL, 'r' },
        { "store-row-chunk-offset",                              required_argument, NULL, 'k' },
        { "score-filter-gteq",                                   required_argument, NULL, '2' },
        { "score-filter-gt",                                     required_argument, NULL, '3' },
        { "score-filter-eq",                                     required_argument, NULL, '4' },
        { "score-filter-lteq",                                   required_argument, NULL, '5' },
        { "score-filter-lt",                                     required_argument, NULL, '6' },
        { "score-filter-ranged-within-exclusive",                required_argument, NULL, '7' },
        { "score-filter-ranged-within-inclusive",                required_argument, NULL, '8' },
        { "score-filter-ranged-outside-exclusive",               required_argument, NULL, '9' },
        { "score-filter-ranged-outside-inclusive",               required_argument, NULL, '0' },
        { "score-normalization-factor",                          required_argument, NULL, 'F' },
        { "mutual-query",                                        no_argument,       NULL, 'm' },
        { "index-query",                                         required_argument, NULL, 'i' },
        { "multiple-index-query",                                required_argument, NULL, 'w' },
        { "multiple-index-query-from-file",                      required_argument, NULL, 'z' },
        { "multiple-row-and-column-index-query-from-file",       required_argument, NULL, 'Z' },
        { "range-query",                                         required_argument, NULL, 'g' },
        { "diagonal-offset-query",                               required_argument, NULL, 'b' },
        { "lookup",                                              required_argument, NULL, 'l' },
        { "store",                                               required_argument, NULL, 's' },
        { "encoding-strategy",                                   required_argument, NULL, 'e' },
        { "encoding-cutoff-zero-min",                            required_argument, NULL, 'n' },
        { "encoding-cutoff-zero-max",                            required_argument, NULL, 'x' },
        { "lookup-frequency",                                    no_argument,       NULL, 'u' },
        { "permutation-test",                                    no_argument,       NULL, 'y' },
        { "permutation-count",                                   required_argument, NULL, 'o' },
        { "permutation-precision",                               required_argument, NULL, 'p' },
        { "permutation-alpha",                                   required_argument, NULL, 'a' },
        { "permutation-significance-level",                      required_argument, NULL, 'v' },
        { "rng-seed",                                            required_argument, NULL, 'd' },
        { "enable-ssl",                                          no_argument,       NULL, 'E' },
        { "ssl-key",                                             required_argument, NULL, 'K' },
        { "ssl-cert",                                            required_argument, NULL, 'C' },
        { "test-pearson-r",                                      no_argument,       NULL, 'P' },
        { "test-spearman-rho",                                   no_argument,       NULL, 'S' },
        { "test-normalized-euclidean-distance",                  no_argument,       NULL, 'D' },
        { "test-cosine-similarity",                              no_argument,       NULL, 'I' },
        { "test-jaccard-index",                                  no_argument,       NULL, 'J' },
        { "test-ochiai-similarity",                              no_argument,       NULL, 'O' },
        { "test-pearson-phi-similarity",                         no_argument,       NULL, 'H' },
        { "test-rogers-and-tanimoto-similarity",                 no_argument,       NULL, 'T' },
        { "test-normalized-pointwise-mutual-information",        no_argument,       NULL, 'M' },
        { "test-score-encoder",                                  no_argument,       NULL, 'N' },
        { "help",                                                no_argument,       NULL, 'h' },
        { NULL,                                                  no_argument,       NULL,  0  }
    };

    static const char* bs_client_opt_string = "t:cqQ:fr:k:2:3:4:5:6:7:8:9:0:F:mi:w:z:Z:g:b:l:s:e:n:x:uyo:p:a:v:d:EK:C:SDIPJOHTMNh?";

    static const char* bs_name = "byte-store";

    /**
     * @brief      bs_encode_byte_to_score_table[]
     *
     * @details    Converts encoded byte to assigned bin interval start, 
     *             e.g., 0x64 maps to -0.00 or (-0.01, -0.00], while 
     *             0x65 maps to +0.00 or [+0.00, +0.01). 
     *
     *             Note the two bins for -0.00 and +0.00. This allows 
     *             mapping of scores between -0.01, 0.00, and 0.01 to 
     *             be mapped to two seperate bytes.
     *
     *             Bins are arranged in base-16 for convenience: read from 
     *             left to right to get bytes 0xI0 through 0xIf; read down
     *             from top to bottom to get bytes 0x0J through 0xfJ.
     */

    static const score_t bs_encode_byte_to_score_table[256] =
        {-1.00, -0.99, -0.98, -0.97, -0.96, -0.95, -0.94, -0.93, -0.92, -0.91, -0.90, -0.89, -0.88, -0.87, -0.86, -0.85,
         -0.84, -0.83, -0.82, -0.81, -0.80, -0.79, -0.78, -0.77, -0.76, -0.75, -0.74, -0.73, -0.72, -0.71, -0.70, -0.69,
         -0.68, -0.67, -0.66, -0.65, -0.64, -0.63, -0.62, -0.61, -0.60, -0.59, -0.58, -0.57, -0.56, -0.55, -0.54, -0.53,
         -0.52, -0.51, -0.50, -0.49, -0.48, -0.47, -0.46, -0.45, -0.44, -0.43, -0.42, -0.41, -0.40, -0.39, -0.38, -0.37,
         -0.36, -0.35, -0.34, -0.33, -0.32, -0.31, -0.30, -0.29, -0.28, -0.27, -0.26, -0.25, -0.24, -0.23, -0.22, -0.21,
         -0.20, -0.19, -0.18, -0.17, -0.16, -0.15, -0.14, -0.13, -0.12, -0.11, -0.10, -0.09, -0.08, -0.07, -0.06, -0.05,
         -0.04, -0.03, -0.02, -0.01, -0.00, +0.00, +0.01, +0.02, +0.03, +0.04, +0.05, +0.06, +0.07, +0.08, +0.09, +0.10,
         +0.11, +0.12, +0.13, +0.14, +0.15, +0.16, +0.17, +0.18, +0.19, +0.20, +0.21, +0.22, +0.23, +0.24, +0.25, +0.26,
         +0.27, +0.28, +0.29, +0.30, +0.31, +0.32, +0.33, +0.34, +0.35, +0.36, +0.37, +0.38, +0.39, +0.40, +0.41, +0.42,
         +0.43, +0.44, +0.45, +0.46, +0.47, +0.48, +0.49, +0.50, +0.51, +0.52, +0.53, +0.54, +0.55, +0.56, +0.57, +0.58,
         +0.59, +0.60, +0.61, +0.62, +0.63, +0.64, +0.65, +0.66, +0.67, +0.68, +0.69, +0.70, +0.71, +0.72, +0.73, +0.74,
         +0.75, +0.76, +0.77, +0.78, +0.79, +0.80, +0.81, +0.82, +0.83, +0.84, +0.85, +0.86, +0.87, +0.88, +0.89, +0.90,
         +0.91, +0.92, +0.93, +0.94, +0.95, +0.96, +0.97, +0.98, +0.99, +1.00,   NAN, +0.00, +0.00, +0.00, +0.00, +0.00,
         +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00,
         +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00,
         +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00};

    /**
     * @brief      bs_encode_unsigned_char_to_score_mqz_table[]
     *
     * @details    Converts encoded byte to assigned bin interval start, 
     *             but maps (-0.25, +0.25) to +0.00
     */

    static const score_t bs_encode_byte_to_score_mqz_table[256] =
        {-1.00, -0.99, -0.98, -0.97, -0.96, -0.95, -0.94, -0.93, -0.92, -0.91, -0.90, -0.89, -0.88, -0.87, -0.86, -0.85,
         -0.84, -0.83, -0.82, -0.81, -0.80, -0.79, -0.78, -0.77, -0.76, -0.75, -0.74, -0.73, -0.72, -0.71, -0.70, -0.69,
         -0.68, -0.67, -0.66, -0.65, -0.64, -0.63, -0.62, -0.61, -0.60, -0.59, -0.58, -0.57, -0.56, -0.55, -0.54, -0.53,
         -0.52, -0.51, -0.50, -0.49, -0.48, -0.47, -0.46, -0.45, -0.44, -0.43, -0.42, -0.41, -0.40, -0.39, -0.38, -0.37,
         -0.36, -0.35, -0.34, -0.33, -0.32, -0.31, -0.30, -0.29, -0.28, -0.27, -0.26, -0.25, +0.00, +0.00, +0.00, +0.00,
         +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00,
         +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00,
         +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.25, +0.26,
         +0.27, +0.28, +0.29, +0.30, +0.31, +0.32, +0.33, +0.34, +0.35, +0.36, +0.37, +0.38, +0.39, +0.40, +0.41, +0.42,
         +0.43, +0.44, +0.45, +0.46, +0.47, +0.48, +0.49, +0.50, +0.51, +0.52, +0.53, +0.54, +0.55, +0.56, +0.57, +0.58,
         +0.59, +0.60, +0.61, +0.62, +0.63, +0.64, +0.65, +0.66, +0.67, +0.68, +0.69, +0.70, +0.71, +0.72, +0.73, +0.74,
         +0.75, +0.76, +0.77, +0.78, +0.79, +0.80, +0.81, +0.82, +0.83, +0.84, +0.85, +0.86, +0.87, +0.88, +0.89, +0.90,
         +0.91, +0.92, +0.93, +0.94, +0.95, +0.96, +0.97, +0.98, +0.99, +1.00,   NAN, +0.00, +0.00, +0.00, +0.00, +0.00,
         +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00,
         +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00,
         +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00, +0.00};

    /* daemon-related definitions */

    typedef enum bs_qd_connection_method {
        kBSQDConnectionMethodGET,
        kBSQDConnectionMethodPOST,
        kBSQDConnectionMethodHEAD,
        kBSQDConnectionMethodUndefined
    } bs_qd_connection_method_t;

    typedef enum bs_qd_request {
        kBSQDRequestUploadTooLarge,
        kBSQDRequestMalformed,
        kBSQDRequestNotFound,
        kBSQDRequestParametersNotFound,
        kBSQDRequestGeneric,
        kBSQDRequestInformation,
        kBSQDRequestRandom,
        kBSQDRequestRandomViaHeap,
        kBSQDRequestRandomViaTemporaryFile,
        kBSQDRequestElements,
        kBSQDRequestElementsViaHeap,
        kBSQDRequestElementsViaTemporaryFile,
        kBSQDRequestUndefined
    } bs_qd_request_t;

    extern const char* kBSQDPairingWholeGenomeStr;
    extern const char* kBSQDPairingMutualStr;

    const char* kBSQDPairingWholeGenomeStr = "wholeGenome";
    const char* kBSQDPairingMutualStr = "mutual";

    typedef enum bs_qd_pairing {
        kBSQDPairingWholeGenome,
        kBSQDPairingMutual,
        kBSQDPairingUndefined
    } bs_qd_pairing_t;

    extern const char* kBSQDSortOffStr;
    extern const char* kBSQDSortIntervalStr;
    extern const char* kBSQDSortScoreStr;

    const char* kBSQDSortOffStr = "off";
    const char* kBSQDSortIntervalStr = "interval";
    const char* kBSQDSortScoreStr = "score";

    typedef enum bs_qd_postsort {
        kBSQDSortOff,
        kBSQDSortInterval,
        kBSQDSortScore,
        kBSQDSortUndefined
    } bs_qd_postsort_t;

    typedef struct bs_qd_filter_param {
        score_filter_t type;
        score_t lone_bound;
        score_t lower_bound;
        score_t upper_bound;
        boolean_t bounds_set;
        int32_t padding;
        boolean_t padding_set;
        bs_qd_pairing_t pairing;
        boolean_t pairing_set;
        bs_qd_postsort_t postsort;
        boolean_t postsort_set;
    } bs_qd_filter_param_t;

    typedef struct bs_qd_connection_info {
        bs_qd_connection_method_t method;
        bs_qd_request_t request_type;
        uint64_t timestamp;
        struct MHD_PostProcessor* post_processor;
        FILE* upload_fp;
        char* upload_filename;
        size_t upload_filesize;
        FILE* query_index_fp;
        char* query_index_filename;
    } bs_qd_connection_info_t;

    extern const char* bs_qd_bedextract;
    extern const char* bs_qd_bedops;
    extern const char* bs_qd_bedmap;
    extern const char* bs_qd_sortbed;

    const char* bs_qd_bedextract = "bedextract";
    const char* bs_qd_bedops = "bedops";
    const char* bs_qd_bedmap = "bedmap";
    const char* bs_qd_sortbed = "sort-bed";

    static int                   bs_qd_request_generic_information(const void* cls, const char* mime, struct MHD_Connection* connection, bs_qd_connection_info_t* con_info, const char* upload_data, size_t* upload_data_size);
    static int                   bs_qd_request_elements_via_temporary_file(const void* cls, const char* mime, struct MHD_Connection* connection, bs_qd_connection_info_t* con_info, const char* upload_data, size_t* upload_data_size);
    static int                   bs_qd_request_elements_via_heap(const void* cls, const char* mime, struct MHD_Connection* connection, bs_qd_connection_info_t* con_info, const char* upload_data, size_t* upload_data_size);
    static int                   bs_qd_request_random_element_via_temporary_file(const void* cls, const char* mime, struct MHD_Connection* connection, bs_qd_connection_info_t* con_info, const char* upload_data, size_t* upload_data_size);
    static int                   bs_qd_request_random_element_via_heap(const void* cls, const char* mime, struct MHD_Connection* connection, bs_qd_connection_info_t* con_info, const char* upload_data, size_t* upload_data_size);
    static int                   bs_qd_debug_kv(void* cls, enum MHD_ValueKind kind, const char* key, const char* value);
    static int                   bs_qd_populate_filter_parameters(void* cls, enum MHD_ValueKind kind, const char* key, const char* value);
    static ssize_t               bs_qd_temporary_file_buffer_reader(void* cls, uint64_t pos, char* buf, size_t max);
    static void                  bs_qd_temporary_file_buffer_callback(void* cls);
    static int                   bs_qd_request_malformed(const void* cls, const char* mime, struct MHD_Connection* connection, bs_qd_connection_info_t* con_info, const char* upload_data, size_t* upload_data_size);
    static int                   bs_qd_request_upload_too_large(const void* cls, const char* mime, struct MHD_Connection* connection, bs_qd_connection_info_t* con_info, const char* upload_data, size_t* upload_data_size);
    static int                   bs_qd_request_not_found(const void* cls, const char* mime, struct MHD_Connection* connection, bs_qd_connection_info_t* con_info, const char* upload_data, size_t* upload_data_size);
    static int                   bs_qd_parameters_not_found(const void* cls, const char* mime, struct MHD_Connection* connection, bs_qd_connection_info_t* con_info, const char* upload_data, size_t* upload_data_size);
    static int                   bs_qd_test_answer_to_connection(void* cls, struct MHD_Connection *connection, const char* url, const char* method, const char* version, const char* upload_data, size_t* upload_data_size, void** con_cls);
    static void                  bs_qd_request_completed(void* cls, struct MHD_Connection* connection, void** con_cls, enum MHD_RequestTerminationCode toe);
    static const char*           bs_qd_connection_method_type_to_str(bs_qd_connection_method_t t);
    static const char*           bs_qd_request_type_to_str(bs_qd_request_t t);
    static uint64_t              bs_qd_timestamp();
    static int                   bs_qd_answer_to_connection(void* cls, struct MHD_Connection *connection, const char* url, const char* method, const char* version, const char* upload_data, size_t* upload_data_size, void** con_cls);
    static int                   bs_qd_iterate_elements_post(void *coninfo_cls, enum MHD_ValueKind kind, const char *key, const char *filename, const char *content_type, const char *transfer_encoding, const char *data, uint64_t off, size_t size);
    static char*                 bs_qd_get_host_fqdn();
    static boolean_t             bs_qd_test_dependencies();
    static boolean_t             bs_qd_print_matches(char* path, char* fn);
    static char*                 bs_qd_strsep(char** stringp, const char* delim);
    static boolean_t             bs_qd_is_there(char* candidate);
    static long                  bs_qd_get_file_size(const char* filename);
    static char*                 bs_qd_load_file(const char* fn);

    #define MAIN_PAGE                       "<html> <head><title>Welcome to byte-store!</title></head>  <body>Welcome to byte-store!</body>       </html>"
    #define METHOD_ERROR                    "<html> <head><title>Illegal request</title></head>         <body>Sorry!</body>                       </html>"
    #define MALFORMED_ERROR                 "<html> <head><title>Malformed request</title></head>       <body>Sorry!</body>                       </html>"
    #define NOT_FOUND_ERROR                 "<html> <head><title>Not found</title></head>               <body>Sorry!</body>                       </html>"
    #define NOT_ENOUGH_MEMORY_ERROR         "<html> <head><title>Not enough memory</title></head>       <body>Sorry!</body>                       </html>"
    #define PARAMETERS_NOT_FOUND_ERROR      "<html> <head><title>Missing parameters</title></head>      <body>Please check your arguments!</body> </html>"
    #define UPLOAD_FILESIZE_TOO_LARGE_ERROR "<html> <head><title>Uploaded file too large</title></head> <body>Uploaded file is too large!</body>  </html>"

    #define BS_QD_POST_BUFFER_SIZE 4096

    typedef int (*bs_qd_request_page_handler)(const void *cls, const char *mime, struct MHD_Connection *connection, bs_qd_connection_info_t* con_info, const char* upload_data, size_t* upload_data_size);

    typedef struct bs_qd_request_page {
        const char *url;
        const char *mime;
        bs_qd_request_page_handler handler;
        const void *handler_cls;
    } bs_qd_request_page_t;

    #define kBSQDURLHome "/"
    #define kBSQDURLRandom "/random"
    #define kBSQDURLRandomViaTemporaryFile "/random_via_tf"
    #define kBSQDURLRandomViaHeap "/random_via_heap"
    #define kBSQDURLElements "/elements"
    #define kBSQDURLElementsViaTemporaryFile "/elements_via_tf"
    #define kBSQDURLElementsViaHeap "/elements_via_heap"

    static bs_qd_request_page_t request_pages[] = {
        { kBSQDURLHome,                                "text/html",   &bs_qd_request_generic_information,                      MAIN_PAGE },
        { kBSQDURLRandom,                              "text/plain",  &bs_qd_request_random_element_via_heap,                  NULL },
        { kBSQDURLRandomViaTemporaryFile,              "text/plain",  &bs_qd_request_random_element_via_temporary_file,        NULL },
        { kBSQDURLRandomViaHeap,                       "text/plain",  &bs_qd_request_random_element_via_heap,                  NULL },
        { kBSQDURLElements,                            "text/plain",  &bs_qd_request_elements_via_heap,                        NULL },
        { kBSQDURLElementsViaTemporaryFile,            "text/plain",  &bs_qd_request_elements_via_temporary_file,              NULL },
        { kBSQDURLElementsViaHeap,                     "text/plain",  &bs_qd_request_elements_via_heap,                        NULL },
        { NULL,                                         NULL,         &bs_qd_request_not_found,                                NULL } /* 404 */
    };

    typedef struct bs_qd_io {
        const bs_qd_connection_info_t* con_info;
        char* write_fn;
        FILE* write_fp;
        FILE* read_fp;
    } bs_qd_io_t;

    /* non-daemon function declarations */

    static inline byte_t         bs_encode_score_to_byte(score_t d);
    static inline byte_t         bs_encode_score_to_byte_mqz(score_t d);
    static inline byte_t         bs_encode_score_to_byte_custom(score_t d, score_t min, score_t max);
    static inline boolean_t      bs_signbit(score_t d);
    static inline score_t        bs_decode_byte_to_score(byte_t uc);
    static inline score_t        bs_decode_byte_to_score_mqz(byte_t uc);
    static inline score_t        bs_decode_byte_to_score_custom(byte_t uc, score_t min, score_t max);
    boolean_t                    bs_parse_query_range_str(lookup_t* l, char* rs, size_t* start, size_t* end);
    boolean_t                    bs_parse_query_index_str(lookup_t* l);
    boolean_t                    bs_parse_query_multiple_index_str(lookup_t* l, char* qs);
    int32_t                      bs_parse_query_multiple_index_str_comparator(const void* a, const void* b);
    boolean_t                    bs_parse_query_multiple_index_file(lookup_t* l, char* qf);
    void                         bs_parse_query_str_to_indices(char* qs, size_t* start, size_t* stop);
    bed_t*                       bs_init_bed(const char* chr, uint64_t start, uint64_t end);
    void                         bs_delete_bed(bed_t** b);
    lookup_t*                    bs_init_lookup(char* fn, boolean_t pi, boolean_t ss, boolean_t ir);
    void                         bs_permute_lookup(lookup_t *l, FILE* os);
    void                         bs_shuffle_signal_data(score_t* d, size_t n);
    void                         bs_print_lookup(lookup_t* l, FILE* os);
    void                         bs_print_lookup_frequency(lookup_t* l, FILE* os);
    void                         bs_increment_lookup_frequency(uint64_t* t, lookup_t* l, score_t (*sf)(signal_t*, signal_t*, uint32_t));
    void                         bs_delete_lookup(lookup_t** l);
    void                         bs_copy_signal(signal_t* src, signal_t** dest, boolean_t ss, boolean_t ir);
    void                         bs_init_signal(char* cds, signal_t** dest, boolean_t ss, boolean_t ir);
    static int                   bs_rank_comparator(const void *a, const void *b);
    void                         bs_print_signal(signal_t* s, FILE* os);
    static inline score_t        bs_mean_signal(score_t* d, uint32_t len);
    static inline score_t        bs_mean_ranks(rank_t* d, uint32_t len);
    static inline score_t        bs_sample_sd_signal(score_t* d, uint32_t len, score_t m);
    static inline score_t        bs_sample_sd_ranks(rank_t* d, uint32_t len, score_t m);
    static inline score_t        bs_pearson_r_signal(signal_t* x, signal_t* y, uint32_t len);
    static inline score_t        bs_normalized_euclidean_distance_signal(signal_t* x, signal_t* y, uint32_t len);
    static inline score_t        bs_spearman_rho_signal_v1(signal_t* x, signal_t* y, uint32_t len);
    static inline score_t        bs_spearman_rho_signal_v2(signal_t* x, signal_t* y, uint32_t len);
    static inline score_t        bs_cosine_similarity_signal(signal_t* x, signal_t* y, uint32_t len);
    static inline score_t        bs_jaccard_index_signal(signal_t* x, signal_t* y, uint32_t len);
    static inline score_t        bs_ochiai_similarity_signal(signal_t* x, signal_t* y, uint32_t len);
    static inline score_t        bs_pearson_phi_similarity_signal(signal_t* x, signal_t* y, uint32_t len);
    static inline score_t        bs_rogers_and_tanimoto_similarity_signal(signal_t* x, signal_t* y, uint32_t len);
    static inline score_t        bs_normalized_pointwise_mutual_information_signal(signal_t* x, signal_t* y, uint32_t len);
    void                         bs_delete_signal(signal_t** s);
    void                         bs_init_element(char* chr, uint64_t start, uint64_t stop, char* id, boolean_t pi, boolean_t ss, boolean_t ir, signal_t* sp, element_t** e);
    void                         bs_delete_element(element_t** e);
    void                         bs_push_elem_to_lookup(element_t* e, lookup_t** l, boolean_t pi, boolean_t ss, boolean_t ir);
    void                         bs_test_pearson_r();
    void                         bs_test_spearman_rho();
    void                         bs_test_normalized_euclidean_distance();
    void                         bs_test_cosine_similarity();
    void                         bs_test_jaccard_index();
    void                         bs_test_ochiai_similarity();
    void                         bs_test_pearson_phi_similarity();
    void                         bs_test_rogers_and_tanimoto_similarity();
    void                         bs_test_normalized_pointwise_mutual_information();
    void                         bs_test_score_encoding();
    void                         bs_init_globals();
    void                         bs_delete_globals();
    void                         bs_init_command_line_options(int argc, char** argv);
    void                         bs_print_usage(FILE* os);
    inline boolean_t             bs_path_exists(const char* p);
    inline ssize_t               bs_file_size(const char* fn);
    inline void                  bs_print_pair(FILE* os, char* chr_a, uint64_t start_a, uint64_t stop_a, char* chr_b, uint64_t start_b, uint64_t stop_b, score_t score);
    inline void                  bs_print_pair_to_buffer(char* b, size_t* bl, char* chr_a, uint64_t start_a, uint64_t stop_a, char* chr_b, uint64_t start_b, uint64_t stop_b, score_t score);
    sut_store_t*                 bs_init_sut_store(uint32_t n);
    void                         bs_populate_sut_store_with_random_scores(sut_store_t* s);
    void                         bs_populate_sut_store(sut_store_t* s, lookup_t* l, score_t (*sf)(signal_t*, signal_t*, uint32_t));
    off_t                        bs_sut_byte_offset_for_element_ij(uint32_t n, uint32_t i, uint32_t j);
    void                         bs_print_sut_store_to_bed7(lookup_t* l, sut_store_t* s, FILE* os);
    void                         bs_print_sut_filtered_store_to_bed7(lookup_t* l, sut_store_t* s, FILE* os, score_t fc, score_filter_t fo);
    void                         bs_print_sut_frequency_to_txt(lookup_t* l, sut_store_t* s, FILE* os);
    void                         bs_delete_sut_store(sut_store_t** s);
    sqr_store_t*                 bs_init_sqr_store(uint32_t n);
    void                         bs_populate_sqr_store_with_random_scores(sqr_store_t* s);
    void                         bs_populate_sqr_store_with_buffered_random_scores(sqr_store_t* s);
    void                         bs_populate_sqr_store(sqr_store_t* s, lookup_t* l, score_t (*sf)(signal_t*, signal_t*, uint32_t));
    char*                        bs_init_sqr_split_store_fn_str(char* d, uint32_t i);
    char*                        bs_init_sqr_split_store_dir_str(char* p);
    char*                        bs_init_sqr_split_store_metadata_fn_str(char* d);
    void                         bs_populate_sqr_split_store(sqr_store_t* s, lookup_t* l, uint32_t n, score_t (*sf)(signal_t*, signal_t*, uint32_t), score_variety_t sv);
    void                         bs_populate_sqr_split_store_chunk(sqr_store_t* s, lookup_t* l, uint32_t n, uint32_t o, score_t (*sf)(signal_t*, signal_t*, uint32_t));
    void                         bs_populate_sqr_split_store_chunk_metadata(sqr_store_t* s, lookup_t* l, uint32_t n, score_variety_t v);
    void                         bs_populate_sqr_bzip2_store(sqr_store_t* s, lookup_t* l, uint32_t n, score_t (*sf)(signal_t*, signal_t*, uint32_t), score_variety_t sv);
    void                         bs_populate_sqr_bzip2_split_store(sqr_store_t* s, lookup_t* l, uint32_t n, score_t (*sf)(signal_t*, signal_t*, uint32_t), score_variety_t sv);
    char*                        bs_init_sqr_bzip2_split_store_dir_str(char* p);
    char*                        bs_init_sqr_bzip2_split_store_fn_str(char* p, uint32_t i);
    char*                        bs_init_sqr_bzip2_split_store_metadata_fn_str(char* d);
    char*                        bs_init_store_frequency_fn(char* p, boolean_t f);
    inline off_t                 bs_sqr_byte_offset_for_element_ij(uint32_t n, uint32_t i, uint32_t j);
    void                         bs_print_sqr_store_to_bed7(lookup_t* l, sqr_store_t* s, boolean_t m, FILE* os, size_t rs, size_t re);
    void                         bs_print_sqr_filtered_store_to_bed7(lookup_t* l, sqr_store_t* s, boolean_t m, FILE* os, score_t fc, score_t flb, score_t fub, score_filter_t fo, size_t rs, size_t re);
    void                         bs_print_sqr_split_store_separate_rows_to_bed7(lookup_t* l, sqr_store_t* s, boolean_t m, FILE* os, size_t* rs, size_t* re, uint32_t rn);
    void                         bs_print_sqr_split_store_separate_rows_to_bed7_via_buffer(lookup_t* l, sqr_store_t* s, boolean_t m, char** b, size_t* rs, size_t* re, uint32_t rn);
    void                         bs_print_sqr_split_store_separate_rows_and_columns_to_bed7_file(lookup_t* l, sqr_store_t* s, char* qf, FILE* os);
    void                         bs_print_sqr_split_store_separate_rows_to_bed7_file(lookup_t* l, sqr_store_t* s, char* qf, boolean_t m, FILE* os);
    void                         bs_print_sqr_split_store_separate_rows_to_bed7_file_via_buffer(lookup_t* l, sqr_store_t* s, char* qf, boolean_t m, char** b);
    void                         bs_print_sqr_filtered_split_store_separate_rows_to_bed7(lookup_t* l, sqr_store_t* s, boolean_t m, FILE* os, size_t* rs, size_t* re, uint32_t rn, score_t fc, score_t flb, score_t fub, score_filter_t fo);
    void                         bs_print_sqr_filtered_split_store_separate_rows_to_bed7_via_buffer(lookup_t* l, sqr_store_t* s, boolean_t m, char** b, size_t* rs, size_t* re, uint32_t rn, score_t fc, score_t flb, score_t fub, score_filter_t fo);
    void                         bs_print_sqr_filtered_split_store_separate_rows_and_columns_to_bed7_file(lookup_t* l, sqr_store_t* s, char* qf, FILE* os, score_t fc, score_t flb, score_t fub, score_filter_t fo);
    void                         bs_print_sqr_filtered_split_store_separate_rows_to_bed7_file(lookup_t* l, sqr_store_t* s, char* qf, boolean_t m, FILE* os, score_t fc, score_t flb, score_t fub, score_filter_t fo);
    void                         bs_print_sqr_filtered_split_store_separate_rows_to_bed7_file_via_buffer(lookup_t* l, sqr_store_t* s, char* qf, boolean_t m, char** b, score_t fc, score_t flb, score_t fub, score_filter_t fo);
    void                         bs_print_sqr_bzip2_store_to_bed7(lookup_t* l, sqr_store_t* s, FILE* os);
    void                         bs_print_sqr_filtered_bzip2_store_to_bed7(lookup_t* l, sqr_store_t* s, FILE* os, score_t fc, score_t flb, score_t fub, score_filter_t fo);
    void                         bs_print_sqr_bzip2_split_store_to_bed7(lookup_t* l, sqr_store_t* s, FILE* os);
    void                         bs_print_sqr_filtered_bzip2_split_store_to_bed7(lookup_t* l, sqr_store_t* s, FILE* os, score_t fc, score_t flb, score_t fub, score_filter_t fo);
    void                         bs_print_sqr_split_diagonal_walk_fixed_distance(lookup_t* l, sqr_store_t* s, FILE* os, uint32_t v, diagonal_side_t ds);
    void                         bs_print_sqr_filtered_split_diagonal_walk_fixed_distance(lookup_t* l, sqr_store_t* s, FILE* os, uint32_t v, diagonal_side_t ds, score_t fc, score_t flb, score_t fub, score_filter_t fo);
    char*                        bs_init_metadata_str(off_t* o, uint32_t n, uint32_t s, score_t f, score_variety_t v);
    metadata_t*                  bs_init_metadata_ptr(char* bsd);
    metadata_t*                  bs_parse_metadata_str(char* ms);
    void                         bs_delete_metadata(metadata_t** m);
    void                         bs_print_sqr_store_frequency_to_txt(lookup_t* l, sqr_store_t* s, FILE* os);
    void                         bs_print_sqr_split_store_frequency_to_txt(lookup_t* l, sqr_store_t* s, FILE* os);
    void                         bs_print_sqr_bzip2_store_frequency_to_txt(lookup_t* l, sqr_store_t* s, FILE* os);
    void                         bs_print_sqr_bzip2_split_store_frequency_to_txt(lookup_t* l, sqr_store_t* s, FILE* os);
    void                         bs_print_frequency_buffer(uint64_t* t, uint64_t n, FILE* os);
    void                         bs_delete_sqr_store(sqr_store_t** s);
    store_buf_node_t*            bs_init_store_buf_node(byte_t uc);
    void                         bs_insert_store_buf_node(store_buf_node_t* n, store_buf_node_t* i);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif // BYTE_STORE_H_
