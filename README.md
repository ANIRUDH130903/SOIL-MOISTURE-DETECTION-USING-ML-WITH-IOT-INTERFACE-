# SOIL-MOISTURE-DETECTION-USING-ML-WITH-IOT-INTERFACE-
In this project basically, we take the live soil moisture data using soil moisture sensor connected with ESP8266,which will tell about the moisture category, along with this using BLYNK IOT , we can see the data from our phone and desktop. 
First we connect the soil moisture sensor along with the temperature sensor to the the NodeMCU.Then we run the code file of .ino.
The auth token , id to be generated of individual in the BLYNK APP.
Then after running and establish the hotspot connection with Nodemcu, we close this file.
Then we run this abc1 python file.After setting, all the essential enviornmnet, this code will show the classification of mositure level using the linear regression model on the basis of live data , whether it is DRY , MEDIUM OR WET .
THE live data also to be shown in blynk iot app and also we can set command for the motor that to be connected with microcontroller.
