/**
 * @file arstream2_h264.h
 * @brief Parrot Streaming Library - H.264 definitions
 * @date 08/04/2015
 * @author aurelien.barre@parrot.com
 */


#ifndef _ARSTREAM2_H264_H_
#define _ARSTREAM2_H264_H_

#include <inttypes.h>


/*
 * Macros
 */

#define ARSTREAM2_H264_BYTE_STREAM_NALU_START_CODE 0x00000001
#define ARSTREAM2_H264_BYTE_STREAM_NALU_START_CODE_LENGTH 4

#define ARSTREAM2_H264_NALU_TYPE_UNKNOWN 0
#define ARSTREAM2_H264_NALU_TYPE_SLICE 1
#define ARSTREAM2_H264_NALU_TYPE_SLICE_IDR 5
#define ARSTREAM2_H264_NALU_TYPE_SEI 6
#define ARSTREAM2_H264_NALU_TYPE_SPS 7
#define ARSTREAM2_H264_NALU_TYPE_PPS 8
#define ARSTREAM2_H264_NALU_TYPE_AUD 9
#define ARSTREAM2_H264_NALU_TYPE_FILLER_DATA 12

#define ARSTREAM2_H264_SEI_PAYLOAD_TYPE_BUFFERING_PERIOD 0
#define ARSTREAM2_H264_SEI_PAYLOAD_TYPE_PIC_TIMING 1
#define ARSTREAM2_H264_SEI_PAYLOAD_TYPE_USER_DATA_UNREGISTERED 5
#define ARSTREAM2_H264_SEI_PAYLOAD_TYPE_RECOVERY_POINT 6

#define ARSTREAM2_H264_SLICE_TYPE_NON_VCL 0xFF
#define ARSTREAM2_H264_SLICE_TYPE_P 0
#define ARSTREAM2_H264_SLICE_TYPE_B 1
#define ARSTREAM2_H264_SLICE_TYPE_I 2
#define ARSTREAM2_H264_SLICE_TYPE_SP 3
#define ARSTREAM2_H264_SLICE_TYPE_SI 4
#define ARSTREAM2_H264_SLICE_TYPE_P_ALL 5
#define ARSTREAM2_H264_SLICE_TYPE_B_ALL 6
#define ARSTREAM2_H264_SLICE_TYPE_I_ALL 7
#define ARSTREAM2_H264_SLICE_TYPE_SP_ALL 8
#define ARSTREAM2_H264_SLICE_TYPE_SI_ALL 9

#define ARSTREAM2_H264_AU_NALU_MAX_COUNT    (128)
#define ARSTREAM2_H264_AU_MIN_REALLOC_SIZE  (10 * 1024)

/*
 * Types
 */

typedef struct ARSTREAM2_H264_SpsContext_s
{
    unsigned int chroma_format_idc;
    unsigned int separate_colour_plane_flag;
    unsigned int log2_max_frame_num_minus4;
    unsigned int pic_order_cnt_type;
    unsigned int log2_max_pic_order_cnt_lsb_minus4;
    unsigned int delta_pic_order_always_zero_flag;
    unsigned int pic_width_in_mbs_minus1;
    unsigned int pic_height_in_map_units_minus1;
    unsigned int frame_mbs_only_flag;

    // VUI
    unsigned int nal_hrd_parameters_present_flag;
    unsigned int vcl_hrd_parameters_present_flag;
    unsigned int pic_struct_present_flag;
    unsigned int num_units_in_tick;
    unsigned int time_scale;

    // HRD params
    unsigned int cpb_cnt_minus1;
    unsigned int initial_cpb_removal_delay_length_minus1;
    unsigned int cpb_removal_delay_length_minus1;
    unsigned int dpb_output_delay_length_minus1;
    unsigned int time_offset_length;

} ARSTREAM2_H264_SpsContext_t;


typedef struct ARSTREAM2_H264_PpsContext_s
{
    unsigned int entropy_coding_mode_flag;
    unsigned int bottom_field_pic_order_in_frame_present_flag;
    unsigned int num_slice_groups_minus1;
    unsigned int slice_group_map_type;
    unsigned int slice_group_change_rate_minus1;
    unsigned int num_ref_idx_l0_default_active_minus1;
    unsigned int num_ref_idx_l1_default_active_minus1;
    unsigned int weighted_pred_flag;
    unsigned int weighted_bipred_idc;
    unsigned int deblocking_filter_control_present_flag;
    unsigned int redundant_pic_cnt_present_flag;

} ARSTREAM2_H264_PpsContext_t;


