/* Rodar */
/* glpsol --model pli.mod --data e0806.dat --output pli.opt --wcpxlp pli.lp */

/* declaracoes de conjuntos e parametros */

param n, integer, >=1;  /* quantidade de cenas */
param m, integer, >= 1; /* quantidade de atores */

/* matriz T */
set ATORES := {1..m}; /* conjunto de indices de atores */
set CENAS := {1..n};  /* conjunto de indices de dias de gravacao */
set DIAS := {1..n}; /* conjunto de indices de dias */
param T{i in ATORES, j in CENAS};

/* custo diário de espera */
param c{i in ATORES};

/* numero de cenas nas quais cada ator participa */
param s{i in ATORES}:=sum{j in CENAS} T[i,j];

/* ===> variaveis: */
var dias_gravacao{i in ATORES, k in DIAS}, >= 0, binary;
var pre_periodo{i in ATORES, k in DIAS}, >= 0, binary;
var pos_periodo{i in ATORES, k in DIAS}, >= 0, binary;
var cenas_dias{j in CENAS, k in DIAS}, >= 0, binary;

var h{i in ATORES}, >=0, integer;

/* ===> funcao objetivo */
minimize custo:
	sum{i in ATORES} h[i]*c[i];

/* ===> restricoes */
s.t. uma_cena_por_dia{j in CENAS}: (sum{k in DIAS} cenas_dias[j, k]) = 1;
s.t. uma_cena_por_dia_2{k in DIAS}: (sum{j in CENAS} cenas_dias[j, k]) = 1;

s.t. marca_dias_gravacao{i in ATORES, k in DIAS}:
	dias_gravacao[i,k] = sum{j in CENAS} T[i, j] * cenas_dias[j, k];

################################################################################
# Periodo de pre-gravacao fica com zero, o resto deve ficar com 1              #
################################################################################
s.t. dias_gravacao_nao_eh_pre_periodo{i in ATORES, k in DIAS}:
	pre_periodo[i, k] >= dias_gravacao[i,k];

s.t. depois_que_gravou_nao_eh_pre_periodo{i in ATORES, k in {2..n}}:
	pre_periodo[i, k] >= pre_periodo[i, k-1];

################################################################################
# Periodo de pos-gravacao fica com zero, o resto deve ficar com 1							 #
################################################################################
s.t. dias_gravacao_nao_eh_pos_periodo{i in ATORES, k in DIAS}:
	pos_periodo[i, k] >= dias_gravacao[i,k];

s.t. ate_ultimo_dia_gravacao_nao_eh_pos_periodo {i in ATORES, k in {1..n-1}}:
	pos_periodo[i, k] >= pos_periodo[i, k+1];


s.t. hold_days{i in ATORES}:
	h[i] = n - sum{k in DIAS} (2 - pre_periodo[i, k] - pos_periodo[i, k]) - s[i];

/* resolve problema */
solve;

for { k in DIAS }{
	printf: "%d ", sum{j in CENAS } cenas_dias[j, k]*j >> "saida.txt";
}
printf: "\n" >> "saida.txt";

/* ===> imprime custo da solucao encontrada */
printf: "%d", custo >> "saida.txt";
printf: "\n" >> "saida.txt";

end;
