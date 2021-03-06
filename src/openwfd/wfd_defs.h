/*
 * OpenWFD - Open-Source Wifi-Display Implementation
 *
 * Copyright (c) 2013 David Herrmann <dh.herrmann@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef OPENWFD_WFD_DEFS_H
#define OPENWFD_WFD_DEFS_H

#include <endian.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup wfd_defs Wifi-Display Definitions
 * Definitions from the Wifi-Display specification
 *
 * This section contains definitions and constants from the Wifi-Display
 * specification.
 *
 * @{
 */

#define OPENWFD__WFD_PACKED __attribute__((__packed__))

/*
 * TODO: WFD 5.2.7 defines service-discovery frames. wpa-supplicant currently
 * does not support custom OUI fields. Fix this and then add support for
 * WFD service discovery.
 */

/*
 * IE elements
 */

#define OPENWFD_WFD_IE_ID 0xdd

#define OPENWFD_WFD_IE_OUI_1_0 0x506f9a0a

#define OPENWFD_WFD_IE_DATA_MAX 251

struct openwfd_wfd_ie {
	uint8_t element_id;
	uint8_t length;
	uint32_t oui;
	uint8_t data[];
} OPENWFD__WFD_PACKED;

/*
 * IE subelements
 */

enum openwfd_wfd_ie_sub_type {
	OPENWFD_WFD_IE_SUB_DEV_INFO			= 0,
	OPENWFD_WFD_IE_SUB_ASSOC_BSSID			= 1,
	OPENWFD_WFD_IE_SUB_AUDIO_FORMATS		= 2,
	OPENWFD_WFD_IE_SUB_VIDEO_FORMATS		= 3,
	OPENWFD_WFD_IE_SUB_3D_FORMATS			= 4,
	OPENWFD_WFD_IE_SUB_CONTENT_PROTECT		= 5,
	OPENWFD_WFD_IE_SUB_COUPLED_SINK			= 6,
	OPENWFD_WFD_IE_SUB_EXT_CAP			= 7,
	OPENWFD_WFD_IE_SUB_LOCAL_IP			= 8,
	OPENWFD_WFD_IE_SUB_SESSION_INFO			= 9,
	OPENWFD_WFD_IE_SUB_ALT_MAC			= 10,
	OPENWFD_WFD_IE_SUB_NUM
};

struct openwfd_wfd_ie_sub {
	uint8_t subelement_id;
	uint16_t length;
	uint8_t data[];
} OPENWFD__WFD_PACKED;

/*
 * IE subelement device information
 */

/* role */
#define OPENWFD_WFD_IE_SUB_DEV_INFO_ROLE_MASK			0x0003
#define OPENWFD_WFD_IE_SUB_DEV_INFO_SOURCE			0x0000
#define OPENWFD_WFD_IE_SUB_DEV_INFO_PRIMARY_SINK		0x0001
#define OPENWFD_WFD_IE_SUB_DEV_INFO_SECONDARY_SINK		0x0002
#define OPENWFD_WFD_IE_SUB_DEV_INFO_DUAL_ROLE			0x0003

/* coupled sink as source */
#define OPENWFD_WFD_IE_SUB_DEV_INFO_SRC_COUPLED_SINK_MASK	0x0004
#define OPENWFD_WFD_IE_SUB_DEV_INFO_SRC_NO_COUPLED_SINK		0x0000
#define OPENWFD_WFD_IE_SUB_DEV_INFO_SRC_CAN_COUPLED_SINK	0x0004

/* coupled sink as sink */
#define OPENWFD_WFD_IE_SUB_DEV_INFO_SINK_COUPLED_SINK_MASK	0x0008
#define OPENWFD_WFD_IE_SUB_DEV_INFO_SINK_NO_COUPLED_SINK	0x0000
#define OPENWFD_WFD_IE_SUB_DEV_INFO_SINK_CAN_COUPLED_SINK	0x0008