typedef struct ARSTREAM2_H264_SliceContext_s
{
    unsigned int nal_ref_idc;
    unsigned int nal_unit_type;
    unsigned int idrPicFlag;
    unsigned int first_mb_in_slice;
    unsigned int sliceMbCount;
    unsigned int slice_type;
    unsigned int sliceTypeMod5;
    unsigned int pic_parameter_set_id;
    unsigned int colour_plane_id;
    unsigned int frame_num;
    unsigned int field_pic_flag;
    unsigned int bottom_field_flag;
    unsigned int idr_pic_id;
    unsigned int pic_order_cnt_lsb;
    int delta_pic_order_cnt_bottom;
    int delta_pic_order_cnt_0;
    int delta_pic_order_cnt_1;
    unsigned int redundant_pic_cnt;
    unsigned int direct_spatial_mv_pred_flag;
    unsigned int num_ref_idx_active_override_flag;
    unsigned int num_ref_idx_l0_active_minus1;
    unsigned int num_ref_idx_l1_active_minus1;
    unsigned int ref_pic_list_modification_flag_l0;
    unsigned int ref_pic_list_modification_flag_l1;
    unsigned int no_output_of_prior_pics_flag;
    unsigned int long_term_reference_flag;
    unsigned int adaptive_ref_pic_marking_mode_flag;
    unsigned int cabac_init_idc;
    int slice_qp_delta;
    unsigned int sp_for_switch_flag;
    int slice_qs_delta;
    unsigned int disable_deblocking_filter_idc;
    int slice_alpha_c0_offset_div2;
    int slice_beta_offset_div2;
    unsigned int slice_group_change_cycle;

} ARSTREAM2_H264_SliceContext_t;


/**
 * @brief NAL unit data
 */
typedef struct ARSTREAM2_H264_NalUnit_s
{
    uint64_t inputTimestamp;
    uint64_t timeoutTimestamp;
    uint64_t ntpTimestamp;
    uint64_t ntpTimestampLocal;
    uint64_t extRtpTimestamp;
    uint32_t rtpTimestamp;
    uint32_t isLastInAu;
    uint32_t seqNumForcedDiscontinuity;
    uint32_t missingPacketsBefore;
    uint32_t importance;
    uint32_t priority;
    uint8_t *metadata;
    unsigned int metadataSize;
    uint8_t *nalu;
    unsigned int naluSize;
    void *auUserPtr;
    void *naluUserPtr;
    uint8_t naluType;
    uint8_t sliceType;

} ARSTREAM2_H264_NalUnit_t;


/**
 * @brief NAL unit FIFO item
 */
typedef struct ARSTREAM2_H264_NaluFifoItem_s
{
    ARSTREAM2_H264_NalUnit_t nalu;

    struct ARSTREAM2_H264_NaluFifoItem_s* prev;
    struct ARSTREAM2_H264_NaluFifoItem_s* next;

} ARSTREAM2_H264_NaluFifoItem_t;


/**
 * @brief NAL unit FIFO
 */
typedef struct ARSTREAM2_H264_NaluFifo_s
{
    int size;
    int count;
    ARSTREAM2_H264_NaluFifoItem_t *head;
    ARSTREAM2_H264_NaluFifoItem_t *tail;
    ARSTREAM2_H264_NaluFifoItem_t *free;
    ARSTREAM2_H264_NaluFifoItem_t *pool;

} ARSTREAM2_H264_NaluFifo_t;


/**
 * @brief Access unit data
 */
typedef struct ARSTREAM2_H264_AccessUnit_s
{
    uint8_t *buffer;
    unsigned int bufferSize;
    unsigned int auSize;
    uint8_t *metadataBuffer;
    unsigned int metadataBufferSize;
    unsigned int metadataSize;
    uint8_t *userDataBuffer;
    unsigned int userDataBufferSize;
    unsigned int userDataSize;
    uint64_t inputTimestamp;
    uint64_t timeoutTimestamp;
    uint64_t ntpTimestamp;
    uint64_t ntpTimestampLocal;
    uint64_t extRtpTimestamp;
    uint32_t rtpTimestamp;
    uint32_t naluCount;
    ARSTREAM2_H264_NaluFifoItem_t *naluHead;
    ARSTREAM2_H264_NaluFifoItem_t *naluTail;

} ARSTREAM2_H264_AccessUnit_t;


