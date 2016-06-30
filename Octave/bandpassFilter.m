% Creating a bandpass filter
%
% Evert H Rozendaal  emb.prog2000@gmail.com

pkg load all

% Bandspass filter
fs = 200e+03;
fc = 40.0e+03;
bw = 10.0e+03;
wl = 2/fs*(fc-bw/2);  % lower band
wh = 2/fs*(fc+bw/2);  % upper band
wn = [wl,wh];

% 6th order Butterworth filter
[B,A] = butter(3,wn);

bins  = 1024;
[h,w] = freqz(B,A,bins);
freq  = ((0:bins-1)/bins)*(fs/2);

%semilogx(freq,20*log10(abs(h)));
plot(freq/1e3,abs(h));
grid
title('Bandpass Filter Transfer Fn')
xlabel('Frequency (kHz)');
ylabel('Gain')

hLine(1/sqrt(2));
vLine(wn*100);


