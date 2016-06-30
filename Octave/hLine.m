% Draw horizontal line at y-position
%
% Evert H Rozendaal  emb.prog2000@gmail.com

function hLine(y)
hold on
x=get(gca,'xlim');
for i=1:length(y)
  plot(x,[y(i) y(i)],'r')
end
hold off