/* availability for session establishment */
#define OPENWFD_WFD_IE_SUB_DEV_INFO_AVAILABLE_MASK		0x0030
#define OPENWFD_WFD_IE_SUB_DEV_INFO_NOT_AVAILABLE		0x0000
#define OPENWFD_WFD_IE_SUB_DEV_INFO_AVAILABLE			0x0010

/* WFD service discovery */
#define OPENWFD_WFD_IE_SUB_DEV_INFO_WSD_MASK			0x0040
#define OPENWFD_WFD_IE_SUB_DEV_INFO_NO_WSD			0x0000
#define OPENWFD_WFD_IE_SUB_DEV_INFO_CAN_WSD			0x0040

/* preferred connectivity */
#define OPENWFD_WFD_IE_SUB_DEV_INFO_PC_MASK			0x0080
#define OPENWFD_WFD_IE_SUB_DEV_INFO_PREFER_P2P			0x0000
#define OPENWFD_WFD_IE_SUB_DEV_INFO_PREFER_TDLS			0x0080

/* content protection */
#define OPENWFD_WFD_IE_SUB_DEV_INFO_CP_MASK			0x0100
#define OPENWFD_WFD_IE_SUB_DEV_INFO_NO_CP			0x0000
#define OPENWFD_WFD_IE_SUB_DEV_INFO_CAN_CP			0x0100

/* separate time-sync */
#define OPENWFD_WFD_IE_SUB_DEV_INFO_TIME_SYNC_MASK		0x0200
#define OPENWFD_WFD_IE_SUB_DEV_INFO_NO_TIME_SYNC		0x0000
#define OPENWFD_WFD_IE_SUB_DEV_INFO_CAN_TIME_SYNC		0x0200

/* no audio */
#define OPENWFD_WFD_IE_SUB_DEV_INFO_NO_AUDIO_MASK		0x0400
#define OPENWFD_WFD_IE_SUB_DEV_INFO_CAN_AUDIO			0x0000
#define OPENWFD_WFD_IE_SUB_DEV_INFO_NO_AUDIO			0x0400

/* audio only */
#define OPENWFD_WFD_IE_SUB_DEV_INFO_AUDIO_ONLY_MASK		0x0800
#define OPENWFD_WFD_IE_SUB_DEV_INFO_NO_AUDIO_ONLY		0x0000
#define OPENWFD_WFD_IE_SUB_DEV_INFO_AUDIO_ONLY			0x0800

/* persistent TLDS */
#define OPENWFD_WFD_IE_SUB_DEV_INFO_PERSIST_TLDS_MASK		0x1000
#define OPENWFD_WFD_IE_SUB_DEV_INFO_NO_PERSIST_TLDS		0x0000
#define OPENWFD_WFD_IE_SUB_DEV_INFO_PERSIST_TLDS		0x1000

/* persistent TLDS group re-invoke */
#define OPENWFD_WFD_IE_SUB_DEV_INFO_TLDS_REINVOKE_MASK		0x2000
#define OPENWFD_WFD_IE_SUB_DEV_INFO_NO_TLDS_REINVOKE		0x0000
#define OPENWFD_WFD_IE_SUB_DEV_INFO_TLDS_REINVOKE		0x2000

#define OPENWFD_WFD_IE_SUB_DEV_INFO_DEFAULT_PORT 7236

struct openwfd_wfd_ie_sub_dev_info {
	uint16_t dev_info;
	uint16_t ctrl_port;
	uint16_t max_throughput;
} OPENWFD__WFD_PACKED;

/*
 * IE subelement associated BSSID
 */

struct openwfd_wfd_ie_sub_assoc_bssid {
	uint8_t bssid[6];
} OPENWFD__WFD_PACKED;

/*
 * IE subelement audio formats
 */

/* lpcm modes; 2C_16_48000 is mandatory */
#define OPENWFD_WFD_IE_SUB_AUDIO_FORMATS_LPCM_2C_16_44100	0x00000001
#define OPENWFD_WFD_IE_SUB_AUDIO_FORMATS_LPCM_2C_16_48000	0x00000002

