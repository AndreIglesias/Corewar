;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    fileC.el                                           :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: ppeltier <ppeltier@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2014/11/09 19:40:49 by ppeltier          #+#    #+#              ;
;    Updated: 2014/11/10 20:11:15 by ppeltier         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

;; File.c's Skeleton
(define-skeleton create-protect-include
  "Create a protection to Includes"
  ""
  "\n"
  "#ifndef		"
  (setq file_name (upcase (file-name-sans-extension (file-name-nondirectory buffer-file-name))))
  "_"
  (setq file_ext (upcase (file-name-extension (file-name-nondirectory buffer-file-name))))
  "\n"
  "# define	"file_name"_"file_ext
  "\n"
  "\n"
  "\n"
  "\n"
  "#endif"
)
