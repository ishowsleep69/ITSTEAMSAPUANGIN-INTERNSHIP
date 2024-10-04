#!/usr/bin/env python

import rospy
from std_msgs.msg import String

def talker2():
    pub = rospy.Publisher('topic2', String, queue_size=10)
    rospy.init_node('talker2', anonymous=True)
    rate = rospy.Rate(1)  # 1 Hz
    while not rospy.is_shutdown():
        message = "Selamat Siang from talker 2!"
        rospy.loginfo(message)
        pub.publish(message)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker2()
    except rospy.ROSInterruptException:
        pass