/* aac modes */
#define OPENWFD_WFD_IE_SUB_AUDIO_FORMATS_AAC_2C_16_48000	0x00000001
#define OPENWFD_WFD_IE_SUB_AUDIO_FORMATS_AAC_4C_16_48000	0x00000002
#define OPENWFD_WFD_IE_SUB_AUDIO_FORMATS_AAC_6C_16_48000	0x00000004
#define OPENWFD_WFD_IE_SUB_AUDIO_FORMATS_AAC_8C_16_48000	0x00000008

/* ac3 modes */
#define OPENWFD_WFD_IE_SUB_AUDIO_FORMATS_AC3_2C_16_48000	0x00000001
#define OPENWFD_WFD_IE_SUB_AUDIO_FORMATS_AC3_4C_16_48000	0x00000002
#define OPENWFD_WFD_IE_SUB_AUDIO_FORMATS_AC3_6C_16_48000	0x00000004

/* audio latency; encoded in multiples of 5ms */
#define OPENWFD_WFD_IE_SUB_AUDIO_FORMATS_UNKNOWN_LATENCY	0x00
#define OPENWFD_WFD_IE_SUB_AUDIO_FORMATS_LATENCY_FROM_MS(_ms) \
							(((_ms) + 4ULL) / 5ULL)

struct openwfd_wfd_ie_sub_audio_formats {
	uint32_t lpcm_modes;
	uint8_t lpcm_latency;
	uint32_t aac_modes;
	uint8_t aac_latency;
	uint32_t ac3_modes;
	uint8_t ac3_latency;
} OPENWFD__WFD_PACKED;

/*
 * IE subelement video formats
 * Multiple video-subelements are allowed, one for each supported 264 profile.
 */

/* cea modes; required cea modes; 640x480@p60 is always required; if you
 * support higher resolutions at p60 or p50, you also must support 720x480@p60
 * or 720x576@p50 respectively */
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_CEA_640_480_P60	0x00000001
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_CEA_720_480_P60	0x00000002
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_CEA_720_480_I60	0x00000004
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_CEA_720_576_P50	0x00000008
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_CEA_720_576_I50	0x00000010
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_CEA_1280_720_P30	0x00000020
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_CEA_1280_720_P60	0x00000040
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_CEA_1920_1080_P30	0x00000080
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_CEA_1920_1080_P60	0x00000100
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_CEA_1920_1080_I60	0x00000200
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_CEA_1280_720_P25	0x00000400
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_CEA_1280_720_P50	0x00000800
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_CEA_1920_1080_P25	0x00001000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_CEA_1920_1080_P50	0x00002000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_CEA_1920_1080_I50	0x00004000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_CEA_1280_720_P24	0x00008000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_CEA_1920_1080_P24	0x00010000

/* vesa modes; if you support higher refresh-rates, you must also support
 * *all* lower rates of the same mode */
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_800_600_P30	0x00000001
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_800_600_P60	0x00000002
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1024_768_P30	0x00000004
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1024_768_P60	0x00000008
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1152_864_P30	0x00000010
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1152_864_P60	0x00000020
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1280_768_P30	0x00000040
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1280_768_P60	0x00000080
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1280_800_P30	0x00000100
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1280_800_P60	0x00000200
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1360_768_P30	0x00000400
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1360_768_P60	0x00000800
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1366_768_P30	0x00001000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1366_768_P60	0x00002000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1280_1024_P30	0x00004000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1280_1024_P60	0x00008000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1400_1050_P30	0x00010000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1400_1050_P60	0x00020000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1440_900_P30	0x00040000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1440_900_P60	0x00080000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1600_900_P30	0x00100000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1600_900_P60	0x00200000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1600_1200_P30	0x00400000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1600_1200_P60	0x00800000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1680_1024_P30	0x01000000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1680_1024_P60	0x02000000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1680_1050_P30	0x04000000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1680_1050_P60	0x08000000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1920_1200_P30	0x10000000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_VESA_1920_1200_P60	0x20000000

