% Import Q1 data from the csv file
filename = "Q8_K835_tau3478_Arrays.csv";
dataTable = readtable(filename);

times                = dataTable.Time_s_;
voltages             = dataTable.Voltage_V_;
predictedFrequencies = dataTable.SetFrequency_rad_s_;
measuredFrequencies  = dataTable.MeasuredFrequency_rad_s_;

% Measured frequency response graph
plot(times, predictedFrequencies, times, measuredFrequencies)
ylim([-5, 35])

% No titles
% title("First Order Expected Output Compared to Actual SRV-02 Dynamics. K = 8.35, τ = 0.03478")

ylabel("Angular Frequency [rad/s]")
xlabel("Time [s]")

legend(["Predicted System Response", "Measured System Response"], Location="northeast")