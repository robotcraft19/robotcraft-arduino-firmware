# Amazebot Driver 

Arduino driver for the autonomous maze solver AMAZEBOT developed for the Robotcraft program.

The robot embeds two encoder-motors, three IR sensors, a LiDaR... (

All source files are divided in tabs right now, as opposed to have cpp and headers, as well as classes. This will be later developed in a seperate branch and merge if tests are passed. 

As for now :

* Header : Gathers all the define, global variables, included libraries and everything used throughout the entire driver.

* Amazebot : Defines the loop and setup functions, as well as an update helper which role is to update at a 10 Hz frequency all the sensors/motor/pid values.

* Kinematics : Contains all the speed and pose calculations for the robot and the wheels.

* Motors : Calculate thanks to the encoder the orientation of the motors.

* PID : As seen in Kinematics.ino, a forward kinematic model is used to move the robot. In order to complete the control task for mobile, it is needed
to control the angular velocity of each wheel beside the position control. Actual velocity of the motor shaft have to
equal the desired ones. So, PID controller is chosen to control the angular velocity of both motor because of its simple theory

* Sensors : Convert analog values provided by IR sensors in centimeters and meters.

* ROS : Instanciate the node handle, declare publishers and subscribers as well as topics they're linked to. Allow us to send data through ROS to the Raspberry in predefined topics and receive feedback from it.
