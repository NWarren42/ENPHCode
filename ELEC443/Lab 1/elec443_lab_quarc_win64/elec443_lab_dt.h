/*
 * elec443_lab_dt.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "elec443_lab".
 *
 * Model version              : 7.5
 * Simulink Coder version : 9.7 (R2022a) 13-Nov-2021
 * C source code generated on : Fri Oct 24 10:40:36 2025
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(int32_T),
  sizeof(t_card),
  sizeof(t_task),
  sizeof(char_T),
  sizeof(uchar_T),
  sizeof(time_T)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "physical_connection",
  "t_card",
  "t_task",
  "char_T",
  "uchar_T",
  "time_T"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&elec443_lab_B.EncoderCalibrationradcount), 0, 0, 7 }
  ,

  { (char_T *)(&elec443_lab_DW.HILInitialize_AIMinimums[0]), 0, 0, 12 },

  { (char_T *)(&elec443_lab_DW.HILInitialize_Card), 15, 0, 1 },

  { (char_T *)(&elec443_lab_DW.HILReadEncoderTimebase_Task), 16, 0, 1 },

  { (char_T *)(&elec443_lab_DW.HILWriteAnalog1_PWORK), 11, 0, 3 },

  { (char_T *)(&elec443_lab_DW.HILInitialize_ClockModes), 6, 0, 6 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  6U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&elec443_lab_P.K_CABLE), 0, 0, 6 },

  { (char_T *)(&elec443_lab_P.HILWriteAnalog1_channels), 7, 0, 1 },

  { (char_T *)(&elec443_lab_P.HILInitialize_OOTerminate), 0, 0, 25 },

  { (char_T *)(&elec443_lab_P.HILInitialize_CKChannels), 6, 0, 5 },

  { (char_T *)(&elec443_lab_P.HILInitialize_AIChannels[0]), 7, 0, 9 },

  { (char_T *)(&elec443_lab_P.HILInitialize_Active), 8, 0, 37 },

  { (char_T *)(&elec443_lab_P.HILReadEncoderTimebase_Overflow), 3, 0, 1 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  7U,
  rtPTransitions
};

/* [EOF] elec443_lab_dt.h */
