function diffs()
  File = fopen("../outputs/diffs.txt", "r");
  
  Data = fscanf(File, "%f");
  Anchors = Data(1);
  H = 1 / (Anchors + 1);
  Repeats = Data(2);
  
  x = zeros(Anchors, 1);
  for xn = 1:Anchors
      x(xn) = H * xn;
  end
  
  y = zeros(Anchors, Repeats);
  for yn = 1:Repeats
      y(1 + (yn - 1) * Anchors:yn * Anchors) = Data(3 + (yn - 1) * Anchors:2 + yn * Anchors);
  end
  
  figure(1);
  hold off;
  plot(x, y(1:Anchors), '-o', 'DisplayName', int2str(Anchors + 1));
  grid on;
  hold on;
  for pn = 2:Repeats
      plot(x, y(1 + (pn - 1) * Anchors:pn * Anchors), '-o', 'DisplayName', int2str((Anchors + 1) * pn));
  end
  legend('show');
  
  fclose("all");
end