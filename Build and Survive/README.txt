Grameni Stere-Alexandru
333CC

Playerul se misca daca tin apasat pe butonul din dreapta al mouse-ului 
si pe tastele w, a, s, d. El schimba armele din tastele 1, 2, 3.

Pentru implementare am creat clasa Bullet pentru gloante, clasa Enemy
pentru inamici, clasa Player pentru jucator, clasa Turn pentru turnuri si
Laborator5 este clasa in care am implementat starile si update-ul.
Initial, in Laborator 5 setez camera, playerul, turnurile si timpul.
In update actualizez pozitia jucatorului, setez timpul, afisez inamicii prin
metoda drawEnemy, fac turnurile sa traga, afisez gloantele si detectez coliziunile.
Am mai creat o metoda MinimapMesh pentru minimap.
In drawTowers afisez turnurile, in drawBullet afisez gloantele, in drawEnemy actualizez 
pozitia inamicilor si ii afisez. In towerShoot fac turnurile sa traga, in findEnemy caut
cel mai apropiat inamic pentru turnuri, in addEnemy adaug inamici dupa un interval de timp, 
in removeBulletDistance sterg gloantele dupa o anumita distanta parcursa, in elimGrenade 
omor inamicii care sunt pe raza unei grenade, in hitEnemys detectez coliziunile si in elimBullet 
si elimEnemies sterg gloantele si inamicii dupa coliziune.