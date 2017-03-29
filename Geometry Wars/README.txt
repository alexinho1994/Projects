Grameni Stere-Alexandru
333CC

	Nava utilizatorului are culoarea rosie si se misca pe tastele w, a, s, d. Ea va trage
	pe butonul stang al mouse-ului.Inamicii de culoare verde au o viata, iar cei de culoare 
	albastra 2 vieti.

	Pentru implementare am folosit laboratorul 3.

	Am creat o clasa pentru gloante, una  pentru inamici, si in clasa laboratorului am 
	implementat restul. Mereu cand creez un inamic sau un proiectil,ii pun intr-un vector
	si la fiecare Update le actualizez pozitia pe harta.  Dupa un anumit timp, apare un 
	inamic nou pe ecran, iar daca nava utilizator se loveste de un inamic, sau daca
	un inamic este lovit de un proiectil, ii introduc intr-un alt vector pentru a elimina
	inamicul de pe ecran. 


	Probleme aparute: pozitia in care mouse-ul are coordonatele 0,0 este in stanga sus
	si mi-a luat ceva pana am aflat asta.