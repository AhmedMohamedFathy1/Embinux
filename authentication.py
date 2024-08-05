from operations import EmployeeList,Targeted_Index
import getpass
import GUI
from tkinter import messagebox


Authentication_Succed = 0 
Authentication_Failed = 1
Trials = 0


def Authentication_Check():
    global Trials
    Target_ID = int(GUI.SignIn_auth.Auth_ID.get())
    ID_Found = False
    for i, dictionary in enumerate(EmployeeList):
        if int(dictionary["ID"]) == Target_ID:  # cast as typr of dictionary["ID"] is str 
            Targeted_Index[0]  = i
            ID_Found = True
            break
    else:
            messagebox.showinfo("ID", f"Wrong ID")


    #print("Please Enter Your Password")
    #Password = int(input())
    # Prompt the user for a password without showing the input on the screen
    if ID_Found == True:
            Password = int(GUI.SignIn_auth.Auth_Password.get())
            if(Password == int(EmployeeList[Targeted_Index[0]]["Password"])):
                print("Authentication Succed")
                #Authentication_Flag = Authentication_Succed 
                GUI.Authentication_Flag[0] = 0
                GUI.show_frame(GUI.SignIn_frame)

            else:
                messagebox.showinfo("Failed", f"Wrong Password")
                print(Password)
                Trials +=1
                print(Trials)
                if Trials >= 3:
                    GUI.show_frame(GUI.main_menu_frame)
                    GUI.Authentication_Flag[0] = 1     
                    Trials = 0

   