/* hh modes (handheld devices) */
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_HH_800_480_P30		0x00000000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_HH_800_480_P60		0x00000000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_HH_854_480_P30		0x00000000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_HH_854_480_P60		0x00000000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_HH_864_480_P30		0x00000000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_HH_864_480_P60		0x00000000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_HH_640_360_P30		0x00000000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_HH_640_360_P60		0x00000000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_HH_960_540_P30		0x00000000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_HH_960_540_P60		0x00000000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_HH_848_480_P30		0x00000000
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_HH_848_480_P60		0x00000000

/* native mode; table */
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_NATIVE_MODE_TABLE_MASK	0x03
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_NATIVE_MODE_CEA_TABLE	0x00
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_NATIVE_MODE_VESA_TABLE	0x01
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_NATIVE_MODE_HH_TABLE	0x02

/* native mode; index */
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_NATIVE_MODE_IDX_MASK	0xfc
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_NATIVE_MODE_IDX_SHIFT	3

/* h264 profiles; base-profile / high-profile; mostly only one bit allowed */
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_PROFILE_CBP		0x01
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_PROFILE_CHP		0x02

/* max h264 level; mostly only one bit allowed */
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_H264_LEVEL_3_1		0x01
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_H264_LEVEL_3_2		0x02
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_H264_LEVEL_4_0		0x04
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_H264_LEVEL_4_1		0x08
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_H264_LEVEL_4_2		0x10

/* display latency; encoded in multiples of 5ms */
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_UNKNOWN_LATENCY	0x00
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_LATENCY_FROM_MS(_ms) \
							(((_ms) + 4ULL) / 5ULL)

/* smallest slice size expressed in number of macro-blocks or 0x0 */
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_NO_SLICES		0x0000

/* if no slices allowed, this can be set on slice_env */
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_NO_SLICE_ENC		0x0000

/* max number of slices per picture MINUS 1 (0 not allowed) */
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_SLICE_ENC_MAX_MASK	0x03ff
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_SLICE_ENC_MAX_SHIFT	0

/* ratio of max-slice-size to be used and slice_min field (0 not allowed) */
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_SLICE_ENC_RATIO_MASK	0x0c00
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_SLICE_ENC_RATIO_SHIFT	10

/* frame skipping */
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_NO_FRAME_SKIP		0x00
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_CAN_FRAME_SKIP		0x01

#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_FRAME_SKIP_MAX_I_MASK	0x0e
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_FRAME_SKIP_MAX_I_SHIFT	1
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_FRAME_SKIP_MAX_I_ANY	0x00

#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_FRAME_SKIP_NO_DYN	0x00
#define OPENWFD_WFD_IE_SUB_VIDEO_FORMATS_FRAME_SKIP_CAN_DYN	0x10

struct openwfd_wfd_ie_sub_video_formats {
	uint32_t cea_modes;
	uint32_t vesa_modes;
	uint32_t hh_modes;
	uint8_t native_mode;
	uint8_t h264_profile;
	uint8_t h264_max_level;
	uint8_t latency;
	uint16_t slice_min;
	uint16_t slice_enc;
	uint8_t frame_skip;
} OPENWFD__WFD_PACKED;

/*
 * IE subelement 3d formats
 * Multiple 3d-subelements are allowed, one for each supported h264 profile.
 */

