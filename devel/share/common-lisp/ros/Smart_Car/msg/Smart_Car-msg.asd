
(cl:in-package :asdf)

(defsystem "Smart_Car-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "where" :depends-on ("_package_where"))
    (:file "_package_where" :depends-on ("_package"))
  ))