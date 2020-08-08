import CoDrone

drone = CoDrone.Codrone()
drone.pair(drone.Nearest)

drone.takeoff()
drone.hover(3)

drone.set_yaw(10)
drone.move(3)

drone.set_yaw(-10)
drone.move(3)

drone.set_yaw(0)

#forward
drone.set_pitch(30)
#for 2 sec
drone.move(2)

#default
drone.set_pitch(0)

#to right
drone.set_roll(30)
#for 2 sec
drone.move(2)

#default
drone.set_roll(0)

#backward
drone.set_pitch(-30)
#for 2 sec
drone.move(2)

#default
drone.set_pitch(0)

#to left
drone.set_roll(-30)
#for 2 sec
drone.move(2)

#default
drone.set_roll(0)

drone.land()

drone.close()
