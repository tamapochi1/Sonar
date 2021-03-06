%MATLAB Code from Sensor Array Analyzer App

%Generated by MATLAB 9.2 and Phased Array System Toolbox 3.4

%Generated on 16-Sep-2017 17:28:24


% Create a uniform hexagonal array
Nside = 4;
delta = 0.01;
rows = [1:Nside Nside-1:-1:1];
Radius = delta * (Nside - 1);
pos = zeros(3,1);
count = 0;
for idx = 1:length(rows)
    y = -Radius/2 - (rows(idx)-1)*delta*0.5 : delta : ...
        Radius/2 + (rows(idx)-1)*delta*0.5;
    pos(2, count+1:count+length(y)) = y;
    pos(3, count+1:count+length(y)) = sqrt(3)/2*Radius - ...
        (idx-1)*delta*sind(60);
    count = count+length(y);
end
h = phased.ConformalArray('ElementPosition', pos, ...
    'ElementNormal', zeros(2,37));
%Calculate Taper
wind = ones(1,37);
h.Taper = wind;



% % Create a uniform rectangular array
% h = phased.URA;
% h.Size = [6 6];
% h.ElementSpacing = [0.01 0.01];
% h.Lattice = 'Rectangular';
% h.ArrayNormal = 'x';
% %Calculate Row Taper
% rwind = ones(1,6);
% rwind = repmat(rwind,6,1);
% %Calculate Column Taper
% cwind = ones(1,6);
% cwind = repmat(cwind.',1,6);
% %Calculate taper
% wind = rwind.*cwind;
% h.Taper = wind;



%Create Cardioid Microphone Element
el = phased.CustomMicrophoneElement;
el.PolarPatternFrequencies = [39000 41000];
el.PolarPattern = g([...
    abs(el.PolarPatternAngles);...
    abs(el.PolarPatternAngles)]);
h.Element = el;

% pattern(el,40000,-180:180,0,'CoordinateSystem','polar');

%Assign steering angles, frequencies and propagation speed
SA = [-15;15];
%Assign number of phase shift quantization bits
PSB = 16;
F = 40000;
PS = 340;
%Create figure, panel, and axes
fig = figure;
panel = uipanel('Parent',fig);
hAxes = axes('Parent',panel,'Color','none');
%Calculate Steering Weights
w = zeros(getNumElements(h), length(F));
SV = phased.SteeringVector('SensorArray',h, 'PropagationSpeed', PS, ...
    'NumPhaseShifterBits', PSB(1));
%Find the weights
for idx = 1:length(F)
    w(:, idx) = step(SV, F(idx), SA(:, idx));
end
%Plot 3d graph
fmt = 'polar';
pattern(h, F(1), 'PropagationSpeed', PS, 'Type','directivity', 'CoordinateSystem', fmt,'weights', w(:,1));
zoom(2);
%Adjust the view angles
hSmallAxes = axes('Parent', panel, 'Position', [0 0.6 0.3 0.3]);
hlink = linkprop([hAxes hSmallAxes],'View');
setappdata(fig, 'Lin1', hlink);
viewArray(h,'AxesHandle', hSmallAxes)
view(hAxes,[120 20]);
title = get(hAxes, 'title');
title_str = get(title, 'String');
%Modify the title
[Fval, ~, Fletter] = engunits(40000);
steeringString = ['steered at ' num2str(SA(1)) 'Az, ' num2str(SA(2)) 'El'];
title_str = [title_str newline num2str(Fval) ' ' Fletter 'Hz ' steeringString];
set(title, 'String', title_str);
