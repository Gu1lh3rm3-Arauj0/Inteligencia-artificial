T = int(input())

while(T > 0):
    T -= 1
    prob_Mutacao = 1.0
    prob_crossover = 0
    
    N = int(input())

    Y, P = map(float, input().split())

    A = input()
    B = input()
    C = input()


    prob_crossover = prob_Mutacao - P
    
    for i in range(int(Y)):
        if A[i] == C[i] or B[i] == C[i]:
            prob_Mutacao *= P
            
        else:
            prob_Mutacao *= 1 + (1.0 - P)**2

    for i in range(int(Y), int(N)):
        if A[i] == C[i] or B[i] == C[i]:
            prob_Mutacao *= P
            
        else:
            prob_Mutacao *= 1 + (1.0 - P)**2
            
        prob_total = prob_crossover - prob_Mutacao
    print("{:.7f}".format(prob_total))