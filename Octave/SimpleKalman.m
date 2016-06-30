% Very simple little script to show the basics of a
% kalman filter.
%
% Evert H. Rozendaal
% emb.prg2000@gmail.com

clear all

a = 0.75;
r = 200;

% Observed values
z = [1100 586 444 405 454 69 302 226 -36 -2];

% Initialize arrays
x  = zeros(size(z));  % For comparison only.
xh = zeros(size(z));  % x-hat (ouput)
g  = zeros(size(z));  % Gain
p  = zeros(size(z));  % Prediction

x(1)  = 1000;
xh(1) = z(1);
p(1)  = 1;

% Run loop
for k=2:length(z)
  x(k)  = x(k-1) * a;
  
  % Prediction
  xh(k) = xh(k-1) * a;
  p(k)  = a * p(k-1) * a;
 
  % Update
  g(k)  = p(k) / (p(k) + r);
  xh(k) = xh(k) + g(k) * (z(k) - xh(k));
  p(k)  = (1 - g(k)) * p(k); 
end

g(1) = g(2);
  
t = 1:length(x);
plot(t,x,t,xh,t,z)
legend('x','xh','z')
grid on
