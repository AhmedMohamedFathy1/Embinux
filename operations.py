import pandas as pd 
import getpass


##################### Constants ########################
### Data Mangament Constants ###
DATA_MANAGAMNET_IDLE_MENU       = 0
DATA_MANAGAMNET_ADD_EMPLOYEE    = 1
DATA_MANAGAMNET_REMOVE_EMPLOYEE = 2
DATA_MANAGAMNET_MODIFY_DATA     = 3
DATA_MANAGAMNET_EXIT            = 4

### Data Mangament ModifyConstants ###
DATA_MANAGAMNET_MODIFY_IDLE      = 0
DATA_MANAGAMNET_MODIFY_NAME      = 1
DATA_MANAGAMNET_MODIFY_DEP       = 2
DATA_MANAGAMNET_MODIFY_SALARY    = 3
DATA_MANAGAMNET_MODIFY_PASSWORD  = 4
DATA_MANAGAMNET_MODIFY_DOA       = 5
DATA_MANAGAMNET_MODIFY_EXIT      = 6

### Sign In Constants ###
SIGNIN_IDLE_MENU       = 0
SIGNIN_DISPLAY_DATA    = 1
SIGNIN_SHOW_BONUS      = 2
SIGNIN_SHOW_DISCOUNT   = 3
SIGNIN_SHOW_DOA        = 4
SIGNIN_EXIT            = 5
######################################


Data_Mangament_Chocie = 0
Data_Mangament_Flag = 0

SignIn_Emplyoee_Chocie = 0
SignIn_Emplyoee_Flag = 0

Targeted_Index = [0]

EmployeeList = []
# Create an empty dictionary with initial keys
initial_keys = {"Name","ID","Depertamnet","Salary","Password","DOA"}
EmployeeData = {key: None for key in initial_keys}

EmployeeList = [
    {"Name": 'Ahmed', "ID": '123', "Depertamnet": 'ENG', "Salary": '2314', "Password": '321', "DOA": '1'},
    {"Name": 'Fathy', "ID": '321', "Depertamnet": 'BUS', "Salary": '3462', "Password": '255', "DOA": '12'}
]

def Add_ID():
    ID_Flag = True
    while ID_Flag:
        ID_Flag = False
        ID_Found = False
        print("Please Enter ID")
        InputID = int(input())
        for dictionary in EmployeeList:
            if int(dictionary["ID"]) == InputID:  # cast as typr of dictionary["ID"] is str 
                print("Please Ener another ID, as ID Chosen already exist")
                ID_Flag = True
                ID_Found = True
                break

        if ID_Found == False:  
            ID_Flag = False
            EmployeeData["ID"] = InputID
    


def AddEmployee():
    global EmployeeList
    global initial_keys
    global EmployeeData

# Initialize dictionary with these keys, setting all values to None

    print("Please Enter Name")
    EmployeeData["Name"] = input()

    Add_ID()

    print("Please Enter Depertamnet")
    EmployeeData["Depertamnet"] = input()

    print("Please Enter salary")
    EmployeeData["Salary"] = input()

    print("Please Enter Password")
    EmployeeData["Password"] = int(getpass.getpass("Please Enter your Password Agian"))

    print("Please Enter Days of Absence")    
    EmployeeData["DOA"] = input()

    EmployeeList.append(EmployeeData)
    EmployeeData = {key: None for key in initial_keys}

    print(EmployeeList , "\n")
    #Convert list of dictionaries to DataFrame
    df = pd.DataFrame(EmployeeList)

    # Print DataFrame as table
    # Print DataFrame as table with left alignment 
    pd.set_option('display.colheader_justify', 'left')
    print(df.to_string(index=False))



def RemoveEmployee():
    global EmployeeList
    global EmployeeData

    print("Please Enter ID you want to delete")
    ID_ToDelete = int(input())

    for i in range(len(EmployeeList)):
        if int(EmployeeList[i]['ID']) == ID_ToDelete:
            del EmployeeList[i]
            print("Deleted Succuesfully")
            break
    
    # printing result
    print ("List after deletion of dictionary : " +  str(EmployeeList))
    df = pd.DataFrame(EmployeeList)

    # Print DataFrame as table
    # Print DataFrame as table with left alignment 
    pd.set_option('display.colheader_justify', 'left')
    print(df.to_string(index=False))


