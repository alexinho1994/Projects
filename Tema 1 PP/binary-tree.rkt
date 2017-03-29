#lang racket

(require racket/include)
(include "binary-tree-test.rkt")

;; TASK pregatitor
(define empty-tree
  '())

(define init-node 
  (λ (value)
     (cons value (cons '() '())))
  )

(define make-node
  (λ (left right value)
    (cons value (cons left right)))
  )

(define is-leaf?                
  (λ (node)
    (if (null? node)
        #f
        (if (null? (car (cdr node)))
            (if (null? (cdr (cdr node)))
                #t
                #f)
            #f))))

(define get-value
  (λ (node) (car node))
  )

(define get-left
  (λ (node) (car (cdr node)))
  )

(define get-right
  (λ (node) (cdr (cdr node)))
  )

(define is-node?
  (λ (node)
    (if (null? node)
        #f
        #t))
  )

(define is-empty?
  (λ (tree)
    (if (null? tree)
        #t
        #f))
  )

(define has-left?
  (λ (tree)
    (if (null? (car (cdr tree)))
        #f
        #t))
  )

(define has-right?
  (λ (tree)
    (if (null? (cdr (cdr tree)))
        #f
        #t))
  )

(define minimum
  (λ (tree)
    (if (is-empty? tree)
        #f
        (if (has-left? tree)
            (if (has-right? tree)
                (min (get-value tree) (minimum (get-left tree)) (minimum (get-right tree)))
                (min (get-value tree) (minimum (get-left tree))))
            (if (has-right? tree)
                (min (get-value tree) (minimum (get-right tree)))
                (get-value tree)))))
  )

(define maximum
  (λ (tree)
    (if (is-empty? tree)
        #f
        (if (has-left? tree)
            (if (has-right? tree)
                (max (get-value tree) (maximum (get-left tree)) (maximum (get-right tree)))
                (max (get-value tree) (maximum (get-left tree))))
            (if (has-right? tree)
                (max (get-value tree) (maximum (get-right tree)))
                (get-value tree))))))

(define height
  (λ (tree)
    (if (is-empty? tree)
        0
        (if (has-left? tree)
            (if (has-right? tree)
                (+ 1 (max (height (get-left tree)) (height (get-right tree))))
                (+ 1 (height (get-left tree))))
            (if (has-right? tree)
                (+ 1 (height (get-right tree)))
                1))))
  )

(define inorder
  (λ (tree)
    (if (is-empty? tree)
        '()
        (append (inorder (get-left tree)) (list (get-value tree)) (inorder (get-right tree)))))
  )

(define preorder
  (λ (tree) #f)
  )

(define postorder
  (λ (tree) #f)
  )

(define successor
  (λ (tree value)
    (succesor tree value (maximum tree))))

(define succesor
  (λ (tree value m)
    (if (has-right? tree)
        (if (has-left? tree)
            (if (> (get-value tree) value)
                (min (succesor (get-left tree) value (min m (get-value tree))) (succesor (get-right tree) value (min m (get-value tree))))
                (succesor (get-right tree) value m))
            (if (> (get-value tree) value)
                (succesor (get-right tree) value (min m (get-value tree)))
                (succesor (get-right tree) value m)))
        (if (has-left? tree)
            (if (> (get-value tree) value)
                (succesor (get-left tree) value (min m (get-value tree)))
                (succesor (get-left tree) value m))
            (if (> (get-value tree) value)
                (min m (get-value tree))
                m)))))

(define predecessor
  (λ (tree value)
    (pred tree value (minimum tree))))
                    
(define pred
  (λ (tree value m)
    (if (has-left? tree)
        (if (has-right? tree)
            (if (< (get-value tree) value)
                (max (pred (get-left tree) value (max m (get-value tree))) (pred (get-right tree) value (max m (get-value tree))))
                (pred (get-left tree) value m))
            (if (< (get-value tree) value)
                (pred (get-left tree) value (max m (get-value tree)))
                (pred (get-left tree) value m)))
        (if (has-right? tree)
            (if (< (get-value tree) value)
                (pred (get-right tree) value (max m (get-value tree)))
                (pred (get-right tree) value m))
            (if (< (get-value tree) value)
                (max m (get-value tree))
                m)))))
                
    
 
(define binary-search-tree (make-node (make-node (make-node (init-node 1) '() 2) (make-node (init-node 5) (make-node (init-node 7) '() 8) 6) 3) (make-node (init-node 11) (make-node (init-node 13) (init-node 21) 15) 12) 9) )


;;Task 1
(define insert
  (λ (tree value)
    (if (is-empty? tree)
        (init-node value)
        (insert2 tree value (cauta tree value)))))

(define (insert2 tree value value2)
  (if (is-empty? tree)
      '()
      (if (eq? (get-value tree) value2)
          (if (< value (get-value tree))
              (make-node (init-node value) (insert2 (get-right tree) value value2) (get-value tree))
              (make-node (insert2 (get-left tree) value value2) (init-node value) (get-value tree)))
          (make-node (insert2 (get-left tree) value value2) (insert2 (get-right tree) value value2) (get-value tree)))))

(define (cauta tree value)
  (if (contains tree value)
      '()
      (if (is-empty? tree)
          '()
          (if (< value (get-value tree))
              (if (has-left? tree)
                  (cauta (get-left tree) value)
                  (get-value tree))
              (if (has-right? tree)
                  (cauta (get-right tree) value)
                  (get-value tree))))))

(define balance
  (λ (tree) empty-tree)
  )

(define union
  (λ (tree1 tree2)
    (if (is-empty? tree2)
        tree1
        (if (has-left? tree2)
            (if (has-right? tree2)
                (union (union (insert tree1 (get-value tree2)) (get-left tree2)) (get-right tree2))
                (union (insert tree1 (get-value tree2)) (get-left tree2)))
            (if (has-right? tree2)
                (union (insert tree1 (get-value tree2)) (get-right tree2))
                (insert tree1 (get-value tree2)))))))
 
                
            
(define intersection
  (λ (tree1 tree2)
    (intersection2 '() tree1 tree2)))

(define intersection2
  (λ (tree tree1 tree2)
    (if (is-empty? tree1)
        '()
        (if (is-empty? tree2)
            '()
            (if (has-left? tree2)
                (if (has-right? tree2)
                    (if (contains tree1 (get-value tree2))
                        (intersection2 (insert (intersection2 tree tree1 (get-left tree2)) (get-value tree2)) tree1 (get-right tree2))
                        (intersection2 (intersection2 tree tree1 (get-left tree2)) tree1 (get-right tree2)))
                    (if (contains tree1 (get-value tree2))
                        (intersection2 (insert tree (get-value tree2)) tree1 (get-left tree2))
                        (intersection2 tree tree1 (get-left tree2))))
                (if (has-right? tree2)
                    (if (contains tree1 (get-value tree2))
                        (intersection2 (insert tree (get-value tree2)) tree1 (get-right tree2))
                        (intersection2 tree tree1 (get-right tree2)))
                    (if (contains tree1 (get-value tree2))
                        (insert tree (get-value tree2))
                        tree)))))))

(define complements
  (λ (tree1 tree2) (complements2 '() tree1 tree2))
  )

(define complements2
  (λ (tree tree1 tree2)
    (if (is-empty? tree1)
        '()
        (if (is-empty? tree2)
            tree1
            (if (has-left? tree1)
                (if (has-right? tree1)
                    (if (contains tree2 (get-value tree1))
                        (complements2 (complements2 tree (get-left tree1) tree2) (get-right tree1) tree2)
                        (complements2 (insert (complements2 tree (get-left tree1) tree2) (get-value tree1)) (get-right tree1) tree2))
                    (if (contains tree2 (get-value tree1))
                        (complements2 tree (get-left tree1) tree2)
                        (complements2 (insert tree (get-value tree1)) (get-left tree1) tree2)))
                (if (has-right? tree1)
                    (if (contains tree2 (get-value tree1))
                        (complements2 tree (get-right tree1) tree2)
                        (complements2 (insert tree (get-value tree1)) (get-right tree1) tree2))
                    (if (contains tree2 (get-value tree1))
                        tree
                        (insert tree (get-value tree1)))))))))
            

(define contains
  (λ (tree value)
    (if (is-empty? tree)
        #f
        (if (eq? value (get-value tree))
            #t
            (if (< value (get-value tree))
                (if (has-left? tree)
                    (contains (get-left tree) value)
                    #f)
                (if (has-right? tree)
                    (contains (get-right tree) value)
                    #f)))))
  )

(define remove
  (λ (tree value) (remove2 '() tree value))
  )

(define remove2
  (λ (tree tree2 value)
    (if (is-empty? tree2)
        tree
        (if (eq? value (get-value tree2))
            (if (has-left? tree2)
                (if (has-right? tree2)
                    (remove2 (insert (remove2 tree (get-left tree2) value) (successor tree2 value)) (get-right tree2) value)
                    (remove2 tree (get-left tree2) value))
                (if (has-right? tree2)
                    (remove2 tree (get-right tree2) value)
                    tree))
            (if (has-left? tree2)
                (if (has-right? tree2)
                    (remove2 (insert (remove2 tree (get-left tree2) value) (get-value tree2)) (get-right tree2) value)
                    (remove2 (insert tree (get-value tree2)) (get-left tree2) value))
                (if (has-right? tree2)
                    (remove2 (insert tree (get-value tree2)) (get-right tree2) value)
                    (insert tree (get-value tree2))))))))

;;Task 2
(define k-subsets
  (λ (set k)
    (if (< (nr-elem (inorder set)) 15)
        (all-ksub (all-subsets (inorder set) '(())) k )
        '())
  ))

(define all-ksub
  (λ (List k)
    (if (null? List)
        '()
        (if (eq? k (nr-elem (car List)))
            (append (list (car List)) (all-ksub (cdr List) k))
            (all-ksub (cdr List) k)))))

(define nr-elem
  (λ (List)
    (if (null? List)
        0
        (+ 1 (nr-elem (cdr List))))))

(define all-subsets
  (λ (List List2)
    (if (null? List)
        List2
        (all-subsets (cdr List) (unite List2 (car List))))))

(define unite
  (λ (List el)
    (append List (add List el))))

(define add
  (λ (List el)
    (if (null? List)
       '()
       (append (list (append (car List) (list el))) (add (cdr List) el)))))
    

(define zig-zag-subsets
  (λ (set) (perm-zig (rem-dupl (k-perm (all-perm (inorder set) '() 0) '() (nr-elem2 (inorder set))) '()) '()))
  )

(define perm-zig
  (λ (List List2)
    (if (null? List)
        List2
        (if (is-zig-zag (car List) >)
            (perm-zig (cdr List) (append (list (car List)) List2))
            (if (is-zig-zag (car List) <)
                (perm-zig (cdr List) (append (list (car List)) List2))
                (perm-zig (cdr List) List2))))))

(define is-zig-zag
  (λ (List x)
    (if (null? (cdr List))
        #t
        (if (eq? x >)
            (if (> (car List) (car (cdr List)))
                (is-zig-zag (cdr List) <)
                #f)
            (if (< (car List) (car (cdr List)))
                (is-zig-zag (cdr List) >)
                #f)))))

(define contains-list
  (λ (List x)
    (if (null? List)
        #f
        (if (eq? (car List) x)
            #t
            (contains-list (cdr List) x)))))

(define cont-dupl
  (λ (List)
    (if (null? List)
        #f
        (if (contains-list (cdr List) (car List))
            #t
            (cont-dupl (cdr List))))))

(define rem-dupl
  (λ (List List2)
    (if (null? List)
        List2
        (if (cont-dupl (car List))
            (rem-dupl (cdr List) List2)
            (rem-dupl (cdr List) (append (list (car List)) List2))))))

(define k-perm
  (λ (List List2 k)
    (if (null? List)
        List2
        (if (eq? (nr-elem2 (car List)) k)
            (k-perm (cdr List) (append (list (car List)) List2) k)
            (k-perm (cdr List) List2 k)))))

(define nr-elem2
  (λ (List)
    (if (null? List)
        0
        (+ 1 (nr-elem2 (cdr List))))))

(define all-perm
  (λ (List1 List2 x)
    (if (eq? x (nr-elem2 List1))
        List2
        (all-perm List1 (perm List1 List2) (+ 1 x)))))

(define perm
  (λ (List1 List2)
    (if (null? List2)
        (for2 List1 List2)
        (append (for2 List1 (car List2)) (perm List1 (cdr List2))))))


(define for2
  (λ (List1 List2)
    (if (null? List1)
        '()
        (append (for2 (cdr List1) List2) (list (append List2 (list (car List1)))))
        )))
;;BONUS
(define parser
  (λ (expression)
    (if (list? expression)
        (make-node (parser (car expression)) (parser (car (cdr (cdr expression)))) (car (cdr expression)))
        (init-node expression))))

(define evaluate
  (λ (expr-tree)
    (if (is-empty? expr-tree)
        0
        (if (is-leaf? expr-tree)
            (get-value expr-tree)
            (if (eq? '+ (get-value expr-tree))
                (+ (evaluate (get-left expr-tree)) (evaluate (get-right expr-tree)))
                (if (eq? '- (get-value expr-tree))
                    (- (evaluate (get-left expr-tree)) (evaluate (get-right expr-tree)))
                    (if (eq? '* (get-value expr-tree))
                        (* (evaluate (get-left expr-tree)) (evaluate (get-right expr-tree)))
                        (if (eq? '/ (get-value expr-tree))
                            (/ (evaluate (get-left expr-tree)) (evaluate (get-right expr-tree)))
                            '()))))))))


;; SECȚIUNE DE TESTARE - NU modificați această linie!
;; ATENȚIE! Pentru a primi punctaj pe temă, NU modificați această secțiune!
;;
;; CHECK - TASK 0 - NU modificați această linie!
;; ATENȚIE! NU modificați această secțiune
(Task 0 : 30 puncte) ;;check-exp
(define functions (list is-node? is-leaf? is-empty? get-value make-node get-right get-left inorder height insert empty-tree)) ;;check-exp
(define tree0 binary-search-tree) ;;check-exp
(check-exp-part 'is-node .037 (is-node? tree0) #t)
(check-exp-part 'is-leaf?1 .037 (is-leaf? tree0) #f)
(check-exp-part 'is-leaf?2 .037 (is-leaf? (init-node 8)) #t)
(check-exp-part 'is-empty?1 .037 (is-empty? tree0) #f)
(check-exp-part 'is-empty?2 .037 (is-empty? empty-tree) #t)
(check-exp-part 'get-value1 .037 (get-value tree0) 9)
(check-exp-part 'get-value2 .037 (get-value (get-left tree0)) 3)
(check-exp-part 'get-value3 .037 (get-value (get-right tree0)) 12)
(check-exp-part 'make-node .037 (make-node (get-left tree0) (get-right tree0) (get-value tree0)) binary-search-tree)
(check-exp-part 'minimum .0833 (minimum tree0) 1)
(check-exp-part 'maximum .0833 (maximum tree0) 21)
(check-exp-part 'height1 .0833 (height tree0) 5)
(check-exp-part 'height2 .0833 (height (get-left (get-left tree0))) 2)
(check-exp-part 'successor1 .055 (successor tree0 9) 11)
(check-exp-part 'successor2 .055 (successor tree0 5) 6)
(check-exp-part 'successor3 .055 (successor tree0 8) 9)
(check-exp-part 'predecessor1 .056 (predecessor tree0 9) 8)
(check-exp-part 'predecessor2 .056 (predecessor tree0 5) 3)
(check-exp-part 'predecessor3 .057 (predecessor tree0 12) 11)
;; SFÂRȘIT CHECK - TASK 0 - NU modificați această linie!
;;
;; CHECK - Task1 - NU modificați această linie!
;; ATENȚIE! NU modificați această secțiune!
(Task 1 : 50 puncte) ;;check-exp
(define A (create-tree '(8 9 10 15 8 5 0 1 4 5 9 7 1 0 151 651 61 45 416 2542 -8 3541 644 2 4 8542 51 142 215) functions)) ;;check-exp
(define B (create-tree '(942 4 54 64 94 25 0 -815 485 251 64 8 10 5 4 644 2 216 2541 5 8 7 5254 2542 214 4511) functions)) ;;check-exp
(define C (create-tree '(8 5 4 1 846 54 0 -5552 4 5 810 42 545 842 54 5488 8755 14 679 25 78 25 955 7891 789 8891 97 54 15 2465 155) functions)) ;;check-exp
(define D (create-tree '(8 9 1 5 9 7 5 9 78 1 5 6 9 89 24 52 95 22 94 6 485 18 6 97 8 100 4 9 655 478 92) functions)) ;;check-exp
(check-exp-part 'check-set1 .04 (test-task1 (create-tree '(8 4 2 1 -5 6 1 8 9 5 3 11 17 10 -6 4 8) functions) functions) result-check-set1)
(check-exp-part 'check-set2 .04 (test-task1 (create-tree '(-9 8 2 1 4 0 9 3 4 2 5 9 11 481 51 35 15 0 4 15 251 6551 12 3 4 7 9) functions) functions) result-check-set2)
(check-exp-part 'check-set3 .04 (test-task1 A functions) result-check-set3)
(check-exp-part 'check-set4 .04 (test-task1 B functions) result-check-set4)
(check-exp-part 'check-set5 .04 (test-task1 C functions) result-check-set5)
(check-exp-part 'union1 .005 (test-task1 (union A B) functions) result-union1)
(check-exp-part 'union2 .005 (test-task1 (union C D) functions) result-union2)
(check-exp-part 'union3 .005 (test-task1 (union A D) functions) result-union3)
(check-exp-part 'union4 .005 (test-task1 (union (union A B) (union C D)) functions) result-union4)
(check-exp-part 'intersection1 .01 (test-task1 (intersection A B) functions) result-intersection1)
(check-exp-part 'intersection2 .01 (test-task1 (intersection B C) functions) result-intersection2)
(check-exp-part 'intersection3 .01 (test-task1 (intersection C D) functions) result-intersection3)
(check-exp-part 'intersection4 .01 (test-task1 (intersection (intersection A B) (intersection  C D)) functions) result-intersection4)
(check-exp-part 'complements1 .01 (test-task1 (complements A B) functions) result-complements1)
(check-exp-part 'complements2 .01 (test-task1 (complements C D) functions) result-complements2)
(check-exp-part 'complements3 .01 (test-task1 (complements C D) functions) result-complements3)
(check-exp-part 'complements4 .01 (test-task1 (complements (complements A B) (complements C D)) functions) result-complements4)
(check-exp-part 'insert1 .005 (test-task1 (insert B -7) functions) result-insert1)
(check-exp-part 'insert2 .005 (test-task1 (insert A 59525) functions) result-insert2)
(check-exp-part 'insert3 .005 (test-task1 (insert C 988522) functions) result-insert3)
(check-exp-part 'insert4 .005 (test-task1 (insert D -812612) functions) result-insert4)
(check-exp-part 'remove1 .02 (test-task1 (remove binary-search-tree (minimum binary-search-tree)) functions) result-remove1)
(check-exp-part 'remove2 .02 (test-task1 (remove binary-search-tree 9) functions) result-remove2)
(check-exp-part 'remove3 .02 (test-task1 (remove binary-search-tree 3) functions) result-remove3)
(check-exp-part 'remove4 .02 (test-task1 (remove (remove (remove A (successor A 10)) (predecessor A 0)) 416) functions) result-remove4)
(check-exp-part 'complex1 .02 (test-task1 (union A (intersection B C)) functions) result-complex1)
(check-exp-part 'complex2 .02 (test-task1 (insert (intersection (complements B C) (remove (union A B) (predecessor A 51))) 7851) functions) result-complex2)
(check-exp-part 'complex3 .02 (test-task1 (insert (remove (remove (union (intersection (complements B C) (complements B A)) binary-search-tree) 214) 1) 1) functions) result-complex3)
(check-exp-part 'complex4 .02 (test-task1 (union (intersection (complements B A) (union C D)) (complements A D)) functions) result-complex4)
(check-exp-part 'complex5 .02 (test-task1 (intersection (union (complements A B) (complements C D)) (complements (intersection A B) (intersection C D))) functions) result-complex5)
(check-exp-part 'complex6 .02 (test-task1 (remove (insert (union (union (complements A B) (intersection C D)) (intersection (complements C D) (intersection A B))) 22) -8) functions) result-complex6)
(check-exp-part 'complex7 .02 (test-task1 (union (union (intersection A C) (complements A D)) (intersection (complements B C) (intersection B D))) functions) result-complex7)
(check-exp-part 'complex8 .02 (test-task1 (union (union (union A B) (union C D)) (intersection (intersection A B) (intersection C D))) functions) result-complex8)
(check-exp-part 'complex9 .02 (test-task1 (intersection (union (complements A B) (complements B A)) (intersection (union A B) (union C D))) functions) result-complex9)
(check-exp-part 'complex10 .02 (test-task1 (insert (remove (intersection (union (complements B A) (union (complements C D) (intersection A B))) (intersection (complements B (union A C)) (union C D))) 485) 100) functions) result-complex10)
(check-exp-part 'height-balanced1 .04 (check-self-balancing-tree B functions) #t)
(check-exp-part 'height-balanced2 .04 (check-self-balancing-tree A functions) #t)
(check-exp-part 'height-balanced3 .04 (check-self-balancing-tree C functions) #t)
(check-exp-part 'height-balanced4 .04 (check-self-balancing-tree D functions) #t)
(check-exp-part 'height-balanced5 .04 (let [(tree (create-tree '(1 2 3 4 5 6 7 8 9 10) functions))] (check-self-balancing-tree tree functions)) #t)
(check-exp-part 'height-balanced6 .04 (let [(tree (create-tree '(20 19 18 17 16 15 10 9 8 7 6 5 4 3 2 1) functions))] (check-self-balancing-tree tree functions)) #t)
(check-exp-part 'height-balanced7 .04 (let [(tree (union A (intersection B C)))] (check-self-balancing-tree tree functions)) #t)
(check-exp-part 'height-balanced8 .04 (let [(tree (remove (insert (union (complements A D) (intersection B C)) 24) 416))] (check-self-balancing-tree tree functions)) #t)
(check-exp-part 'height-balanced9 .04 (let [(tree (union (remove binary-search-tree 9) A))] (check-self-balancing-tree tree functions)) #t)
(check-exp-part 'height-balanced10 .04 (let [(tree (intersection (union (remove A (get-value A)) (remove B (get-value B))) (remove C (get-value C))))] (check-self-balancing-tree tree functions)) #t)
;; SFÂRȘIT CHECK - TASK 1 - NU modificați această linie!
;;
;; CHECK - TASK 2 - NU modificați această linie!
;; ATENȚIE! NU modificați această secțiune
(Task 2 : 20 puncte) ;;check-exp
(check-exp-part 'k-subsets1 0.1 (test-subsets (k-subsets (intersection A B) 8) result-k-subsets1) #t)
(check-exp-part 'k-subsets2 0.1 (let [(subsets (k-subsets binary-search-tree 11))] (and (= (length subsets) 78) (not (equal? (member '(2 3 5 6 8 9 11 12 13 15 21) subsets) #f)))) #t)
(check-exp-part 'k-subsets3 0.1 (test-subsets (k-subsets (create-tree '(1 2 3 4 5) functions) 3) result-k-subsets3) #t)
(check-exp-part 'k-subsets4 0.1 (test-subsets (k-subsets (create-tree '(8 7 6 5) functions) 2) result-k-subsets4) #t)
(check-exp-part 'k-subsets5 0.1 (test-subsets (k-subsets D 20) result-k-subsets5) #t)
(check-exp-part 'zig-zag-subsets1 0.1 (test-subsets (zig-zag-subsets (create-tree '(1 2 3 4 5 6) functions)) result-zig-zag1) #t)
(check-exp-part 'zig-zag-subsets2 0.1 (test-subsets (zig-zag-subsets (create-tree '(1 2 3 4) functions)) result-zig-zag2) #t)
(check-exp-part 'zig-zag-subsets3 0.1 (test-subsets (zig-zag-subsets (create-tree '(1 7 9 10 5) functions)) result-zig-zag3) #t)
(check-exp-part 'zig-zag-subsets4 0.1 (test-subsets (zig-zag-subsets (create-tree '(98 5 1 -85 -457) functions)) result-zig-zag4) #t)
(check-exp-part 'zig-zag-subsets5 0.1 (length (zig-zag-subsets (create-tree '(982 616 542 125 98 85) functions))) 122)
;; SFÂRȘIT CHECK - TASK 2 - NU modificați această linie!
;;
;; CHECK - BONUS - NU modificați această linie!
;; ATENȚIE! NU modificați această secțiune
(Bonus 3 : 20 puncte BONUS) ;;check-exp
(check-exp-part 'bonus1 0.1 (test-bonus (parser '(1 + (((2 * 3) - 4) * 5))) functions) 11)
(check-exp-part 'bonus2 0.1 (test-bonus (parser '((((5 + 8) * (9 - (8 / 2))) + (8 * 9)) * 10)) functions) 1370)
(check-exp-part 'bonus3 0.1 (test-bonus (parser '((5 * 8) - (7 * (3 + (5 * (10 / 2)))))) functions) -156)
(check-exp-part 'bonus4 0.1 (test-bonus (parser '(((((80 - 78) + 15) * 4 ) / 2) + (7 + (((5 * 3) - 2) * 4)))) functions) 93)
(check-exp-part 'bonus5 0.2 (test-bonus (parser '(((((((((5 + 8) + (9 + 8)) * 3) + (8 - 7)) * 2) + 10) / 2) * 10) - (5 + (7 + (8 * (1 + 2)))))) functions) 924)
(check-exp-part 'bonus6 0.2 (test-bonus (parser '((((((5 + 6) * 7) + 9) * 10) / 2) + (7 * (2 * (4 * (10 - (7 + (1 * (2 - 1))))))))) functions) 542)
(check-exp-part 'bonus7 0.2 (test-bonus (parser '(((5 + (7 - (2 * (3 + (9 - (7 + (8 + (5 * 2)))))))) + (5 * (((2 + 2) * (3 + 7)) + (7 * (9 - (4 + 7)))))) / 2)) functions) 84)
;; SFÂRȘIT CHECK - BONUS - NU modificați această linie!
;; SFÂRȘIT SECȚIUNE DE TESTARE

(sumar)
