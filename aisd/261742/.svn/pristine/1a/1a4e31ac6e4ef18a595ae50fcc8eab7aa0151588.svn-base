hold off

SWAP = 4:10;
COMP = 4:10;


%######################SWAPS###########################
i = 1;
names = [ "select", "randselect"];
for algname = names
    for N = 100:100:10000
        name = algname + "_for_" + N;
        T = readtable(name);
        COMP(i,N/100) = mean(T.Var1);
        SWAP(i,N/100) = mean(T.Var2);
        
    end
    
    
    p = plot(100:100:10000,SWAP(i,:),'-o');
    hold on
    i=i+1;
end

legend(names)
ylabel('Number of swaps')
xlabel('N')
hold off
saveas(p,"graph/avg_swaps_all_k.png")

COMP=[];
SWAP=[];
names = [ "select", "randselect"];
for N = 100:100:10000
        i = 1;

    for algname = names
        name = algname + "_for_" + N;
        T = readtable(name);
        COMP(i,:) = T.Var1;
        SWAP(i,:) = T.Var2;
        p = plot(1:1:10,SWAP(i,:),'-o');
        hold on
        i=i+1;
    end 
        legend(names)
        ylabel('Number of swaps')
        xlabel('index of element selected [1/N]')
        hold off
        saveas(p,"graph/swaps_for_" + N + ".png")
     
end

%######################COMPS###########################
COMP=[];
SWAP=[];
i = 1;
names = [ "select", "randselect"];
for algname = names
    for N = 100:100:10000
        name = algname + "_for_" + N;
        T = readtable(name);
        COMP(i,N/100) = mean(T.Var1);
        SWAP(i,N/100) = mean(T.Var2);
        
    end
    
    
    p = plot(100:100:10000,COMP(i,:),'-o');
    hold on
    i=i+1;
end

legend(names)
ylabel('Number of comps')
xlabel('N')
hold off
saveas(p,"graph/avg_comps_all_k.png")

COMP=[];
SWAP=[];
names = [ "select", "randselect"];
for N = 100:100:10000
        i = 1;
    for algname = names
        name = algname + "_for_" + N;
        T = readtable(name);
        COMP(i,:) = T.Var1;
        SWAP(i,:) = T.Var2;
        p = plot(1:1:10,COMP(i,:),'-o');
        hold on
        i=i+1;
    end 
        legend(names)
        ylabel('Number of comps')
        xlabel('index of element selected [1/N]')
        hold off
        saveas(p,"graph/comps_for_" + N + ".png")
     
end

%#######################different_mts#####################
COMP=[];
SWAP=[];
i = 1;
algname = "select";
legendnames=["3","5","7","9"];
mts = [3,5,7,9];
for k=mts
    for N = 100:100:10000
        name = algname + k + "_for_" + N;
        T = readtable(name);
        COMP(i,N/100) = mean(T.Var1);
        SWAP(i,N/100) = mean(T.Var2);
        
    end
    
    
    p = plot(100:100:10000,COMP(i,:),'-o');
    hold on
    i=i+1;
end

legend(legendnames)
ylabel('Number of comps')
xlabel('N')
hold off
saveas(p,"graph/avg_comps_group_size.png")
COMP=[];
SWAP=[];
i = 1;
algname = "select";
mts = [3,5,7,9];
for k =mts
    for N = 100:100:10000
        name = algname + k + "_for_" + N;
        T = readtable(name);
        COMP(i,N/100) = mean(T.Var1);
        SWAP(i,N/100) = mean(T.Var2);
        
    end
    
    
    p = plot(100:100:10000,SWAP(i,:),'-o');
    hold on
    i=i+1;
end
%NAPRAW LEGENDE

legend(legendnames)
ylabel('Number of swaps')
xlabel('N')
hold off
saveas(p,"graph/avg_swaps_group_size.png")

%##########################BINARY_SEARCH###################
COMP=[];
SWAP=[];
i = 1;
algname = "binary";

for N = 1000:1000:100000
    name = algname + "_for_" + N;
    T = readtable(name);
    COMP(i,N/1000) = mean(T.Var1);
    SWAP(i,N/1000) = mean(T.Var2);
    
end


p = plot(1000:1000:100000,COMP(i,:),'-o');
hold on
i=i+1;


ylabel('Number of comps')
xlabel('N')
hold off
saveas(p,"graph/binary_search_comps.png")

