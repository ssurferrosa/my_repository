import rclpy as rp
from rclpy.node import Node

#int64 num(이건 거북이갯수할때쓸것이다)  --- float64[] x float64[] y float64[] theta
from my_first_package_msg.srv import MultiSpawn

#/turtle1/teleport_absolute [turtlesim/srv/TeleportAbsolute] 
# float32 x float32 y float32 theta --- response없음
from turtlesim.srv import TeleportAbsolute

#/spawn [turtlesim/srv/Spawn] float32 x,float32 y,float32 z,string name(option) --- string name
from turtlesim.srv import Spawn
import time #1초간격으로 해보기..(spawn 시간 걸림)
import numpy as np

class MultiSpawning(Node):
    
    def __init__(self):
        super().__init__('multi_spawn_yoon')
        self.server = self.create_service(MultiSpawn,
                                          'multi_spawn_yoon',
                                          self.callback_service)
        #클라이언트 만들어보자
        self.teleport = self.create_client(TeleportAbsolute,'/turtle1/teleport_absolute')
        
        #클라이언트 만들었고 이렇게 request를 받고(이건 대문자로 가야하는듯 이렇게도 접근할수있고나 알아가자 기술적인처리이다)
        #callback 에서 클라이언트.call_async(self.req_teleport) 해주는 방식으로 가자
        self.req_teleport = TeleportAbsolute.Request()

        #클라이언트 하나더만들고
        self.spawn = self.create_client(Spawn,'/spawn')
        #teleport랑 같은방식으로 처리해보자
        self.req_spawn = Spawn.Request()
        
        #위치(원점이 실제로는 5.54정도니깐)
        self.center_x = 5.54
        self.center_y = 5.54

    def calc_position(self,n,r):
        gap_theta = 2*np.pi / n
        theta = [gap_theta * n for n in range(n)]
        x = [r*np.cos(th) for th in theta]
        y = [r*np.sin(th) for th in theta]

        return x,y,theta
    
    # topic 의 msg같은느낌으로 여기는 request, response사용가능
    def callback_service(self,request,response):
        #일단 원점으로 이동
        self.req_teleport.x = self.center_x
        self.req_teleport.y = self.center_y
        self.teleport.call_async(self.req_teleport)

        #spawn시켜보자
        x, y, theta = self.calc_position(request.num,3)

        for n in range(len(theta)):
            self.req_spawn.x = x[n] + self.center_x
            self.req_spawn.y = y[n] + self.center_y
            self.req_spawn.theta = theta[n]
            self.spawn.call_async(self.req_spawn)
            time.sleep(0.1)

        response.x = x #여기의 response는 당연하게도 server의 response일것이다(이거하려고 배열로만들었다 srv를)
        response.y = y
        response.theta = theta

        return response
        
        #print("request: ",request)
        #response.x = [1.,2.,3.] #response.y = [10.,20.,30.] #response.theta = [100.,200.,300.] #return response




def main(args=None):
    rp.init(args=args)
    multi_spawn = MultiSpawning()
    
    rp.spin(multi_spawn)
    
    rp.shutdown()

if __name__ == '__main__':
    main()