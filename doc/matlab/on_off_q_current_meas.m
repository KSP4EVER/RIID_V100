%current consumption vs input voltage @ 25°C
u = 7:0.1:10;
i = [15.62 15.65 15.7 15.73 15.77 15.78 15.82 15.86 15.88 15.92 15.97 16.01 16.04 16.06 16.10 16.14 16.17 16.21 16.24 16.28 16.34 16.37 16.42 16.45 16.52 16.55 16.57 16.62 16.65 16.68 16.75];

plot(u,i,'-k','LineWidth',2);
ylim([0 25]);
yticks([0 5 10 15 20 25]);
grid on;
grid minor;
xlabel("Bemeneti feszültség [V]");
ylabel("Felvett áram [uA]");
title("Felvett áram a bementi feszültség függvényében T = 25°C");

figure();

T = -5:5:60;
i = [15.5 23 21.7 20.35 19.7 18.7 18 17.2 16.6 17.6 20.5 22 20 19];

plot(T,i,T,movmean(i,10),'-k','LineWidth',2);
grid on;
grid minor;

ylim([0 30]);
yticks([0 5 10 15 20 25 30]);