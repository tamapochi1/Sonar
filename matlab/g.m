function ydb = g(y) %#codegen
%MAG2DB  Magnitude to dB conversion.
% Ç»Ç¢Ç≈Ç∑ÅB

y = 3.8889e-05*(y.^2) - 0.0141*y + 1;
y(y<0.001) = 0.001;
ydb = 20*log10(y);
