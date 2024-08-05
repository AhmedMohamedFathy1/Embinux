#!/usr/bin/python3
import tkinter as tk
from operations import AddEmployee,RemoveEmployee,Modify_Data,Employee_DataDisplay,Employee_ShowDiscount,Employee_ShowBonus,Employee_ShowDOA
from tkinter import font

from authentication import Authentication_Check

# Function to update dictionary with data from entry fields
""" def update_dictionary():
    # Collect data from entry fields'
    op.EmployeeData["Name"] = add_employee_frame.entry_value1.get()
    op.EmployeeData["ID"] =  add_employee_frame.entry_value2.get()
    op.EmployeeData["Depertamnet"] = add_employee_frame.entry_value3.get()
    op.EmployeeData["Salary"] = add_employee_frame.entry_value4.get()
    op.EmployeeData["Password"] = add_employee_frame.entry_value5.get()
    op.EmployeeData["DOA"] = add_employee_frame.entry_value6.get()

    op.AddEmployee()
    add_emp_t.Clear_Txt() """

# Initial dictionary
data_dict = {}
Authentication_Flag = [-1]  # used to store auth falg in auth module 
# Setting up the GUI
root = tk.Tk()
root.title("Data Entry")
# Set geometry(width height)
root.geometry('450x500')

initial_font = ('Arial', 16)
tk.Label(root, text="Embinux!", font=initial_font).grid(row=0, column=0, padx=0, pady=0, sticky="nsew")

# Create a container for all frames
container = tk.Frame(root)
container.grid(row=0, column=0, sticky="nsew")

# Set column and row weight for the container to expand properly
container.grid_rowconfigure(0, weight=1)
container.grid_columnconfigure(0, weight=1)

# Dictionary to hold the frames
frames = {}

