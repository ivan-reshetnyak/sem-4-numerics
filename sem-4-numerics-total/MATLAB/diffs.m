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
  y = Data(3:2 + Anchors); 
  plot(x, y, '-o', 'DisplayName', 'RK 2');
  grid on;
  hold on;
  y = Data(3 + Anchors:2 + 2 * Anchors); 
  plot(x, y, '-o', 'DisplayName', 'Adams 1-2');
  y = Data(3 + 2 * Anchors:2 + 3 * Anchors);
  plot(x, y, '-o', 'DisplayName', 'Adams 2-2');
  legend('show');
  ylim([-0.1 4]);
  
  fclose("all");
end