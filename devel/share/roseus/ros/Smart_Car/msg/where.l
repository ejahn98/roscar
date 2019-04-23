;; Auto-generated. Do not edit!


(when (boundp 'Smart_Car::where)
  (if (not (find-package "SMART_CAR"))
    (make-package "SMART_CAR"))
  (shadow 'where (find-package "SMART_CAR")))
(unless (find-package "SMART_CAR::WHERE")
  (make-package "SMART_CAR::WHERE"))

(in-package "ROS")
;;//! \htmlinclude where.msg.html


(defclass Smart_Car::where
  :super ros::object
  :slots (_data ))

(defmethod Smart_Car::where
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
    ;; int32 _data
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _data
       (write-long _data s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _data
     (setq _data (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get Smart_Car::where :md5sum-) "da5909fbe378aeaf85e547e830cc1bb7")
(setf (get Smart_Car::where :datatype-) "Smart_Car/where")
(setf (get Smart_Car::where :definition-)
      "int32 data

")



(provide :Smart_Car/where "da5909fbe378aeaf85e547e830cc1bb7")


