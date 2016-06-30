% Draw vertical line at x-position
%
% Evert H Rozendaal  emb.prog2000@gmail.com

function vLine(x)
hold on
y=get(gca,'ylim');
for i=1:length(x)
  plot([x(i) x(i)],y,'r')
end
hold off
end