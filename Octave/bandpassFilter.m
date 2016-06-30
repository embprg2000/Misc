% Creating a bandpass filter
%
% Evert H Rozendaal - emb.prog2000@gmail.com

pkg load signal  % Octave only

% Bandspass filter
fs = 200e+07;     % Sample frequency
fc = 40.0e+07;    % Center frequency
bw = 10.0e+07;    % Bandwidth

bLog = 0;

% Auto adjust scaling
em = floor(log10(fs+bw)/3);
emStr = {'Hz','kHz','MHz','GHz'}
emStr = emStr{em+1};
em    = 10^(em*3);

% Calculate lower and upper cutoff
wl = 2/fs*(fc-bw/2);  % lower band
wh = 2/fs*(fc+bw/2);  % upper band
wn = [wl,wh];

% 6th order Butterworth filter
[B,A] = butter(3,wn);

bins  = 1024;   % Number of bins
[h,w] = freqz(B,A,bins);
freq  = ((0:bins-1)/bins)*(fs/2);

freq = freq / em;

if bLog == 1
  semilogx(freq,20*log10(abs(h)));
  yLine = 20*log10(1/sqrt(2))
else
  plot(freq,abs(h));
  yLine = 1/sqrt(2);
end
grid
title('Bandpass Filter Transfer Fn')
xlabel(['Frequency (' emStr ')']);
ylabel('Gain')

hLine(yLine);
vLine(wn*(freq(2)-freq(1))*bins);


