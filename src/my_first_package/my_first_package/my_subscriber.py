import rclpy as rp
from rclpy.node import Node

from turtlesim.msg import Pose

class TurtlesimSubscriber(Node):
    
    #그대로 가져오되 super로 이름만 바꾼다(rclpy의 노드클래스는 초기화시 이름을 요구함)
    def __init__(self):
        super().__init__('yoon_turtlesim_subscriber')
        self.subscription = self.create_subscription(
            Pose,
            '/turtle1/pose',
            self.callback,
            10)
        self.subscription # prevent unused variable warning


    def callback(self,msg):
        print("X: ",msg.x,"Y: ",msg.y)


def main(args=None):
    rp.init(args=args)

    #spin 계속되니깐 사실상 구독할 토픽이 들어오는걸 기다리고 토픽들어오면 callback실행
    turtlesim_subscriber = TurtlesimSubscriber()
    rp.spin(turtlesim_subscriber)                                  

    turtlesim_subscriber.destroy_node() #spin에서 빠져나오면 노드를 중단하고 rclpy도 종료
    rp.shutdown()

if __name__ == '__main__':
    main()