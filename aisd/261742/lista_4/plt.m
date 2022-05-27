hold off

SWAP = 3:10;
MAX_SWAP = 3:10;
AVG_SWAP = 3:10;
COMP = 3:10;
MAX_COMP = 3:10;
AVG_COMP = 3:10;



data_type  = [ "rand", "asc" ];
for data = data_type

%######################DATA###########################
i = 1;
names = [ "splay", "bst" , "rbt"];

for N = 10000:10000:100000
    for algname = names
        name = "data_h/" + algname + "_h_for_" + N + "_"+data+".csv";
        H = readtable(name);
        limit=2*N-1;
        k = plot(1:1:limit,H.x_1);
        ylabel('TreeHeight')
        xlabel('N')
        hold off
        saveas(k,"graph/height/" + algname + "_for_" + N + "_" + data +".png");
    end
end

for algname = names
    for N = 10000:10000:100000
        name = "data/" + algname + "_for_" + N + "_"+data+".csv";
        T = readtable(name);
        SWAP(i,N/10000) = mean(T.Var1);
        MAX_SWAP(i,N/10000) = mean(T.Var2);
        AVG_SWAP(i,N/10000) = mean(T.Var3);
        COMP(i,N/10000) = mean(T.Var4);
        MAX_COMP(i,N/10000) = mean(T.Var5);
        AVG_COMP(i,N/10000) = mean(T.Var6);
    end
    
    
    p = plot(10000:10000:100000,SWAP(i,:),'-o');
    hold on
    i=i+1;
end


%######################SWAPS###########################

legend(names)
ylabel('Number of swaps')
xlabel('N')
hold off
saveas(p,"graph/swaps_" + data +  ".png")

%######################MAX_SWAPS###########################

i = 1;
for algname = names
    p = plot(10000:10000:100000,MAX_SWAP(i,:),'-o');
    hold on
    i=i+1;
end

legend(names)
ylabel('Maximum swaps per operation')
xlabel('N')
hold off
saveas(p,"graph/max_swaps_" + data +  ".png")


%######################AVG_SWAPS###########################

i = 1;
for algname = names
    p = plot(10000:10000:100000,AVG_SWAP(i,:),'-o');
    hold on
    i=i+1;
end

legend(names)
ylabel('Avarage comparison per operation')
xlabel('N')
hold off
saveas(p,"graph/avg_swaps_" + data +  ".png")



%######################COMPS###########################
i = 1;
for algname = names
    p = plot(10000:10000:100000,COMP(i,:),'-o');
    hold on
    i=i+1;
end

legend(names)
ylabel('Number of comps')
xlabel('N')
hold off
saveas(p,"graph/comps_" + data +  ".png")

%######################MAX_COMPS###########################
i = 1;
for algname = names
    p = plot(10000:10000:100000,MAX_COMP(i,:),'-o');
    hold on
    i=i+1;
end

legend(names)
ylabel('Maximum comparison per operation')
xlabel('N')
hold off
saveas(p,"graph/max_comps_" + data +  ".png")


%######################AVG_COMPS###########################

i = 1;
for algname = names
    p = plot(10000:10000:100000,AVG_COMP(i,:),'-o');
    hold on
    i=i+1;
end

legend(names)
ylabel('Avarage comparison per operation')
xlabel('N')
hold off
saveas(p,"graph/avg_comps_" + data +  ".png")

end