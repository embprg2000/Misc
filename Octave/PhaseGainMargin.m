# This little script calculates the gain and phase margin.

pkg load control % Octave only

s=zpk(0,[],1)

g=1.3*(s+2)/(s^3+s^2+6*s+1)

[mag,pha,w] = bode(g);

subplot(2,1,1)
dBmag = 20 * log10(mag);
semilogx(w,dBmag)
grid on

subplot(2,1,2)
semilogx(w,pha)
grid on

# Find index closed to -180 degrees.
idx = find(abs(pha + 180) == min(abs(pha + 180)));

GainMargin = dBmag(idx)

# Find index closed to 0 gain
idx = find(abs(dBmag) == min(abs(dBmag)));

PhaseMargin = 180 + pha(idx)
