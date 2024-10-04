#!/usr/bin/env python

import rospy
from std_msgs.msg import String

def talker3():
    pub = rospy.Publisher('topic3', String, queue_size=10)
    rospy.init_node('talker3', anonymous=True)
    rate = rospy.Rate(1)  # 1 Hz
    while not rospy.is_shutdown():
        message = "Selamat Sore from talker 3!"
        rospy.loginfo(message)
        pub.publish(message)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker3()
    except rospy.ROSInterruptException:
        pass
