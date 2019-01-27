edges = csvread('../edges_2_10.csv');

for i = 1:length(edges)
    pair = edges(i,:);
    if pair(2) < pair(1)
        pair = [pair(2) pair(1)];
    end
    for j = i+1:length(edges)
        other = edges(j,:);
        if other(2) < other(1)
            other = [other(2) other(1)];
        end
        if pair(1) == other(1) && pair(2) == other(2)
            disp([num2str(pair(1)) ' ' num2str(pair(2)) ' ' num2str(other)])
        end
    end
end

clear edges