def Modify_Data():
    Data_Mangament_Modfy_Flag = True
    ModifyIndex = 0
    Data_Mangament_Modify = 0
    DataManagmentCounter = 0 # counter to check if ID Is entered 3 times wrong break from loop 
    while(Data_Mangament_Modfy_Flag):
        if (Data_Mangament_Modify == DATA_MANAGAMNET_MODIFY_IDLE):
            print("Please Enter Your ID " )
            try:
              Target_ID = int(input())
            except:
               Target_ID = int(input("Please Enter Valid ID\n"))

            for i, dictionary in enumerate(EmployeeList):
                  if int(dictionary["ID"]) == Target_ID:  # cast as typr of dictionary["ID"] is str 
                   print(f"Found ID {ModifyIndex} at index: {i}")
                   ModifyIndex  = i
                   print("Enter Which data you want to modify")
                   print("1- Name \n2- Depertament\n3- Salary\n4- Password\n5- Days of Absence\n6- Exit")    
                   Data_Mangament_Modify = int(input())
                   break
            else:
              print(f"ID ",Target_ID , " not found in EmployeeList")
              Data_Mangament_Modify = DATA_MANAGAMNET_MODIFY_IDLE 
              DataManagmentCounter +=1
              if DataManagmentCounter == 3:
                DataManagmentCounter =0
                break
            
        elif (Data_Mangament_Modify == DATA_MANAGAMNET_MODIFY_NAME):
            print("Enter New Name")
            Modified_Name = input()
            EmployeeList[ModifyIndex]["Name"] = Modified_Name
            print(EmployeeList[ModifyIndex])   
            Data_Mangament_Modify = DATA_MANAGAMNET_MODIFY_IDLE 
            
        elif(Data_Mangament_Modify == DATA_MANAGAMNET_MODIFY_DEP):
            print("Enter New Depertament")
            Modified_Dep = input()
            EmployeeList[ModifyIndex]["Depertament"] = Modified_Dep
            print(EmployeeList[ModifyIndex])   
            Data_Mangament_Modify = DATA_MANAGAMNET_MODIFY_IDLE 
        
        elif(Data_Mangament_Modify == DATA_MANAGAMNET_MODIFY_SALARY):
            print("Enter New Salary")
            Modified_Salary= input()
            EmployeeList[ModifyIndex]["Salary"] = Modified_Salary
            print(EmployeeList[ModifyIndex])    
            Data_Mangament_Modify = DATA_MANAGAMNET_MODIFY_IDLE 
        
        elif(Data_Mangament_Modify == DATA_MANAGAMNET_MODIFY_PASSWORD):
            Old_PasswordCheck= int(getpass.getpass("Enter old password"))
            if int(EmployeeList[ModifyIndex]["Password"]) == Old_PasswordCheck:
               New_Password= int(getpass.getpass("Enter New password"))
               EmployeeList[ModifyIndex]["Password"] = New_Password
               print(EmployeeList[ModifyIndex])   
            else:
                print("Wrong password")

            Data_Mangament_Modify = DATA_MANAGAMNET_MODIFY_IDLE 
        
        elif(Data_Mangament_Modify == DATA_MANAGAMNET_MODIFY_DOA):
            print("Enter New Days of Abesence")
            Modified_DOA= input()
            EmployeeList[ModifyIndex]["DOA"] = Modified_DOA
            print(EmployeeList[ModifyIndex])    
            Data_Mangament_Modify = DATA_MANAGAMNET_MODIFY_IDLE 
        
        elif(Data_Mangament_Modify == DATA_MANAGAMNET_MODIFY_EXIT):
            Data_Mangament_Modfy_Flag = False             

        else: 
            Data_Mangament_Modify = DATA_MANAGAMNET_MODIFY_IDLE
            print("Wrong Choice Please Enter Agian") 



