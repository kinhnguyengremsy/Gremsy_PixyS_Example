#ifndef CRDEVICEPROPERTY_H
#define CRDEVICEPROPERTY_H

#include "CrDefines.h"

#if defined(_MSC_VER)
// Windows definitions
#pragma warning (push)
#pragma warning (disable: 4480)	// warning C4480: 'specifying underlying type for enum' are not treated as standard in VS 2010.

	#ifdef CR_SDK_EXPORTS
		#define SCRSDK_API __declspec(dllexport)
	#else
		#define SCRSDK_API __declspec(dllimport)
	#endif
// End Windows definitions
#else
	#if defined(__GNUC__)
		#ifdef CR_SDK_EXPORTS
			#define SCRSDK_API __attribute__ ((visibility ("default")))
		#else
			#define SCRSDK_API
		#endif
	#endif
#endif

namespace SCRSDK
{
enum CrDevicePropertyCode : CrInt32u
{
	CrDeviceProperty_Undefined 			= 0,

	CrDeviceProperty_S1,
	CrDeviceProperty_AEL,
	CrDeviceProperty_FEL,
	CrDeviceProperty_AFL,
	CrDeviceProperty_AWBL,

	CrDeviceProperty_FNumber 			= 0x0100,
	CrDeviceProperty_ExposureBiasCompensation,
	CrDeviceProperty_FlashCompensation,
	CrDeviceProperty_ShutterSpeed,
	CrDeviceProperty_IsoSensitivity,
	CrDeviceProperty_ExposureProgramMode,
	CrDeviceProperty_FileType,
	CrDeviceProperty_JpegQuality,
	CrDeviceProperty_WhiteBalance,
	CrDeviceProperty_FocusMode,
	CrDeviceProperty_MeteringMode,
	CrDeviceProperty_FlashMode,
	CrDeviceProperty_WirelessFlash,
	CrDeviceProperty_RedEyeReduction,
	CrDeviceProperty_DriveMode,
	CrDeviceProperty_DRO,
	CrDeviceProperty_ImageSize,
	CrDeviceProperty_AspectRatio,
	CrDeviceProperty_PictureEffect,
	CrDeviceProperty_FocusArea,
	CrDeviceProperty_reserved4,
	CrDeviceProperty_Colortemp,
	CrDeviceProperty_ColorTuningAB,
	CrDeviceProperty_ColorTuningGM,

	CrDeviceProperty_LiveViewDisplayEffect,
	CrDeviceProperty_StillImageStoreDestination,
	CrDeviceProperty_PriorityKeySettings,
	CrDeviceProperty_reserved5,
	CrDeviceProperty_reserved6,
	CrDeviceProperty_Focus_Magnifier_Setting,
	CrDeviceProperty_DateTime_Settings,
	CrDeviceProperty_NearFar,
	CrDeviceProperty_reserved7,
	CrDeviceProperty_AF_Area_Position,
	CrDeviceProperty_reserved8,
	CrDeviceProperty_reserved9,

	CrDeviceProperty_Zoom_Scale,
	CrDeviceProperty_Zoom_Setting,
	CrDeviceProperty_Zoom_Operation,
	CrDeviceProperty_Movie_File_Format,
	CrDeviceProperty_Movie_Recording_Setting,
	CrDeviceProperty_Movie_Recording_FrameRateSetting,
	CrDeviceProperty_CompressionFileFormatStill,
	CrDeviceProperty_MediaSLOT1_FileType,
	CrDeviceProperty_MediaSLOT2_FileType,
	CrDeviceProperty_MediaSLOT1_JpegQuality,
	CrDeviceProperty_MediaSLOT2_JpegQuality,
	CrDeviceProperty_MediaSLOT1_ImageSize,
	CrDeviceProperty_MediaSLOT2_ImageSize,
	CrDeviceProperty_RAW_FileCompressionType,
	CrDeviceProperty_MediaSLOT1_RAW_FileCompressionType,
	CrDeviceProperty_MediaSLOT2_RAW_FileCompressionType,
	CrDeviceProperty_ZoomAndFocusPosition_Save,
	CrDeviceProperty_ZoomAndFocusPosition_Load,

	CrDeviceProperty_IrisModeSetting,
	CrDeviceProperty_ShutterModeSetting,
	CrDeviceProperty_GainControlSetting,
	CrDeviceProperty_GainBaseIsoSensitivity,
	CrDeviceProperty_GainBaseSensitivity,
	CrDeviceProperty_ExposureIndex,
	CrDeviceProperty_BaseLookValue,
	CrDeviceProperty_PlaybackMedia,
	CrDeviceProperty_DispModeSetting,
	CrDeviceProperty_DispMode,
	CrDeviceProperty_TouchOperation,
	CrDeviceProperty_SelectFinder,
	CrDeviceProperty_AutoPowerOffTemperature,
	CrDeviceProperty_BodyKeyLock,
	CrDeviceProperty_ImageID_Num_Setting,
	CrDeviceProperty_ImageID_Num,
	CrDeviceProperty_ImageID_String,
	CrDeviceProperty_ExposureCtrlType,
	CrDeviceProperty_MonitorLUTSetting,
	CrDeviceProperty_FocalDistanceInMeter,
	CrDeviceProperty_FocalDistanceInFeet,
	CrDeviceProperty_FocalDistanceUnitSetting,
	CrDeviceProperty_DigitalZoomScale,
	CrDeviceProperty_ZoomDistance,
	CrDeviceProperty_ZoomDistanceUnitSetting,
	CrDeviceProperty_ShutterModeStatus,
	CrDeviceProperty_ShutterSlow,
	CrDeviceProperty_ShutterSlowFrames,
	CrDeviceProperty_Movie_Recording_ResolutionForMain,
	CrDeviceProperty_Movie_Recording_ResolutionForProxy,
	CrDeviceProperty_Movie_Recording_FrameRateProxySetting,
	CrDeviceProperty_BatteryRemainDisplayUnit,
	CrDeviceProperty_PowerSource,
	CrDeviceProperty_MovieShootingMode,
	CrDeviceProperty_MovieShootingModeColorGamut,
	CrDeviceProperty_MovieShootingModeTargetDisplay,
	CrDeviceProperty_DepthOfFieldAdjustmentMode,
	CrDeviceProperty_ColortempStep,
	CrDeviceProperty_WhiteBalanceModeSetting,
	CrDeviceProperty_WhiteBalanceTint,
	CrDeviceProperty_WhiteBalanceTintStep,
	CrDeviceProperty_Focus_Operation,
	CrDeviceProperty_ShutterECSSetting,
	CrDeviceProperty_ShutterECSNumber,
	CrDeviceProperty_ShutterECSNumberStep,
	CrDeviceProperty_ShutterECSFrequency,
	CrDeviceProperty_RecorderControlProxySetting,
	CrDeviceProperty_ButtonAssignmentAssignable1,
	CrDeviceProperty_ButtonAssignmentAssignable2,
	CrDeviceProperty_ButtonAssignmentAssignable3,
	CrDeviceProperty_ButtonAssignmentAssignable4,
	CrDeviceProperty_ButtonAssignmentAssignable5,
	CrDeviceProperty_ButtonAssignmentAssignable6,
	CrDeviceProperty_ButtonAssignmentAssignable7,
	CrDeviceProperty_ButtonAssignmentAssignable8,
	CrDeviceProperty_ButtonAssignmentAssignable9,
	CrDeviceProperty_ButtonAssignmentLensAssignable1,
	CrDeviceProperty_AssignableButton1,
	CrDeviceProperty_AssignableButton2,
	CrDeviceProperty_AssignableButton3,
	CrDeviceProperty_AssignableButton4,
	CrDeviceProperty_AssignableButton5,
	CrDeviceProperty_AssignableButton6,
	CrDeviceProperty_AssignableButton7,
	CrDeviceProperty_AssignableButton8,
	CrDeviceProperty_AssignableButton9,
	CrDeviceProperty_LensAssignableButton1,
	CrDeviceProperty_FocusModeSetting,
	CrDeviceProperty_ShutterAngle,
	CrDeviceProperty_ShutterSetting,
	CrDeviceProperty_ShutterMode,
	CrDeviceProperty_ShutterSpeedValue,
	CrDeviceProperty_NDFilter,
	CrDeviceProperty_NDFilterModeSetting,
	CrDeviceProperty_NDFilterValue,
	CrDeviceProperty_GainUnitSetting,
	CrDeviceProperty_GaindBValue,
	CrDeviceProperty_AWB,
	CrDeviceProperty_SceneFileIndex,
	CrDeviceProperty_MoviePlayButton,
	CrDeviceProperty_MoviePlayPauseButton,
	CrDeviceProperty_MoviePlayStopButton,
	CrDeviceProperty_MovieForwardButton,
	CrDeviceProperty_MovieRewindButton,
	CrDeviceProperty_MovieNextButton,
	CrDeviceProperty_MoviePrevButton,
	CrDeviceProperty_MovieRecReviewButton,
	CrDeviceProperty_FaceEyeDetectionAF,
	CrDeviceProperty_AFTransitionSpeed,
	CrDeviceProperty_AFSubjShiftSens,
	CrDeviceProperty_AFAssist,
	CrDeviceProperty_NDPresetOrVariableSwitchingSetting,
	CrDeviceProperty_FunctionOfRemoteTouchOperation,
	CrDeviceProperty_RemoteTouchOperation,
	CrDeviceProperty_FollowFocusPositionSetting,
	CrDeviceProperty_FocusBracketShotNumber,
	CrDeviceProperty_FocusBracketFocusRange,

	CrDeviceProperty_S2 = 0x0500,
	CrDeviceProperty_reserved10,
	CrDeviceProperty_reserved11,
	CrDeviceProperty_reserved12,
	CrDeviceProperty_reserved13,
	CrDeviceProperty_Interval_Rec_Mode,
	CrDeviceProperty_Still_Image_Trans_Size,
	CrDeviceProperty_RAW_J_PC_Save_Image,
	CrDeviceProperty_LiveView_Image_Quality,
	CrDeviceProperty_CustomWB_Capture_Standby,
	CrDeviceProperty_CustomWB_Capture_Standby_Cancel,
	CrDeviceProperty_CustomWB_Capture,
	CrDeviceProperty_Remocon_Zoom_Speed_Type,

