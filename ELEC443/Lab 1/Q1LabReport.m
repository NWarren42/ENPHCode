subplot(2, 1, 1)
plot(Vm(1:5000, 1), Vm(1:5000, 2))

ylim([0, 4])

title("Input Voltage to SRV-02 Over Time")
ylabel("Voltage [V]")
xlabel("Time [s]")

legend("Input Voltage")

subplot(2, 1, 2)
plot(wl(1:5000, 1), wl(1:5000, 2), wl(1:5000, 1), wl(1:5000, 3))
ylim([-5, 30])

title("First Order System Output Compared to Actual SRV-02 Dynamics. K = 8.35, τ = 0.03478")
ylabel("Angular Frequency [rad/s]")
xlabel("Time [s]")

legend(["Measured Angular Velocity", "Control Signal Input"], Location="southeast")


tab = table(Vm(1:5000, 1), Vm(1:5000, 2), wl(1:5000, 3), wl(1:5000, 2));
tab.Properties.VariableNames= ["Time [s]", "Voltage [V]", "Set Frequency [rad/s]", "Measured Frequency [rad/s]"];

writetable(tab, "Q8_K835_tau3478_Arrays.csv")