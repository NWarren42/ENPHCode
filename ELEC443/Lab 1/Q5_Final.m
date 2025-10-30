% Import Q1 data from the csv file
filename = "Q1_K1_tau1_Arrays.csv";
dataTable = readtable(filename);

times                = dataTable.Time_s_;
voltages             = dataTable.Voltage_V_;
predictedFrequencies = dataTable.SetFrequency_rad_s_;
measuredFrequencies  = dataTable.MeasuredFrequency_rad_s_;

lowTime = 1250;
highTime = 1500;

% Measured frequency response graph
plot(times(lowTime:highTime), measuredFrequencies(lowTime:highTime))
ylim([5, 28])
xlim([2.5, 2.7])

lowW = 7.593;
highW = 25.05;

yline(lowW + 0.63*(highW - lowW), Color="#FF0000", LineWidth=1)
yline(lowW + 0.90*(highW - lowW), Color="#00ff00", LineWidth=1)
yline(lowW + 0.95*(highW - lowW), Color="#ff00ff", LineWidth=1)
yline(lowW + 0.98*(highW - lowW), Color="#00ffff", LineWidth=1)

% No Titles
% title("Measured Step Response of SRV02 Angular Velocity with Rise Time Thresholds. K = 1, τ = 0.1")
ylabel("Angular Frequency [rad/s]")
xlabel("Time [s]")

legend(["Measured System Response", "63%", "90%", "95%", "98%"], Location="southeast")