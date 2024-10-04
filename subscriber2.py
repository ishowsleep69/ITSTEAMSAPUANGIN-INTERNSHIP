#!/usr/bin/env python

import rospy
from std_msgs.msg import String

def callback(data):
    rospy.loginfo("Subscriber 2 heard: %s", data.data)

def listener2():
    rospy.init_node('subscriber2', anonymous=True)
    rospy.Subscriber('topic2', String, callback)
    rospy.spin()

if __name__ == '__main__':
    listener2()
