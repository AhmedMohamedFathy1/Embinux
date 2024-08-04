from operations import EmployeeList,Targeted_Index
import getpass

Authentication_Flag = -1
Authentication_Succed = 0 
Authentication_Failed = 1


def Authentication_Check():
    global Authentication_Flag

    Trials = 0
    print("Please Enter Your ID " )
    Target_ID = int(input())

    for i, dictionary in enumerate(EmployeeList):
        if int(dictionary["ID"]) == Target_ID:  # cast as typr of dictionary["ID"] is str 
            print(f"Found ID {Target_ID} at index: {i}")
            Targeted_Index[0]  = i
            break
    else:
        print(f"ID {Target_ID} not found in EmployeeList")


    #print("Please Enter Your Password")
    #Password = int(input())
    # Prompt the user for a password without showing the input on the screen
    Password = int(getpass.getpass("Enter your password: "))

    while (Trials < 2):
        if(Password == int(EmployeeList[Targeted_Index[0]]["Password"])):
            print("Authentication Succed")
            Authentication_Flag = Authentication_Succed 
            break
        else:
            Password = int(getpass.getpass("Please Enter your Password Agian"))
            print(Password)
            Trials+=1
            Authentication_Flag = Authentication_Failed
   