	CrDeviceProperty_GetOnly = 0x0700,

	CrDeviceProperty_SnapshotInfo,
	CrDeviceProperty_BatteryRemain,
	CrDeviceProperty_BatteryLevel,
	CrDeviceProperty_EstimatePictureSize,
	CrDeviceProperty_RecordingState,
	CrDeviceProperty_LiveViewStatus,
	CrDeviceProperty_FocusIndication,
	CrDeviceProperty_MediaSLOT1_Status,
	CrDeviceProperty_MediaSLOT1_RemainingNumber,
	CrDeviceProperty_MediaSLOT1_RemainingTime,
	CrDeviceProperty_MediaSLOT1_FormatEnableStatus,
	CrDeviceProperty_reserved20,
	CrDeviceProperty_MediaSLOT2_Status,
	CrDeviceProperty_MediaSLOT2_FormatEnableStatus,
	CrDeviceProperty_MediaSLOT2_RemainingNumber,
	CrDeviceProperty_MediaSLOT2_RemainingTime,
	CrDeviceProperty_reserved22,
	CrDeviceProperty_Media_FormatProgressRate,
	CrDeviceProperty_reserved24,
	CrDeviceProperty_reserved25,
	CrDeviceProperty_LiveView_Area,
	CrDeviceProperty_reserved26,
	CrDeviceProperty_reserved27,
	CrDeviceProperty_Interval_Rec_Status,
	CrDeviceProperty_CustomWB_Execution_State,
	CrDeviceProperty_CustomWB_Capturable_Area,
	CrDeviceProperty_CustomWB_Capture_Frame_Size,
	CrDeviceProperty_CustomWB_Capture_Operation,
	CrDeviceProperty_reserved32,
	CrDeviceProperty_Zoom_Operation_Status,
	CrDeviceProperty_Zoom_Bar_Information,
	CrDeviceProperty_Zoom_Type_Status,
	CrDeviceProperty_MediaSLOT1_QuickFormatEnableStatus,
	CrDeviceProperty_MediaSLOT2_QuickFormatEnableStatus,
	CrDeviceProperty_Cancel_Media_FormatEnableStatus,
	CrDeviceProperty_Zoom_Speed_Range,

	CrDeviceProperty_SdkControlMode,
	CrDeviceProperty_ContentsTransferStatus,
	CrDeviceProperty_ContentsTransferCancelEnableStatus,
	CrDeviceProperty_ContentsTransferProgress,

	CrDeviceProperty_IsoCurrentSensitivity,
	CrDeviceProperty_CameraSetting_SaveOperationEnableStatus,
	CrDeviceProperty_CameraSetting_ReadOperationEnableStatus,
	CrDeviceProperty_CameraSetting_SaveRead_State,
	CrDeviceProperty_CameraSettingsResetEnableStatus,
	CrDeviceProperty_APS_C_or_Full_SwitchingSetting,
	CrDeviceProperty_APS_C_or_Full_SwitchingEnableStatus,
	CrDeviceProperty_DispModeCandidate,
	CrDeviceProperty_ShutterSpeedCurrentValue,
	CrDeviceProperty_Focus_Speed_Range,
	CrDeviceProperty_NDFilterMode,
	CrDeviceProperty_MoviePlayingSpeed,
	CrDeviceProperty_MediaSLOT1Player,
	CrDeviceProperty_MediaSLOT2Player,
	CrDeviceProperty_BatteryRemainingInMinutes,
	CrDeviceProperty_BatteryRemainingInVoltage,
	CrDeviceProperty_DCVoltage,
	CrDeviceProperty_MoviePlayingState,
	CrDeviceProperty_FocusTouchSpotStatus,
	CrDeviceProperty_FocusTrackingStatus,
	CrDeviceProperty_DepthOfFieldAdjustmentInterlockingMode,
	CrDeviceProperty_RecorderClipName,
	CrDeviceProperty_RecorderControlMainSetting,
	CrDeviceProperty_RecorderStartMain,
	CrDeviceProperty_RecorderStartProxy,
	CrDeviceProperty_RecorderMainStatus,
	CrDeviceProperty_RecorderProxyStatus,
	CrDeviceProperty_RecorderExtRawStatus,
	CrDeviceProperty_RecorderSaveDestination,
	CrDeviceProperty_AssignableButtonIndicator1,
	CrDeviceProperty_AssignableButtonIndicator2,
	CrDeviceProperty_AssignableButtonIndicator3,
	CrDeviceProperty_AssignableButtonIndicator4,
	CrDeviceProperty_AssignableButtonIndicator5,
	CrDeviceProperty_AssignableButtonIndicator6,
	CrDeviceProperty_AssignableButtonIndicator7,
	CrDeviceProperty_AssignableButtonIndicator8,
	CrDeviceProperty_AssignableButtonIndicator9,
	CrDeviceProperty_LensAssignableButtonIndicator1,
	CrDeviceProperty_GaindBCurrentValue,
	CrDeviceProperty_SoftwareVersion,
	CrDeviceProperty_CurrentSceneFileEdited,
	CrDeviceProperty_MovieRecButtonToggleEnableStatus,
	CrDeviceProperty_RemoteTouchOperationEnableStatus,
	CrDeviceProperty_CancelRemoteTouchOperationEnableStatus,
	CrDeviceProperty_LensInformationEnableStatus,
	CrDeviceProperty_FollowFocusPositionCurrentValue,
	CrDeviceProperty_FocusBracketShootingStatus,