# Frame classes
class MainMenuFrame(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        # Create a font with underline
        underlined_font = font.Font(family="Arial", size=20, underline=True)
        
        # Create a Label with the underlined font
        tk.Label(self, text="Employee Management System", font=underlined_font).grid(row=0, column=1, columnspan=3, pady=15)
       # tk.Label(self, text="Employee Management System", font=('Arial', 20)).grid(row=0, column=1, columnspan=3, pady=15,underline=True)

        tk.Button(self, text="Sign In", command=lambda: show_frame(SignIn_auth)).grid(row=1, column=1, padx = 10 ,pady=10, sticky="ew")
        tk.Button(self, text="Data Managamnet", command=lambda: show_frame(data_managamentframe)).grid(row=2, column=1,padx = 10, pady=10, sticky="ew")


# Frame classes
class DataMangamentFrame(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        tk.Label(self, text="Employee Management System", font=('Arial', 20)).grid(row=0, column=0, columnspan=2, pady=20)

        tk.Button(self, text="Add Employee", command=lambda: show_frame(add_employee_frame)).grid(row=1, column=0, pady=10, sticky="ew")
        tk.Button(self, text="Remove Employee", command=lambda: show_frame(remove_employee_frame)).grid(row=2, column=0, pady=10, sticky="ew")
        tk.Button(self, text="Modify Employee Data", command=lambda: show_frame(modify_employee_frame)).grid(row=3, column=0, pady=10, sticky="ew")
        tk.Button(self, text="Back to Main Menu", command=lambda: show_frame(main_menu_frame)).grid(row=4, column=0, pady=10, sticky="ew")

class AddEmployeeFrame(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        tk.Label(self, text="Add Employee", font=('Arial', 20)).grid(row=0, column=0, columnspan=2, pady=20)

        tk.Label(self, text="Name:").grid(row=1, column=0, sticky="e")
        self.entry_value1 = tk.Entry(self)
        self.entry_value1 .grid(row=1, column=1, pady=5, sticky="ew")

        tk.Label(self, text="ID:").grid(row=2, column=0, sticky="e")
        self.entry_value2 = tk.Entry(self)
        self.entry_value2 .grid(row=2, column=1, pady=5, sticky="ew")
        # Department Data Entry
        tk.Label(self, text="Department:").grid(row=3, column=0, pady=5, sticky="e")
        self.entry_value3 = tk.Entry(self)
        self.entry_value3 .grid(row=3, column=1, pady=5, sticky="ew")
       

        # Salary Data Entry
        tk.Label(self, text="Salary:").grid(row=4, column=0, pady=5, sticky="e")
        self.entry_value4 = tk.Entry(self)
        self.entry_value4 .grid(row=4, column=1, pady=5, sticky="ew")

        # Password Data Entry
        tk.Label(self, text="Password:").grid(row=5, column=0, pady=5, sticky="e")
        self.entry_value5 = tk.Entry(self, show="*")
        self.entry_value5 .grid(row=5, column=1, pady=5, sticky="ew")

        # Days of Absence Data Entry
        tk.Label(self, text="Days of Absence:").grid(row=6, column=0, pady=5, sticky="e")
        self.entry_value6 = tk.Entry(self)
        self.entry_value6 .grid(row=6, column=1, pady=5, sticky="ew")
       

        tk.Button(self, text="Submit", command=AddEmployee).grid(row=7, column=0, columnspan=2, pady=20)
        tk.Button(self, text="Back to Main Menu", command=lambda: show_frame(data_managamentframe)).grid(row=8, column=0, columnspan=2)

    def Clear_Txt(self):
        print("I entered")
        self.entry_value1.delete(0,tk.END)
        self.entry_value2.delete(0,tk.END)
        self.entry_value3.delete(0,tk.END)
        self.entry_value4.delete(0,tk.END)
        self.entry_value5.delete(0,tk.END)
        self.entry_value6.delete(0,tk.END)

class RemoveEmployeeFrame(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        tk.Label(self, text="Remove Employee", font=('Arial', 20)).grid(row=0, column=0, columnspan=2, pady=20)

        tk.Label(self, text="Please Enter ID you want to Remove", font=('Arial', 16)).grid(row=0, column=0, columnspan=2, pady=20)

        tk.Label(self, text="Employee ID:").grid(row=1, column=0, sticky="e")
        self.RemoveEntery = tk.Entry(self)
        self.RemoveEntery.grid(row=1, column=1, pady=5, sticky="ew")

        tk.Button(self, text="Remove", command=RemoveEmployee).grid(row=2, column=0, columnspan=2, pady=20)
        tk.Button(self, text="Back to Main Menu", command=lambda: show_frame(data_managamentframe)).grid(row=3, column=0, columnspan=2)


class ModifyEmployeeFrame(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        tk.Label(self, text="Please Enter ID", font=('Arial', 20)).grid(row=0, column=0, columnspan=2, pady=20)

        tk.Label(self, text="Employee ID:").grid(row=1, column=0, sticky="e")
        self.Modify_ID = tk.Entry(self)
        self.Modify_ID.grid(row=1, column=1, pady=5, sticky="ew")

        tk.Label(self, text="Employee Password:").grid(row=2, column=0, sticky="e")
        self.Modify_Password = tk.Entry(self)
        self.Modify_Password.grid(row=2, column=1, pady=5, sticky="ew")


        tk.Button(self, text="Search",command=Modify_Data).grid(row=3, column=0, columnspan=2, pady=20)
        tk.Button(self, text="Back to Main Menu", command=lambda: show_frame(data_managamentframe)).grid(row=4, column=0, columnspan=2)


class ModifyEmployeePageFrame(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        tk.Label(self, text="Modify Page", font=('Arial', 20)).grid(row=0, column=0, columnspan=2, pady=20)

        tk.Label(self, text="Employee Name:").grid(row=1, column=0, sticky="e")
        self.Modify_Name = tk.Entry(self)
        self.Modify_Name.grid(row=1, column=1, pady=5, sticky="ew")

        tk.Label(self, text="Employee Password:").grid(row=2, column=0, sticky="e")
        self.Modify_Password = tk.Entry(self)
        self.Modify_Password.grid(row=2, column=1, pady=5, sticky="ew")

        tk.Label(self, text="Employee Salary:").grid(row=3, column=0, sticky="e")
        self.Modify_Salary = tk.Entry(self)
        self.Modify_Salary.grid(row=3, column=1, pady=5, sticky="ew")

        tk.Label(self, text="Employee Departament:").grid(row=4, column=0, sticky="e")
        self.Modify_DEP= tk.Entry(self)
        self.Modify_DEP.grid(row=4, column=1, pady=5, sticky="ew")

        tk.Label(self, text="Employee Days of Absence:").grid(row=5, column=0, sticky="e")
        self.Modify_DOA= tk.Entry(self)
        self.Modify_DOA.grid(row=5, column=1, pady=5, sticky="ew")


        tk.Button(self, text="Modify",command=Modify_Data).grid(row=6, column=0, columnspan=2, pady=20)
        tk.Button(self, text="Back to Main Menu", command=lambda: show_frame(main_menu_frame)).grid(row=7, column=0, columnspan=2)


################################ sign in Classes ################################
class SignInPageAuthFrame(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        tk.Label(self, text="Please Enter ID", font=('Arial', 20)).grid(row=0, column=0, columnspan=2, pady=20)

        tk.Label(self, text="Employee ID:").grid(row=1, column=0, sticky="e")
        self.Auth_ID = tk.Entry(self)
        self.Auth_ID.grid(row=1, column=1, pady=5, sticky="ew")

        tk.Label(self, text="Employee Password:").grid(row=2, column=0, sticky="e")
        self.Auth_Password = tk.Entry(self)
        self.Auth_Password.grid(row=2, column=1, pady=5, sticky="ew")


        tk.Button(self, text="sign in",command=Authentication_Check).grid(row=3, column=0, columnspan=2, pady=20)
        tk.Button(self, text="Main Menu", command=lambda: show_frame(main_menu_frame)).grid(row=4, column=0, columnspan=2)

class SignInPageFrame(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        tk.Label(self, text="Sign In", font=('Arial', 20)).grid(row=0, column=0, columnspan=2, pady=20)

        tk.Button(self, text="Display Data", command=self.Display_CombinedFunction).grid(row=1, column=0, pady=10, sticky="ew")
        tk.Button(self, text="Bonus", command=self.Bonus_CombinedFunction).grid(row=2, column=0, pady=10, sticky="ew")
        tk.Button(self, text="Discount", command=self.Discount_CombinedFunction).grid(row=3, column=0, pady=10, sticky="ew")
        tk.Button(self, text="Days of Absence", command=self.DOA_CombinedFunction).grid(row=4, column=0, pady=10, sticky="ew")

        tk.Button(self, text="Back to Main Menu", command=lambda: show_frame(main_menu_frame)).grid(row=5, column=0, pady=10, sticky="ew")

    def Display_CombinedFunction(self):
        Employee_DataDisplay()
        show_frame(SignInDisplay_frame)

    def Bonus_CombinedFunction(self):
        Employee_ShowBonus()
        show_frame(SignInDisplayBonus_frame)

    def Discount_CombinedFunction(self):
        Employee_ShowDiscount()
        show_frame(SignInDisplayDiscount_frame)

    def DOA_CombinedFunction(self):
        Employee_ShowDOA()
        show_frame(SignInDisplayDOA_frame)


        
class SignInPage_DataDisplayFrame(tk.Frame):
    def __init__(self, parent, controller):
        self.DataDisplayList= []

        tk.Frame.__init__(self, parent)
        tk.Label(self, text="Employee Data", font=('Arial', 20)).grid(row=0, column=0, columnspan=2, pady=20)     

        tk.Label(self, text="Employee Name:").grid(row=1, column=0, pady=10,sticky="w")
        self.DisplayName_Label =  tk.Label(self, text="Employee Bonus")
        self.DisplayName_Label.grid(row=1, column=1, padx=10,pady=10,sticky="w")

        tk.Label(self, text="Employee Password:").grid(row=2, column=0,pady=10, sticky="w")
        self.DisplayPassword_Label =  tk.Label(self, text="Employee Password")
        self.DisplayPassword_Label.grid(row=2, column=1, padx=5,pady=10,sticky="w")

        tk.Label(self, text="Employee Salary:").grid(row=3, column=0, pady=10,sticky="w")
        self.DisplaySalary_Label =  tk.Label(self, text="Employee Salary")
        self.DisplaySalary_Label.grid(row=3, column=1, padx=5,pady=10,sticky="w")

        
        tk.Label(self, text="Employee Departament:").grid(row=4, column=0, pady=10,sticky="w")
        self.DisplayDepartament_Label =  tk.Label(self, text="Employee Departament")
        self.DisplayDepartament_Label.grid(row=4, column=1, padx=5,pady=10,sticky="w")
        
        tk.Label(self, text="Employee Days of Absence:").grid(row=5, column=0, pady=10,sticky="w")
        self.DisplayDOA_Label =  tk.Label(self, text="Employee Days of Absence")
        self.DisplayDOA_Label.grid(row=5, column=1, padx=5,pady=10,sticky="w")

        tk.Button(self, text="Back to Main Menu", command=lambda: show_frame(SignIn_frame)).grid(row=6, column=0, pady=10, sticky="ew")

class SignInPage_DataDisplayBonusFrame(tk.Frame):
    def __init__(self, parent, controller):
           tk.Frame.__init__(self, parent)
           tk.Label(self, text="Employee Bonus:", font=('Arial', 15)).grid(row=0, column=0, columnspan=2, pady=20)     
           
           self.BonusLabel =  tk.Label(self, text="EmployeeBonus", font=('Arial', 15))
           self.BonusLabel.grid(row=0, column=2, padx=5,sticky="e")

           tk.Button(self, text="Back to Menu", command=lambda: show_frame(SignIn_frame)).grid(row=7, column=0, columnspan=2)
    
class SignInPage_DataDisplayDsicountFrame(tk.Frame):
    def __init__(self, parent, controller):        
           tk.Frame.__init__(self, parent)
           
           tk.Label(self, text="Employee Discount:",font=('Arial', 15)).grid(row=0, column=0, columnspan=2, pady=20)
           
           self.DiscountLabel =  tk.Label(self, text="EmployeeDiscount",font=('Arial', 15))
           self.DiscountLabel.grid(row=0, column=2, padx=5,sticky="e")
           
           tk.Button(self, text="Back to Menu", command=lambda: show_frame(SignIn_frame)).grid(row=7, column=0, columnspan=2)
    

class SignInPage_DataDisplayDOAFrame(tk.Frame):
    def __init__(self, parent, controller):
           tk.Frame.__init__(self, parent)
           tk.Label(self, text="Employee Days of Absennce:",font=('Arial', 15)).grid(row=0, column=0, columnspan=2, pady=20)

           self.DOALabel =  tk.Label(self, text="EmployeeDOA",font=('Arial', 15))
           self.DOALabel.grid(row=0, column=3, padx=5,sticky="e")
           
           tk.Button(self, text="Back to menu", command=lambda: show_frame(SignIn_frame)).grid(row=1, column=1, padx=10, pady=10, sticky="ew")

# Create frames for different operations
for F in (MainMenuFrame, AddEmployeeFrame, DataMangamentFrame,RemoveEmployeeFrame, ModifyEmployeeFrame,ModifyEmployeePageFrame, SignInPageFrame,SignInPageAuthFrame,SignInPage_DataDisplayFrame,SignInPage_DataDisplayDsicountFrame,SignInPage_DataDisplayBonusFrame,SignInPage_DataDisplayDOAFrame):
    frame = F(container, root)
    frames[F] = frame
    frame.grid(row=0, column=0, sticky="nsew")

# Functions for each operation
def show_frame(frame_class):
    # Hide all frames
    for frame in frames.values():
        frame.grid_forget()
    
    # Show the selected frame
    frame_class.grid(row=0, column=0, sticky="nsew")



# Create instances of frames for different operations
main_menu_frame = MainMenuFrame(container, root)

data_managamentframe = DataMangamentFrame(container, root)
add_employee_frame = AddEmployeeFrame(container, root)
remove_employee_frame = RemoveEmployeeFrame(container, root)
modify_employee_frame = ModifyEmployeeFrame(container, root)
modify_employeePage_frame = ModifyEmployeePageFrame(container, root)

SignIn_auth = SignInPageAuthFrame(container, root)
SignIn_frame = SignInPageFrame(container, root)
SignInDisplay_frame = SignInPage_DataDisplayFrame(container, root)
SignInDisplayBonus_frame = SignInPage_DataDisplayBonusFrame(container, root)
SignInDisplayDiscount_frame = SignInPage_DataDisplayDsicountFrame(container, root)
SignInDisplayDOA_frame = SignInPage_DataDisplayDOAFrame(container, root)



# Add frames to the dictionary
frames[main_menu_frame] = main_menu_frame
frames[data_managamentframe] = data_managamentframe

frames[add_employee_frame] = add_employee_frame
frames[remove_employee_frame] = remove_employee_frame
frames[modify_employee_frame] = modify_employee_frame
frames[modify_employeePage_frame] = modify_employeePage_frame

frames[SignIn_auth] = SignIn_auth
frames[SignIn_frame] = SignIn_frame
frames[SignInDisplay_frame] = SignInDisplay_frame
frames[SignInDisplayBonus_frame] = SignInDisplayBonus_frame
frames[SignInDisplayDiscount_frame] = SignInDisplayDiscount_frame
frames[SignInDisplayDOA_frame] = SignInDisplayDOA_frame

add_emp_t = AddEmployeeFrame(root,None)

# Show the main menu frame at the start
show_frame(main_menu_frame)

""" # Function to show the selected frame
def show_frame(frame):
    # Hide all frames
    frame1.grid_remove()
    frame2.grid_remove()
    
    # Show the selected frame
    frame.grid() """


""" # Create frames for different screens
frame1 = tk.Frame(root)
frame1.grid(row=8, column=0, columnspan=2, padx=10, pady=10)

frame2 = tk.Frame(root)
frame2.grid(row=9, column=0, columnspan=2, padx=10, pady=10)

# Buttons to navigate between frames
button1 = tk.Button(frame1, text="Sign in", command=lambda: show_frame(frame2))
button1.grid(row=0, column=0, padx=10, pady=5, sticky="w")

button2 = tk.Button(frame1, text="Data Management", command=lambda: show_frame(frame1))
button2.grid(row=1, column=0, padx=5, pady=5, sticky="w")

 """

""" # Start with frame1 visible
show_frame(frame1)


################ Frame 3 Add Employee  ######################
# Create entry fields for multiple key-value pairs
# Name Data Entry
tk.Label(frame2, text="Name").grid(row=1, column=0, padx=10, pady=5)
entry_value1 = tk.Entry(frame2)
entry_value1.grid(row=1, column=1, padx=10, pady=5)

# ID Data Entry
tk.Label(frame2, text="ID:").grid(row=2, column=0, padx=10, pady=5)
entry_value2 = tk.Entry(frame2)
entry_value2.grid(row=2, column=1, padx=10, pady=5)

# Department Data Entry
tk.Label(frame2, text="Department:").grid(row=3, column=0, padx=10, pady=5)
entry_value3 = tk.Entry(frame2)
entry_value3.grid(row=3, column=1, padx=10, pady=5)

# Salary Data Entry
tk.Label(frame2, text="Salary:").grid(row=4, column=0, padx=10, pady=5)
entry_value4 = tk.Entry(frame2)
entry_value4.grid(row=4, column=1, padx=10, pady=5)

# Password Data Entry
tk.Label(frame2, text="Password:").grid(row=5, column=0, padx=10, pady=5)
entry_value5 = tk.Entry(frame2, show="*")
entry_value5.grid(row=5, column=1, padx=10, pady=5)

# Days of Absence Data Entry
tk.Label(frame2, text="Days of Absence:").grid(row=6, column=0, padx=10, pady=5)
entry_value6 = tk.Entry(frame2)
entry_value6.grid(row=6, column=1, padx=10, pady=5)

# Button to update the dictionary with data from entry fields
update_button = tk.Button(frame2, text="Update Dictionary", command=update_dictionary)
update_button.grid(row=7, column=0, columnspan=2, pady=10, sticky="nsew")
 """

# Start the GUI event loop
root.mainloop()
