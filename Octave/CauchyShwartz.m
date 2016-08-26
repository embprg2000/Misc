% Cauchy Shwartz

fs = 1e3;
f1 = 10; a1 = 1; ph1 = 1;
f2 = 10; a2 = 3; ph2 = 2.2;

t  = 0:1/fs:10;
s1 = a1 * sin(2*pi*t*f1+ph1);
s2 = a2 * sin(2*pi*t*f2+ph2);

cs = dot(s1,s2) / (norm(s1) * norm(s2));
co = cos(ph2-ph1);

disp(['cosine via Cauchy Shwartz:' num2str(cs) '   Real Cosine:' num2str(co)])

