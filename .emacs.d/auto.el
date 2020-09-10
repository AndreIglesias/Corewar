;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    auto.el                                            :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: ppeltier <ppeltier@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2014/11/13 16:49:58 by ppeltier          #+#    #+#              ;
;    Updated: 2014/12/10 19:50:14 by ppeltier         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;


;; Commenter prochaine ligne pour desactiver le makefile automatique
(add-to-list 'auto-mode-alist '("Makefile" . load-makefile))

;; Commenter prochaines lignes pour desactiver les header automatique
(add-to-list 'auto-mode-alist '("\\.h\\'" . load-fileH))
(add-to-list 'auto-mode-alist '("\\.c\\'" . load-fileC))
(add-to-list 'auto-mode-alist '("\\.sh\\'" . load-fileSH))
(add-to-list 'auto-mode-alist '(".myzshrc" . load-fileSH))
(add-to-list 'auto-mode-alist '("\\.cpp\\'" . load-fileCPP))
(add-to-list 'auto-mode-alist '("\\.cc\\'" . load-fileCPP))
(add-to-list 'auto-mode-alist '("\\.hh\\'" . load-fileCPP))
(add-to-list 'auto-mode-alist '("\\.html\\'" . load-fileHTML))
(add-to-list 'auto-mode-alist '("\\.el\\'" . load-fileLISP))

(defun load-makefile ()
  "Load Header and push a Makefile squeleton model"
  (load-file "~/.emacs.d/skeleton/makefile.el")
  (interactive)
  (goto-char(point-min))
  (makefile-mode)
  (if  (< (buffer-size) 10)
	  (progn
		(create-makefile)
		(header-insert)
		(goto-char(point-min))
		(forward-char 900)
		))
)

(defun load-fileH ()
  "Load Header and add a main squeleton model"
  (load-file "~/.emacs.d/skeleton/fileC.el")
  (interactive)
  (goto-char(point-min))
  (c-mode)
  (if  (< (buffer-size) 10)
	  (progn
		(create-protect-include)
		(header-insert)
		(goto-char(point-max))
		(backward-char 8)
		))
)

(defun load-fileC ()
  "Load Header and add a main squeleton model"
  (interactive)
  (goto-char(point-min))
  (c-mode)
  (if  (< (buffer-size) 10)
	  (progn
		(newline)
		(header-insert)
		(goto-char(point-max))
		))
)

(defun load-fileSH ()
  "Load Header and add a main squeleton model"
  (interactive)
  (goto-char(point-min))
  (sh-mode)
  (if  (< (buffer-size) 10)
	  (progn
		(newline)
		(header-insert)
		(goto-char(point-max))
		))
)

(defun load-fileLISP ()
  "Load Header and add a main squeleton model"
  (interactive)
  (goto-char(point-min))
  (emacs-lisp-mode)
  (if  (< (buffer-size) 10)
	  (progn
		(newline)
		(header-insert)
		(goto-char(point-max))
		))
)

(defun load-fileCPP ()
  "Load Header and add a main squeleton model"
  (interactive)
  (goto-char(point-min))
  (c++-mode)
  (if  (< (buffer-size) 10)
	  (progn
		(newline)
		(header-insert)
		(goto-char(point-max))
		))
)

(defun load-fileHTML ()
  "Load Header and add a main squeleton model"
  (interactive)
  (goto-char(point-min))
  (html-mode)
  (if  (< (buffer-size) 10)
	  (progn
		(newline)
		(header-insert)
		(goto-char(point-max))
		))
)

(defun load-fileEL ()
  "Load Header and add a main squeleton model"
  (interactive)
  (goto-char(point-min))
  (emacs-lisp-mode)
  (if  (< (buffer-size) 10)
	  (progn
		(newline)
		(header-insert)
		(goto-char(point-max))
		))
)
