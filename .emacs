;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    .emacs                                             :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/07/27 02:55:55 by ciglesia          #+#    #+#              ;
;    Updated: 2020/08/23 19:00:11 by ciglesia         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

; Load general features files
(require 'package)
(let* ((no-ssl (and (memq system-type '(windows-nt ms-dos))
                    (not (gnutls-available-p))))
       (proto (if no-ssl "http" "https")))
  (when no-ssl
    (warn "\
Your version of Emacs does not support SSL connections,
which is unsafe because it allows man-in-the-middle attacks.
There are two things you can do about this warning:
1. Install an Emacs version that does support SSL and be safe.
2. Remove this warning from your init file so you won't see it again."))
  ;; Comment/uncomment these two lines to enable/disable MELPA and MELPA Stable as desired
  (add-to-list 'package-archives (cons "melpa" (concat proto "://melpa.org/packages/")) t)
  ;;(add-to-list 'package-archives (cons "melpa-stable" (concat proto "://stable.melpa.org/packages/")) t)
  (when (< emacs-major-version 24)
    ;; For important compatibility libraries like cl-lib
    (add-to-list 'package-archives (cons "gnu" (concat proto "://elpa.gnu.org/packages/")))))
;; Added by Package.el.  This must come before configurations of
;; installed packages.  Don't delete this line.  If you don't want it,
;; just comment it out by adding a semicolon to the start of the line.
;; You may delete these explanatory comments.
(package-initialize)

(require 'package)
(add-to-list 'package-archives '("org" . "https://orgmode.org/elpa/") t)

(setq config_files "~/.emacs.d/root_42/")
(setq load-path (append (list nil config_files) load-path))

(load "list.el")
(load "string.el")
(load "comments.el")
(load "header.el")

; Set default emacs configuration
(set-language-environment "UTF-8")
(setq-default font-lock-global-modes nil)
(setq-default line-number-mode nil)
(setq-default tab-width 4)
(setq-default indent-tabs-mode t)
(global-set-key (kbd "DEL") 'backward-delete-char)
(setq-default c-backspace-function 'backward-delete-char)
(setq-default c-basic-offset 4)
(setq-default c-default-style "linux")
(setq-default tab-stop-list '(4 8 12 16 20 24 28 32 36 40 44 48 52 56 60
                             64 68 72 76 80 84 88 92 96 100 104 108 112 116 120))

; Load user configuration
(if (file-exists-p "~/.emacs.d/myemacs") (load-file "~/.emacs.d/myemacs"))

;*******************************************************************************;
(ac-config-default)

(global-auto-complete-mode t)


(defun my-insert-tab-char ()
  "Insert a tab char. (ASCII 9, \t)"
  (interactive)
  (insert "\t"))

(add-hook 'buffer-list-update-hook 'font-lock-mode)

(global-set-key (kbd "<backtab>") 'my-insert-tab-char)

(global-set-key (kbd "<mouse-2>") 'clipboard-yank)

;*******************************************************************************;

(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(ansi-color-faces-vector
   [default default default italic underline success warning error])
 '(ansi-color-names-vector
   ["#2d3743" "#ff4242" "#74af68" "#dbdb95" "#34cae2" "#008b8b" "#00ede1" "#e1e1e0"])
 '(custom-enabled-themes (quote (dracula)))
 '(custom-safe-themes
   (quote
	("d61f6c49e5db58533d4543e33203fd1c41a316eddb0b18a44e0ce428da86ef98" "b59d7adea7873d58160d368d42828e7ac670340f11f36f67fa8071dbf957236a" "bd7b7c5df1174796deefce5debc2d976b264585d51852c962362be83932873d9" "c9b89349d269af4ac5d832759df2f142ae50b0bbbabcce9c0dd53f79008443c9" "274fa62b00d732d093fc3f120aca1b31a6bb484492f31081c1814a858e25c72e" default)))
 '(gud-gdb-command-name "gdb --annotate=1")
 '(large-file-warning-threshold nil)
 '(linum-format "%3i")
 '(org-latex-tables-centered t)
 '(package-selected-packages
   (quote
	(org-edit-latex multiple-cursors all-the-icons org-pdfview pdf-tools auto-complete realgud command-log-mode airline-themes evil powerline dracula-theme)))
 '(powerline-color1 "#3d3d68")
 '(powerline-color2 "#292945"))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(org-level-1 ((t (:inherit bold :foreground "brightred" :height 1.3)))))
(require 'airline-themes)
(load-theme 'airline-behelit)

(require 'auto-complete-config)
(ac-config-default)

(require 'column-marker)
 (add-hook 'c-mode-hook (lambda () () (column-marker-1 80)))

(add-to-list 'load-path "~/.emacs.d/neotree")
(require 'neotree)
(global-set-key [f8] 'neotree-toggle)

(require 'man)
;(set-face-attribute 'Man-overstrike nil :inherit font-lock-type-face :bold t)
;(set-face-attribute 'Man-underline nil :inherit font-lock-keyword-face :underline t)

(set-face-attribute 'Man-overstrike nil :inherit 'bold :foreground "orange red")
(set-face-attribute 'Man-underline nil :inherit 'underline :foreground "forest green")

;*******************************************************************************;

(global-set-key (kbd "<home>") 'beginning-of-line)
(global-set-key (kbd "<end>") 'end-of-line)


(defun count-lines-fun ()
  "Print number of lines words and characters in the region."
  (interactive "r")
  (beginning-of-defun)
  (set-mark (point-min))
  (goto-char (end-of-defun))
  (activate-mark)
  (message "Region has %d lines, %d words, %d characters"
		   (count-lines)))

(defun count-words-in-defun ()
  "Return the number of words and symbols in a defun."
  (beginning-of-defun)
  (let ((count 0)
		(end (save-excursion (end-of-defun) (point))))
    (while
        (and (< (point) end)
             (re-search-forward
;              "\\(\\w\\|\\s_\\)+[^ \t\n]*[ \t\n]*"
              "\n" end t))
      (setq count (1+ count)))
	(setq count (- count 3))
	count))


;;; Interactive version.
(defun count-words-defun ()
  "Number of words and symbols in a function definition."
  (interactive)
  (message
   "Counting lines in function definition ... ")
  (let ((count (count-words-in-defun)))
    (cond
     ((zerop count)
      (message
       "The definition does NOT have any lines."))
     ((= 1 count)
      (message
       "The definition has 1 line."))
	 ((< 25 count)
	  (message
	   "the function has TOO MANY lines (%d)." count))
     (t
      (message
       "The definition has %d lines." count)))))

;(global-set-key (kbd "C-c C-v") 'count-words-defun)
(global-set-key (kbd "C-c C-v") 'count-words-defun)

(require 'multiple-cursors)
(global-set-key (kbd "C-c C-r") 'mc/mark-next-like-this)
(global-set-key (kbd "C-c r") 'mc/mark-previous-like-this)
(global-set-key (kbd "C-c s") 'mc/mark-all-like-this)
(global-unset-key (kbd "M-<down-mouse-1>"))
(global-set-key (kbd "M-<mouse-1>") 'mc/add-cursor-on-click)
(eval-after-load "gud"
  '(progn
     (define-key gud-mode-map (kbd "<up>") 'comint-previous-input)
     (define-key gud-mode-map (kbd "<down>") 'comint-next-input)
	 (setq comint-scroll-to-bottom-on-input t)
	 (setq comint-scroll-to-bottom-on-output t)))



(setq org-emphasis-alist (quote (("."  (bold :foreground "red"))
								 ("`"  (bold :foreground "green"))
								 ("'"  (bold :foreground "blue"))
								 (","  (bold :foreground "yellow"))
								 ("~"  (bold :foreground "white"))
								 ("/" italic "<i>" "</i>")
								 ("_" underline "<span style=\"text-decoration:underline;\">" "</span>")
								 ("-" (:overline t) "<span style=\"text-decoration:overline;\">" "</span>")
								 ("=" org-code "<code>" "</code>" verbatim)
								 ("*" (bold) org-verbatim "<code>" "</code>" verbatim)
								 ("!" (bold :foreground "Orange") org-verbatim "<code>" "</code>" verbatim)
								 )))
; ("+" (:strike-through t) "<del>" "</del>")
(setq org-hide-emphasis-markers (quote ((".")("`"))))
