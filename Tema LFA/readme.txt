Grameni Stere-Alexandru
333CC

Pentru implementarea temei, am citit toate fisierele date ca argument in linia de intrare. In urma rularii makefile-ului se va crea executabilul a.out.
Am folosit doua stari, una pentru numele de camp si una pentru valori. Cea pentru numele de camp este INITIAL. Pentru numele de canp am cautat toate sirurile care nu contin tab, newline si /. Daca programul gaseste un nume de camp urmat de /, creste un contor folosit pentru a tine numarul de /-uri intalnite, iar daca programul gaseste un nume de camp fara / si contorul este doi,inseamna ca avem un nume valid si incepem cautarea valorilor. Daca pana sa gasim un nume de camp valid gasim un separator(tab sau newline), anulam ce am gasit pana atunci.
Pentru valori, am cautat orice sir care nu contine tab, newline sau spatiu. Nu am cautat spatiu pentru ca daca gasesc spatiu in starea pentru valori, schimb spatiul cu | si caut in continuare restul valorii. Daca am gasit o valoare si am intalnit un separator, reincep starea INITIAL pentru cautarea numelor de camp.
