hold off

SWAP = 4:10;
COMP = 4:10;
i = 1;
names = [ "queue"];
for algname = names
    for N = 100:100:1000
        name = algname + "_for_" + N + ".csv";
        T = readtable(name);
        COMP(i,N/100) = mean(T.Var1);
        SWAP(i,N/100) = mean(T.Var2);
    end
    
    
    p = plot(100:100:1000,SWAP(i,:),'-o');
    hold on
    p = plot(100:100:1000,COMP(i,:),'-o');

    i=i+1;
end
legend(["SWAPS", "COMPS"])
ylabel('Number of operations')
xlabel('N')
hold off
saveas(p,"graph/queue.png")
clear
i = 1;
for algname = ["lcs"]
    for N = 1000:1000:5000
        name = algname + "_for_" + N + ".csv";
        T = readtable(name);
        COMP(i,N/1000) = mean(T.Var1);
        SWAP(i,N/1000) = mean(T.Var2);
    end
    
    
    p = plot(1000:1000:5000,COMP(i,:),'-o');
    hold on
    p = plot(1000:1000:5000,SWAP(i,:),'-o');
    hold on
    i=i+1;
end
legend(["SWAPS", "COMPS"])
ylabel('Number of comps')
xlabel('N')
hold off
saveas(p,"graph/lcs.png")

%#########################################

