 #include <AFMotor.h>
 #include <Servo.h>
 #include <HCSR04.h>

 AF_DCMotor motor1(1);
 AF_DCMotor motor2(2);
 AF_DCMotor motor3(3);
 AF_DCMotor motor4(4);

 Servo F_servo;
 Servo B_servo;

 UltraSonicDistanceSensor F_sensor(51, 50);
 UltraSonicDistanceSensor B_sensor(52, 53);

 #define mid   90
 #define right 0
 #define left  180

 #define front 1
 #define back  0

 #define Yes 1
 #define No 0

bool reverse_flag = 0;
   
void setup() {
  
  F_servo.attach(10); 
  B_servo.attach(9);
  
  delay(3000);
 
}

   
void loop() {

   
  run_Car(200);
   //forward(100); 
    
    
}

 //This function runs the autonomous arduino car in different directions. 
  void run_Car(int speed){

       if(reverse_flag){
          run_ReverseCar(speed);
       }

      //Keep looking if there's an obstruction infront of the car. Then stop and start looking in other directions
       while(check_way(mid, front) == No){
            forward(speed);
       }
          Brake();
       
       if(check_way(right, front) == No){
           turnRight(speed);
           delay(700); 
           return;
       }else if(check_way(left, front) == No){
           turnLeft(speed);
           delay(700);
           return;
       }else{

           reverse_flag == 1;
           run_ReverseCar(speed);
       }
                     
  }

  void run_ReverseCar(int speed){

       while(check_way(mid, back) == No){
          backward(speed);    
       }
          Brake();

       if(check_way(left, back) == No){
           turnReverseRight(speed);
           delay(700); 
           return;
       }else if(check_way(right, front) == No){
           turnReverseLeft(speed);
           delay(700);
           return;
       }else{
           Brake();
           reverse_flag = 0;
           return;
       }
       
  }

  
//This function looks for obstacles in different directions.
  int check_way(int angle, int direction){

    double distance;
    
    if(direction == front){
      
      F_servo.write(angle);
      delay(200);
      distance = F_sensor.measureDistanceCm();
    }
    else if(direction == back){

      B_servo.write(angle);
      delay(200);
      distance = B_sensor.measureDistanceCm();
    }


    if(distance <=30){
        return Yes;      
    }else{
      return No;
    }
    
  }


//This function is to move forward.
  void forward(int speed){

    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
    motor3.setSpeed(speed);
    motor4.setSpeed(speed); 
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
 }


//This func is to move backwards.
  void backward(int speed){

    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
    motor3.setSpeed(speed);
    motor4.setSpeed(speed); 
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
 }


//This function is to turn right
  void turnRight(int speed){
    
    motor1.setSpeed(0);
    motor2.setSpeed(speed);
    motor3.setSpeed(speed);
    motor4.setSpeed(0);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD); 
  }


//This func is to turn left.  
  void turnLeft(int speed){

    motor1.setSpeed(speed);
    motor2.setSpeed(0);
    motor3.setSpeed(0);
    motor4.setSpeed(speed);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
  }

 //This function is turn right in reverse mode.
  void turnReverseRight(int speed){
    motor1.setSpeed(speed);
    motor2.setSpeed(0);
    motor3.setSpeed(0);
    motor4.setSpeed(speed);
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
  }

 //This function is turn left in reverse mode.
  void turnReverseLeft(int speed){
    motor1.setSpeed(0);
    motor2.setSpeed(speed);
    motor3.setSpeed(speed);
    motor4.setSpeed(0);
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
  }

  
//This fucntion is to apply brake.
  void Brake(){

    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
  }

  
