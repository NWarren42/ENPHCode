/*
 * elec443_lab.c
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

#include "elec443_lab.h"
#include "rtwtypes.h"
#include <math.h>
#include "elec443_lab_private.h"
#include "rt_nonfinite.h"
#include "elec443_lab_dt.h"

/* Block signals (default storage) */
B_elec443_lab_T elec443_lab_B;

/* Continuous states */
X_elec443_lab_T elec443_lab_X;

/* Block states (default storage) */
DW_elec443_lab_T elec443_lab_DW;

/* Real-time model */
static RT_MODEL_elec443_lab_T elec443_lab_M_;
RT_MODEL_elec443_lab_T *const elec443_lab_M = &elec443_lab_M_;

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 3;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  elec443_lab_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void elec443_lab_output(void)
{
  real_T rtb_HILReadEncoderTimebase;
  real_T u0;
  if (rtmIsMajorTimeStep(elec443_lab_M)) {
    /* set solver stop time */
    if (!(elec443_lab_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&elec443_lab_M->solverInfo,
                            ((elec443_lab_M->Timing.clockTickH0 + 1) *
        elec443_lab_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&elec443_lab_M->solverInfo,
                            ((elec443_lab_M->Timing.clockTick0 + 1) *
        elec443_lab_M->Timing.stepSize0 + elec443_lab_M->Timing.clockTickH0 *
        elec443_lab_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(elec443_lab_M)) {
    elec443_lab_M->Timing.t[0] = rtsiGetT(&elec443_lab_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(elec443_lab_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S5>/HIL Read Encoder Timebase' */

    /* S-Function Block: elec443_lab/SRV02 Experiment/SRV02-ET/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(elec443_lab_DW.HILReadEncoderTimebase_Task,
        1, &elec443_lab_DW.HILReadEncoderTimebase_Buffer);
      if (result < 0) {
        rtb_HILReadEncoderTimebase = 0;
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(elec443_lab_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase =
          elec443_lab_DW.HILReadEncoderTimebase_Buffer;
      }
    }

    /* Gain: '<S5>/Encoder Calibration  (rad//count)' */
    elec443_lab_B.EncoderCalibrationradcount = -elec443_lab_P.K_ENC *
      rtb_HILReadEncoderTimebase;

    /* Gain: '<S2>/Slider Gain' incorporates:
     *  Constant: '<Root>/Constant'
     */
    elec443_lab_B.SliderGain = elec443_lab_P.OffsetV_gain *
      elec443_lab_P.Constant_Value;
  }

  /* TransferFcn: '<S5>/Encoder High-Pass Filter' */
  elec443_lab_B.EncoderHighPassFilter = 0.0;
  elec443_lab_B.EncoderHighPassFilter += elec443_lab_P.EncoderHighPassFilter_C[0]
    * elec443_lab_X.EncoderHighPassFilter_CSTATE[0];
  elec443_lab_B.EncoderHighPassFilter += elec443_lab_P.EncoderHighPassFilter_C[1]
    * elec443_lab_X.EncoderHighPassFilter_CSTATE[1];

  /* SignalGenerator: '<Root>/Signal Generator' */
  rtb_HILReadEncoderTimebase = elec443_lab_P.SignalGenerator_Frequency *
    elec443_lab_M->Timing.t[0];
  if (rtb_HILReadEncoderTimebase - floor(rtb_HILReadEncoderTimebase) >= 0.5) {
    rtb_HILReadEncoderTimebase = elec443_lab_P.SignalGenerator_Amplitude;
  } else {
    rtb_HILReadEncoderTimebase = -elec443_lab_P.SignalGenerator_Amplitude;
  }

  /* End of SignalGenerator: '<Root>/Signal Generator' */

  /* Sum: '<Root>/Vi' incorporates:
   *  Gain: '<S1>/Slider Gain'
   */
  rtb_HILReadEncoderTimebase = elec443_lab_P.AmplitudeV_gain *
    rtb_HILReadEncoderTimebase + elec443_lab_B.SliderGain;

  /* Gain: '<S6>/Direction Convention: (Right-Hand) system' */
  u0 = elec443_lab_P.DirectionConventionRightHandsys *
    rtb_HILReadEncoderTimebase;

  /* Saturate: '<S6>/UPM  Saturation (V)' */
  if (u0 > elec443_lab_P.VMAX_UPM) {
    u0 = elec443_lab_P.VMAX_UPM;
  } else if (u0 < -elec443_lab_P.VMAX_UPM) {
    u0 = -elec443_lab_P.VMAX_UPM;
  }

  /* End of Saturate: '<S6>/UPM  Saturation (V)' */

  /* Gain: '<S6>/Inverse Amplifier  Gain (V//V)' */
  u0 *= 1.0 / elec443_lab_P.K_CABLE;

  /* Saturate: '<S6>/DACB Saturation (V)' */
  if (u0 > elec443_lab_P.VMAX_DAC) {
    /* Saturate: '<S6>/DACB Saturation (V)' */
    elec443_lab_B.DACBSaturationV = elec443_lab_P.VMAX_DAC;
  } else if (u0 < -elec443_lab_P.VMAX_DAC) {
    /* Saturate: '<S6>/DACB Saturation (V)' */
    elec443_lab_B.DACBSaturationV = -elec443_lab_P.VMAX_DAC;
  } else {
    /* Saturate: '<S6>/DACB Saturation (V)' */
    elec443_lab_B.DACBSaturationV = u0;
  }

  /* End of Saturate: '<S6>/DACB Saturation (V)' */
  if (rtmIsMajorTimeStep(elec443_lab_M)) {
    /* S-Function (hil_write_analog_block): '<S5>/HIL Write Analog1' */

    /* S-Function Block: elec443_lab/SRV02 Experiment/SRV02-ET/HIL Write Analog1 (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(elec443_lab_DW.HILInitialize_Card,
        &elec443_lab_P.HILWriteAnalog1_channels, 1,
        &elec443_lab_B.DACBSaturationV);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(elec443_lab_M, _rt_error_message);
      }
    }
  }

  /* Gain: '<S6>/Amplifier  Gain (V//V)' */
  elec443_lab_B.AmplifierGainVV = elec443_lab_P.K_CABLE *
    elec443_lab_B.DACBSaturationV;
  if (rtmIsMajorTimeStep(elec443_lab_M)) {
  }

  /* TransferFcn: '<S4>/Transfer Fcn' */
  elec443_lab_B.TransferFcn = 0.0;
  elec443_lab_B.TransferFcn += elec443_lab_P.TransferFcn_C *
    elec443_lab_X.TransferFcn_CSTATE;
  if (rtmIsMajorTimeStep(elec443_lab_M)) {
  }

  /* Gain: '<S7>/Inverse Amplifier  Gain (V//V)' */
  u0 = 1.0 / elec443_lab_P.K_CABLE * rtb_HILReadEncoderTimebase;

  /* Saturate: '<S7>/DACB Saturation (V)' */
  if (u0 > elec443_lab_P.VMAX_DAC) {
    u0 = elec443_lab_P.VMAX_DAC;
  } else if (u0 < -elec443_lab_P.VMAX_DAC) {
    u0 = -elec443_lab_P.VMAX_DAC;
  }

  /* End of Saturate: '<S7>/DACB Saturation (V)' */

  /* Gain: '<S7>/Amplifier  Gain (V//V)' */
  u0 *= elec443_lab_P.K_CABLE;

  /* Saturate: '<S7>/UPM  Saturation (V)' */
  if (u0 > elec443_lab_P.VMAX_UPM) {
    /* Saturate: '<S7>/UPM  Saturation (V)' */
    elec443_lab_B.UPMSaturationV = elec443_lab_P.VMAX_UPM;
  } else if (u0 < -elec443_lab_P.VMAX_UPM) {
    /* Saturate: '<S7>/UPM  Saturation (V)' */
    elec443_lab_B.UPMSaturationV = -elec443_lab_P.VMAX_UPM;
  } else {
    /* Saturate: '<S7>/UPM  Saturation (V)' */
    elec443_lab_B.UPMSaturationV = u0;
  }

  /* End of Saturate: '<S7>/UPM  Saturation (V)' */
}

/* Model update function */
void elec443_lab_update(void)
{
  if (rtmIsMajorTimeStep(elec443_lab_M)) {
    rt_ertODEUpdateContinuousStates(&elec443_lab_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++elec443_lab_M->Timing.clockTick0)) {
    ++elec443_lab_M->Timing.clockTickH0;
  }

  elec443_lab_M->Timing.t[0] = rtsiGetSolverStopTime(&elec443_lab_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++elec443_lab_M->Timing.clockTick1)) {
      ++elec443_lab_M->Timing.clockTickH1;
    }

    elec443_lab_M->Timing.t[1] = elec443_lab_M->Timing.clockTick1 *
      elec443_lab_M->Timing.stepSize1 + elec443_lab_M->Timing.clockTickH1 *
      elec443_lab_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void elec443_lab_derivatives(void)
{
  XDot_elec443_lab_T *_rtXdot;
  _rtXdot = ((XDot_elec443_lab_T *) elec443_lab_M->derivs);

  /* Derivatives for TransferFcn: '<S5>/Encoder High-Pass Filter' */
  _rtXdot->EncoderHighPassFilter_CSTATE[0] =
    elec443_lab_P.EncoderHighPassFilter_A[0] *
    elec443_lab_X.EncoderHighPassFilter_CSTATE[0];
  _rtXdot->EncoderHighPassFilter_CSTATE[0] +=
    elec443_lab_P.EncoderHighPassFilter_A[1] *
    elec443_lab_X.EncoderHighPassFilter_CSTATE[1];
  _rtXdot->EncoderHighPassFilter_CSTATE[1] =
    elec443_lab_X.EncoderHighPassFilter_CSTATE[0];
  _rtXdot->EncoderHighPassFilter_CSTATE[0] +=
    elec443_lab_B.EncoderCalibrationradcount;

  /* Derivatives for TransferFcn: '<S4>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = elec443_lab_P.TransferFcn_A *
    elec443_lab_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += elec443_lab_B.UPMSaturationV;
}

/* Model initialize function */
void elec443_lab_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<S5>/HIL Initialize' */

  /* S-Function Block: elec443_lab/SRV02 Experiment/SRV02-ET/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q2_usb", "0", &elec443_lab_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(elec443_lab_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(elec443_lab_DW.HILInitialize_Card,
      "d0=digital;d1=digital;led=auto;update_rate=normal;decimation=1", 63);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(elec443_lab_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(elec443_lab_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(elec443_lab_M, _rt_error_message);
      return;
    }

    if ((elec443_lab_P.HILInitialize_AIPStart && !is_switching) ||
        (elec443_lab_P.HILInitialize_AIPEnter && is_switching)) {
      elec443_lab_DW.HILInitialize_AIMinimums[0] =
        (elec443_lab_P.HILInitialize_AILow);
      elec443_lab_DW.HILInitialize_AIMinimums[1] =
        (elec443_lab_P.HILInitialize_AILow);
      elec443_lab_DW.HILInitialize_AIMaximums[0] =
        elec443_lab_P.HILInitialize_AIHigh;
      elec443_lab_DW.HILInitialize_AIMaximums[1] =
        elec443_lab_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges(elec443_lab_DW.HILInitialize_Card,
        elec443_lab_P.HILInitialize_AIChannels, 2U,
        &elec443_lab_DW.HILInitialize_AIMinimums[0],
        &elec443_lab_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(elec443_lab_M, _rt_error_message);
        return;
      }
    }

    if ((elec443_lab_P.HILInitialize_AOPStart && !is_switching) ||
        (elec443_lab_P.HILInitialize_AOPEnter && is_switching)) {
      elec443_lab_DW.HILInitialize_AOMinimums[0] =
        (elec443_lab_P.HILInitialize_AOLow);
      elec443_lab_DW.HILInitialize_AOMinimums[1] =
        (elec443_lab_P.HILInitialize_AOLow);
      elec443_lab_DW.HILInitialize_AOMaximums[0] =
        elec443_lab_P.HILInitialize_AOHigh;
      elec443_lab_DW.HILInitialize_AOMaximums[1] =
        elec443_lab_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges(elec443_lab_DW.HILInitialize_Card,
        elec443_lab_P.HILInitialize_AOChannels, 2U,
        &elec443_lab_DW.HILInitialize_AOMinimums[0],
        &elec443_lab_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(elec443_lab_M, _rt_error_message);
        return;
      }
    }

    if ((elec443_lab_P.HILInitialize_AOStart && !is_switching) ||
        (elec443_lab_P.HILInitialize_AOEnter && is_switching)) {
      elec443_lab_DW.HILInitialize_AOVoltages[0] =
        elec443_lab_P.HILInitialize_AOInitial;
      elec443_lab_DW.HILInitialize_AOVoltages[1] =
        elec443_lab_P.HILInitialize_AOInitial;
      result = hil_write_analog(elec443_lab_DW.HILInitialize_Card,
        elec443_lab_P.HILInitialize_AOChannels, 2U,
        &elec443_lab_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(elec443_lab_M, _rt_error_message);
        return;
      }
    }

    if (elec443_lab_P.HILInitialize_AOReset) {
      elec443_lab_DW.HILInitialize_AOVoltages[0] =
        elec443_lab_P.HILInitialize_AOWatchdog;
      elec443_lab_DW.HILInitialize_AOVoltages[1] =
        elec443_lab_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (elec443_lab_DW.HILInitialize_Card,
         elec443_lab_P.HILInitialize_AOChannels, 2U,
         &elec443_lab_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(elec443_lab_M, _rt_error_message);
        return;
      }
    }

    if ((elec443_lab_P.HILInitialize_EIPStart && !is_switching) ||
        (elec443_lab_P.HILInitialize_EIPEnter && is_switching)) {
      elec443_lab_DW.HILInitialize_QuadratureModes[0] =
        elec443_lab_P.HILInitialize_EIQuadrature;
      elec443_lab_DW.HILInitialize_QuadratureModes[1] =
        elec443_lab_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode(elec443_lab_DW.HILInitialize_Card,
        elec443_lab_P.HILInitialize_EIChannels, 2U, (t_encoder_quadrature_mode *)
        &elec443_lab_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(elec443_lab_M, _rt_error_message);
        return;
      }
    }

    if ((elec443_lab_P.HILInitialize_EIStart && !is_switching) ||
        (elec443_lab_P.HILInitialize_EIEnter && is_switching)) {
      elec443_lab_DW.HILInitialize_InitialEICounts[0] =
        elec443_lab_P.HILInitialize_EIInitial;
      elec443_lab_DW.HILInitialize_InitialEICounts[1] =
        elec443_lab_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts(elec443_lab_DW.HILInitialize_Card,
        elec443_lab_P.HILInitialize_EIChannels, 2U,
        &elec443_lab_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(elec443_lab_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S5>/HIL Read Encoder Timebase' */

  /* S-Function Block: elec443_lab/SRV02 Experiment/SRV02-ET/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(elec443_lab_DW.HILInitialize_Card,
      elec443_lab_P.HILReadEncoderTimebase_SamplesI,
      &elec443_lab_P.HILReadEncoderTimebase_Channels, 1,
      &elec443_lab_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (elec443_lab_DW.HILReadEncoderTimebase_Task, (t_buffer_overflow_mode)
         (elec443_lab_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(elec443_lab_M, _rt_error_message);
    }
  }

  /* InitializeConditions for TransferFcn: '<S5>/Encoder High-Pass Filter' */
  elec443_lab_X.EncoderHighPassFilter_CSTATE[0] = 0.0;
  elec443_lab_X.EncoderHighPassFilter_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Transfer Fcn' */
  elec443_lab_X.TransferFcn_CSTATE = 0.0;
}

/* Model terminate function */
void elec443_lab_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<S5>/HIL Initialize' */

  /* S-Function Block: elec443_lab/SRV02 Experiment/SRV02-ET/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    hil_task_stop_all(elec443_lab_DW.HILInitialize_Card);
    hil_monitor_stop_all(elec443_lab_DW.HILInitialize_Card);
    is_switching = false;
    if ((elec443_lab_P.HILInitialize_AOTerminate && !is_switching) ||
        (elec443_lab_P.HILInitialize_AOExit && is_switching)) {
      elec443_lab_DW.HILInitialize_AOVoltages[0] =
        elec443_lab_P.HILInitialize_AOFinal;
      elec443_lab_DW.HILInitialize_AOVoltages[1] =
        elec443_lab_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 2U;
    } else {
      num_final_analog_outputs = 0;
    }

    if (num_final_analog_outputs > 0) {
      result = hil_write_analog(elec443_lab_DW.HILInitialize_Card,
        elec443_lab_P.HILInitialize_AOChannels, num_final_analog_outputs,
        &elec443_lab_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(elec443_lab_M, _rt_error_message);
      }
    }

    hil_task_delete_all(elec443_lab_DW.HILInitialize_Card);
    hil_monitor_delete_all(elec443_lab_DW.HILInitialize_Card);
    hil_close(elec443_lab_DW.HILInitialize_Card);
    elec443_lab_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  elec443_lab_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  elec443_lab_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  elec443_lab_initialize();
}

void MdlTerminate(void)
{
  elec443_lab_terminate();
}

/* Registration function */
RT_MODEL_elec443_lab_T *elec443_lab(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)elec443_lab_M, 0,
                sizeof(RT_MODEL_elec443_lab_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&elec443_lab_M->solverInfo,
                          &elec443_lab_M->Timing.simTimeStep);
    rtsiSetTPtr(&elec443_lab_M->solverInfo, &rtmGetTPtr(elec443_lab_M));
    rtsiSetStepSizePtr(&elec443_lab_M->solverInfo,
                       &elec443_lab_M->Timing.stepSize0);
    rtsiSetdXPtr(&elec443_lab_M->solverInfo, &elec443_lab_M->derivs);
    rtsiSetContStatesPtr(&elec443_lab_M->solverInfo, (real_T **)
                         &elec443_lab_M->contStates);
    rtsiSetNumContStatesPtr(&elec443_lab_M->solverInfo,
      &elec443_lab_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&elec443_lab_M->solverInfo,
      &elec443_lab_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&elec443_lab_M->solverInfo,
      &elec443_lab_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&elec443_lab_M->solverInfo,
      &elec443_lab_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&elec443_lab_M->solverInfo, (&rtmGetErrorStatus
      (elec443_lab_M)));
    rtsiSetRTModelPtr(&elec443_lab_M->solverInfo, elec443_lab_M);
  }

  rtsiSetSimTimeStep(&elec443_lab_M->solverInfo, MAJOR_TIME_STEP);
  elec443_lab_M->intgData.f[0] = elec443_lab_M->odeF[0];
  elec443_lab_M->contStates = ((real_T *) &elec443_lab_X);
  rtsiSetSolverData(&elec443_lab_M->solverInfo, (void *)&elec443_lab_M->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&elec443_lab_M->solverInfo, false);
  rtsiSetSolverName(&elec443_lab_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = elec443_lab_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "elec443_lab_M points to
       static memory which is guaranteed to be non-NULL" */
    elec443_lab_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    elec443_lab_M->Timing.sampleTimes = (&elec443_lab_M->
      Timing.sampleTimesArray[0]);
    elec443_lab_M->Timing.offsetTimes = (&elec443_lab_M->
      Timing.offsetTimesArray[0]);

    /* task periods */
    elec443_lab_M->Timing.sampleTimes[0] = (0.0);
    elec443_lab_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    elec443_lab_M->Timing.offsetTimes[0] = (0.0);
    elec443_lab_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(elec443_lab_M, &elec443_lab_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = elec443_lab_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    elec443_lab_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(elec443_lab_M, 20.0);
  elec443_lab_M->Timing.stepSize0 = 0.002;
  elec443_lab_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  elec443_lab_M->Sizes.checksums[0] = (2135810100U);
  elec443_lab_M->Sizes.checksums[1] = (2567009037U);
  elec443_lab_M->Sizes.checksums[2] = (2610759896U);
  elec443_lab_M->Sizes.checksums[3] = (2866428114U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    elec443_lab_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(elec443_lab_M->extModeInfo,
      &elec443_lab_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(elec443_lab_M->extModeInfo,
                        elec443_lab_M->Sizes.checksums);
    rteiSetTPtr(elec443_lab_M->extModeInfo, rtmGetTPtr(elec443_lab_M));
  }

  elec443_lab_M->solverInfoPtr = (&elec443_lab_M->solverInfo);
  elec443_lab_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&elec443_lab_M->solverInfo, 0.002);
  rtsiSetSolverMode(&elec443_lab_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  elec443_lab_M->blockIO = ((void *) &elec443_lab_B);
  (void) memset(((void *) &elec443_lab_B), 0,
                sizeof(B_elec443_lab_T));

  /* parameters */
  elec443_lab_M->defaultParam = ((real_T *)&elec443_lab_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &elec443_lab_X;
    elec443_lab_M->contStates = (x);
    (void) memset((void *)&elec443_lab_X, 0,
                  sizeof(X_elec443_lab_T));
  }

  /* states (dwork) */
  elec443_lab_M->dwork = ((void *) &elec443_lab_DW);
  (void) memset((void *)&elec443_lab_DW, 0,
                sizeof(DW_elec443_lab_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    elec443_lab_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 20;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  elec443_lab_M->Sizes.numContStates = (3);/* Number of continuous states */
  elec443_lab_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  elec443_lab_M->Sizes.numY = (0);     /* Number of model outputs */
  elec443_lab_M->Sizes.numU = (0);     /* Number of model inputs */
  elec443_lab_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  elec443_lab_M->Sizes.numSampTimes = (2);/* Number of sample times */
  elec443_lab_M->Sizes.numBlocks = (22);/* Number of blocks */
  elec443_lab_M->Sizes.numBlockIO = (7);/* Number of block outputs */
  elec443_lab_M->Sizes.numBlockPrms = (84);/* Sum of parameter "widths" */
  return elec443_lab_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
