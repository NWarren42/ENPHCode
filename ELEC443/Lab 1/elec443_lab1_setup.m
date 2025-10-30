%% elec443_lab1_setup.m
%
% Sets the necessary parameters to run the SRV02 Experiment #1: Modeling
% laboratory using the "elec443_lab1.slx" Simulink diagram.
% 
% This work is a derivative of "setup_srv02_exp01_mdl.m"
% Copyright (C) 2007 Quanser Consulting Inc.
% Modified for ELEC 443 by Shane Forbrigger, 2020
clearvars;
%
%% SRV02 Configuration
% External Gear Configuration: set to 'HIGH' or 'LOW'
EXT_GEAR_CONFIG = 'LOW';
% Encoder Type: set to 'E' or 'EHR'
ENCODER_TYPE = 'E';
% Is SRV02 equipped with Tachometer? (i.e. option T): set to 'YES' or 'NO'
TACH_OPTION = 'NO';
% Type of Load: set to 'NONE', 'DISC', or 'BAR'
LOAD_TYPE = 'DISC';
% Cable Gain used: set to 1, 3, or 5
K_CABLE = 1;
% Universal Power Module (UPM) Type: set to 'UPM_1503' or 'UPM_2405'
UPM_TYPE = 'UPM_2405';
% Digital-to-Analog Maximum Voltage (V)
VMAX_DAC = 10;
%
%% SRV02 System Parameters
% Set Model Variables Accordingly to the USER-DEFINED SRV02 System Configuration
% Also Calculate the SRV02 Model Parameters and 
% Write them to the MATLAB Workspace (to be used in Simulink diagrams)
[~,~,~,~,~,~,~,~,~,~,~, K_ENC, VMAX_UPM, ~] = config_srv02( EXT_GEAR_CONFIG, ENCODER_TYPE, TACH_OPTION, UPM_TYPE, LOAD_TYPE );
%
%% Filter Parameters
% Encoder high-pass filter used to compute velocity
% Cutoff frequency (rad/s)
wcf_e = 2 * pi * 25.0;
% Damping ratio
zetaf_e = 0.9;
%
%% SRV02 Model Parameters
% Default model parameters
K = 8.35;
tau = 0.03478;
disp( 'Calculated SRV02 model parameters: ' )
disp( [ '   K = ' num2str( K, 3 ) ' rad/s/V' ] )
disp( [ '   tau = ' num2str( tau, 3 ) ' s' ] )