/**
 * @brief Access unit FIFO item
 */
typedef struct ARSTREAM2_H264_AuFifoItem_s
{
    ARSTREAM2_H264_AccessUnit_t au;

    struct ARSTREAM2_H264_AuFifoItem_s* prev;
    struct ARSTREAM2_H264_AuFifoItem_s* next;

} ARSTREAM2_H264_AuFifoItem_t;


/**
 * @brief Access unit FIFO
 */
typedef struct ARSTREAM2_H264_AuFifo_s
{
    int size;
    int count;
    ARSTREAM2_H264_AuFifoItem_t *head;
    ARSTREAM2_H264_AuFifoItem_t *tail;
    ARSTREAM2_H264_AuFifoItem_t *free;
    ARSTREAM2_H264_AuFifoItem_t *pool;

} ARSTREAM2_H264_AuFifo_t;


/*
 * Functions
 */

void ARSTREAM2_H264_NaluReset(ARSTREAM2_H264_NalUnit_t *nalu);

void ARSTREAM2_H264_AuReset(ARSTREAM2_H264_AccessUnit_t *au);

int ARSTREAM2_H264_NaluFifoInit(ARSTREAM2_H264_NaluFifo_t *fifo, int maxCount);

int ARSTREAM2_H264_NaluFifoFree(ARSTREAM2_H264_NaluFifo_t *fifo);

ARSTREAM2_H264_NaluFifoItem_t* ARSTREAM2_H264_NaluFifoPopFreeItem(ARSTREAM2_H264_NaluFifo_t *fifo);

int ARSTREAM2_H264_NaluFifoPushFreeItem(ARSTREAM2_H264_NaluFifo_t *fifo, ARSTREAM2_H264_NaluFifoItem_t *item);

int ARSTREAM2_H264_NaluFifoEnqueueItem(ARSTREAM2_H264_NaluFifo_t *fifo, ARSTREAM2_H264_NaluFifoItem_t *item);

ARSTREAM2_H264_NaluFifoItem_t* ARSTREAM2_H264_NaluFifoDequeueItem(ARSTREAM2_H264_NaluFifo_t *fifo);

int ARSTREAM2_H264_NaluFifoFlush(ARSTREAM2_H264_NaluFifo_t *fifo);

int ARSTREAM2_H264_AuFifoInit(ARSTREAM2_H264_AuFifo_t *fifo, int maxCount, int bufferSize,
                              int metadataBufferSize, int userDataBufferSize);

int ARSTREAM2_H264_AuFifoFree(ARSTREAM2_H264_AuFifo_t *fifo);

ARSTREAM2_H264_AuFifoItem_t* ARSTREAM2_H264_AuFifoPopFreeItem(ARSTREAM2_H264_AuFifo_t *fifo);

int ARSTREAM2_H264_AuFifoPushFreeItem(ARSTREAM2_H264_AuFifo_t *fifo, ARSTREAM2_H264_AuFifoItem_t *item);

int ARSTREAM2_H264_AuFifoEnqueueItem(ARSTREAM2_H264_AuFifo_t *fifo, ARSTREAM2_H264_AuFifoItem_t *item);

ARSTREAM2_H264_AuFifoItem_t* ARSTREAM2_H264_AuFifoDequeueItem(ARSTREAM2_H264_AuFifo_t *fifo);

int ARSTREAM2_H264_AuFifoFlush(ARSTREAM2_H264_AuFifo_t *fifo);

int ARSTREAM2_H264_AuEnqueueNalu(ARSTREAM2_H264_AccessUnit_t *au, ARSTREAM2_H264_NaluFifoItem_t *naluItem);

int ARSTREAM2_H264_AuEnqueueNaluBefore(ARSTREAM2_H264_AccessUnit_t *au, ARSTREAM2_H264_NaluFifoItem_t *naluItem,
                                       ARSTREAM2_H264_NaluFifoItem_t *nextNaluItem);

ARSTREAM2_H264_NaluFifoItem_t* ARSTREAM2_H264_AuDequeueNalu(ARSTREAM2_H264_AccessUnit_t *au);

int ARSTREAM2_H264_AuCheckSizeRealloc(ARSTREAM2_H264_AccessUnit_t *au, unsigned int size);


#endif /* #ifndef _ARSTREAM2_H264_H_ */
