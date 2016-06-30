% Draw vertical line at x-position
%
% Evert H Rozendaal - emb.prog2000@gmail.com

function vLine(x)
g=ishold(gca);
hold on

y=get(gca,'ylim');
for i=1:length(x)
  plot([x(i) x(i)],y,'r')
end

if g == 0
  hold off
end

end
