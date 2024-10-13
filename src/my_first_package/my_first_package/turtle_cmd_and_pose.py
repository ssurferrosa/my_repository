import rclpy as rp
from rclpy.node import Node

#Pose Topic이 사용하는 Pose타입 메세지
#float32 x, float32 y,  float32 theta,  float32 linear_velocity,  float32 angular_velocity
from turtlesim.msg import Pose
#cmd_vel이란 topic이 사용하는 Twist의 타입 메세지 linear.xyz 3개, angular.x,y,z 3개
from geometry_msgs.msg import Twist
# 내가만든 메세지 float32 cmd_vel_linear,  float32 cmd_vel_angular,      float32 pose_x
#               float32 pose_y,         float32 linear_vel,           float32 angular_vel
from my_first_package_msg.msg import CmdAndPoseVel

class CmdAndPose(Node):

    def __init__(self):
        super().__init__('yoon_turtle_cmd_pose')
        self.sub_pose = self.create_subscription(Pose,
                                                 '/turtle1/pose',
                                                 self.callback_pose,
                                                 10)
        self.pub_vel = self.create_subscription(Twist,
                                             '/turtle1/cmd_vel',
                                             self.callback_cmd,
                                             10)
        
        # !!!!ros2 topic echo /cmd_and_pose_Result_yoons 2번째 인자로 인해서 이렇게 확인가능하다
        self.publisher = self.create_publisher(CmdAndPoseVel,
                                            '/cmd_and_pose_Result_yoons',
                                            10)
        self.time_period = 1.0
        self.timer = self.create_timer(self.time_period,self.timer_callback)

        self.cmd_pose = CmdAndPoseVel()
        
        #여기서 받는 msg는 pose Topic을 'yoon_turtle_cmd_pose노드가 받았으니 pose토픽 메세지가온다
        #ros에서는 이걸 뭉뚱그려서 msg라고 하는것같다 pose에서 구독해서받은 메세지를 내가 정의한매세지로 받자
    def callback_pose(self, msg):
        self.cmd_pose.pose_x = msg.x
        self.cmd_pose.pose_y = msg.y
        self.cmd_pose.linear_vel = msg.linear_velocity
        self.cmd_pose.angular_vel - msg.angular_velocity
        

    def callback_cmd(self, msg):
        self.cmd_pose.cmd_vel_angular = msg.linear.x
        self.cmd_pose.cmd_vel_angular = msg.angular.y
        print(self.cmd_pose)
    
    ''' !!!!오류 예시 애는 퍼블리셔관련이라 일단은 msg를 인수로 할수없다고 알아두자,그리고 퍼블리셔는 print하는거아니다
        그냥 퍼블리쉬만하자
    def timer__callback(self, msg):
        print(self.cmd_pose)
    '''
    def timer_callback(self):
        self.publisher.publish(self.cmd_pose)

def main(args=None):
    rp.init(args=args)

    turtle_cmd_pose_node = CmdAndPose()
    rp.spin(turtle_cmd_pose_node)

    turtle_cmd_pose_node.destroy_node()
    rp.shutdown()



if __name__ == '__main__' :
    main()