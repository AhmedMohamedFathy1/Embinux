#! usr/bin/python3
import operations 
import authentication as au

# Constants 
IDLE_MENU = 0
SIGN_IN   = 1
DATA_MANGAMENT  = 2


Choice =0

while True:
   if (Choice == IDLE_MENU):
        print("**********************  Employee System  **********************")
        print("1- Sign in")
        print("2- Data Managment \n")    
        try:
          Choice = int(input())
        except:
            Choice = IDLE_MENU
            print("Wrong Choice Please Enter Agian") 
     
   elif(Choice == SIGN_IN):
        print("**********************  Authentaction  **********************")
        au.Authentication_Check()
        print(au.Authentication_Flag)
        if(au.Authentication_Flag == 0):
            print("Authentication Succed")
            operations.SignIn_Emplyoee_Flag = True
            operations.SignIn_Emplyoee_Chocie = IDLE_MENU
            operations.Employee_SignIn_Handler()
            Choice = IDLE_MENU
        else:
            print("Authentication Failed")
        
   elif(Choice == DATA_MANGAMENT):
        print("**********************  Data Managment  **********************")
        operations.Data_Mangament_Chocie = IDLE_MENU
        operations.Data_Mangament_Flag = True
        operations.DataManagment_Handler()
        Choice = IDLE_MENU

   else:
       print("Wrong Choice please enter choice agian\n")
       Choice = IDLE_MENU