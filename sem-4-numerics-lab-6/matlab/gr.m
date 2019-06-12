function gr()
  x = [1 2 3 4];
  l01 = [8 16 64 128];
  l001 = [16 64 128 256];
  l0001 = [64 256 512 1024];
  %l00001 = [16 64 128 256];
  
  hold off;
  plot(x, l01, '-o');
  hold on;
  grid on;
  plot(x, l001, '-o');
  plot(x, l0001, '-o');
  %plot(x, l00001, '-o');
  legend('0.1', '0.01', '0.001');
end