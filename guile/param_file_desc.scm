(use-syntax (ice-9 syncase))

(define fuzzy-string "uo")
(define exact "c")
(define date "d")

(define config '((directory . ".")
                 (filea . "sorta.dat")
                 (fileb . "sortb.dat")
                 (verbose . #f)
                 (summary . #f)))

(define config-fields '())
(define config-strategies '())

(define (directory s)
  (assq-set! config 'directory s))

(define (files . fs)
  (assq-set! config 'filea (car fs))
  (assq-set! config 'fileb (cadr fs)))

(define (set-flag-value! s)
  (let* ((val (string-prefix? "no-" s))
         (sym (string->symbol (if val (substring s 3) s))))
    (assq-set! config sym (not val))))

(define-syntax flags
  (syntax-rules ()
    ((_ f ...) (begin (set-flag-value! (symbol->string 'f)) ...))))

;; (symbol-pair foo x) -> ('foo . x)
(define-syntax symbol-pair
  (syntax-rules ()
    ((_ k v) (cons 'k 'v))
    ((_ k . vs) (cons 'k 'vs))))

(define-syntax fields
  (syntax-rules ()
    ((_ f ...)
     (set! config-fields (list (symbol-pair . f) ...)))))

(define-syntax strategy
  (syntax-rules ()
    ((_ f ...)
     (set! config-strategies
           (cons (list (symbol-pair . f) ...) config-strategies)))))
