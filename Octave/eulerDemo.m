function eulerDemo()

octaveAnimate('animation');  # Init animation

for angle = linspace(0,6, 6)
  pa = exp(1j*angle);
  na = exp(-1j*angle);
  p1 = [0+0j, pa];
  p2 = [0+0j, na];

  add = [pa, pa+na];
  sub = [pa, pa-na];
  
  cir = exp(1j*(0:0.01:2*pi));

  plot(real(p1),imag(p1),real(p2),imag(p2), ...
        real(add),imag(add),real(sub),imag(sub),real(cir),imag(cir),'k-')
  title(['exp(+j' num2str(angle) ')    exp(-j' num2str(angle) ')'])
  xlabel('Real part')
  ylabel('Imaginary part')
  legend('+O','-O','add','sub')
  grid on
  axis([-2 2 -2 2], "square");

  octaveAnimate();  # Append graph to PDF file
endfor

octaveAnimate(1.0); # Convert PDF to gif.

end

