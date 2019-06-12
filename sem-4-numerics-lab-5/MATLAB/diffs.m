function diffs()
  File = fopen("../outputs/diff.txt", "r");
  
  Data = fscanf(File, "%f");
  Anchors = Data(1);
  H = 2 / (Anchors + 1);
  Repeats = Data(2);
  
  x = zeros(Anchors, 1);
  for xn = 1:Anchors
      x(xn) = H * xn;
  end
  
  figure(1);
  hold off;
  doff = 3;
  y = Data(doff:doff - 1 + Anchors); 
  doff = doff + Anchors;
  plot(x, y, '-o', 'DisplayName', int2str(Anchors));
  legend('show');
  grid on;
  hold on;  
  for repn = 2:Repeats
      y = Data(doff:doff - 1 + Anchors); 
      doff = doff + Anchors;
      plot(x, y, '-o', 'DisplayName', int2str(Anchors * 2 ^ repn));
  end
  
  fclose("all");
end