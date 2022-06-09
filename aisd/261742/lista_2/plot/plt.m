hold off

SWAP = 4:10;
COMP = 4:10;
i = 1;
names = [ "quick","dpquick", "hybrid", "merge", "heapsort"];
for algname = names
    for N = 100:100:1000
        name = algname + "_for_" + N + ".csv";
        T = readtable(name);
        COMP(i,N/100) = mean(T.Var1);
        SWAP(i,N/100) = mean(T.Var2);
    end
    
    
    p = plot(100:100:1000,SWAP(i,:),'-o');
    hold on
    i=i+1;
end
legend(names)
ylabel('Number of swaps')
xlabel('N')
hold off
saveas(p,"graph/swap_sorts.png")

i = 1;
for algname = names
    for N = 100:100:1000
        name = algname + "_for_" + N + ".csv";
        T = readtable(name);
        COMP(i,N/100) = mean(T.Var1);
        SWAP(i,N/100) = mean(T.Var2);
    end
    
    
    p = plot(100:100:1000,COMP(i,:),'-o');
    hold on
    i=i+1;
end
legend(names)
ylabel('Number of comps')
xlabel('N')
hold off
saveas(p,"graph/comp_sorts.png")

%#########################################

