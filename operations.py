import pandas as pd 
import getpass
import GUI

import tkinter as tk
from tkinter import messagebox

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
        InputID = GUI.add_employee_frame.entry_value2.get()
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

    EmployeeData["Name"] = GUI.add_employee_frame.entry_value1.get()
    Add_ID()
    EmployeeData["Depertamnet"] = GUI.add_employee_frame.entry_value2.get()

    EmployeeData["Salary"] = GUI.add_employee_frame.entry_value3.get()

    EmployeeData["Password"] = GUI.add_employee_frame.entry_value4.get()

    EmployeeData["DOA"] = GUI.add_employee_frame.entry_value5.get()

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
    Remove_ID_Flag = False
    ID_ToDelete = GUI.remove_employee_frame.RemoveEntery.get()
    if not ID_ToDelete :
            # Show error message if blank
            messagebox.showerror("Error", "Name field cannot be empty!")
    else:
            # Process the data if not blank
            messagebox.showinfo("Success", f"Employee '{ID_ToDelete}' added successfully!")
            
    print(ID_ToDelete)
    print(type(ID_ToDelete))
    for i in range(len(EmployeeList)):
        if int(EmployeeList[i]['ID']) == int(ID_ToDelete):
            del EmployeeList[i]
            messagebox.showinfo("Success", f"Employee ID'{ID_ToDelete}' Removed successfully!")
            Remove_ID_Flag = True
            break
    if Remove_ID_Flag == False:
         messagebox.showinfo("Failed", f"Employee ID'{ID_ToDelete}' is not found on system!")

    
    # printing result
    print ("List after deletion of dictionary : " +  str(EmployeeList))
    df = pd.DataFrame(EmployeeList)

    # Print DataFrame as table
    # Print DataFrame as table with left alignment 
    pd.set_option('display.colheader_justify', 'left')
    print(df.to_string(index=False))

DataManagmentCounter = 0 # counter to check if ID Is entered 3 times wrong break from loop 

def Modify_Data():
        global DataManagmentCounter
        ModifyIndex = 0
        Target_ID = int(GUI.modify_employee_frame.Modify_ID.get())
        ID_Found_GDB = False
        Auth_Succed_GDB = False
        if not Target_ID:
                # Show error message if blank
                messagebox.showerror("Error", "Name field cannot be empty!")
        
        for i, dictionary in enumerate(EmployeeList):
                
                if int(dictionary["ID"]) == Target_ID:  # cast as typr of dictionary["ID"] is str 
                  ModifyIndex  = i
                  ID_Found_GDB = True

        if(ID_Found_GDB == False):
            messagebox.showerror("Failure", f"Employee ID'{Target_ID}' Not Found!")

        else:
            Old_PasswordCheck= int(GUI.modify_employee_frame.Modify_Password.get())

            if (int(EmployeeList[ModifyIndex]["Password"]) == Old_PasswordCheck) and (ID_Found_GDB == True):
                GUI.show_frame(GUI.modify_employeePage_frame)
                Auth_Succed_GDB = True
            else:
                DataManagmentCounter +=1
                messagebox.showinfo("Failed", f"Wrong Password")
                if DataManagmentCounter == 3:
                    print("I Entered")
                    GUI.show_frame(GUI.data_managamentframe)
                    DataManagmentCounter =0
                messagebox.showinfo("Failed", f"Wrong Password")

                        
        if(Auth_Succed_GDB == True):
            Modified_Name= GUI.modify_employeePage_frame.Modify_Name.get()
            New_Password= GUI.modify_employeePage_frame.Modify_Password.get()
            Modified_Salary = GUI.modify_employeePage_frame.Modify_Salary.get()
            Modified_Dep = GUI.modify_employeePage_frame.Modify_DEP.get()
            Modified_DOA = GUI.modify_employeePage_frame.Modify_DOA.get()

            if  Modified_Name:
                EmployeeList[ModifyIndex]["Name"] = Modified_Name

            if  New_Password:
                EmployeeList[ModifyIndex]["Password"] = New_Password           
                
            if  Modified_Dep:
                EmployeeList[ModifyIndex]["Depertament"] = Modified_Dep

            if Modified_Salary:
                EmployeeList[ModifyIndex]["Salary"] = Modified_Salary

            if Modified_DOA:
                EmployeeList[ModifyIndex]["DOA"] = Modified_DOA
                
            #Convert list of dictionaries to DataFrame
            df = pd.DataFrame(EmployeeList)

            # Print DataFrame as table
            # Print DataFrame as table with left alignment 
            pd.set_option('display.colheader_justify', 'left')
            print(df.to_string(index=False))


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

    return EmployeeList[Targeted_Index[0]]

def Employee_ShowBonus():
     print("Bonus:",(float(EmployeeList[Targeted_Index[0]]["Salary"]) * 0.1))
     Bonus = (float(EmployeeList[Targeted_Index[0]]["Salary"]) * 0.1)
     return Bonus

def Employee_ShowDiscount():
     print("Discount:",(int(EmployeeList[Targeted_Index[0]]["Salary"]) * 0.05))
     return ((EmployeeList[Targeted_Index[0]]["Salary"]) * 0.05)
def Employee_ShowDOA():
     print("Days of Absence: ",EmployeeList[Targeted_Index[0]]["DOA"])
     return EmployeeList[Targeted_Index[0]]["DOA"]


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