def DataManagment_Handler():
    global Data_Mangament_Chocie 
    global Data_Mangament_Flag
    while(Data_Mangament_Flag):
        if (Data_Mangament_Chocie == DATA_MANAGAMNET_IDLE_MENU):
            print("Please Enter Choice")
            print("1- Add Employee \n2- Remove Employee \n3- Modify Data\n4- Exit")    
            try:
                Data_Mangament_Chocie = int(input())
            except:
                Data_Mangament_Chocie = DATA_MANAGAMNET_IDLE_MENU
                print("Wrong Choice Please Enter Agian") 

        elif(Data_Mangament_Chocie == DATA_MANAGAMNET_ADD_EMPLOYEE):
            AddEmployee()
            Data_Mangament_Chocie = DATA_MANAGAMNET_IDLE_MENU 
            
        elif(Data_Mangament_Chocie == DATA_MANAGAMNET_REMOVE_EMPLOYEE):
            RemoveEmployee() 
            Data_Mangament_Chocie = DATA_MANAGAMNET_IDLE_MENU 
        
        elif(Data_Mangament_Chocie == DATA_MANAGAMNET_MODIFY_DATA):
            Modify_Data()
            Data_Mangament_Flag = False 

        elif(Data_Mangament_Chocie == DATA_MANAGAMNET_EXIT):
            Data_Mangament_Flag = False             

        else: 
            Data_Mangament_Chocie = DATA_MANAGAMNET_IDLE_MENU
            print("Wrong Choice Please Enter Agian") 


def Employee_DataDisplay():
    print("Employee Data:")
    print("Targeted_Index" ,Targeted_Index[0])
    print(EmployeeList[Targeted_Index[0]])   

def Employee_ShowBonus():
     print("Bonus:",(int(EmployeeList[Targeted_Index[0]]["Salary"]) * 0.1))

def Employee_ShowDiscount():
     print("Discount:",(int(EmployeeList[Targeted_Index[0]]["Salary"]) * 0.05))

def Employee_ShowDOA():
     print("Days of Absence: ",EmployeeList[Targeted_Index[0]]["DOA"])



def Employee_SignIn_Handler():
    global SignIn_Emplyoee_Chocie 
    global SignIn_Emplyoee_Flag
    
    while(SignIn_Emplyoee_Flag):
        if (SignIn_Emplyoee_Chocie == SIGNIN_IDLE_MENU):
            print("Please Enter Choice")
            print("1- Display Employee Data \n2- Show Bonus \n3- Show Discount\n4- Show Days of Absence\n5- Exit")    
            try:
                SignIn_Emplyoee_Chocie = int(input())
            except:
                SignIn_Emplyoee_Chocie = SIGNIN_IDLE_MENU
                print("Wrong Choice Please Enter Agian") 

        elif(SignIn_Emplyoee_Chocie == SIGNIN_DISPLAY_DATA):
            Employee_DataDisplay()
            SignIn_Emplyoee_Chocie = SIGNIN_IDLE_MENU 

        elif(SignIn_Emplyoee_Chocie == SIGNIN_SHOW_BONUS):
            Employee_ShowBonus() 
            SignIn_Emplyoee_Chocie = SIGNIN_IDLE_MENU 

        elif(SignIn_Emplyoee_Chocie == SIGNIN_SHOW_DISCOUNT):
            Employee_ShowDiscount() 
            SignIn_Emplyoee_Chocie = SIGNIN_IDLE_MENU 

        elif(SignIn_Emplyoee_Chocie == SIGNIN_SHOW_DOA):
            Employee_ShowDOA() 
            SignIn_Emplyoee_Chocie = SIGNIN_IDLE_MENU 

        elif(SignIn_Emplyoee_Chocie == SIGNIN_EXIT):
            SignIn_Emplyoee_Flag = False  

        else: 
            SignIn_Emplyoee_Chocie = SIGNIN_IDLE_MENU
            print("Wrong Choice Please Enter Agian") 



