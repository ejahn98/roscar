;; Auto-generated. Do not edit!


(when (boundp 'Smart_Car::MsgTutorial)
  (if (not (find-package "SMART_CAR"))
    (make-package "SMART_CAR"))
  (shadow 'MsgTutorial (find-package "SMART_CAR")))
(unless (find-package "SMART_CAR::MSGTUTORIAL")
  (make-package "SMART_CAR::MSGTUTORIAL"))

(in-package "ROS")
;;//! \htmlinclude MsgTutorial.msg.html


(defclass Smart_Car::MsgTutorial
  :super ros::object
  :slots (_data ))

(defmethod Smart_Car::MsgTutorial
  (:init
   (&key
    ((:data __data) 0)
    )
   (send-super :init)
   (setq _data (round __data))
   self)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:serialization-length
   ()
   (+
    ;; int8 _data
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _data
       (write-byte _data s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _data
     (setq _data (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _data 127) (setq _data (- _data 256)))
   ;;
   self)
  )

(setf (get Smart_Car::MsgTutorial :md5sum-) "27ffa0c9c4b8fb8492252bcad9e5c57b")
(setf (get Smart_Car::MsgTutorial :datatype-) "Smart_Car/MsgTutorial")
(setf (get Smart_Car::MsgTutorial :definition-)
      "int8 data

")



(provide :Smart_Car/MsgTutorial "27ffa0c9c4b8fb8492252bcad9e5c57b")


