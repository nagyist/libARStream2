/**
 * @file arstream2_stream_receiver_test.h
 * @brief Parrot Streaming Library - Stream Receiver test program
 * @date 07/27/2016
 * @author aurelien.barre@parrot.com
 */

#ifndef _ARSTREAM2_STREAM_RECEIVER_TEST_H_
#define _ARSTREAM2_STREAM_RECEIVER_TEST_H_

typedef struct READER_THREAD_DATA_t READER_THREAD_DATA_t;

typedef struct
{
    ARNETWORKAL_Manager_t *alManager;
    ARNETWORK_Manager_t *netManager;
    ARSTREAM2_StreamReceiver_Handle streamReceiver;
    ARSAL_Thread_t rxThread;
    ARSAL_Thread_t txThread;
    ARSAL_Thread_t streamNetworkThread;
    ARSAL_Thread_t streamOutputThread;
    char *addr;
    int d2cPort;
    int c2dPort;
    int arstream2ServerStreamPort;
    int arstream2ServerControlPort;
    int arstream2ClientStreamPort;
    int arstream2ClientControlPort;
    int arstream2MaxPacketSize;
    int arstream2MaxLatency;
    int arstream2MaxNetworkLatency;
    int arstream2MaxBitrate;
    uint8_t *auBuffer;
    uint32_t auBufferSize;
    
    FILE *video_out;
    
    ARSAL_Thread_t *readerThreads;
    READER_THREAD_DATA_t *readerThreadsData;
    int run;
} BD_MANAGER_t;

struct READER_THREAD_DATA_t
{
    BD_MANAGER_t *deviceManager;
    int readerBufferId;
};

void sighandler(int signum);
void *readerRun (void* data);

int ardiscoveryConnect (BD_MANAGER_t *deviceManager);
eARDISCOVERY_ERROR ARDISCOVERY_Connection_SendJsonCallback (uint8_t *dataTx, uint32_t *dataTxSize, void *customData);
eARDISCOVERY_ERROR ARDISCOVERY_Connection_ReceiveJsonCallback (uint8_t *dataRx, uint32_t dataRxSize, char *ip, void *customData);

int startNetwork (BD_MANAGER_t *deviceManager);
void onDisconnectNetwork (ARNETWORK_Manager_t *manager, ARNETWORKAL_Manager_t *alManager, void *customData);
void stopNetwork (BD_MANAGER_t *deviceManager);

int startVideo (BD_MANAGER_t *deviceManager);
void stopVideo (BD_MANAGER_t *deviceManager);

eARSTREAM2_ERROR spsPpsCallback(uint8_t *spsBuffer, int spsSize, uint8_t *ppsBuffer, int ppsSize, void *userPtr);
eARSTREAM2_ERROR getAuBufferCallback(uint8_t **auBuffer, int *auBufferSize, void **auBufferUserPtr, void *userPtr);
eARSTREAM2_ERROR auReadyCallback(uint8_t *auBuffer, int auSize, uint64_t auExtRtpTimestamp, uint64_t auNtpTimestamp,
                                 uint64_t auNtpTimestampLocal, eARSTREAM2_STREAM_RECEIVER_AU_SYNC_TYPE auSyncType,
                                 void *auMetadata, int auMetadataSize, void *auUserData, int auUserDataSize, void *auBufferUserPtr, void *userPtr);

int sendBeginStream(BD_MANAGER_t *deviceManager);

eARNETWORK_MANAGER_CALLBACK_RETURN arnetworkCmdCallback(int buffer_id, uint8_t *data, void *custom, eARNETWORK_MANAGER_CALLBACK_STATUS cause);

#endif /* #ifndef _ARSTREAM2_STREAM_RECEIVER_TEST_H_ */