	CrDeviceProperty_MaxVal	= 0x1000,
};

enum CrLiveViewPropertyCode : CrInt32u
{
	CrLiveViewProperty_AF_Area_Position = CrDevicePropertyCode::CrDeviceProperty_AF_Area_Position,
	CrLiveViewProperty_Focus_Magnifier_Position = 0x0122,
	CrLiveViewProperty_LiveViewUndefined = CrDevicePropertyCode::CrDeviceProperty_MaxVal,
	CrLiveViewProperty__LiveViewMaxVal = 0x2000,
};

enum CrSdkControlMode : CrInt32u
{
	CrSdkControlMode_Remote = 0x00000000,
	CrSdkControlMode_ContentsTransfer,
};

// =========================== S1, AEL, FEL, AFL, AWBL ===========================
enum CrLockIndicator : CrInt16u
{
	CrLockIndicator_Unknown = 0x0000,
	CrLockIndicator_Unlocked,
	CrLockIndicator_Locked,
};
// ===============================================================================


enum CrPropValueSet : CrInt16
{
	CrPropValueMinus1 = -1,
	CrPropValuePlus1 = 1,
};

// FNumber
// type: CrDataType_UInt16
// value = F number * 100
enum CrFnumberSet : CrInt16u
{
	CrFnumber_Unknown = 0xFFFE, // Display "--"
	CrFnumber_Nothing = 0xFFFF, // Nothing to display
};

// ExposureBiasCompensation
// type: CrDataType_UInt16
// value: compensation value * 1000

// FlashCompensation
// type: CrDataType_UInt16
// value = compensation value * 1000

// ShutterSpeed
// type: CrDataType_UInt32
// value = low-order word / high-order word
enum CrShutterSpeedSet : CrInt32u
{
	CrShutterSpeed_Bulb = 0x00000000,
	CrShutterSpeed_Nothing = 0xFFFFFFFF, // Nothing to display
};

// IsoSensitivity
// type: CrDataType_UInt32
// value: bit 28-31 extension, bit 24-27 ISO mode, bit 0-23 ISO value
enum CrISOMode : CrInt32u
{
	CrISO_Normal = 0x00,	// ISO setting Normal
	CrISO_MultiFrameNR = 0x01,	// Multi Frame NR
	CrISO_MultiFrameNR_High = 0x02,	// Multi Frame NR High
	CrISO_Ext = 0x10,	// Indicates of extended value
	CrISO_AUTO = 0xFFFFFF,
};
// ===============================================================================

// ShutterSlowFrames
static const CrInt8u CrShutterSlowFrames_Disable = 0x00;

//
// ShutterAngle
static const CrInt32u CrShutterAngle_Disable = 0x00000000;

// MoviePlayingSpeed
// type: CrDataType_UInt64
// value: upper four bytes = numerator, lower four bytes = denominator.
enum CrMoviePlayingSpeed : CrInt64u
{
	CrMoviePlayingSpeed_Nothing = 0xFFFFFFFFFFFFFFFF, // Nothing to display
};

// FocalDistanceInMeter/Feet
static const CrInt32u CrFocalDistance_Infinity = 0xFFFFFFFF;

// BatteryRemaininginMinutes
static const CrInt32u CrBatteryRemainingInMinutes_Untaken = 0xFFFFFFFF;

// BatteryRemainingInVoltage
static const CrInt32u CrBatteryRemainingInVoltage_Untaken = 0xFFFFFFFF;

// DCVoltage
static const CrInt32u CrDCVoltage_Untaken = 0xFFFFFFFF;

//ND Filter Value
enum CrNDFilterValue : CrInt64u
{
	CrNDFilterValue_Nothing = 0xFFFFFFFFFFFFFFFF // Nothing to display
};

// ExposureProgramMode
enum CrExposureProgram : CrInt32u
{
	CrExposure_M_Manual						= 0x00000001,
	CrExposure_P_Auto,
	CrExposure_A_AperturePriority,
	CrExposure_S_ShutterSpeedPriority,
	CrExposure_Program_Creative,
	CrExposure_Program_Action,
	CrExposure_Portrait,
	CrExposure_Auto							= 0x00008000,
	CrExposure_Auto_Plus,
	CrExposure_P_A,
	CrExposure_P_S,
	CrExposure_Sports_Action,
	CrExposure_Sprots_Action = CrExposure_Sports_Action, /* Do not use. Will be removed in the next release. */
	CrExposure_Sunset,
	CrExposure_Night,
	CrExposure_Landscape,
	CrExposure_Macro,
	CrExposure_HandheldTwilight,
	CrExposure_NightPortrait,
	CrExposure_AntiMotionBlur,
	CrExposure_Pet,
	CrExposure_Gourmet,
	CrExposure_Fireworks,
	CrExposure_HighSensitivity,
	CrExposure_MemoryRecall						= 0x00008020,
	CrExposure_ContinuousPriority_AE_8pics		= 0x00008031,
	CrExposure_ContinuousPriority_AE_10pics,
	CrExposure_ContinuousPriority_AE_12pics,
	CrExposure_3D_SweepPanorama					= 0x00008040,
	CrExposure_SweepPanorama,
	CrExposure_Movie_P							= 0x00008050,
	CrExposure_Movie_A,
	CrExposure_Movie_S,
	CrExposure_Movie_M,
	CrExposure_Movie_Auto,
	CrExposure_Movie_F,
	CrExposure_Movie_SQMotion_P				= 0x00008059,
	CrExposure_Movie_SQMotion_A,
	CrExposure_Movie_SQMotion_S,
	CrExposure_Movie_SQMotion_M,
	CrExposure_Movie_SQMotion_AUTO,
	CrExposure_Movie_SQMotion_F,
	CrExposure_Flash_Off					= 0x00008060,
	CrExposure_PictureEffect				= 0x00008070,
	CrExposure_HiFrameRate_P				= 0x00008080,
	CrExposure_HiFrameRate_A,
	CrExposure_HiFrameRate_S,
	CrExposure_HiFrameRate_M,
	CrExposure_SQMotion_P,
	CrExposure_SQMotion_A,
	CrExposure_SQMotion_S,
	CrExposure_SQMotion_M,
	CrExposure_MOVIE,
	CrExposure_STILL,
	CrExposure_Movie_F_Mode, /* Do not use. Will be removed in the next release. */
	CrExposure_F_MovieOrSQMotion = CrExposure_Movie_F_Mode,
};

// FileType
enum CrFileType : CrInt16u
{
	CrFileType_None = 0x0000,
	CrFileType_Jpeg,
	CrFileType_Raw,
	CrFileType_RawJpeg,
	CrFileType_RawHeif,
	CrFileType_Heif,
};

// JpegQuality
enum CrJpegQuality : CrInt16u
{
	CrJpegQuality_Unknown  = 0x0000,
	CrJpegQuality_Light,
	CrJpegQuality_Standard,
	CrJpegQuality_Fine,
	CrJpegQuality_ExFine,
};

// WhiteBalance
enum CrWhiteBalanceSetting : CrInt16u
{
	CrWhiteBalance_AWB				= 0x0000,
	CrWhiteBalance_Underwater_Auto,
	CrWhiteBalance_Daylight				= 0x0011,
	CrWhiteBalance_Shadow,
	CrWhiteBalance_Cloudy,
	CrWhiteBalance_Tungsten,
	CrWhiteBalance_Fluorescent			= 0x0020,
	CrWhiteBalance_Fluorescent_WarmWhite,
	CrWhiteBalance_Fluorescent_CoolWhite,
	CrWhiteBalance_Fluorescent_DayWhite,
	CrWhiteBalance_Fluorescent_Daylight,
	CrWhiteBalance_Flush				= 0x0030,
	CrWhiteBalance_ColorTemp			= 0x0100,
	CrWhiteBalance_Custom_1,
	CrWhiteBalance_Custom_2,
	CrWhiteBalance_Custom_3,
	CrWhiteBalance_Custom,
};

// FocusMode
enum CrFocusMode : CrInt16u
{
	CrFocus_MF					= 0x0001,
	CrFocus_AF_S,
	CrFocus_AF_C,
	CrFocus_AF_A,
	CrFocus_AF_D,
	CrFocus_DMF,
	CrFocus_PF,
};

// MeteringMode
enum CrMeteringMode : CrInt16u
{
	CrMetering_Average				= 0x0001,
	CrMetering_CenterWeightedAverage,
	CrMetering_MultiSpot,
	CrMetering_CenterSpot,
	CrMetering_Multi,
	CrMetering_CenterWeighted,
	CrMetering_EntireScreenAverage,
	CrMetering_Spot_Standard,
	CrMetering_Spot_Large,
	CrMetering_HighLightWeighted,
};

// FlashMode
enum CrFlashMode : CrInt16u
{
	CrFlash_Auto					= 0x0001,
	CrFlash_Off,
	CrFlash_Fill,
	CrFlash_ExternalSync,
	CrFlash_SlowSync,
	CrFlash_RearSync,
};

// WirelessFlash
enum CrWirelessFlash : CrInt16u
{
	CrWirelessFlash_Off = 0x0000,
	CrWirelessFlash_On,
};

// RedEyeReduction
enum CrRedEyeReduction : CrInt16u
{
	CrRedEye_Off = 0x0000,
	CrRedEye_On,
};

// MediaFormat
enum CrMediaFormat : CrInt8u
{
	CrMediaFormat_Disable = 0x00,
	CrMediaFormat_Enable,
};

// Cancel MediaFormat
enum CrCancelMediaFormat : CrInt8u
{
	CrCancelMediaFormat_Disable = 0x00,
	CrCancelMediaFormat_Enable,
};

// DriveMode
enum CrDriveMode : CrInt32u
{
	CrDrive_Single					= 0x00000001,
	CrDrive_Continuous_Hi				= 0x00010001,
	CrDrive_Continuous_Hi_Plus,
	CrDrive_Continuous_Hi_Live,
	CrDrive_Continuous_Lo,
	CrDrive_Continuous,
	CrDrive_Continuous_SpeedPriority,
	CrDrive_Continuous_Mid,
	CrDrive_Continuous_Mid_Live,
	CrDrive_Continuous_Lo_Live,
	CrDrive_SingleBurstShooting_lo			= 0x00011001,
	CrDrive_SingleBurstShooting_mid,
	CrDrive_SingleBurstShooting_hi,
	CrDrive_FocusBracket					= 0x00012001,
	CrDrive_Timelapse				= 0x00020001,
	CrDrive_Timer_2s				= 0x00030001,
	CrDrive_Timer_5s,
	CrDrive_Timer_10s,
	CrDrive_Continuous_Bracket_03Ev_3pics		= 0x00040301,
	CrDrive_Continuous_Bracket_03Ev_5pics,
	CrDrive_Continuous_Bracket_03Ev_9pics,
	CrDrive_Continuous_Bracket_05Ev_3pics,
	CrDrive_Continuous_Bracket_05Ev_5pics,
	CrDrive_Continuous_Bracket_05Ev_9pics,
	CrDrive_Continuous_Bracket_07Ev_3pics,
	CrDrive_Continuous_Bracket_07Ev_5pics,
	CrDrive_Continuous_Bracket_07Ev_9pics,
	CrDrive_Continuous_Bracket_10Ev_3pics,
	CrDrive_Continuous_Bracket_10Ev_5pics,
	CrDrive_Continuous_Bracket_10Ev_9pics,
	CrDrive_Continuous_Bracket_20Ev_3pics,
	CrDrive_Continuous_Bracket_20Ev_5pics,
	CrDrive_Continuous_Bracket_30Ev_3pics,
	CrDrive_Continuous_Bracket_30Ev_5pics,
	CrDrive_Continuous_Bracket_03Ev_2pics_Plus,
	CrDrive_Continuous_Bracket_03Ev_2pics_Minus,
	CrDrive_Continuous_Bracket_03Ev_7pics,
	CrDrive_Continuous_Bracket_05Ev_2pics_Plus,
	CrDrive_Continuous_Bracket_05Ev_2pics_Minus,
	CrDrive_Continuous_Bracket_05Ev_7pics,
	CrDrive_Continuous_Bracket_07Ev_2pics_Plus,
	CrDrive_Continuous_Bracket_07Ev_2pics_Minus,
	CrDrive_Continuous_Bracket_07Ev_7pics,
	CrDrive_Continuous_Bracket_10Ev_2pics_Plus,
	CrDrive_Continuous_Bracket_10Ev_2pics_Minus,
	CrDrive_Continuous_Bracket_10Ev_7pics,
	CrDrive_Continuous_Bracket_13Ev_2pics_Plus,
	CrDrive_Continuous_Bracket_13Ev_2pics_Minus,
	CrDrive_Continuous_Bracket_13Ev_3pics,
	CrDrive_Continuous_Bracket_13Ev_5pics,
	CrDrive_Continuous_Bracket_13Ev_7pics,
	CrDrive_Continuous_Bracket_15Ev_2pics_Plus,
	CrDrive_Continuous_Bracket_15Ev_2pics_Minus,
	CrDrive_Continuous_Bracket_15Ev_3pics,
	CrDrive_Continuous_Bracket_15Ev_5pics,
	CrDrive_Continuous_Bracket_15Ev_7pics,
	CrDrive_Continuous_Bracket_17Ev_2pics_Plus,
	CrDrive_Continuous_Bracket_17Ev_2pics_Minus,
	CrDrive_Continuous_Bracket_17Ev_3pics,
	CrDrive_Continuous_Bracket_17Ev_5pics,
	CrDrive_Continuous_Bracket_17Ev_7pics,
	CrDrive_Continuous_Bracket_20Ev_2pics_Plus,
	CrDrive_Continuous_Bracket_20Ev_2pics_Minus,
	CrDrive_Continuous_Bracket_20Ev_7pics,
	CrDrive_Continuous_Bracket_23Ev_2pics_Plus,
	CrDrive_Continuous_Bracket_23Ev_2pics_Minus,
	CrDrive_Continuous_Bracket_23Ev_3pics,
	CrDrive_Continuous_Bracket_23Ev_5pics,
	CrDrive_Continuous_Bracket_25Ev_2pics_Plus,
	CrDrive_Continuous_Bracket_25Ev_2pics_Minus,
	CrDrive_Continuous_Bracket_25Ev_3pics,
	CrDrive_Continuous_Bracket_25Ev_5pics,
	CrDrive_Continuous_Bracket_27Ev_2pics_Plus,
	CrDrive_Continuous_Bracket_27Ev_2pics_Minus,
	CrDrive_Continuous_Bracket_27Ev_3pics,
	CrDrive_Continuous_Bracket_27Ev_5pics,
	CrDrive_Continuous_Bracket_30Ev_2pics_Plus,
	CrDrive_Continuous_Bracket_30Ev_2pics_Minus,
	CrDrive_Single_Bracket_03Ev_3pics		= 0x00050001,
	CrDrive_Single_Bracket_03Ev_5pics,
	CrDrive_Single_Bracket_03Ev_9pics,
	CrDrive_Single_Bracket_05Ev_3pics,
	CrDrive_Single_Bracket_05Ev_5pics,
	CrDrive_Single_Bracket_05Ev_9pics,
	CrDrive_Single_Bracket_07Ev_3pics,
	CrDrive_Single_Bracket_07Ev_5pics,
	CrDrive_Single_Bracket_07Ev_9pics,
	CrDrive_Single_Bracket_10Ev_3pics,
	CrDrive_Single_Bracket_10Ev_5pics,
	CrDrive_Single_Bracket_10Ev_9pics,
	CrDrive_Single_Bracket_20Ev_3pics,
	CrDrive_Single_Bracket_20Ev_5pics,
	CrDrive_Single_Bracket_30Ev_3pics,
	CrDrive_Single_Bracket_30Ev_5pics,
	CrDrive_Single_Bracket_03Ev_2pics_Plus,
	CrDrive_Single_Bracket_03Ev_2pics_Minus,
	CrDrive_Single_Bracket_03Ev_7pics,
	CrDrive_Single_Bracket_05Ev_2pics_Plus,
	CrDrive_Single_Bracket_05Ev_2pics_Minus,
	CrDrive_Single_Bracket_05Ev_7pics,
	CrDrive_Single_Bracket_07Ev_2pics_Plus,
	CrDrive_Single_Bracket_07Ev_2pics_Minus,
	CrDrive_Single_Bracket_07Ev_7pics,
	CrDrive_Single_Bracket_10Ev_2pics_Plus,
	CrDrive_Single_Bracket_10Ev_2pics_Minus,
	CrDrive_Single_Bracket_10Ev_7pics,
	CrDrive_Single_Bracket_13Ev_2pics_Plus,
	CrDrive_Single_Bracket_13Ev_2pics_Minus,
	CrDrive_Single_Bracket_13Ev_3pics,
	CrDrive_Single_Bracket_13Ev_5pics,
	CrDrive_Single_Bracket_13Ev_7pics,
	CrDrive_Single_Bracket_15Ev_2pics_Plus,
	CrDrive_Single_Bracket_15Ev_2pics_Minus,
	CrDrive_Single_Bracket_15Ev_3pics,
	CrDrive_Single_Bracket_15Ev_5pics,
	CrDrive_Single_Bracket_15Ev_7pics,
	CrDrive_Single_Bracket_17Ev_2pics_Plus,
	CrDrive_Single_Bracket_17Ev_2pics_Minus,
	CrDrive_Single_Bracket_17Ev_3pics,
	CrDrive_Single_Bracket_17Ev_5pics,
	CrDrive_Single_Bracket_17Ev_7pics,
	CrDrive_Single_Bracket_20Ev_2pics_Plus,
	CrDrive_Single_Bracket_20Ev_2pics_Minus,
	CrDrive_Single_Bracket_20Ev_7pics,
	CrDrive_Single_Bracket_23Ev_2pics_Plus,
	CrDrive_Single_Bracket_23Ev_2pics_Minus,
	CrDrive_Single_Bracket_23Ev_3pics,
	CrDrive_Single_Bracket_23Ev_5pics,
	CrDrive_Single_Bracket_25Ev_2pics_Plus,
	CrDrive_Single_Bracket_25Ev_2pics_Minus,
	CrDrive_Single_Bracket_25Ev_3pics,
	CrDrive_Single_Bracket_25Ev_5pics,
	CrDrive_Single_Bracket_27Ev_2pics_Plus,
	CrDrive_Single_Bracket_27Ev_2pics_Minus,
	CrDrive_Single_Bracket_27Ev_3pics,
	CrDrive_Single_Bracket_27Ev_5pics,
	CrDrive_Single_Bracket_30Ev_2pics_Plus,
	CrDrive_Single_Bracket_30Ev_2pics_Minus,
	CrDrive_WB_Bracket_Lo				= 0x00060001,
	CrDrive_WB_Bracket_Hi,
	CrDrive_DRO_Bracket_Lo				= 0x00070001,
	CrDrive_DRO_Bracket_Hi,
	CrDrive_Continuous_Timer_3pics			= 0x00080001,
	CrDrive_Continuous_Timer_5pics,
	CrDrive_Continuous_Timer_2s_3pics,
	CrDrive_Continuous_Timer_2s_5pics,
	CrDrive_Continuous_Timer_5s_3pics,
	CrDrive_Continuous_Timer_5s_5pics,
	CrDrive_LPF_Bracket				= 0x10000001,
	CrDrive_RemoteCommander,
	CrDrive_MirrorUp,
	CrDrive_SelfPortrait_1,
	CrDrive_SelfPortrait_2,
};

// DRO
enum CrDRangeOptimizer : CrInt16u
{
	CrDRangeOptimizer_Off				= 0x0000,
	CrDRangeOptimizer_On,
	CrDRangeOptimizer_Plus				= 0x0010,
	CrDRangeOptimizer_Plus_Manual_1,
	CrDRangeOptimizer_Plus_Manual_2,
	CrDRangeOptimizer_Plus_Manual_3,
	CrDRangeOptimizer_Plus_Manual_4,
	CrDRangeOptimizer_Plus_Manual_5,
	CrDRangeOptimizer_Auto				= 0x0020,
	CrDRangeOptimizer_HDR_Auto			= 0x0030,
	CrDRangeOptimizer_HDR_10Ev,
	CrDRangeOptimizer_HDR_20Ev,
	CrDRangeOptimizer_HDR_30Ev,
	CrDRangeOptimizer_HDR_40Ev,
	CrDRangeOptimizer_HDR_50Ev,
	CrDRangeOptimizer_HDR_60Ev,
};

// ImageSize
enum CrImageSize: CrInt16u
{
	CrImageSize_L	= 0x0001,
	CrImageSize_M,
	CrImageSize_S,
	CrImageSize_VGA,
};

// AspectRatio
enum CrAspectRatioIndex : CrInt16u
{
	CrAspectRatio_3_2	= 0x0001,
	CrAspectRatio_16_9,
	CrAspectRatio_4_3,
	CrAspectRatio_1_1,
};

// PictureEffect
enum CrPictureEffect : CrInt32u
{
	CrPictureEffect_Off = 0x00000000,
	CrPictureEffect_ToyCameraNormal,
	CrPictureEffect_ToyCameraCool,
	CrPictureEffect_ToyCameraWarm,
	CrPictureEffect_ToyCameraGreen,
	CrPictureEffect_ToyCameraMagenta,
	CrPictureEffect_Pop = 0x00000100,
	CrPictureEffect_PosterizationBW = 0x00000200,
	CrPictureEffect_PosterizationColor,
	CrPictureEffect_Retro = 0x00000300,
	CrPictureEffect_SoftHighkey = 0x00000400,
	CrPictureEffect_PartColorRed = 0x00000500,
	CrPictureEffect_PartColorGreen,
	CrPictureEffect_PartColorBlue,
	CrPictureEffect_PartColorYellow,
	CrPictureEffect_HighContrastMonochrome = 0x00000600,
	CrPictureEffect_SoftFocusLow = 0x00000700,
	CrPictureEffect_SoftFocusMid,
	CrPictureEffect_SoftFocusHigh,
	CrPictureEffect_HDRPaintingLow = 0x00000800,
	CrPictureEffect_HDRPaintingMid,
	CrPictureEffect_HDRPaintingHigh,
	CrPictureEffect_RichToneMonochrome = 0x00000901,
	CrPictureEffect_MiniatureAuto = 0x00000A00,
	CrPictureEffect_MiniatureTop,
	CrPictureEffect_MiniatureMidHorizontal,
	CrPictureEffect_MiniatureBottom,
	CrPictureEffect_MiniatureLeft,
	CrPictureEffect_MiniatureMidVertical,
	CrPictureEffect_MiniatureRight,
	CrPictureEffect_MiniatureWaterColor = 0x00000B00,
	CrPictureEffect_MiniatureIllustrationLow = 0x00000C00,
	CrPictureEffect_MiniatureIllustrationMid,
	CrPictureEffect_MiniatureIllustrationHigh,
};

// Movie Recording State
enum CrMovie_Recording_State : CrInt16u
{
	CrMovie_Recording_State_Not_Recording = 0x0000,
	CrMovie_Recording_State_Recording = 0x0001,
	CrMovie_Recording_State_Recording_Failed = 0x0002,
};

// FocusArea
enum CrFocusArea : CrInt16u
{
	CrFocusArea_Unknown				= 0x0000,
	CrFocusArea_Wide,
	CrFocusArea_Zone,
	CrFocusArea_Center,
	CrFocusArea_Flexible_Spot_S,
	CrFocusArea_Flexible_Spot_M,
	CrFocusArea_Flexible_Spot_L,
	CrFocusArea_Expand_Flexible_Spot,
	CrFocusArea_Flexible_Spot,
	CrFocusArea_Tracking_Wide		= 0x0011,
	CrFocusArea_Tracking_Zone,
	CrFocusArea_Tracking_Center,
	CrFocusArea_Tracking_Flexible_Spot_S,
	CrFocusArea_Tracking_Flexible_Spot_M,
	CrFocusArea_Tracking_Flexible_Spot_L,
	CrFocusArea_Tracking_Expand_Flexible_Spot,
	CrFocusArea_Tracking_Flexible_Spot,
};

// Colortemp
// type unsigned long
// value = color temp (K) step 100

enum CrColortemp : CrInt16u
{
	CrColortemp_Min = 0x0000,
	CrColortemp_Max = 0xFFFF,
};

// ColorTuningAB
// type signed short
// value < 0 : A value 0.25 step. Min -36 (eg. -4=A1)
// value > 0 : B value 0.25 step. Max 36 (eg. 4=B1)

// ColorTuningGM
// type signed short
// value < 0 : M value 0.25 step. Min -36 (eg. -4=M1)
// value > 0 : G value 0.25 step. Max 36 (eg. 4=G1)

enum CrColorTuning : CrInt8u
{
	CrColorTuning_Min = 0x00,
	CrColorTuning_Max = 0xFF,
};


// LiveViewDisplayEffect
enum CrLiveViewDisplayEffect : CrInt16u
{
	CrLiveViewDisplayEffect_Unknown = 0x0000,
	CrLiveViewDisplayEffect_ON,
	CrLiveViewDisplayEffect_OFF,
};

// StillImageStoreDestination
enum CrStillImageStoreDestination : CrInt16u
{
	CrStillImageStoreDestination_HostPC = 0x0001,
	CrStillImageStoreDestination_MemoryCard,
	CrStillImageStoreDestination_HostPCAndMemoryCard,
};

// Near/Far Enable Status
enum CrNearFarEnableStatus : CrInt16u
{
	CrNearFar_Disable,
	CrNearFar_Enable,
};

// IntervalRecMode state
enum CrIntervalRecMode : CrInt16u
{
	CrIntervalRecMode_OFF = 0x0001,
	CrIntervalRecMode_ON,
};

// Buffered image file count
// type unsigned short
// value number of buffered image files.

// Battery Residual Quantity
// type unsigned short
// 0~100: percentage of the battery residual quantity.
static const CrInt16u CrBatteryRemain_Untaken = 0xFFFF;

// Battery LV
enum CrBatteryLevel : CrInt32u
{
	CrBatteryLevel_PreEndBattery	= 0x00000001,
	CrBatteryLevel_1_4,								// Level 1/4
	CrBatteryLevel_2_4,
	CrBatteryLevel_3_4,
	CrBatteryLevel_4_4,
	CrBatteryLevel_1_3,								// Level 1/3
	CrBatteryLevel_2_3,
	CrBatteryLevel_3_3,
	CrBatteryLevel_USBPowerSupply = 0x00010000,	// USB Power Supply
	CrBatteryLevel_PreEnd_PowerSupply,
	CrBatteryLevel_1_4_PowerSupply,					// Level 1/4 with USB Power Supply
	CrBatteryLevel_2_4_PowerSupply,
	CrBatteryLevel_3_4_PowerSupply,
	CrBatteryLevel_4_4_PowerSupply,
	CrBatteryLevel_Fake = 0xFFFFFFFD,				// Fake
};

// Estimated Maximum File Size
// type unsigned long
// value Byte

enum CrWhiteBalanceInitialize : CrInt16u
{
	CrWhiteBalance_Initialized = 0x0001,	// Initialized PTP=0x01
};

// LiveView status
enum CrLiveViewStatus: CrInt16u
{
	CrLiveView_NotSupport				= 0x0000,	// Live view is not supported
	CrLiveView_Disable,								// Live view is supported, but can't get LV image
	CrLiveView_Enable,								// Live view is supported, application can get LV image
};

// Interval Rec status
enum CrIntervalRecStatus : CrInt16u
{
	CrIntervalRecStatus_WaitingStart = 0x0001,
	CrIntervalRecStatus_IntervalShooting,
};

// Focus Indicator
enum CrFocusIndicator : CrInt32u
{
	CrFocusIndicator_Unlocked = 0x00000001,
	CrFocusIndicator_Focused_AF_S = 0x00000102,
	CrFocusIndicator_NotFocused_AF_S = 0x00000202,
	CrFocusIndicator_Focused_AF_C = 0x00000103,
	CrFocusIndicator_NotFocused_AF_C = 0x00000203,
	CrFocusIndicator_TrackingSubject_AF_C = 0x00000303,
};

// MediaSLOT_Status
enum CrSlotStatus : CrInt16u
{
	CrSlotStatus_OK = 0x0000,
	CrSlotStatus_NoCard,
	CrSlotStatus_CardError,
	CrSlotStatus_RecognizingOrLockedError,
};

enum CrPriorityKeySettings : CrInt16u
{
	CrPriorityKey_CameraPosition = 0x0001,
	CrPriorityKey_PCRemote = 0x0002,
};

enum CrFocusFrameType : CrInt16u
{
    CrFocusFrameType_Unknown,
};

enum CrFocusFrameState : CrInt16u
{
    CrFocusFrameState_Unknown,
};

enum CrFrameInfoType : CrInt16u
{
    CrFrameInfoType_Unknown,
    CrFrameInfoType_FocusFrameInfo,
	CrFrameInfoType_Magnifier_Position,
};

enum CrPropertyEnableFlag : CrInt16
{
	CrEnableValue_NotSupported = -1,
	CrEnableValue_False = 0,
	CrEnableValue_True,
	CrEnableValue_DisplayOnly,
	CrEnableValue_SetOnly,
};

enum CrPropertyVariableFlag : CrInt16u
{
	CrEnableValue_Invalid,
	CrEnableValue_Invariable,
	CrEnableValue_Variable,
};

enum CrPropertyStillImageTransSize : CrInt16u
{
	CrPropertyStillImageTransSize_Original,
	CrPropertyStillImageTransSize_SmallSize,
	CrPropertyStillImageTransSize_SmallSizeJPEG = CrPropertyStillImageTransSize_SmallSize, /* Do not use. Will be removed in the next release. */
};

enum CrPropertyRAWJPCSaveImage : CrInt16u
{
	CrPropertyRAWJPCSaveImage_RAWAndJPEG,
	CrPropertyRAWJPCSaveImage_JPEGOnly,
	CrPropertyRAWJPCSaveImage_RAWOnly,
	CrPropertyRAWJPCSaveImage_RAWAndHEIF,
	CrPropertyRAWJPCSaveImage_HEIFOnly,
};

enum CrPropertyLiveViewImageQuality : CrInt16u
{
	CrPropertyLiveViewImageQuality_Low,
	CrPropertyLiveViewImageQuality_High,
};

enum CrPropertyCustomWBOperation : CrInt16u
{
	CrPropertyCustomWBOperation_Disable,
	CrPropertyCustomWBOperation_Enable,
};

enum CrPropertyCustomWBExecutionState : CrInt16u
{
	CrPropertyCustomWBExecutionState_Invalid,
	CrPropertyCustomWBExecutionState_Standby,
	CrPropertyCustomWBExecutionState_Capturing,
	CrPropertyCustomWBExecutionState_OperatingCamera,
};

enum CrPropertyCustomWBCaptureButton : CrInt16u
{
	CrPropertyCustomWBCapture_Up,
	CrPropertyCustomWBCapture_Down,
};

// File Format(Movie)
enum CrFileFormatMovie : CrInt8u
{
	CrFileFormatMovie_AVCHD,
	CrFileFormatMovie_MP4,
	CrFileFormatMovie_XAVC_S_4K,
	CrFileFormatMovie_XAVC_S_HD,
	CrFileFormatMovie_XAVC_HS_8K,
	CrFileFormatMovie_XAVC_HS_4K,
	CrFileFormatMovie_XAVC_S_L_4K,
	CrFileFormatMovie_XAVC_S_L_HD,
	CrFileFormatMovie_XAVC_S_I_4K,
	CrFileFormatMovie_XAVC_S_I_HD,
	CrFileFormatMovie_XAVC_I,
	CrFileFormatMovie_XAVC_L,
};

// Recording Setting(Movie)
enum CrRecordingSettingMovie : CrInt16u
{
	CrRecordingSettingMovie_60p_50M = 0x0001,
	CrRecordingSettingMovie_30p_50M,
	CrRecordingSettingMovie_24p_50M,
	CrRecordingSettingMovie_50p_50M,
	CrRecordingSettingMovie_25p_50M,
	CrRecordingSettingMovie_60i_24M,
	CrRecordingSettingMovie_50i_24M_FX,
	CrRecordingSettingMovie_60i_17M_FH,
	CrRecordingSettingMovie_50i_17M_FH,
	CrRecordingSettingMovie_60p_28M_PS,
	CrRecordingSettingMovie_50p_28M_PS,
	CrRecordingSettingMovie_24p_24M_FX,
	CrRecordingSettingMovie_25p_24M_FX,
	CrRecordingSettingMovie_24p_17M_FH,
	CrRecordingSettingMovie_25p_17M_FH,
	CrRecordingSettingMovie_120p_50M_1280x720,
	CrRecordingSettingMovie_100p_50M_1280x720,
	CrRecordingSettingMovie_1920x1080_30p_16M,
	CrRecordingSettingMovie_1920x1080_25p_16M,
	CrRecordingSettingMovie_1280x720_30p_6M,
	CrRecordingSettingMovie_1280x720_25p_6M,
	CrRecordingSettingMovie_1920x1080_60p_28M,
	CrRecordingSettingMovie_1920x1080_50p_28M,
	CrRecordingSettingMovie_60p_25M_XAVC_S_HD,
	CrRecordingSettingMovie_50p_25M_XAVC_S_HD,
	CrRecordingSettingMovie_30p_16M_XAVC_S_HD,
	CrRecordingSettingMovie_25p_16M_XAVC_S_HD,
	CrRecordingSettingMovie_120p_100M_1920x1080_XAVC_S_HD,
	CrRecordingSettingMovie_100p_100M_1920x1080_XAVC_S_HD,
	CrRecordingSettingMovie_120p_60M_1920x1080_XAVC_S_HD,
	CrRecordingSettingMovie_100p_60M_1920x1080_XAVC_S_HD,
	CrRecordingSettingMovie_30p_100M_XAVC_S_4K,
	CrRecordingSettingMovie_25p_100M_XAVC_S_4K,
	CrRecordingSettingMovie_24p_100M_XAVC_S_4K,
	CrRecordingSettingMovie_30p_60M_XAVC_S_4K,
	CrRecordingSettingMovie_25p_60M_XAVC_S_4K,
	CrRecordingSettingMovie_24p_60M_XAVC_S_4K,
	CrRecordingSettingMovie_600M_422_10bit,
	CrRecordingSettingMovie_500M_422_10bit,
	CrRecordingSettingMovie_400M_420_10bit,
	CrRecordingSettingMovie_300M_422_10bit,
	CrRecordingSettingMovie_280M_422_10bit,
	CrRecordingSettingMovie_250M_422_10bit,
	CrRecordingSettingMovie_240M_422_10bit,
	CrRecordingSettingMovie_222M_422_10bit,
	CrRecordingSettingMovie_200M_422_10bit,
	CrRecordingSettingMovie_200M_420_10bit,
	CrRecordingSettingMovie_200M_420_8bit,
	CrRecordingSettingMovie_185M_422_10bit,
	CrRecordingSettingMovie_150M_420_10bit,
	CrRecordingSettingMovie_150M_420_8bit,
	CrRecordingSettingMovie_140M_422_10bit,
	CrRecordingSettingMovie_111M_422_10bit,
	CrRecordingSettingMovie_100M_422_10bit,
	CrRecordingSettingMovie_100M_420_10bit,
	CrRecordingSettingMovie_100M_420_8bit,
	CrRecordingSettingMovie_93M_422_10bit,
	CrRecordingSettingMovie_89M_422_10bit,
	CrRecordingSettingMovie_75M_420_10bit,
	CrRecordingSettingMovie_60M_420_8bit,
	CrRecordingSettingMovie_50M_422_10bit,
	CrRecordingSettingMovie_50M_420_10bit,
	CrRecordingSettingMovie_50M_420_8bit,
	CrRecordingSettingMovie_45M_420_10bit,
	CrRecordingSettingMovie_30M_420_10bit,
	CrRecordingSettingMovie_25M_420_8bit,
	CrRecordingSettingMovie_16M_420_8bit,
	CrRecordingSettingMovie_520M_422_10bit,
	CrRecordingSettingMovie_260M_422_10bit,
};

// Recording Frame Rate Setting(Movie)
enum CrRecordingFrameRateSettingMovie : CrInt8u
{
	CrRecordingFrameRateSettingMovie_120p = 0x01,
	CrRecordingFrameRateSettingMovie_100p,
	CrRecordingFrameRateSettingMovie_60p,
	CrRecordingFrameRateSettingMovie_50p,
	CrRecordingFrameRateSettingMovie_30p,
	CrRecordingFrameRateSettingMovie_25p,
	CrRecordingFrameRateSettingMovie_24p,
	CrRecordingFrameRateSettingMovie_23_98p,
	CrRecordingFrameRateSettingMovie_29_97p,
	CrRecordingFrameRateSettingMovie_59_94p,
};

// Compression File Format (Still)
enum CrCompressionFileFormat : CrInt8u
{
	CrCompressionFileFormat_JPEG = 0x01,
	CrCompressionFileFormat_HEIF_422,
	CrCompressionFileFormat_HEIF_420,
};

// Zoom Operation Enable Status
enum CrZoomOperationEnableStatus : CrInt8u
{
	CrZoomOperationEnableStatus_Default = 0x00,
	CrZoomOperationEnableStatus_Disable = 0x00,
	CrZoomOperationEnableStatus_Enable,
};

// Zoom Setting
enum CrZoomSettingType : CrInt8u
{
	CrZoomSetting_OpticalZoomOnly = 0x01,
	CrZoomSetting_SmartZoomOnly,
	CrZoomSetting_On_ClearImageZoom,
	CrZoomSetting_On_DigitalZoom,
};

// Zoom Type Status
enum CrZoomTypeStatus : CrInt8u
{
	CrZoomTypeStatus_OpticalZoom = 0x01,
	CrZoomTypeStatus_SmartZoom,
	CrZoomTypeStatus_ClearImageZoom,
	CrZoomTypeStatus_DigitalZoom,
};

// Zoom Operation
enum CrZoomOperation : CrInt8
{
	CrZoomOperation_Wide = -1,
	CrZoomOperation_Stop = 0,
	CrZoomOperation_Tele = 1,
};

// Remocon Zoom Speed Type
enum CrRemoconZoomSpeedType : CrInt8u
{
	CrRemoconZoomSpeedType_Invalid = 0x00,
	CrRemoconZoomSpeedType_Variable,
	CrRemoconZoomSpeedType_Fixed,
};

// RAW File Type
enum CrRAWFileCompressionType : CrInt16u
{
	CrRAWFile_Uncompression = 0x0000,
	CrRAWFile_Compression,
	CrRAWFile_LossLess,
	CrRAWFile_LossLessS,
	CrRAWFile_LossLessM,
	CrRAWFile_LossLessL,
};

enum CrContentsTransferStatus : CrInt16u
{
	CrContentsTransfer_OFF = 0x0000,
	CrContentsTransfer_ON,
};

enum CrCancelContentsTransferEnableStatus : CrInt16u
{
	CrCancelContentsTransfer_Disable = 0x0000,
	CrCancelContentsTransfer_Enable,
};

// APS-C or Full Switching Setting
enum CrAPS_C_or_Full_SwitchingSetting : CrInt8u
{
	CrAPS_C_or_Full_SwitchingSetting_Full = 0x01,
	CrAPS_C_or_Full_SwitchingSetting_APS_C,
};

// APS-C or Full Switching Enable Status
enum CrAPS_C_or_Full_SwitchingEnableStatus : CrInt8u
{
	CrAPS_C_or_Full_Switching_Disable = 0x00,
	CrAPS_C_or_Full_Switching_Enable,
};

// Camera-Setting Save Operation Enable Status
enum CrCameraSettingSaveOperation : CrInt8u
{
	CrCameraSettingSaveOperation_Disable,
	CrCameraSettingSaveOperation_Enable,
};

// Camera-Setting Read Operation Enable Status
enum CrCameraSettingReadOperation : CrInt8u
{
	CrCameraSettingReadOperation_Disable,
	CrCameraSettingReadOperation_Enable,
};

// Camera-Setting Save/Read State
enum CrCameraSettingSaveReadState : CrInt8u
{
	CrCameraSettingSaveReadState_Idle,
	CrCameraSettingSaveReadState_Reading,
};

enum CrDownloadSettingFileType : CrInt32u
{
	CrDownloadSettingFileType_Setup = 0x00000000,
	CrDownloadSettingFileType_Reserve =0x00000002,
	CrDownloadSettingFileType_None = 0xFFFFFFFF,
};

enum CrUploadSettingFileType : CrInt32u
{
	CrUploadSettingFileType_Setup = 0x00001000,
	CrUploadSettingFileType_Reserve = 0x00001002,
};

// Playback Media
enum CrPlaybackMedia : CrInt8u
{
	CrPlaybackMedia_Slot1 = 0x01,
	CrPlaybackMedia_Slot2,
};

// Touch Operation
enum CrTouchOperation : CrInt8u
{
	CrTouchOperation_Off = 0x01,
	CrTouchOperation_On,
	CrTouchOperation_PlaybackOnly,
};

// Camera Setting Reset Enable Status
enum CrCameraSettingsResetEnableStatus : CrInt8u
{
	CrCameraSettingsReset_Disable = 0x00,
	CrCameraSettingsReset_Enable,
};

// Auto Power OFF Temperature
enum CrAutoPowerOffTemperature : CrInt8u
{
	CrAutoPowerOffTemperature_Standard = 0x01,
	CrAutoPowerOffTemperature_High,
};

// Body Key Lock
enum CrBodyKeyLock : CrInt8u
{
	CrBodyKey_Unlock = 0x01,
	CrBodyKey_Lock,
};

// Select Finder/Monitor
enum CrSelectFinder : CrInt8u
{
	CrSelectFinder_Auto = 0x01,
	CrSelectFinder_ViewFinder_M,
	CrSelectFinder_Monitor_M,
};

// Disp Mode
enum CrDispMode : CrInt8u
{
	CrDispMode_GraphicDisplay = 0x01,
	CrDispMode_DisplayAllInfo,
	CrDispMode_NoDispInfo,
	CrDispMode_Histogram,
	CrDispMode_Level,
	CrDispMode_ForViewFinder,
	CrDispMode_MonitorOff,
};

// Disp Mode Bit Num
enum CrDispModeBitNum : CrInt32u
{
	CrDispModeBitNum_GraphicDisplay = 0x00000001,
	CrDispModeBitNum_DisplayAllInfo = 0x00000002,
	CrDispModeBitNum_Histogram = 0x00000004,
	CrDispModeBitNum_Level = 0x00000008,
	CrDispModeBitNum_NoDispInfo = 0x00000010,
	CrDispModeBitNum_NoDispInfoExposureOn = 0x00000020,
	CrDispModeBitNum_NoDispInfoExposureTimeOut = 0x00000040,
	CrDispModeBitNum_ForViewFinder = 0x00000080,
	CrDispModeBitNum_MonitorOff = 0x00000100,
};

// Gain Base Sensitivity
enum CrGainBaseSensitivity : CrInt8u
{
	CrGainBaseSensitivity_High = 0x01,
	CrGainBaseSensitivity_Low,
};

// Gain Base ISO Sensitivity
enum CrGainBaseIsoSensitivity : CrInt8u
{
	CrGainBaseIsoSensitivity_High = 0x01,
	CrGainBaseIsoSensitivity_Low,
};

// BaseLook Value
// type: CrDataType_UInt16
// value: bit bit 8-15 mode, bit 0-7 index
// ex: 0x0003 = index3 (Preset)
// ex: 0x0108 = index8 (User)
enum CrBaseLookValueSetter : CrInt16u
{
	CrBaseLookValue_Preset = 0x00,
	CrBaseLookValue_User = 0x01,
};

// Monitor LUT Setting (All Line)
enum CrMonitorLUTSetting : CrInt8u
{
	CrMonitorLUT_OFF = 0x01,
	CrMonitorLUT_ON,
};

// GetDisplayStringList of Type 
enum CrDisplayStringType : CrInt32u
{
	CrDisplayStringType_AllList = 0x00000000,
	CrDisplayStringType_BaseLook_AELevelOffset_ExposureValue = 0x00000001,
	CrDisplayStringType_BaseLook_Input_Display = 0x00000002,
	CrDisplayStringType_BaseLook_Name_Display = 0x00000003,
	CrDisplayStringType_BaseLook_Output_Display = 0x00000004,
	CrDisplayStringType_SceneFile_Name_Display = 0x00000005,
	CrDisplayStringType_ShootingMode_Cinema_ColorGamut_Display = 0x00000006,
	CrDisplayStringType_ShootingMode_TargetDisplay_Display = 0x00000007,
	CrDisplayStringType_Camera_Gain_BaseISO_Display = 0x00000008,
	CrDisplayStringType_Video_EIGain_Display = 0x00000009,
	CrDisplayStringType_Button_Assign_Display = 0x0000000A,
	CrDisplayStringType_Button_Assign_ShortDisplay = 0x0000000B,
};

// Image ID (Numerical Value) Setting
enum CrImageIDNumSetting : CrInt8u
{
	CrImageIDNumSetting_Off = 0x01,
	CrImageIDNumSetting_On,
};

// Iris Mode Setting
enum CrIrisModeSetting : CrInt8u
{
	CrIrisMode_Automatic = 0x01,
	CrIrisMode_Manual,
};

// Shutter Mode Setting
enum CrShutterModeSetting : CrInt8u
{
	CrShutterMode_Automatic = 0x01,
	CrShutterMode_Manual,
};

// Exporsure Ctrl Type
enum CrExposureCtrlType : CrInt8u
{
	CrExposureCtrlType_PASMMode = 0x01,
	CrExposureCtrlType_FlexibleExposureMode,
};

// Gain Control Setting
enum CrGainControlSetting : CrInt8u
{
	CrGainControl_Automatic = 0x01,
	CrGainControl_Manual,
};

// Focal Distance Unit Setting
enum CrFocalDistanceUnitSetting : CrInt8u
{
	CrFocalDistanceUnitSetting_Meter= 0x01,
	CrFocalDistanceUnitSetting_Feet,
};

// Shutter Mode Status
enum CrShutterModeStatus : CrInt8u
{
	CrShutterModeStatus_Off = 0x01,
	CrShutterModeStatus_Speed,
	CrShutterModeStatus_Angle,
	CrShutterModeStatus_ECS,
	CrShutterModeStatus_Auto,
};

// Shutter Slow
enum CrShutterSlow : CrInt8u
{
	CrShutterSlow_Off = 0x01,
	CrShutterSlow_On,
};

// Recording Frame Rate Proxy Setting(Movie)
enum CrRecordingFrameRateProxySettingMovie : CrInt8u
{
	CrRecordingFrameRateProxySettingMovie_50p = 0x04,
	CrRecordingFrameRateProxySettingMovie_25p = 0x06,
	CrRecordingFrameRateProxySettingMovie_24p,
	CrRecordingFrameRateProxySettingMovie_23_98p,
	CrRecordingFrameRateProxySettingMovie_29_97p,
	CrRecordingFrameRateProxySettingMovie_59_94p,
};

// Zoom Distance Unit Setting
enum CrZoomDistanceUnitSetting : CrInt8u
{
	CrZoomDistanceUnitSetting_mm = 0x01,
	CrZoomDistanceUnitSetting_percent,
};

// Battery Remain Display Unit
enum CrBatteryRemainDisplayUnit : CrInt8u
{
	CrBatteryRemainDisplayUnit_minute = 0x01,
	CrBatteryRemainDisplayUnit_percent,
	CrBatteryRemainDisplayUnit_voltage,
};

// Power Source
enum CrPowerSource : CrInt8u
{
	CrPowerSource_DC = 0x01,
	CrPowerSource_Battery,
};

// ND Filter Mode
enum CrNDFilterMode : CrInt8u
{
	CrNDFilterMode_Auto = 0x01,
	CrNDFilterMode_Preset,
	CrNDFilterMode_PresetClear,
	CrNDFilterMode_Variable,
	CrNDFilterMode_VariableClear,
};

// Media SLOT1/2 Player
enum CrMediaPlayer : CrInt8u
{
	CrMediaPlayer_None = 0x00,
	CrMediaPlayer_Player,
	CrMediaPlayer_Recorder,
	CrMediaPlayer_Player_Recorder,
};

// Movie Playing State
enum CrMoviePlayingState : CrInt8u
{
	CrMoviePlayingState_NotPlaying = 0x00,
	CrMoviePlayingState_Playing,
};

// Movie Shooting Mode Color Gamut
enum CrMovieShootingModeColorGamut : CrInt8u
{
	CrMovieShootingModeColorGamut_S_Gamut3_Cine = 0x01,
	CrMovieShootingModeColorGamut_S_Gamut3,
};

// Depth of Field Adjustment Mode
enum CrDepthOfFieldAdjustmentMode : CrInt8u
{
	CrDepthOfFieldAdjustmentMode_OFF = 0x01,
	CrDepthOfFieldAdjustmentMode_ON,
};

// Focus TouchSpot Status
enum CrFocusTouchSpotStatus : CrInt8u
{
	CrFocusTouchSpotStatus_Stopped = 0x01,
	CrFocusTouchSpotStatus_Running,
};

// Focus Tracking Status
enum CrFocusTrackingStatus : CrInt8u
{
	CrFocusTrackingStatus_OFF = 0x01,
	CrFocusTrackingStatus_Focusing,
	CrFocusTrackingStatus_Tracking,
};

// Depth of Field Adjustment Interlocking Mode State
enum CrDepthOfFieldAdjustmentInterlockingMode : CrInt8u
{
	CrDepthOfFieldAdjustmentInterlockingMode_NDInterlockingMode = 0x01,
	CrDepthOfFieldAdjustmentInterlockingMode_GainInterlockingMode,
};

// Recorder Control Main Setting,Recorder Control Proxy Setting
enum CrRecorderControlSetting : CrInt8u
{
	CrRecorderControlSetting_RecDisable = 0x00,
	CrRecorderControlSetting_RecEnable,
};

// Recorder Start Main,Recorder Start Proxy
enum CrRecorderStart : CrInt8u
{
	CrRecorderStart_RecStartDisable = 0x00,
	CrRecorderStart_RecStartEnable,
};

// Recorder Main Status,Recorder Proxy Status,Recorder Ext Raw Status
enum CrRecorderStatus : CrInt8u
{
	CrRecorderStatus_Idle = 0x00,
	CrRecorderStatus_Ready,
	CrRecorderStatus_PreparingToRecord,
	CrRecorderStatus_Standby,
	CrRecorderStatus_Recording,
	CrRecorderStatus_Stopping,
};

// Recorder Save Destination
enum CrRecorderSaveDestination : CrInt16u
{
	CrRecorderSaveDestination_External = 0x0001,
	CrRecorderSaveDestination_Internal = 0x0010,
	CrRecorderSaveDestination_ExternalAndInternal = 0x0011,
};

// Focus Operation
enum CrFocusOperation : CrInt8
{
	CrFocusOperation_Wide = -1,
	CrFocusOperation_Stop = 0,
	CrFocusOperation_Tele = 1,
};

// Movie Shooting Mode Target Display
enum CrMovieShootingModeTargetDisplay : CrInt8u
{
	CrMovieShootingModeTargetDisplay_BT709 = 0x01,
	CrMovieShootingModeTargetDisplay_BT2020,
};

// Movie Shooting Mode
enum CrMovieShootingMode : CrInt16u
{
	CrMovieShootingMode_CineEI = 0x0301,
	CrMovieShootingMode_Custom = 0x0401,
};

// Shutter ECS Setting
enum CrShutterECSSetting : CrInt8u
{
	CrShutterECSSetting_OFF = 0x01,
	CrShutterECSSetting_ON,
};

// Focus Mode Setting
enum CrFocusModeSetting : CrInt8u
{
    CrFocusModeSetting_Automatic     = 0x01,
    CrFocusModeSetting_Manual,
};

// Function of Remote Touch Operation
enum CrFunctionOfRemoteTouchOperation : CrInt8u
{
	CrFunctionOfRemoteTouchOperation_Tracking_AF = 0x01,
	CrFunctionOfRemoteTouchOperation_Spot_AF,
	CrFunctionOfRemoteTouchOperation_AFAreaSelect,
};

// Remote Touch Operation Enable Status
enum CrRemoteTouchOperationEnableStatus : CrInt8u
{
	CrRemoteTouchOperation_Disable = 0x00,
	CrRemoteTouchOperation_Enable,
};

// Cancel Remote Touch Operation Enable Status
enum CrCancelRemoteTouchOperationEnableStatus : CrInt8u
{
	CrCancelRemoteTouchOperation_Disable = 0x00,
	CrCancelRemoteTouchOperation_Enable,
};

// Lens Information Enable Status
enum CrLensInformationEnableStatus : CrInt8u
{
	CrLensInformation_Disable = 0x00,
	CrLensInformation_Enable,
};

// White Balance Mode Setting
enum CrWhiteBalanceModeSetting : CrInt8u
{
    CrWhiteBalanceModeSetting_Automatic     = 0x01,
    CrWhiteBalanceModeSetting_Manual,
};

// Shutter Setting
enum CrShutterSetting : CrInt8u
{
    CrShutterSetting_OFF        = 0x01,
    CrShutterSetting_ON,
};

// Shutter Mode
enum CrShutterMode : CrInt8u
{
    CrShutterMode_Speed         = 0x01,
    CrShutterMode_Angle,
};

// ND Filter
enum CrNDFilter : CrInt8u
{
    CrNDFilter_OFF          = 0x01,
    CrNDFilter_ON,
};

// ND Filter Mode Setting
enum CrNDFilterModeSetting : CrInt8u
{
    CrNDFilterModeSetting_Automatic     = 0x01,
    CrNDFilterModeSetting_Manual,
};

// Gain Unit Setting
enum CrGainUnitSetting : CrInt8u
{
    CrGainUnitSetting_dB        = 0x01,
    CrGainUnitSetting_ISO,
};

// AWB
enum CrAWB : CrInt16u
{
    CrAWB_Up    = 0x0001,
    CrAWB_Down,
};

// Current SceneFile Edited
enum CrCurrentSceneFileEdited : CrInt8u
{
    CrCurrentSceneFileEdited_Unedited = 0x01,
    CrCurrentSceneFileEdited_Edited,
};

// Movie Button
enum CrMovieXButton : CrInt16u
{
    CrMovieXButton_Up    = 0x0001,
    CrMovieXButton_Down,
};

// Movie Rec Button(Toggle) Enable Status
enum CrMovieRecButtonToggleEnableStatus : CrInt8u
{
    CrMovieRecButtonToggle_Disable   = 0x00,
    CrMovieRecButtonToggle_Enable,
};

// Face Eye Detection AF
enum CrFaceEyeDetectionAF : CrInt8u
{
    CrFaceEyeDetectionAF_Off                = 0x01,
    CrFaceEyeDetectionAF_FaceEyeOnlyAF,
    CrFaceEyeDetectionAF_FaceEyePriorityAF,
};

// AF Assist
enum CrAFAssist : CrInt8u
{
    CrAFAssist_Off = 0x01,
    CrAFAssist_On,
};

// ND PRESET or VARIABLE Switching Setting
enum CrNDPresetOrVariableSwitchingSetting : CrInt16u
{
    CrNDPresetOrVariableSwitchingSetting_Preset   = 0x0001,
    CrNDPresetOrVariableSwitchingSetting_Variable,
};

// Lens Information of Type 
enum CrLensInformationType : CrInt32u
{
	CrLensInformationType_Undefined = 0x00000000,
	CrLensInformationType_Feet ,
	CrLensInformationType_Meter,
};

// Assignable/LensAssignable Button Setting
enum CrAssignableButton : CrInt16u
{
	CrAssignableButton_Up = 0x0001,
	CrAssignableButton_Down,
};

//  Assignable/LensAssignable Button Indicator
enum CrAssignableButtonIndicator : CrInt8u
{
	CrAssignableButtonIndicator_Off = 0x1,
	CrAssignableButtonIndicator_On,
};

// Focus Bracket Shooting Status
enum CrFocusBracketShootingStatus : CrInt8u
{
	CrFocusBracket_NotShooting = 0x00,
	CrFocusBracket_Shooting,
};

class SCRSDK_API CrDeviceProperty
{
public:
	CrDeviceProperty();
	~CrDeviceProperty();

