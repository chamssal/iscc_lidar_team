;; Auto-generated. Do not edit!


(when (boundp 'waypoint_maker::ObjectInfo)
  (if (not (find-package "WAYPOINT_MAKER"))
    (make-package "WAYPOINT_MAKER"))
  (shadow 'ObjectInfo (find-package "WAYPOINT_MAKER")))
(unless (find-package "WAYPOINT_MAKER::OBJECTINFO")
  (make-package "WAYPOINT_MAKER::OBJECTINFO"))

(in-package "ROS")
;;//! \htmlinclude ObjectInfo.msg.html


(defclass waypoint_maker::ObjectInfo
  :super ros::object
  :slots (_objectCounts _centerX _centerY _centerZ _lengthX _lengthY _lengthZ ))

(defmethod waypoint_maker::ObjectInfo
  (:init
   (&key
    ((:objectCounts __objectCounts) 0)
    ((:centerX __centerX) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:centerY __centerY) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:centerZ __centerZ) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:lengthX __lengthX) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:lengthY __lengthY) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:lengthZ __lengthZ) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _objectCounts (round __objectCounts))
   (setq _centerX __centerX)
   (setq _centerY __centerY)
   (setq _centerZ __centerZ)
   (setq _lengthX __lengthX)
   (setq _lengthY __lengthY)
   (setq _lengthZ __lengthZ)
   self)
  (:objectCounts
   (&optional __objectCounts)
   (if __objectCounts (setq _objectCounts __objectCounts)) _objectCounts)
  (:centerX
   (&optional __centerX)
   (if __centerX (setq _centerX __centerX)) _centerX)
  (:centerY
   (&optional __centerY)
   (if __centerY (setq _centerY __centerY)) _centerY)
  (:centerZ
   (&optional __centerZ)
   (if __centerZ (setq _centerZ __centerZ)) _centerZ)
  (:lengthX
   (&optional __lengthX)
   (if __lengthX (setq _lengthX __lengthX)) _lengthX)
  (:lengthY
   (&optional __lengthY)
   (if __lengthY (setq _lengthY __lengthY)) _lengthY)
  (:lengthZ
   (&optional __lengthZ)
   (if __lengthZ (setq _lengthZ __lengthZ)) _lengthZ)
  (:serialization-length
   ()
   (+
    ;; int32 _objectCounts
    4
    ;; float64[] _centerX
    (* 8    (length _centerX)) 4
    ;; float64[] _centerY
    (* 8    (length _centerY)) 4
    ;; float64[] _centerZ
    (* 8    (length _centerZ)) 4
    ;; float64[] _lengthX
    (* 8    (length _lengthX)) 4
    ;; float64[] _lengthY
    (* 8    (length _lengthY)) 4
    ;; float64[] _lengthZ
    (* 8    (length _lengthZ)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _objectCounts
       (write-long _objectCounts s)
     ;; float64[] _centerX
     (write-long (length _centerX) s)
     (dotimes (i (length _centerX))
       (sys::poke (elt _centerX i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _centerY
     (write-long (length _centerY) s)
     (dotimes (i (length _centerY))
       (sys::poke (elt _centerY i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _centerZ
     (write-long (length _centerZ) s)
     (dotimes (i (length _centerZ))
       (sys::poke (elt _centerZ i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _lengthX
     (write-long (length _lengthX) s)
     (dotimes (i (length _lengthX))
       (sys::poke (elt _lengthX i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _lengthY
     (write-long (length _lengthY) s)
     (dotimes (i (length _lengthY))
       (sys::poke (elt _lengthY i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _lengthZ
     (write-long (length _lengthZ) s)
     (dotimes (i (length _lengthZ))
       (sys::poke (elt _lengthZ i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _objectCounts
     (setq _objectCounts (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64[] _centerX
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _centerX (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _centerX i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _centerY
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _centerY (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _centerY i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _centerZ
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _centerZ (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _centerZ i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _lengthX
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _lengthX (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _lengthX i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _lengthY
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _lengthY (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _lengthY i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _lengthZ
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _lengthZ (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _lengthZ i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(setf (get waypoint_maker::ObjectInfo :md5sum-) "5e6aef47c27b53cd5c80f176681e421e")
(setf (get waypoint_maker::ObjectInfo :datatype-) "waypoint_maker/ObjectInfo")
(setf (get waypoint_maker::ObjectInfo :definition-)
      "int32 objectCounts
float64[] centerX
float64[] centerY
float64[] centerZ
float64[] lengthX
float64[] lengthY
float64[] lengthZ

")



(provide :waypoint_maker/ObjectInfo "5e6aef47c27b53cd5c80f176681e421e")


