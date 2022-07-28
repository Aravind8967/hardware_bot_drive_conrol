#!/usr/bin/env python3
import rospy
from std_msgs.msg import String, Int16
ultra = 0

def ultra_data(msg):
    global ultra

    ultra = msg.data


def control_loop():
    print(" rospy is activated sir ..! ")
    rospy.init_node("quader_pad")

    motor_forward = rospy.Publisher('/motor_forward', String, queue_size=10)
    motor_backward = rospy.Publisher('/motor_backward', String, queue_size=10)
    motor_left = rospy.Publisher('/motor_left', String, queue_size=10)
    motor_right = rospy.Publisher('/motor_right', String, queue_size=10)
    motor_stop = rospy.Publisher('/motor_stop', String, queue_size=10)
    rate = rospy.Rate(1)

    motor = String()

    print(" Commands ")
    print (" f = Forward , b = Backward , l = Left , r = Right")

    while not rospy.is_shutdown():

        cmd = input("enter your comand : " )

        if cmd == 'f':
            motor.data = 'foward'
            motor_forward.publish(motor)
            print(" Robot going Forward ..! ")
            rate.sleep()

        elif cmd == 'b':
            motor.data = 'backward'
            motor_backward.publish(motor)
            print(" Robot going Backward ..! ")
            rate.sleep()

        elif cmd == 'l':
            motor.data = 'left'
            motor_left.publish(motor)
            print(" Robot roatating left ..! ")
            rate.sleep()

        elif cmd == 'r':
            motor.data = 'right'
            motor_right.publish(motor)
            print(" Robot rotaing right ..! ")
            rate.sleep()

        elif cmd == 's':
            motor.data = 'stop'
            motor_stop.publish(motor)
            print(" Robot stopped ..! ")
            rate.sleep()

        
if __name__ == '__main__':
    try:
        control_loop()
    except rospy.ROSInterruptException:
        pass