	CrDeviceProperty(const CrDeviceProperty& ref);

	CrDeviceProperty& operator =(const CrDeviceProperty& ref);

	// Do not use. Will be removed in the next release.
	void Alloc(const CrInt32u size, const CrInt32u getSetSize, const CrInt16u getStrSize);

	bool IsGetEnableCurrentValue();

	bool IsSetEnableCurrentValue();

	void SetCode(CrInt32u code);

	CrInt32u GetCode();

	void SetValueType(CrDataType type);
	CrDataType GetValueType();

	// Do not use. Will be removed in the next release.
	void SetPropertyEnableFlag(CrPropertyEnableFlag flag);


	CrPropertyEnableFlag GetPropertyEnableFlag();

	// Do not use. Will be removed in the next release.
	void SetPropertyVariableFlag(CrPropertyVariableFlag flag);

	CrPropertyVariableFlag GetPropertyVariableFlag();

	void SetCurrentValue(CrInt64u value);
	CrInt64u GetCurrentValue();

	void SetCurrentStr(CrInt16u* str);
	CrInt16u* GetCurrentStr();

	// Do not use. Will be removed in the next release.
	void SetValueSize(CrInt32u size);

	CrInt32u GetValueSize();

	// Do not use. Will be removed in the next release.
	void SetValues(CrInt8u* value);

