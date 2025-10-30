lowW = 7.593;
highW = 25.05;

plot(wl(1:2500, 1), wl(1:2500, 2))

yline(lowW + 0.63*(highW - lowW), Color="#FF0000", LineWidth=1)
yline(lowW + 0.90*(highW - lowW), Color="#00ff00", LineWidth=1)
yline(lowW + 0.95*(highW - lowW), Color="#ff00ff", LineWidth=1)
yline(lowW + 0.98*(highW - lowW), Color="#00ffff", LineWidth=1)

legend(["SRV-02 Angular Frequency", "68%", "90%", "95%", "98%"], Location="southeast")

xlim([2.5, 2.7])
ylim([5, 27])

title("Single Control Cycle SRV02")