function gr2()
  File = fopen("../outputs/out.txt", "r");
  
  y = fscanf(File, "%f");
  x = [1 2 3 4 5 6 7 8 9];
  
  hold off;
  plot(x, y, '-o');
  grid on;
  ylim([0 0.05]);
  
  fclose("all");
end