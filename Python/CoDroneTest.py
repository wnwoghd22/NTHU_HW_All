import CoDrone

#initiate object 코딩 상 객체 생성
drone = CoDrone.CoDrone()

#pairing
drone.pair(drone.Nearest)

#이륙
drone.takeoff()

#3초간 호버링
drone.hover(3)

#착륙
drone.land()

#연결 해제
drone.close()
