function stab()
  File = fopen("../outputs/stab.txt", "r");
  
  Data = fscanf(File, "%f");
  Anchors = Data(1);
  H = 1 / (Anchors + 1);
  
  x = zeros(Anchors, 1);
  for xn = 1:Anchors
      x(xn) = H * xn;
  end
  
  y = Data(2:1 + Anchors);
  
  figure(2);
  hold off;
  plot(x, y, '-o');
  grid on;
  
  fclose("all");
end