/* 3d cpabilities; required modes; 1920x540/540@p24 is always required; if you
 * support higher resolutions at p60 or p50, you also must support
 * 1280x360/360@p60 or 1280x360/360@p50 respectively */
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1920_X_540_540_P24		0x0000000000000001
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1280_X_360_360_P60		0x0000000000000002
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1280_X_360_360_P50		0x0000000000000004
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1920_X_1080_P24_P24		0x0000000000000008
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1280_X_720_P60_P60		0x0000000000000010
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1280_X_720_P30_P30		0x0000000000000020
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1280_X_720_P50_P50		0x0000000000000040
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1280_X_720_P25_P25		0x0000000000000080
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1920_X_1080_45_1080_P24	0x0000000000000100
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1280_X_720_30_720_P60		0x0000000000000200
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1280_X_720_30_720_P30		0x0000000000000400
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1280_X_720_30_720_P50		0x0000000000000800
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1280_X_720_30_720_P25		0x0000000000001000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_960_960_X_1080_I60		0x0000000000002000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_960_960_X_1080_I50		0x0000000000004000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_640_X_240_240_P60		0x0000000000008000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_320_320_X_480_P60		0x0000000000010000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_720_X_240_240_P60		0x0000000000020000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_360_360_X_480_P60		0x0000000000040000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_720_X_288_288_P50		0x0000000000080000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_360_360_X_576_P50		0x0000000000100000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1280_X_360_360_P24		0x0000000000200000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_640_640_X_720_P24		0x0000000000400000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1280_X_360_360_P25		0x0000000000800000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_640_640_X_720_P25		0x0000000001000000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1280_X_360_360_P30		0x0000000002000000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_640_640_X_720_P30		0x0000000004000000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1920_X_540_540_P30		0x0000000008000000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1920_X_540_540_P50		0x0000000010000000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1920_X_540_540_P60		0x0000000020000000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_640_640_X_720_P50		0x0000000040000000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_640_640_X_720_P60		0x0000000080000000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_960_960_X_1080_P24		0x0000000100000000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_960_960_X_1080_P50		0x0000000200000000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_960_960_X_1080_P60		0x0000000400000000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1920_X_1080_45_1080_P30	0x0000000800000000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1920_X_1080_45_1080_I50	0x0000001000000000
#define OPENWFD_WFD_IE_SUB_3D_FORMATS_CAP_1920_X_1080_45_1080_I60	0x0000002000000000

struct openwfd_wfd_ie_sub_3d_formats {
	uint64_t capabilities;
	uint8_t native_mode;	/* same as video_formats.native_mode */
	uint8_t h264_profile;	/* same as video_formats.h264_profile */
	uint8_t h264_max_level;	/* same as video_formats.h264_max_level */
	uint8_t latency;	/* same as video_formats.latency */
	uint16_t slice_min;	/* same as video_formats.slice_min */
	uint16_t slice_enc;	/* same as video_formats.slice_enc */
	uint8_t frame_skip;	/* same as video_formats.frame_skip */
} OPENWFD__WFD_PACKED;

/*
 * IE subelement content protection
 */

/* HDCP 2.0 */
#define OPENWFD_WFD_IE_SUB_CONTENT_PROTECT_HDCP_2_0_MASK	0x01
#define OPENWFD_WFD_IE_SUB_CONTENT_PROTECT_NO_HDCP_2_0		0x00
#define OPENWFD_WFD_IE_SUB_CONTENT_PROTECT_CAN_HDCP_2_0		0x01

/* HDCP 2.1; if set, you must also set HDCP 2.0 */
#define OPENWFD_WFD_IE_SUB_CONTENT_PROTECT_HDCP_2_1_MASK	0x02
#define OPENWFD_WFD_IE_SUB_CONTENT_PROTECT_NO_HDCP_2_1		0x00
#define OPENWFD_WFD_IE_SUB_CONTENT_PROTECT_CAN_HDCP_2_1		0x02

struct openwfd_wfd_ie_sub_content_protect {
	uint8_t flags;
} OPENWFD__WFD_PACKED;

/*
 * IE subelement coupled sink information
 */

