#!/usr/bin/env python3

import rospy
from std_msgs.msg import String

def callback(data):
    rospy.loginfo("Subscriber 1 heard: %s", data.data)

def listener():
    rospy.init_node('subscriber', anonymous=True)
    rospy.Subscriber('topic1', String, callback)
    rospy.spin()

if __name__ == '__main__':
    listener()
