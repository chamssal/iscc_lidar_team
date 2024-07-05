
(cl:in-package :asdf)

(defsystem "lidar_object_detector-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Boundingbox" :depends-on ("_package_Boundingbox"))
    (:file "_package_Boundingbox" :depends-on ("_package"))
    (:file "Delivery" :depends-on ("_package_Delivery"))
    (:file "_package_Delivery" :depends-on ("_package"))
    (:file "DriveValues" :depends-on ("_package_DriveValues"))
    (:file "_package_DriveValues" :depends-on ("_package"))
    (:file "DynamicVelocity" :depends-on ("_package_DynamicVelocity"))
    (:file "_package_DynamicVelocity" :depends-on ("_package"))
    (:file "TrafficCone" :depends-on ("_package_TrafficCone"))
    (:file "_package_TrafficCone" :depends-on ("_package"))
    (:file "Waypoint" :depends-on ("_package_Waypoint"))
    (:file "_package_Waypoint" :depends-on ("_package"))
  ))