/* status */
#define OPENWFD_WFD_IE_SUB_COUPLED_SINK_STATUS_MASK		0x03
#define OPENWFD_WFD_IE_SUB_COUPLED_SINK_NOT_COUPLED		0x00
#define OPENWFD_WFD_IE_SUB_COUPLED_SINK_COUPLED			0x01
#define OPENWFD_WFD_IE_SUB_COUPLED_SINK_COUPLE_TEARDOWN		0x02

struct openwfd_wfd_ie_sub_coupled_sink {
	uint8_t status;
	uint8_t mac[6];
} OPENWFD__WFD_PACKED;

/*
 * IE subelement extended capabilities
 */

/* UIBC */
#define OPENWFD_WFD_IE_SUB_EXT_CAP_UIBC_MASK			0x01
#define OPENWFD_WFD_IE_SUB_EXT_CAP_NO_UIBC			0x00
#define OPENWFD_WFD_IE_SUB_EXT_CAP_CAN_UIBC			0x01

/* I2C */
#define OPENWFD_WFD_IE_SUB_EXT_CAP_I2C_MASK			0x02
#define OPENWFD_WFD_IE_SUB_EXT_CAP_NO_I2C			0x00
#define OPENWFD_WFD_IE_SUB_EXT_CAP_CAN_I2C			0x02

/* Preferred Mode */
#define OPENWFD_WFD_IE_SUB_EXT_CAP_PREFER_MODE_MASK		0x04
#define OPENWFD_WFD_IE_SUB_EXT_CAP_NO_PREFER_MODE		0x00
#define OPENWFD_WFD_IE_SUB_EXT_CAP_CAN_PREFER_MODE		0x04

/* Standby */
#define OPENWFD_WFD_IE_SUB_EXT_CAP_STANDBY_MASK			0x08
#define OPENWFD_WFD_IE_SUB_EXT_CAP_NO_STANDBY			0x00
#define OPENWFD_WFD_IE_SUB_EXT_CAP_CAN_STANDBY			0x08

/* Persistend TDLS */
#define OPENWFD_WFD_IE_SUB_EXT_CAP_PERSIST_TDLS_MASK		0x10
#define OPENWFD_WFD_IE_SUB_EXT_CAP_NO_PERSIST_TDLS		0x00
#define OPENWFD_WFD_IE_SUB_EXT_CAP_CAN_PERSIST_TDLS		0x10

/* Persistend TDLS BSSID */
#define OPENWFD_WFD_IE_SUB_EXT_CAP_PERSIST_TDLS_BSSID_MASK	0x20
#define OPENWFD_WFD_IE_SUB_EXT_CAP_NO_PERSIST_TDLS_BSSID	0x00
#define OPENWFD_WFD_IE_SUB_EXT_CAP_CAN_PERSIST_TDLS_BSSID	0x20

struct openwfd_wfd_ie_sub_ext_cap {
	uint16_t flags;
} OPENWFD__WFD_PACKED;

/*
 * IE subelement local ip
 */

#define OPENWFD_WFD_IE_SUB_LOCAL_IP_IPV4			0x01

struct openwfd_wfd_ie_sub_local_ip {
	uint8_t version;
	uint8_t ip[4];
} OPENWFD__WFD_PACKED;

/*
 * IE subelement session information
 */

/* real payload is actually an array of this object for each device */
struct openwfd_wfd_ie_sub_session_info {
	uint8_t length;			/* fixed: 23 == (sizeof(this) - 1) */
	uint8_t mac[6];
	uint8_t bssid[6];
	uint16_t dev_info;		/* same as dev_info.dev_info */
	uint16_t max_throughput;	/* same as dev_info.max_throughput */
	uint8_t coupled_status;		/* same as coupled_sink.status */
	uint8_t coupled_mac[6];		/* same as coupled_sink.mac */
} OPENWFD__WFD_PACKED;

/*
 * IE subelement alternative mac
 */

struct openwfd_wfd_ie_sub_alt_mac {
	uint8_t mac[6];
} OPENWFD__WFD_PACKED;

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* OPENWFD_WFD_DEFS_H */
