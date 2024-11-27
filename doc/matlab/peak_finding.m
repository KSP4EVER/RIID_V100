% Example Radioactive Spectrum Data
% Replace this with your actual spectrum data
x = linspace(0, 4096, 4096); % Energy levels (e.g., channel numbers)
%y = exp(-0.001*x) .* sin(0.05*x) + rand(1, 1000) * 0.1; % Simulated spectrum with noise
y = th232';
% Parameters for peak detection
minPeakHeight = 80;   % Minimum height of peaks
minPeakDistance = 10;  % Minimum distance between peaks (in indices)
smoothingWindow = 5;   % Size of the moving average window

% Smoothing the data
y_smoothed = movmean(y, smoothingWindow);

% Calculate the first derivative
dy = diff(y_smoothed); % First derivative
dy = [dy, 0]; % Pad with zero to match the size of y_smoothed

% Calculate the second derivative
d2y = diff(dy); % Second derivative
d2y = [d2y, 0]; % Pad with zero to match the size of y_smoothed

% Find peaks using derivative criteria
peaks = [];
locations = [];

for i = 2:length(y_smoothed)-1
    % Peak detection conditions:
    % 1. First derivative changes sign from positive to negative
    % 2. Second derivative is negative (concave down)
    % 3. Value is above the minimum peak height
    if dy(i-1) > 0 && dy(i) < 0 && d2y(i) < 0 && y_smoothed(i) > minPeakHeight
        peaks = [peaks, y(i)];         % Store peak height
        locations = [locations, x(i)];          % Store corresponding location
    end
end

% Enforce minimum distance between peaks
if minPeakDistance > 1
    validPeaks = true(1, length(peaks)); % Keep track of valid peaks
    for i = 1:length(peaks)
        for j = i+1:length(peaks)
            if abs(locations(i) - locations(j)) < minPeakDistance
                if peaks(i) < peaks(j)
                    validPeaks(i) = false; % Remove smaller peak
                else
                    validPeaks(j) = false; % Remove smaller peak
                end
            end
        end
    end
    peaks = peaks(validPeaks);
    locations = locations(validPeaks);
end

% Plot the original spectrum and the smoothed spectrum
figure;
semilogy(x, y, 'b', 'DisplayName', 'Original Spectrum');
hold on;
semilogy(x, y_smoothed, 'g', 'LineWidth', 1.5, 'DisplayName', 'Smoothed Spectrum');
semilogy(locations, peaks, 'r^', 'MarkerFaceColor', 'r', 'DisplayName', 'Detected Peaks');
title('Radioactive Spectrum with Detected Peaks');
xlabel('Energy (e.g., keV or Channel)');
ylabel('Counts');
legend();
grid on;

% Display peak information
disp('Peaks found:');
disp(table(locations', peaks', 'VariableNames', {'Location', 'Height'}));