	CrInt8u* GetValues();

	// Do not use. Will be removed in the next release.
	void SetSetValueSize(CrInt32u size);

	CrInt32u GetSetValueSize();

	// Do not use. Will be removed in the next release.
	void SetSetValues(CrInt8u* value);

	CrInt8u* GetSetValues();

private:
	CrInt32u code;
	CrDataType valueType;
	CrPropertyEnableFlag enableFlag;
	CrPropertyVariableFlag variableFlag;
	CrInt64u currentValue;
	CrInt16u* currentStr;
	CrInt32u valuesSize;
	CrInt8u* values;
	CrInt32u getSetValuesSize;
	CrInt8u* getSetValues;
};

class SCRSDK_API CrLiveViewProperty
{
public:
	CrLiveViewProperty();
	~CrLiveViewProperty();
	CrLiveViewProperty(const CrLiveViewProperty& ref);
	CrLiveViewProperty& operator =(const CrLiveViewProperty& ref);

	// Do not use. Will be removed in the next release.
	void Alloc(const CrInt32u size);

	bool IsGetEnableCurrentValue();

	// Do not use. Will be removed in the next release.
	void SetCode(CrInt32u code);

	CrInt32u GetCode();

	// Do not use. Will be removed in the next release.
	void SetPropertyEnableFlag(CrPropertyEnableFlag flag);

