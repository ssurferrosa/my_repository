import rclpy as rp
from rclpy.node import Node
#/turtle1/cmd_vel [geometry_msgs/msg/Twist] 사용하기
#publisher 0, subscription 1

from geometry_msgs.msg import Twist

class TurtlesimPublisher(Node):

    def __init__(self):
        super().__init__('yoon_turtlesim_publisher')
        #Defination of publisher
        self.publisher = self.create_publisher(Twist,'turtle1/cmd_vel',10)
        timer_period = 0.5
        self.timer = self.create_timer(timer_period,self.timer_callback)

    def timer_callback(self):
        msg = Twist()
        msg.linear.x= 2.0
        msg.angular.z = 2.0
        #13줄에서 선언한 퍼블리셔를 publish명령으로 발행
        self.publisher.publish(msg)



def main(args=None):
    rp.init(args=args)

    turtlesim_publisher = TurtlesimPublisher()
    rp.spin(turtlesim_publisher)

    turtlesim_publisher.destroy_node()
    rp.shutdown()

if __name__ == '__main__':
    main()