	CrPropertyEnableFlag GetPropertyEnableFlag();

	// Do not use. Will be removed in the next release.
	void SetFrameInfoType(CrFrameInfoType type);

	CrFrameInfoType GetFrameInfoType();

	// Do not use. Will be removed in the next release.
	void SetValueSize(CrInt32u size);

	CrInt32u GetValueSize();

	// Do not use. Will be removed in the next release.
	void SetValue(CrInt8u* value);

	CrInt8u* GetValue();

private:
        CrInt32u code;
		CrPropertyEnableFlag enableFlag;
        CrFrameInfoType valueType;
		CrInt32u valueSize;
		CrInt8u* value;
};

class SCRSDK_API CrMtpFolderInfo
{
public:
	CrMtpFolderInfo();
	~CrMtpFolderInfo();
	CrMtpFolderInfo(const CrMtpFolderInfo& ref);
	CrMtpFolderInfo& operator =(const CrMtpFolderInfo& ref);

private:
	// Do not use. Will be removed in the next release.
	void Alloc(const CrInt32u size); 

public:
	CrFolderHandle handle;
	CrInt32u folderNameSize;
	CrChar*  folderName;
};


class SCRSDK_API CrMtpContentsInfo
{
public:
	CrMtpContentsInfo();
	~CrMtpContentsInfo();
	CrMtpContentsInfo(const CrMtpContentsInfo& ref);
	CrMtpContentsInfo& operator =(const CrMtpContentsInfo& ref);

private:
	// Do not use. Will be removed in the next release.
	void Alloc(const CrInt32u size); 

public:
	CrContentHandle handle;
	CrFolderHandle parentFolderHandle;
	CrInt64u contentSize;
	CrChar dateChar[16];
	CrInt32u width;
	CrInt32u height;
	CrInt32u fileNameSize;
	CrChar* fileName;
};

#pragma pack(1)
class CrFocusFrameInfo
{
public:
	CrFocusFrameInfo()
		: type(CrFocusFrameType_Unknown)
		, state(CrFocusFrameState_Unknown)
		, priority(0)
		, xNumerator(0)
		, xDenominator(0)
		, yNumerator(0)
		, yDenominator(0)
		, width(0)
		, height(0)
	{}
	~CrFocusFrameInfo()
	{}

public:
    CrFocusFrameType type;
    CrFocusFrameState state;
    CrInt8u priority;
    CrInt32u xNumerator;
    CrInt32u xDenominator;
    CrInt32u yNumerator;
    CrInt32u yDenominator;
    CrInt32u width;
    CrInt32u height;
};
#pragma pack()

class CrMagPosInfo
{
public:
	CrMagPosInfo()
		: xNumerator(0)
		, xDenominator(0)
		, yNumerator(0)
		, yDenominator(0)
		, width(0)
		, height(0)
	{}
	~CrMagPosInfo()
	{}

public:
	CrInt32u xNumerator;
	CrInt32u xDenominator;
	CrInt32u yNumerator;
	CrInt32u yDenominator;
    CrInt32u width;
    CrInt32u height;
};

class SCRSDK_API CrDisplayStringListInfo
{
public:
	CrDisplayStringListInfo();
	~CrDisplayStringListInfo();
	CrDisplayStringListInfo(const 	CrDisplayStringListInfo& ref);
	CrDisplayStringListInfo& operator =(const 	CrDisplayStringListInfo& ref);

private:
	void Alloc(const CrInt32u size);

public:
	CrDataType dataType;
	CrDisplayStringType listType;
	CrInt64u value;
	CrInt32u displayStringSize;
	CrInt8u* displayString;
};

#pragma pack(1)
class SCRSDK_API CrMediaProfileInfo
{
public:
	CrMediaProfileInfo();
	~CrMediaProfileInfo();
	CrMediaProfileInfo(const CrMediaProfileInfo& ref);
	CrMediaProfileInfo& operator =(const CrMediaProfileInfo& ref);

public:
	CrInt8u* contentName;
	CrInt8u* contentUrl;
	CrInt8u* contentType;
	CrInt8u* contentFrameRate;
	CrInt8u* contentAspectRatio;
	CrInt8u* contentChannel;
	CrInt8u* contentVideoType;
	CrInt8u* contentAudioType;
	CrInt8u* proxyUrl;
	CrInt8u* proxyType;
	CrInt8u* proxyFrameRate;
	CrInt8u* proxyAspectRatio;
	CrInt8u* proxyChannel;
	CrInt8u* proxyVideoType;
	CrInt8u* proxyAudioType;
	CrInt8u* thumbnailUrl;
};
#pragma pack()

class SCRSDK_API CrLensInformation
{
public:
	CrLensInformation();
	~CrLensInformation();
	CrLensInformation(const  CrLensInformation& ref);
	CrLensInformation& operator =(const 	CrLensInformation& ref);

public:
	CrLensInformationType type;
	CrInt16u dataVersion;
	CrInt32u normalizedValue;
	CrInt32u focusPosition;
};


}

#pragma warning (pop)

#endif //CRDEVICEPROPERTY_H
